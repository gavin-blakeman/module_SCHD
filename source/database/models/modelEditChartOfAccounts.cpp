#include "include/database/models/modelEditChartOfAccounts.h"

  // Standard C++ library header files

#include <cmath>
#include <map>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

  // msmERP Application header files.

#include "include/core/formatFunctions.h"
#include "include/database/tables/tbl_fi_accounts.h"

namespace models
{

  /// @brief      Class constructor
  /// @param[in]  a: The application owner of this instance.
  /// @param[in]  accountID: Reference to the plant register ID
  /// @throws
  /// @version    202-05-26/GGB - Function created.

  CModelEditChartOfAccounts::CModelEditChartOfAccounts(CApplication &a) : CModelCustom(a)
  {
  }

  /// @brief      Takes the information from the hierarchy and adds it into the model.
  /// @throws
  /// @version    2022-07-30/GGB - Function created.

  void CModelEditChartOfAccounts::reload()
  {
    using namespace database;
    using record_t = tbl_fi_accounts::record_t;

    using hierarchy_t = SCL::sortedHierarchy<index_t, sindex_t, record_t>;

      /* A map is used rather than a vector, as a vector needs the [] operator to refer to already constructed objects.
       * the map [] creates an object as required. */

    using level_t = hierarchy_t::iterator::size_type;

    hierarchy_t chartOfAccounts(0);
    std::map<hierarchy_t::size_type, Wt::WStandardItem *> levelPointers;
    level_t level;

    tbl_fi_accounts::buildHierarchy(application(), chartOfAccounts);

    clear();    // Clear the data from the WStandardItemModel

    for(auto iterator = chartOfAccounts.begin(); iterator != chartOfAccounts.end(); ++iterator)
    {
      level = std::get<0>(*iterator);

      record_t record = std::get<2>(*iterator);

        // Account name and ID

      std::unique_ptr<Wt::WStandardItem> item = std::make_unique<Wt::WStandardItem>(record.shortText);
      item->setData(record.ID, Wt::ItemDataRole::User);

//      if (record.accountFlags.placeHolderAccount)
//      {
//        item->setStyleClass("text-primary");
//      }
//      else if (record.accountFlags.assetAccount || record.accountFlags.equityAccount || record.accountFlags.liabilityAccount)
//      {
//        item->setStyleClass("text-success");
//      }

      if (level == 0) // Special case for level 0.
      {
        levelPointers[level] = item.get();
        appendRow(std::move(item));
      }
      else
      {
        levelPointers[level] = item.get();
        levelPointers[level-1]->appendRow(std::move(item));
      };
    };

  }

} //  namespace models
