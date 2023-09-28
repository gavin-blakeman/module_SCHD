﻿//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                tbl_imm_exchanges
// SUBSYSTEM:           Table definitions security exchanges
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

#include "include/database/tables/tbl_imm_exchanges.h"

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

namespace TBL_IMM_EXCHANGES
{
  std::string TABLE = "IMM_exchanges";

  std::string PK = "ID";
  std::string FK_COUNTRY = "CountryID";
  std::string COL_LONGTEXT = "ExtendedText";
  std::string COL_SUFFIX2 = "suffix2";
  std::string COL_SUFFIX3 = "suffix3";
}

namespace database::tbl_imm_exchanges
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

    tbl_core_workflowStatus::readRecords(application, TBL_IMM_WORKFLOWSTATUS::TABLE, OT_IMM_EXCHANGES, ID, recordSet);

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
    using namespace TBL_IMM_EXCHANGES;
    using namespace GCL;

    sqlWriter sqlQuery;

    sqlQuery
        .select({ COL_SUFFIX3, COL_LONGTEXT, COL_SUFFIX2, FK_COUNTRY })
        .from(TABLE)
        .where(PK, eq, record.ID)
        .orderBy(COL_SUFFIX3, ASC);

    try
    {
      CRecord row = application.session().record(sqlQuery);

      record.shortText = row[0].toString();
      record.longText = row[1].toString();
      record.suffix = row[2].toString();
      record.countryID = static_cast<sindex_t>(row[3]);
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
    using namespace TBL_IMM_EXCHANGES;
    GCL::sqlWriter sqlQuery;

    sqlQuery
        .insertInto(TABLE,
                    { COL_SUFFIX3, COL_LONGTEXT, COL_SUFFIX2, FK_COUNTRY })
        .values({
                  {
                    record.shortText,
                    record.longText,
                    record.suffix,
                    record.countryID,
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

  /// @brief      Checks if the specified record exists
  /// @param[in]  application: The application instance
  /// @param[in]  shortText: The short text to search.
  /// @returns    true - if the specified stock exists.
  /// @throws
  /// @version    2023-07-23/GGB - Function created.

  bool recordExists(CApplication &application, std::string const &shortText)
  {
    using namespace TBL_IMM_EXCHANGES;
    using namespace GCL;

    GCL::sqlWriter sqlQuery;
    bool returnValue =  false;

    sqlQuery.count(PK).from(TABLE).where(COL_SUFFIX3, eq, shortText);

    try
    {
      returnValue = (application.session().record(sqlQuery)[0].toU32() != 0);
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

    return returnValue;
  }

  /// @brief      Gets the ID of the specified record.
  /// @param[in]  application: The application instance
  /// @param[in]  shortText: The short text to search.
  /// @returns    true - if the specified stock exists.
  /// @throws
  /// @version    2023-07-23/GGB - Function created.


  index_t recordID(CApplication &application, std::string const &shortText)
  {
    using namespace TBL_IMM_EXCHANGES;
    using namespace GCL;

    GCL::sqlWriter sqlQuery;
    index_t returnValue = 0;

    sqlQuery.select({PK}).from(TABLE).where(COL_SUFFIX3, eq, shortText);

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


  /// @brief      Update the specified record
  /// @param[in]  application: The session to use.
  /// @param[out] record: The record to update.
  /// @throws
  /// @version    2022-05-25/GGB - Function created.

  void updateRecord(CApplication &application, record_t const &record)
  {
    using namespace TBL_IMM_EXCHANGES;
    using namespace GCL;

    record_t oldRecord;

    oldRecord.ID = record.ID;
    readRecord(application, oldRecord);

    GCL::sqlWriter sqlQuery;

    sqlQuery
        .update(TABLE)
        .set({
               { COL_SUFFIX3, record.shortText},
               { COL_LONGTEXT, record.longText },
               { COL_SUFFIX2, record.suffix },
             })
        .where(PK, eq, record.ID);

    try
    {
      CTransaction transaction { application.session() };

      application.session().exec(sqlQuery);

      if (record.shortText != oldRecord.shortText)
      {
        tbl_core_audit::insert(application, TBL_IMM_AUDIT::TABLE, TABLE, "Value Changed: " + COL_SUFFIX3,
                               std::to_string(record.ID), oldRecord.shortText, record.shortText);
      }
      if (record.longText != oldRecord.longText)
      {
        tbl_core_audit::insert(application, TBL_IMM_AUDIT::TABLE, TABLE, "Value Changed: " + COL_LONGTEXT,
                               std::to_string(record.ID), oldRecord.longText, record.longText);
      }
      tbl_core_audit::compareInsert(application, TBL_IMM_AUDIT::TABLE, TABLE, COL_SUFFIX2, record.ID, oldRecord.suffix, record.suffix);

    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }
  }

  /// @brief      Finds the recordID corresponding to the suffix2.
  /// @param[in]  suffix2: The suffix2 value to find.
  /// @returns    The index or 0.
  /// @throws
  /// @version    2023-09-23/GGB - Function created.

  index_t recordSuffix2(CApplication &application, std::string const &suffix2)
  {
    using namespace TBL_IMM_EXCHANGES;
    using namespace GCL;

    GCL::sqlWriter sqlQuery;
    index_t returnValue = 0;
    std::string tempSuffix2{suffix2};
    boost::to_upper(tempSuffix2);

    sqlQuery.select({PK}).from(TABLE).where(COL_SUFFIX2, eq, tempSuffix2);

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
