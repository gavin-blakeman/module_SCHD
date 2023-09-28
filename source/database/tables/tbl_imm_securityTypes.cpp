#include "include/database/tables/tbl_imm_securityTypes.h"

  // Standard C++ library

#include <memory>

  // Wt++

#include <Wt/WStandardItem.h>

  // Miscellaneous libraries

#include <GCL>


namespace database::tbl_imm_securityTypes
{
  securityTypeMap_t securityTypeMap =
  {
    { ST_NONE, "No Object" },
  };

  /// @brief      Builds a model for the object types.
  /// @param[in]  unused.
  /// @param[out] model: The model to build.
  /// @throws
  /// @version    2023-07-24/GGB - Function created.

  void createModel(CDatabaseSession &, Wt::WStandardItemModel &model)
  {
    model.clear();
    std::map<std::string, securityType_t> reverseSecurityTypeMap;

    for (auto const &record: securityTypeMap)
    {
      reverseSecurityTypeMap.emplace(record.second, record.first);
    };
    for (auto const &record: reverseSecurityTypeMap)
    {
      std::unique_ptr<Wt::WStandardItem> item = std::make_unique<Wt::WStandardItem>(record.first);
      item->setData(record.second, Wt::ItemDataRole::User);

      model.appendRow(std::move(item));
    }
  }

  /// @brief Returns the user readable name of the objectType.
  /// @param[in] objectTypeID to get name for.
  /// @returns Human readable string of the objectType
  /// @throws
  /// @version 2022-11-01/GGB - Function created.

  std::string const &shortText(securityType_t oid)
  {
    RUNTIME_ASSERT(securityTypeMap.contains(oid), "Unknown Object Type");

    return securityTypeMap[oid];
  }
}
