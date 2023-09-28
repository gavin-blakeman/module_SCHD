//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                tbl_imm_tradingLedger.h
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
// HISTORY:             2023-08-31/GGB - File created
//
//**********************************************************************************************************************************

#include "include/database/tables/tbl_imm_tradingLedger.h"

  // Miscellaneous library header files

#include <GCL>

  // msmERP header files

#include "include/application.h"
#include "include/database/tables/tbl_imm_audit.h"

namespace TBL_IMM_TRADINGLEDGER
{
  std::string TABLE = "IMM_tradingLedger";

  std::string PK = "ID";
  std::string FK_PORTFOLIO = "PortfolioID";
  std::string FK_SECURITY = "SecurityID";
  std::string COL_QTY = "Quantity";
  std::string COL_VALUE = "Value";
  std::string COL_TRANSACTIONDATE = "TransactionDate";
  std::string COL_CREATEDATE = "CreationDate";
}

namespace database::tbl_imm_tradingLedger
{
  /// @brief    Creates a new record.
  /// @version  2023-08-31/GGB - Function created.

  void createRecord(CApplication &application, record_t &record)
  {
    using namespace TBL_IMM_TRADINGLEDGER;
    GCL::sqlWriter sqlQuery;

    sqlQuery
        .insertInto(TABLE,
                    { FK_PORTFOLIO, FK_SECURITY, COL_QTY, COL_VALUE, COL_TRANSACTIONDATE })
        .values({
                  {
                    record.portfolioID,
                    record.securityID,
                    record.quantity,
                    static_cast<decimal_t>(record.value),
                    record.transactionDate,
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

  /// @brief    Reads the specified record.
  /// @version  2023-08-31/GGB - Function created.

  void readRecord(CApplication &application, record_t &record)
  {
    using namespace TBL_IMM_TRADINGLEDGER;
    using namespace GCL;

    sqlWriter sqlQuery;

    sqlQuery
        .select({ FK_PORTFOLIO, FK_SECURITY, COL_QTY, COL_VALUE, COL_TRANSACTIONDATE })
        .from(TABLE)
        .where(PK, eq, record.ID);

    try
    {
      CRecord row = application.session().record(sqlQuery);

      record.portfolioID = static_cast<index_t>(row[0]);
      record.securityID = static_cast<index_t>(row[1]);
      record.quantity = static_cast<decimal_t>(row[2]);
      record.value = static_cast<decimal_t>(row[3]);
      record.transactionDate = row[4].toDate();
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

  }


  void readRecordsSecurity(CApplication &, index_t, index_t, securityRecords_t)
  {

  }

  /// @brief      Reads all the records for a portfolio.
  ///
  /// @version  2023-08-31/GGB - Function created.

  void readRecordsPortfolio(CApplication &application, index_t PID, portfolioRecords_t & records)
  {
    using namespace TBL_IMM_TRADINGLEDGER;
    using namespace GCL;

    sqlWriter sqlQuery;

    sqlQuery
        .select({ PK, FK_SECURITY, COL_QTY, COL_VALUE, COL_TRANSACTIONDATE })
        .from(TABLE)
        .where(FK_PORTFOLIO, eq, PID)
        .orderBy(COL_TRANSACTIONDATE, ASC);

    try
    {
      CRecordSet rowSet = application.session().recordSet(sqlQuery);

      for (auto const &row: rowSet)
      {
        record_t record;

        record.ID = static_cast<index_t>(row[0]);
        record.portfolioID = PID;
        record.securityID = static_cast<index_t>(row[1]);
        record.quantity = static_cast<decimal_t>(row[2]);
        record.value = static_cast<decimal_t>(row[3]);
        record.transactionDate = row[4].toDate();

        records[record.securityID].push_back(record);
      }
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

  }
}
