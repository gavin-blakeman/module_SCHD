﻿//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                tbl_imm_customerTransactionTypes
// SUBSYSTEM:           Module: Investment Management
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
// HISTORY:             2023-09-17/GGB - File created
//
//**********************************************************************************************************************************

#ifndef TBL_IMM_CUSTOMERTRANSACTIONTYPE_H
#define TBL_IMM_CUSTOMERTRANSACTIONTYPE_H

  // Standard C++ library

#include <map>
#include <set>
#include <string>

  // msmERP header files

#include "include/dbe.h"
#include "include/core/typeDefinitions.h"
#include "include/database/models/modelComboBox.h"

class CApplication;

namespace database::tbl_imm_customerTransactionTypes
{
  enum customerTransactionType_t : tindex_t
  {
    CTT_NONE = 0,
    CTT_INVEST = 1,
    CTT_REDEAM = 2,
  };


  void createModel(CApplication &, models::CModelComboBox<tindex_t> &model);
  std::string const &shortText(CApplication &, customerTransactionType_t);
}

#endif // TBL_IMM_CUSTOMERTRANSACTIONTYPE_H
