//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                tbl_imm_securityTypes
// SUBSYSTEM:           Investment Management Module
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
// OVERVIEW:						Classes for interating with the financial years table.
//
// HISTORY:             2023-07-23/GGB - Start Project
//
//**********************************************************************************************************************************

#ifndef TBL_IMM_SECURITYTYPES_H
#define TBL_IMM_SECURITYTYPES_H

  // Standard C++ library header files

#include <cstdint>
#include <map>
#include <string>

  // Wt++

#include <Wt/WStandardItemModel.h>

  // msmERP Application header files

#include "include/core/typeDefinitions.h"
#include "include/database/database/session.h"

class CApplication;

namespace database::tbl_imm_securityTypes
{

  enum securityType_t: sindex_t
  {
    ST_NONE         = 0,
    ST_GOV_BONDS    = 1,
    ST_CORP_BONDS   = 2,
    ST_SHARES       = 3,
  };


  using securityTypeMap_t = std::map<securityType_t, std::string>;

  extern securityTypeMap_t securityTypeMap;

  std::string const &shortText(securityType_t);
  void createModel(CDatabaseSession &, Wt::WStandardItemModel &);

} // namespace database

#endif // TBL_IMM_SECURITYTYPES_H
