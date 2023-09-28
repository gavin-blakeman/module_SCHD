//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                tbl_imm_portfolio
// SUBSYSTEM:           Module: Investment Management
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
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
// OVERVIEW:						Table definitions and interface for metering points.
//
// HISTORY:             2022-07-26/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/tables/tbl_imm_portfolio.h"

  // Standard C++ library

#include <memory>

  // Wt++

#include <Wt/WStandardItem.h>

  // Miscellaneous libraries

#include <GCL>

  // msmERP

#include "include/dbe.h"
#include "include/application.h"
#include "include/database/tables/tbl_imm_audit.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/tbl_imm_workflowStatus.h"

namespace TBL_IMM_PORTFOLIO
{
  std::string TABLE = "IMM_portfolio";

  std::string PK = "ID";
  std::string FK_ENTERPRISE = "EnterpriseID";
  std::string FK_BROKERAGEACCOUNT = "BrokerageAccountID";
  std::string FK_SECURITYLEDGER = "SecurityLedgerID";
  std::string COL_SHORTTEXT = "ShortText";
  std::string FK_TRADINGACCOUNT = "TradingAccountID";
  std::string FK_DRIPACCOUNT = "DRIPAccountID";
}


namespace database::tbl_imm_portfolio
{
  /// @brief      Returns a set containing the active statuses for the specified object.
  /// @param[in]  application: The application object
  /// @param[in]  ID: The exchange ID to get the status for.
  /// @returns    A set with the active statuses.
  /// @throws
  /// @version    2023-07-20/GGB - Function created.

  std::set<workFlowStatus_t> activeStatuses(CApplication &application, index_t ID)
  {
    std::set<workFlowStatus_t> rv;

    tbl_core_workflowStatus::recordSet_t recordSet;

    tbl_core_workflowStatus::readRecords(application, TBL_IMM_WORKFLOWSTATUS::TABLE, OT_IMM_PORTFOLIO, ID, recordSet);

    for (auto const &record : recordSet)
    {
      switch (record.statusID)
      {
        case SC_CREATED:
        {
          rv.emplace(SC_CREATED);
          break;
        }
        case SC_ACTIVE:
        {
          if (rv.contains(SC_INACTIVE))
          {
            rv.erase(SC_INACTIVE);
          }
          rv.emplace(SC_ACTIVE);
          break;
        }
        case SC_INACTIVE:
        {
          if (rv.contains(SC_ACTIVE))
          {
            rv.erase(SC_ACTIVE);
          }
          rv.emplace(SC_INACTIVE);
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

  /// @brief      Returns the brokerage account ID.
  /// @param[in]  application: The application instance.
  /// @param[in]  portFolioID
  /// @returns    The trading account ID
  /// @throws
  /// @version    2023-08-31/GGB - Function created.

  index_t brokerageAccountID(CApplication &application, index_t portfolioID)
  {
    using namespace TBL_IMM_PORTFOLIO;
    using namespace GCL;

    sqlWriter sqlQuery;
    index_t rv = 0;

    sqlQuery
        .select({ FK_BROKERAGEACCOUNT })
        .from(TABLE)
        .where(PK, eq, portfolioID);

    try
    {
      CRecord row = application.session().record(sqlQuery);

      rv = static_cast<index_t>(row[0]);
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

    return rv;
  }

  /// @brief          Reads accound data for the specified account.
  /// @param[in/out]  record: The record to hold the information. The ID od the account is in the record.
  /// @version        2023-07-26/GGB - Function created.

  void readRecord(CApplication &application, record_t &record)
  {
    using namespace TBL_IMM_PORTFOLIO;
    using namespace GCL;

    sqlWriter sqlQuery;

    sqlQuery
        .select({ FK_BROKERAGEACCOUNT, FK_SECURITYLEDGER, COL_SHORTTEXT, FK_DRIPACCOUNT, FK_TRADINGACCOUNT })
        .from(TABLE)
        .where(PK, eq, record.ID)
        .orderBy(COL_SHORTTEXT, ASC);

    try
    {
      CRecord row = application.session().record(sqlQuery);

      record.BrokerageAccountID = static_cast<index_t>(row[0]);
      record.securityLedgerID = static_cast<index_t>(row[1]);
      record.shortText = row[2].toString();
      record.DRIPAccountID = static_cast<index_t>(row[3]);
      record.tradingAccountID = static_cast<index_t>(row[4]);
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

  }

  /// @brief      Inserts a record into the database.
  /// @param[in]  application: The application object
  /// @param[in]  record: The record to insert.
  /// @throws
  /// @version    2022-08-01/GGB - Function created.

  void createRecord(CApplication &application, record_t &record)
  {
    using namespace TBL_IMM_PORTFOLIO;
    GCL::sqlWriter sqlQuery;

    sqlQuery
        .insertInto(TABLE,
                    { FK_ENTERPRISE, FK_BROKERAGEACCOUNT, FK_SECURITYLEDGER, COL_SHORTTEXT })
        .values({
                  {
                    application.enterpriseID(),
                    record.BrokerageAccountID,
                    record.securityLedgerID,
                    record.shortText
                  }
                })
        .returning(PK);

    try
    {
      record.ID = static_cast<index_t>(application.session().record(sqlQuery)[0]);

      tbl_core_audit::insert(application, TBL_IMM_AUDIT::TABLE, TABLE, "Record Created", std::to_string(record.ID), "", "");
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }
  }

  /// @brief      Returns the trading account ID.
  /// @param[in]  application: The application instance.
  /// @param[in]  portFolioID
  /// @returns    The trading account ID
  /// @throws
  /// @version    2023-08-31/GGB - Function created.

  index_t tradingAccountID(CApplication &application, index_t portfolioID)
  {
    using namespace TBL_IMM_PORTFOLIO;
    using namespace GCL;

    sqlWriter sqlQuery;
    index_t rv = 0;

    sqlQuery
        .select({ FK_TRADINGACCOUNT })
        .from(TABLE)
        .where(PK, eq, portfolioID);

    try
    {
      CRecord row = application.session().record(sqlQuery);

      rv = static_cast<index_t>(row[0]);
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

    return rv;
  }


}
