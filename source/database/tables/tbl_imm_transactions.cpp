//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                tbl_imm_transactions
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
// OVERVIEW:						Classes for interating with the IMM transaction lines table.
//
// HISTORY:             2023-07-25/GGB - File created
//
//**********************************************************************************************************************************

#include "include/database/tables/tbl_imm_transactions.h"

  // msmERP header files

#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/tbl_imm_workflowStatus.h"

namespace TBL_IMM_SECURITYTRANSACTIONS
{
  std::string TABLE = "IMM_securityTransactions";

  std::string PK = "ID";
  std::string FK_PORTFOLIO = "PortfolioID";
  std::string COL_QUANTITY = "Quantity";
}


namespace database::tbl_imm_transactions
{
  /// @brief      Determines the active statuses for the specified record.
  /// @param[in]  application: The application instance to use with database access.
  /// @returns    Set with all the active statuses.
  /// @throws
  /// @version    2023-08-31/GGB - Function created.

  std::set<workFlowStatus_t> activeStatuses(CApplication &application, index_t ID)
  {
    std::set<workFlowStatus_t> rv;

    tbl_core_workflowStatus::recordSet_t recordSet;

    tbl_core_workflowStatus::readRecords(application, TBL_IMM_WORKFLOWSTATUS::TABLE, OT_IMM_TRANSACTION, ID, recordSet);

    for (auto const &record : recordSet)
    {
      switch (record.statusID)
      {
        case SC_CREATED:
        {
          rv.emplace(SC_CREATED);
          break;
        }
        case SC_POSTED:
        {
          rv.clear();
          rv.emplace(SC_POSTED);
          break;
        }
        case SC_DELETED:
        {
          rv.clear();
          rv.emplace(SC_DELETED);
          break;
        }
        default:
        {
          CODE_ERROR();
          break;
        }
      }
    }

    return rv;
  }
  void createRecord(CApplication &, record_t &)
  {

  }
  void readRecord(CApplication &, record_t &)
  {

  }
  void updateRecord(CApplication &, record_t const &)
  {

  }
}
