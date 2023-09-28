﻿//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investment Management
// FILE:                processBusinessTransactions.h
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
// OVERVIEW:
//
// HISTORY:             2023-08-31/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef PROCESSBUSINESSTRANSACTIONS_H
#define PROCESSBUSINESSTRANSACTIONS_H

  // msmERP header files

#include "include/database/views/viewTransaction.h"

class CApplication;

namespace IMM
{
  void postTransaction(CApplication &, views::CViewTransaction &);
}

#endif // PROCESSBUSINESSTRANSACTIONS_H