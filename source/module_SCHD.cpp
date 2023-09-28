//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Scheduler
// FILE:                module_SCHD.cpp
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
// HISTORY:             2023-07-28/GGB - File created
//
//**********************************************************************************************************************************

#include "include/pluginInterface/interfaceModules.h"

  // Miscellaneous libraries.

#include <GCL>

  // msmERP header files.

#include "include/core/typeDefinitions.h"
#include "include/configSettings.h"
#include "include/database/tables/core/tbl_businessTransactions.h"
#include "include/database/tables/core/tbl_objectTypes.h"

namespace pluginInterface
{
  /// @brief      Constructor for the module.
  /// @note       This can run multiple times. As the OS calls it on subsequent library loads. Not sure why.
  /// @version    2023-07-20/GGB - Function created.

  void initialiseModule(GCL::plugin::CPluginManager *pluginManager, GCL::CReaderSections *configReader)
  {
    database::tbl_objectTypes::objectTypeMap.emplace(OT_IMM_EXCHANGES, "IMM - Exchanges");
    database::tbl_objectTypes::objectTypeMap.emplace(OT_IMM_SECURITIES, "IMM - Securities");
    database::tbl_objectTypes::objectTypeMap.emplace(OT_IMM_PORTFOLIO, "IMM - Portfolio");
    database::tbl_objectTypes::objectTypeMap.emplace(OT_IMM_TRANSACTION, "IMM - Transactions");
    database::tbl_objectTypes::objectTypeMap.emplace(OT_IMM_SECURITYPRICES, "IMM - Security Prices");
    database::tbl_objectTypes::objectTypeMap.emplace(OT_IMM_COSTTYPES, "IMM - Cost Types");
    database::tbl_objectTypes::objectTypeMap.emplace(OT_IMM_CONFIGURATION, "IMM - Configuration Data");
    database::tbl_objectTypes::objectTypeMap.emplace(OT_IMM_CUSTOMERTRANSACTION, "IMM - Customer Transactions");
    database::tbl_objectTypes::objectTypeMap.emplace(OT_IMM_CUSTOMERTRANSACTIONLINE, "IMM - Customer Transaction - Lines");

    database::tbl_businessTransactions::objectTransactionsMap[OT_IMM_EXCHANGES] =
      { BT_VIEW, BT_CREATE, BT_UPDATE, BT_DELETE, BT_ENABLE, BT_DISABLE};
    database::tbl_businessTransactions::objectTransactionsMap[OT_IMM_SECURITIES] =
      { BT_VIEW, BT_CREATE, BT_UPDATE, BT_DELETE, BT_ENABLE, BT_DISABLE, BT_HIDE, BT_UNHIDE};
    database::tbl_businessTransactions::objectTransactionsMap[OT_IMM_PORTFOLIO] =
      { BT_VIEW, BT_CREATE, BT_UPDATE, BT_DELETE, BT_ENABLE, BT_DISABLE};
    database::tbl_businessTransactions::objectTransactionsMap[OT_IMM_TRANSACTION] =
      { BT_VIEW, BT_CREATE, BT_UPDATE, BT_DELETE, BT_POST, BT_ROLLBACK };
    database::tbl_businessTransactions::objectTransactionsMap[OT_IMM_SECURITYPRICES] =
      { BT_VIEW, BT_CREATE, BT_UPDATE, BT_DELETE };
    database::tbl_businessTransactions::objectTransactionsMap[OT_IMM_COSTTYPES] =
      { BT_VIEW, BT_CREATE, BT_UPDATE, BT_DELETE, BT_ENABLE, BT_DISABLE };
    database::tbl_businessTransactions::objectTransactionsMap[OT_IMM_CONFIGURATION] = { BT_VIEW, BT_UPDATE};
    database::tbl_businessTransactions::objectTransactionsMap[OT_IMM_CUSTOMERTRANSACTION] =
      { BT_VIEW, BT_CREATE, BT_UPDATE, BT_DELETE, BT_POST, BT_ROLLBACK};
    database::tbl_businessTransactions::objectTransactionsMap[OT_IMM_CUSTOMERTRANSACTIONLINE] =
      { BT_VIEW, BT_CREATE, BT_UPDATE, BT_DELETE, BT_POST, BT_ROLLBACK};

    IMM::priceUpload::CPriceUploadManager::loadPriceUploadPlugins(*pluginManager, *configReader);
    IMM::priceFetch::CPriceFetchManager::loadPriceFetchPlugins(*pluginManager, *configReader);
  }

  /// @brief      Processes the specified transaction.
  /// @param[in]  application: The application instance.
  /// @param[in]  businessTransaction: The transactioType.
  /// @param[in]  timeSheetID: The timesheet to process,
  /// @returns    An index to the log written for the transaction.
  /// @throws
  /// @version 2023-02-14/GGB - Function created.

  index_t processTransaction(CApplication &application, businessTransactionID_t businessTransaction, index_t timeSheetID)
  {
//    plugins::CTimesheetPost postTimesheet(application);

//    return postTimesheet.transaction(businessTransaction, timeSheetID);
  }


} // namespace
