//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                tbl_imm_costTypes
// SUBSYSTEM:           Table definitions for cost types
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
// OVERVIEW:						Table definitions and interface for cost types.
//
// HISTORY:             2023-08-08/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TBL_IMM_COSTTYPES_H
#define TBL_IMM_COSTTYPES_H

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

namespace TBL_IMM_COSTTYPES
{
  extern std::string TABLE;

  extern std::string PK;
  extern std::string FK_ENTERPRISE;
  extern std::string COL_SHORTTEXT;
  extern std::string COL_COSTELEMENTID;
}

namespace database::tbl_imm_costTypes
{
  struct record_t
  {
    index_t ID = 0;
    std::string shortText;
    index_t costElementID;
  };
  using recordSet_t = std::vector<record_t>;

  std::set<workFlowStatus_t> activeStatuses(CApplication &, index_t);

  bool recordExists(CApplication &, std::string const &);
  index_t recordID(CApplication &, std::string const &);

  void createRecord(CApplication &, record_t &);
  void readRecord(CApplication &, record_t &);
  void updateRecord(CApplication &, record_t const &);

} // namespace database



#endif // TBL_IMM_COSTTYPES_H
