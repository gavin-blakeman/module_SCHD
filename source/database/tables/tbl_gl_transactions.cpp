//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                tbl_gl_transactions
// SUBSYSTEM:
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2019-2021 Gavin Blakeman.
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
// OVERVIEW:						Project file for compiling the project
//
// HISTORY:             2019-12-03/GGB - File created
//
//**********************************************************************************************************************************

#include "include/database/tables/tbl_gl_transactions.h"

  // Wt framework header files


  // Miscellaneous library header files.

#include <WtExtensions>
#include <GCL>

  // msmERP

#include "include/application.h"
#include "include/database/tables/core/tbl_audit.h"

namespace TBL_GL_TRANSACTIONS
{
  std::string TABLE = "gl_transactions";

  std::string PK = "ID";
  std::string FK_CURRENCY = "Currency_ID";
  std::string COL_NUM = "num";
  std::string COL_POSTDATE = "PostDate";
  std::string COL_ENTERDATE = "CreateDate";
  std::string COL_SHORTTEXT = "ShortText";
}

namespace database::tbl_gl_transactions
{

  /// @brief          Inserts a record into the table.
  /// @param[in]      session: The session to use.
  /// @param[in/out]  record: The record to insert. The inserted key is written back.
  /// @throws
  /// @version        2022-05-14/GGB - Function created.

  void insertRecord(CApplication &application, record_t &record)
  {
    using namespace TBL_GL_TRANSACTIONS;
    GCL::sqlWriter sqlQuery;

//    sqlQuery
//        .insertInto(TABLE,
//                    {COL_POSTDATE, COL_SHORTTEXT})
//        .values({ { record.postDate, record.shortText }})
//        .returning(PK);

    try
    {
      record.ID = static_cast<index_t>(application.session().record(sqlQuery)[0]);

      tbl_core_audit::insert(application, TABLE, "Record Created", std::to_string(record.ID), "", "");
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }
  }

  /// @brief Updates a record in the table. If the record does not exist then it is created.
  /// @param[in] session: The session to use.
  /// @param[in] modificationType: The type of modification.
  /// @param[in] primaryID: The Primary maintenance strategy ID.
  /// @param[in] secondaryID: The Secondary maintenance strategy ID.
  /// @param[in] value: The value to assign.
  /// @note: If the record does not exist it will be created with a call to insertRecord.
  /// @throws
  /// @version 2019-12-08/GGB - Function created.

  void updateRecord(database::CDatabaseSession &session, int8_t modificationType, int32_t primaryID,
                                               int32_t secondaryID, bool value)
  {
    using namespace GCL;
    GCL::sqlWriter sqlWriter;

    try
    {
//      CTransaction transaction { session };

//      sqlWriter.upsert("tbl_scheduleModifications")
//          .set("Value", value)
//          .where(where_v(
//                   where_v("ModificationType", "=", modificationType},
//                   {"Primary_ID", "=", primaryID},
//                   {"Secondary_ID", "=", secondaryID},
//                 });

//      session.execute(sqlWriter.string());
    }
    catch(...)
    {
      //insertRecord(session, modificationType, primaryID, secondaryID, value);
    }

  }

}  // namespace database
