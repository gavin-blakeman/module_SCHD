//**********************************************************************************************************************************
//
// PROJECT:             Engineering Workshop Tracker (engineeringShop)
// FILE:
// SUBSYSTEM:
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2022 Gavin Blakeman.
//                      This file is part of the engineeringShop Project
//
//                      engineeringShop is free software: you can redistribute it and/or modify it under the terms of the GNU
//                      General Public License as published by the Free Software Foundation, either version 2 of the License, or (at
//                      your option) any later version.
//
//                      engineeringShop is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
//                      even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
//                      Public License for more details.
//
//                      You should have received a copy of the GNU General Public License along with engineeringShop.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:
//
// HISTORY:             2022-05-24/GGB - File Created
//
//**********************************************************************************************************************************

#include "include/database/models/modelChartOfAccounts.h"

  // Standard C++ library header files

#include <algorithm>
#include <cmath>
#include <map>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

  // engineeringShop Application header files.

#include "include/core/formatFunctions.h"
#include "include/database/tables/tbl_fi_accounts.h"
#include "include/database/tables/tbl_gl_transactionLines.h"

namespace models
{

  /// @brief      Class Constructor
  /// @param[in]  a: The owning application.
  /// @throws     std::bad_alloc
  /// @version    2022-05-24/GGB - Function created.

  CModelChartOfAccounts::CModelChartOfAccounts(CApplication &a) : CModelCustom(a)
  {

  }

  std::any CModelChartOfAccounts::headerData(int section,
                                             Wt::Orientation,
                                             Wt::ItemDataRole role) const
  {
    std::any returnValue;

    if (role == Wt::ItemDataRole::Display)
    {
      switch (section)
      {
        case 0:
        {
          returnValue = "Account";
          break;
        };
        case 1:
        {
          returnValue = "Dr";
          break;
        }
        case 2:
        {
          returnValue = "Cr";
          break;
        }
      }
    }

    return returnValue;
  }

  /// @brief      Takes the information from the hierarchy and adds it into the model.
  /// @throws
  /// @version    2022-05-24/GGB - Function created.

