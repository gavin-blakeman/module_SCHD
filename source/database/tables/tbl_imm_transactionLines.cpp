//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                tbl_imm_transactionLines
// SUBSYSTEM:           Module: Investement Management
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
// OVERVIEW:						Classes for interating with the financial years table.
//
// HISTORY:             2023-07-25/GGB - File created
//
//**********************************************************************************************************************************

#include "include/database/tables/tbl_imm_transactionLines.h"

  // Standard C++ library header files

#include <string>

  // Miscellaneous library header files

#include <GCL>

  // msmERP


namespace TBL_IMM_TRANSACTIONLINES
{
  std::string TABLE = "IMM_transactionLines";

  std::string PK = "ID";
  std::string FK_TRANSACTION = "TransactionID";
  std::string COL_SORTORDER = "SortOrder";
  std::string FK_COSTTYPE = "CostTypeID";
  std::string FK_ACCOUNT = "AccountID";
  std::string COL_VALUE = "Value";
  std::string COL_SHORTTEXT = "ShortText";
}

namespace database::tbl_imm_transactionLines
{
  void insertRecords(CApplication &, index_t, records_t &)
  {

  }

  void deleteRecord(CApplication &, index_t)
  {

  }

  void readRecords(CApplication &, index_t, records_t &)
  {

  }

  void updateRecords(CApplication &, records_t &)
  {

  }

}  // namespace database
