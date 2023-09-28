//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                view_imm_customerTransactionLines.cpp
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
// OVERVIEW:
//
// HISTORY:             2023-09-19/GGB - File created
//
//**********************************************************************************************************************************

#include "include/database/views/view_imm_customerTransactionLines.h"

  // msmERP

#include "include/database/tables/humanResources/tbl_timeSheetLines.h"

namespace views
{

  /// @brief      Operator = implementation. Copies the records.
  /// @param[in]  other: The element to copy.
  /// @throws
  /// @version    2023-08-08/GGB - Function created.

  CViewCustomerTransactionLines &CViewCustomerTransactionLines::operator=(CViewCustomerTransactionLines const &other) noexcept
  {
    if (this != &other)
    {

      CViewRecord::operator =(other);
      record_ = other.record_;
    }

    return *this;
  }

  /// @brief      Clears the data
  /// @version    2023-09-19/GGB - Function created.

  void CViewCustomerTransactionLines::processClearData() noexcept
  {
    record_.ID = 0;
    record_.customerTransactionID = 0;
    record_.sortOrder = 0;
    record_.portfolioID = 0;
    record_.quantity = 0;
    record_.value = 0;
  }

  void CViewCustomerTransactionLines::processLoadData()
  {

  }


  /// @brief      Save the transaction line,
  /// @version    2023-07-25/GGB - Function created.

  void CViewCustomerTransactionLines::processSaveData()
  {
    //database::tbl_timesheetLines::insertRecord(application(), record_);
  }

}