  void CModelChartOfAccounts::populateModel()
  {
      /* A map is used rather than a vector, as a vector needs the [] operator to refer to already constructed objects.
       * the map [] creates an object as required. */

    using level_t = SCL::sortedHierarchy<index_t, sindex_t, std::string>::iterator::size_type;
    using row_t = std::vector<std::unique_ptr<Wt::WStandardItem>>;
    using value_t = std::pair<decimal_t, decimal_t>;

    SCL::sortedHierarchy<index_t, sindex_t, std::string> chartOfAccounts(0);
    std::map<SCL::sortedHierarchy<index_t, sindex_t, std::string>::size_type, Wt::WStandardItem *> levelPointers;
    level_t level;
    row_t row;
    database::tbl_gl_transactionLines::balances_t accountBalances;
    std::map<index_t, value_t> accountValues;

    database::tbl_fi_accounts::buildHierarchyName(application(), chartOfAccounts);
    database::tbl_gl_transactionLines::accountBalances(session(), accountBalances);
    clear();    // Clear the data from the WStandardItemModel

      // Run through the hierarchy and assign values and roll up the values.

    using balanceValues_t = std::tuple<level_t, index_t, decimal_t, decimal_t>;
    std::stack<balanceValues_t> balanceStack;

    //DEBUGMESSAGE("Starting ChartOfAccounts rollup");

    for(auto iterator = chartOfAccounts.begin(); iterator != chartOfAccounts.end(); ++iterator)
    {
      decimal_t dr = 0;
      decimal_t cr = 0;

      level = std::get<0>(*iterator);

      auto i = accountBalances.find(std::get<1>(*iterator));
      if (i != accountBalances.end())
      {
        dr = std::max(decimal_t{0.0}, i->second);
        cr = abs(std::min(decimal_t{0.0}, i->second));
      }

      accountValues[std::get<1>(*iterator)] = std::make_pair(dr, cr);

      if (level == 0)
      {
        balanceStack.push({level, std::get<1>(*iterator), dr, cr});
        //DEBUGMESSAGE(boost::format("Push: %i, %i, %.2f, %.2f") % level % std::get<1>(*iterator) % dr % cr);
      }
      else if (level > std::get<0>(balanceStack.top()))
      {
        balanceStack.push({level, std::get<1>(*iterator), dr, cr});
        //DEBUGMESSAGE(boost::format("Push: %i, %i, %.2f, %.2f") % level % std::get<1>(*iterator) % dr % cr);
      }
      else if (level == std::get<0>(balanceStack.top()))
      {
        balanceStack.push({level, std::get<1>(*iterator), dr, cr});
        //DEBUGMESSAGE(boost::format("Push: %i, %i, %.2f, %.2f") % level % std::get<1>(*iterator) % dr % cr);
      }
      else
      {
        level_t rollupLevel = std::get<0>(balanceStack.top());

        while (level < rollupLevel)
        {
          decimal_t drRollup = 0;
          decimal_t crRollup = 0;

          while (std::get<0>(balanceStack.top()) == rollupLevel)
          {
            drRollup += std::get<2>(balanceStack.top());
            crRollup += std::get<3>(balanceStack.top());
            balanceStack.pop();
          }
          std::get<2>(balanceStack.top()) += drRollup;
          std::get<3>(balanceStack.top()) += crRollup;
          accountValues[std::get<1>(balanceStack.top())].first = std::get<2>(balanceStack.top());
          accountValues[std::get<1>(balanceStack.top())].second = std::get<3>(balanceStack.top());
          //DEBUGMESSAGE(boost::format("Rollup: %i, %i, %.2f %.2f") % std::get<0>(balanceStack.top()) % std::get<1>(balanceStack.top()) % drRollup % crRollup);

          rollupLevel--;
        };

        balanceStack.push({level, std::get<1>(*iterator), dr, cr});
        //DEBUGMESSAGE(boost::format("Push: %i, %i, %.2f, %.2f") % level % std::get<1>(*iterator) % dr % cr);
      };
    }

      // Rollup any remaining items on the balance stack.

    while (!balanceStack.empty())
    {
      level = std::get<0>(balanceStack.top());

      decimal_t drRollup = 0;
      decimal_t crRollup = 0;
      balanceStack.pop();

      if (!balanceStack.empty())
      {
        while (std::get<0>(balanceStack.top()) == level)
        {
          drRollup += std::get<2>(balanceStack.top());
          crRollup += std::get<3>(balanceStack.top());
          balanceStack.pop();
        }
        //DEBUGMESSAGE(boost::format("Account Balance Pre: %i, %.2f, %.2f") % std::get<1>(balanceStack.top()) %  std::get<2>(balanceStack.top()) % std::get<3>(balanceStack.top()));
        std::get<2>(balanceStack.top()) += drRollup;
        std::get<3>(balanceStack.top()) += crRollup;
        //DEBUGMESSAGE(boost::format("Account Balance Post: %i, %.2f, %.2f") % std::get<1>(balanceStack.top()) %  std::get<2>(balanceStack.top()) % std::get<3>(balanceStack.top()));
        accountValues[std::get<1>(balanceStack.top())].first = std::get<2>(balanceStack.top());
        accountValues[std::get<1>(balanceStack.top())].second = std::get<3>(balanceStack.top());
        //DEBUGMESSAGE(boost::format("Account Balance Post: %i, %.2f") % std::get<1>(balanceStack.top()) % accountBalances[std::get<1>(balanceStack.top())]);
        //DEBUGMESSAGE(boost::format("Rollup: %i, %i, %.2f %.2f") % std::get<0>(balanceStack.top()) % std::get<1>(balanceStack.top()) % drRollup % crRollup);
      };
    };

    for(auto iterator = chartOfAccounts.begin(); iterator != chartOfAccounts.end(); ++iterator)
    {

      level = std::get<0>(*iterator);

      std::string itemName = std::get<2>(*iterator);

        // Account name and ID

      row.emplace_back(std::make_unique<Wt::WStandardItem>(itemName));
      row.back()->setData(std::get<1>(*iterator), Wt::ItemDataRole::User);

        // Assign the values onto the stack items.

      if (accountValues[std::get<1>(*iterator)].first > 0)
      {
        row.emplace_back(std::make_unique<Wt::WStandardItem>(formatMoney(accountValues[std::get<1>(*iterator)].first)));
      }
      else
      {
        row.emplace_back(std::make_unique<Wt::WStandardItem>(""));
      }
      if (accountValues[std::get<1>(*iterator)].second > 0)
      {
        row.emplace_back(std::make_unique<Wt::WStandardItem>(formatMoney(accountValues[std::get<1>(*iterator)].second)));
      }
      else
      {
        row.emplace_back(std::make_unique<Wt::WStandardItem>(""));
      }

      if (level == 0) // Special case for level 0.
      {
        levelPointers[level] = row.front().get();
        appendRow(std::move(row));
      }
      else
      {
        levelPointers[level] = row.front().get();
        levelPointers[level-1]->appendRow(std::move(row));
      };
    };

  }

} //  namespace models
