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

#ifndef TBL_IMM_TRADINGLEDGER_H
#define TBL_IMM_TRADINGLEDGER_H

  // Standard C++ library

#include <map>
#include <string>
#include <vector>

  // msmERP header files

#include "include/core/typeDefinitions.h"

class CApplication;

namespace TBL_IMM_TRADINGLEDGER
{
  extern std::string TABLE;

  extern std::string PK;
  extern std::string FK_PORTFOLIO;
  extern std::string FK_SECURITY;
  extern std::string COL_QTY;
  extern std::string COL_VALUE;
  extern std::string COL_TRANSACTIONDATE;
  extern std::string COL_CREATEDATE;
}

namespace database::tbl_imm_tradingLedger
{
  struct record_t
  {
    index_t ID = 0;
    index_t portfolioID = 0;
    index_t securityID = 0;
    decimal_t quantity = 0.0;
    money_t value;
    date_t transactionDate;
  };
  using securityRecords_t = std::vector<record_t>;
  using portfolioRecords_t = std::map<index_t, securityRecords_t>;

  void createRecord(CApplication &, record_t &);
  void readRecord(CApplication &, record_t &);
  void readRecordsSecurity(CApplication &, index_t, index_t, securityRecords_t);
  void readRecordsPortfolio(CApplication &, index_t, portfolioRecords_t &);
}

#endif // TBL_IMM_TRADINGLEDGER_H
