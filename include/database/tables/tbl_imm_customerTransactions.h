//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                tbl_imm_customerTransactions
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
// HISTORY:             2023-09-17/GGB - File created
//
//**********************************************************************************************************************************

#ifndef TBL_IMM_CUSTOMERTRANSACTIONS_H
#define TBL_IMM_CUSTOMERTRANSACTIONS_H

  // Standard C++ library

#include <string>

  // msmERP header files

#include "include/core/typeDefinitions.h"
#include "include/database/tables/core/tbl_workflowStatus.h"

namespace TBL_IMM_CUSTOMERTRANSACTIONS
{
  extern std::string TABLE;

  extern std::string PK;
  extern std::string FK_TRANSACTIONTYPE;
  extern std::string FK_CUSTOMER;
  extern std::string COL_DATE_TRANSACTION;
  extern std::string COL_DATE_CREATE;
}

class CApplication;

namespace database::tbl_imm_customerTransactions
{
  struct record_t
  {
    index_t ID;
    tindex_t transactionTypeID;
    index_t customerID;
    date_t transactionDate;
  };

  std::set<workFlowStatus_t> activeStatuses(CApplication &, index_t);
  void createRecord(CApplication &, record_t &);
  void readRecord(CApplication &, record_t &);
  void updateRecord(CApplication &, record_t const &);
}

#endif // TBL_IMM_CUSTOMERTRANSACTIONS_H
