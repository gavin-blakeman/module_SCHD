//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                viewCostType
// SUBSYSTEM:           Module: Investement Management
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           database
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2023 Gavin Blakeman.
//                      This file is part of the msmERP Project
//
//                      msmERP is free software: you can redistribute it and/or modify it under the terms of the GNU
//                      General Public License as published by the Free Software Foundation, either version 2 of the License, or (at
//                      your option) any later version.
//
//                      msmERP is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
//                      even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
//                      Public License for more details.
//
//                      You should have received a copy of the GNU General Public License along with msmERP.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:
//
// HISTORY:             2023-07-25/GGB - File created
//
//**********************************************************************************************************************************

#include "include/database/views/viewCostType.h"

namespace views
{

  /// @brief Determines the current statuses
  /// @throws
  /// @version 2023-03-09/GGB - Function created.

  void CViewCostType::processActiveStatus()
  {
    activeStatus_ = database::tbl_imm_costTypes::activeStatuses(application(), ID());
  }

  /// @brief Returns a set containing the allowed business transactions based on the current status train.
  /// @throws
  /// @version 2023-07-21/GGB - Function created.

  std::set<businessTransaction_e> CViewCostType::processAllowedBusinessTransactions() const
  {
    std::set<businessTransaction_e> rv;

    if (!activeStatus_.contains(SC_DELETED))
    {
      if (activeStatus_.contains(SC_ACTIVE))
      {
        rv.emplace(BT_DISABLE);
      }
      else if (activeStatus_.contains(SC_INACTIVE))
      {
        rv.emplace(BT_ENABLE);
        rv.emplace(BT_DELETE);
        rv.emplace(BT_UPDATE);
      }
      else
      {
        rv.emplace(BT_ENABLE);
        rv.emplace(BT_DELETE);
        if (record_.ID == 0)
        {
          rv.emplace(BT_CREATE);
        }
        else
        {
          rv.emplace(BT_UPDATE);
        }
      }
    }

    return rv;
  }

  /// @brief      Determines if a speficied transaction is allowed.
  /// @param[in]  bt: The trsansaction to test.
  /// @returns    true if the transaction is allowed.
  /// @throws
  /// @version    2023-07-21/GGB - Function created.

  bool CViewCostType::processAllowTransaction(businessTransaction_e bt) const
  {
    bool rv = false;

    if (!activeStatus_.contains(SC_DELETED))
    {
      switch (bt)
      {
        case BT_CREATE:
        {
          rv = true;
          break;
        }
        case BT_UPDATE:
        {
          if (!activeStatus_.contains(SC_ACTIVE))
          {
            rv = true;
          }
          break;
        }
        case BT_ENABLE:
        {
          if (!activeStatus_.contains(SC_INACTIVE))
          {
            rv = true;
          }
          break;
        }
        case BT_DISABLE:
        {
          if (!activeStatus_.contains(SC_ACTIVE))
          {
            rv = true;
          }
          break;
        }
        default:
        {
          // Return false.
          break;
        }
      }
    }


    return rv;
  }

  /// @brief      Processes the specified business transaction.
  /// @param[in]  businessTransaction:
  /// @throws
  /// @version    2023-03-30/GGB - Function created.

  void CViewCostType::processBusinessTransaction(businessTransaction_e businessTransaction)
  {
    switch (businessTransaction)
    {
      case BT_ENABLE:
      {
        updateStatus(SC_ACTIVE);
        break;
      };
      case BT_DISABLE:
      {
        updateStatus(SC_INACTIVE);
        break;
      }
      default:
      {
        CODE_ERROR();
        break;
      }
    }
  }

  /// @brief      Clears the record data.
  /// @throws     None.
  /// @version    2023-08-08/GGB - Function created.

  void CViewCostType::processClearData() noexcept
  {
    record_.ID = 0;
    record_.shortText.clear();
  }

  /// @brief      Loads data from the database.
  /// @version    2023-08-08/GGB - Function created.

  void CViewCostType::processLoadData()
  {
    database::tbl_imm_costTypes::readRecord(application(), record_);
  }

  /// @brief      Saves data to the database.
  /// @version    2023-08-08/GGB - Function created.

  void CViewCostType::processSaveData()
  {
    std::cout << "Process Save Data" << std::endl;

    if (ID() == 0)
    {
      database::tbl_imm_costTypes::createRecord(application(), record_);
      updateStatus(SC_CREATED);
    }
    else
    {
      database::tbl_imm_costTypes::updateRecord(application(), record_);
    }
  }
}
