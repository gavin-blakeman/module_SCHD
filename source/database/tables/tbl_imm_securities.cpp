//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                tbl_imm_securities
// SUBSYSTEM:           Table definitions securities
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
// HISTORY:             2022-07-20/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/tables/tbl_imm_securities.h"

  // Standard C++ library

#include <map>
#include <tuple>

  // Wt Library

#include <Wt/WStandardItem.h>

  // Miscellaneous libraries

#include <boost/algorithm/string.hpp>
#include <GCL>

  // msmERP

#include "include/dbe.h"
#include "include/application.h"
#include "include/database/tables/tbl_imm_audit.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/tbl_imm_workflowStatus.h"

namespace TBL_IMM_SECURITIES
{
  std::string TABLE = "IMM_securities";

  std::string PK = "ID";
  std::string FK_EXCHANGE = "ExchangeID";
  std::string FK_CURRENCY = "CurrencyID";
  std::string COL_SHORTTEXT = "ShortText";
  std::string COL_LONGTEXT = "ExtendedText";
  std::string COL_SYMBOL = "Symbol";
}

namespace database::tbl_imm_securities
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

    tbl_core_workflowStatus::readRecords(application, TBL_IMM_WORKFLOWSTATUS::TABLE, OT_IMM_SECURITIES, ID, recordSet);

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

  /// @brief          Reads accound data for the specified account.
  /// @param[in/out]  record: The record to hold the information. The ID od the account is in the record.
  /// @version        2023-03-27/GGB - Changed table to use AccountTypeID.
  /// @version        2022-07-31/GGB - Function created.

  void readRecord(CApplication &application, record_t &record)
  {
    using namespace TBL_IMM_SECURITIES;
    using namespace GCL;

    sqlWriter sqlQuery;

    sqlQuery
        .select({ FK_EXCHANGE, COL_SHORTTEXT, COL_SYMBOL, FK_CURRENCY, COL_LONGTEXT })
        .from(TABLE)
        .where(PK, eq, record.ID);

    try
    {
      CRecord row = application.session().record(sqlQuery);

      record.exchangeID = static_cast<index_t>(row[0]);
      record.shortText = row[1].toString();
      record.code = row[2].toString();
      record.currencyID = static_cast<sindex_t>(row[3]);
      record.longText = row[4].toString();
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

  }

  /// @brief    Inserts a record into the database.
  /// @param[in]  application: The application object
  /// @param[in]  record: The record to insert.
  /// @throws
  /// @version    2022-08-01/GGB - Function created.

  void createRecord(CApplication &application, record_t &record)
  {
    using namespace TBL_IMM_SECURITIES;
    GCL::sqlWriter sqlQuery;

    sqlQuery
        .insertInto(TABLE,
                    { FK_EXCHANGE, COL_SHORTTEXT, COL_SYMBOL, FK_CURRENCY, COL_LONGTEXT })
        .values({
                  {
                    record.exchangeID,
                    record.shortText,
                    record.code,
                    record.currencyID,
                    record.longText,
                  }
                })
        .returning(PK);

    try
    {
      record.ID = static_cast<index_t>(application.session().record(sqlQuery)[0]);

      tbl_core_audit::insert(application, TBL_IMM_AUDIT::TABLE,  TABLE, "Record Created", std::to_string(record.ID), "", "");
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }
  }

  /// @brief      Update the specified record
  /// @param[in]  application: The session to use.
  /// @param[out] record: The record to update.
  /// @throws
  /// @version    2022-05-25/GGB - Function created.

  void updateRecord(CApplication &application, record_t const &record)
  {
    using namespace TBL_IMM_SECURITIES;
    using namespace GCL;

    record_t oldRecord;

    oldRecord.ID = record.ID;
    readRecord(application, oldRecord);

    GCL::sqlWriter sqlQuery;

    sqlQuery
        .update(TABLE)
        .set({
               { FK_EXCHANGE, record.exchangeID},
               { COL_SHORTTEXT, record.shortText},
               { COL_SYMBOL, record.code},
               { FK_CURRENCY, record.currencyID },
               { COL_LONGTEXT, record.longText },
             })
        .where(PK, eq, record.ID);

    try
    {
      CTransaction transaction { application.session() };

      application.session().exec(sqlQuery);

      if (record.shortText != oldRecord.shortText)
      {
        tbl_core_audit::insert(application, TBL_IMM_AUDIT::TABLE, TABLE, "Value Changed: " + COL_SHORTTEXT,
                               std::to_string(record.ID), oldRecord.shortText, record.shortText);
      }
      tbl_core_audit::compareInsert(application, TBL_IMM_AUDIT::TABLE, TABLE, COL_SYMBOL, record.ID, oldRecord.code, record.code);
      tbl_core_audit::compareInsert(application, TBL_IMM_AUDIT::TABLE, TABLE, FK_CURRENCY, record.ID, oldRecord.currencyID, record.currencyID);

    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }
  }

  /// @brief      Gets the security name as a string.
  /// @param[in]  application: The application instance.
  /// @param[in]  ID: The ID of the security.
  /// @returns    The security name.
  /// @throws
  /// @version    2023-08-31/GGB - Function created.

  std::string shortText(CApplication &application, index_t ID)
  {
    using namespace TBL_IMM_SECURITIES;
    using namespace GCL;

    std::string rv;
    sqlWriter sqlQuery;

    sqlQuery
        .select({ COL_SHORTTEXT })
        .from(TABLE)
        .where(PK, eq, ID);

    try
    {
      CRecord row = application.session().record(sqlQuery);

      rv = row[0].toString();

    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

    return rv;
  }

  /// @brief      Obtains the index for the symbol.
  /// @param[in]  application: The application instance.
  /// @param[in]  symbol: The symbol to find.
  /// @returns    The index of the symbol. Or zero if not found.
  /// @throws
  /// @version    2023-09-23/GGB - Function created.

  index_t recordSymbol(CApplication &application, index_t exchangeID, std::string const &symbol)
  {
    using namespace TBL_IMM_SECURITIES;
    using namespace GCL;

    GCL::sqlWriter sqlQuery;
    index_t returnValue = 0;
    std::string tempSymbol{symbol};
    boost::to_upper(tempSymbol);

    sqlQuery.select({PK}).from(TABLE).where(where_v(where_v(COL_SYMBOL, eq, tempSymbol),
                                                    AND,
                                                    where_v(FK_EXCHANGE, eq, exchangeID)));

    try
    {
      returnValue = static_cast<index_t>(application.session().record(sqlQuery)[0]);
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

    return returnValue;
  }

} // namespace

