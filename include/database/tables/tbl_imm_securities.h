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

#ifndef TBL_IMM_SECURITIES_H
#define TBL_IMM_SECURITIES_H

  // Standard C++ library header files.

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

  // Miscellaneous library header files

#include <SCL>

  // msmERP Application header files

#include "include/dbe.h"
#include "include/core/typeDefinitions.h"
#include "include/database/tables/core/tbl_workflowStatus.h"

class CApplication;

namespace TBL_IMM_SECURITIES
{
  extern std::string TABLE;

  extern std::string PK;
  extern std::string FK_EXCHANGE;
  extern std::string FK_CURRENCY;
  extern std::string COL_SHORTTEXT;
  extern std::string COL_LONGTEXT;
  extern std::string COL_SYMBOL;
}

namespace database::tbl_imm_securities
{
  struct record_t
  {
    index_t ID = 0;
    index_t exchangeID;
    std::string shortText;
    std::string code;
    sindex_t currencyID;
    std::string longText;
  };
  using recordSet_t = std::vector<record_t>;

  std::set<workFlowStatus_t> activeStatuses(CApplication &, index_t);
  void createRecord(CApplication &, record_t &);
  void readRecord(CApplication &, record_t &);
  void updateRecord(CApplication &, record_t const &);
  std::string shortText(CApplication &, index_t);
  index_t recordSymbol(CApplication &, index_t, std::string const &);

} // namespace database


#endif // TBL_IMM_SECURITIES_H
