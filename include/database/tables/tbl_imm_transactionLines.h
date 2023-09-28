//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                tbl_imm_transactionLines
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

#ifndef TBL_IMM_TRANSACTIONLINES_H
#define TBL_IMM_TRANSACTIONLINES_H

  // Standard C++ library header files

#include <set>
#include <string>
#include <vector>

  // Miscellaneous Library Header Files

#include <SCL>

  // msmERP

#include "include/core/typeDefinitions.h"
#include "include/database/database/session.h"
#include "include/database/tables/core/tbl_statusCodes.h"

class CApplication;

namespace TBL_IMM_TRANSACTIONLINES
{
  extern std::string TABLE;

  extern std::string PK;
  extern std::string FK_TRANSACTION;
  extern std::string COL_SORTORDER;
  extern std::string FK_COSTTYPE;
  extern std::string FK_ACCOUNT;
  extern std::string COL_VALUE;
  extern std::string COL_SHORTTEXT;
}

namespace database::tbl_imm_transactionLines
{
  struct record_t
  {
    index_t ID;
    index_t transactionID;
    sindex_t sortOrder;
    index_t costTypeID;
    index_t costElementID;
    money_t value;
    std::string shortText;
  };
  using records_t = std::vector<record_t>;

  void insertRecords(CApplication &, index_t, records_t &);
  void deleteRecord(CApplication &, index_t);
  void readRecords(CApplication &, index_t, records_t &);
  void updateRecords(CApplication &, records_t &);

} // namespace database

#endif // TBL_IMM_TRANSACTIONLINES_H
