//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:
// SUBSYSTEM:
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2022 Gavin Blakeman.
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
// HISTORY:             2022-05-14/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TBL_GL_TRANSACTIONLINES_H
#define TBL_GL_TRANSACTIONLINES_H

  // Standard C++ library header files.

#include <map>
#include <string>
#include <tuple>
#include <vector>

  // msmERP header files

#include "include/dbe.h"
#include "include/core/typeDefinitions.h"


namespace TBL_GL_TRANSACTIONLINES
{
  extern std::string TABLE;

  extern std::string PK;
  extern std::string FK_TRANSACTION;
  extern std::string FK_ACCOUNT;
  extern std::string COL_SHORTTEXT;
  extern std::string COL_VALUE;

  inline std::string qCol(std::string const &col)
  {
    return TABLE + "." + col;
  }
}

namespace database::tbl_gl_transactionLines
{
  struct record_t
  {
    index_t ID;
    index_t transactionID;
    index_t accountID;
    std::string shortText;
    money_t value;
  };
  using recordSet_t = std::vector<record_t>;

  using balances_t = std::map<index_t, decimal_t>;

  void accountBalances(CDatabaseSession &, balances_t &);
  void insertRecords(CDatabaseSession &, recordSet_t const &);
  void accountTransactions(CDatabaseSession &, index_t, recordSet_t &);

} // namespace database

#endif // TBL_GL_TRANSACTIONLINES_H
