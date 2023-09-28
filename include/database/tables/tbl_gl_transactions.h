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
// OVERVIEW:
//
// HISTORY:             2022-05-02/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TBL_GL_TRANSACTIONS_H
#define TBL_GL_TRANSACTIONS_H

  // Standard C++ library header files.

#include <cstdint>
#include <string>
#include <vector>

  // Wt++ framework header files

#include <Wt/WDate.h>

  // msmERP header files

#include "include/dbe.h"
#include "include/core/typeDefinitions.h"


namespace TBL_GL_TRANSACTIONS
{
  extern std::string TABLE;

  extern std::string PK;
  extern std::string COL_POSTDATE;
  extern std::string COL_ENTERDATE;
  extern std::string COL_SHORTTEXT;

  inline std::string qCol(std::string const &col)
  {
    return TABLE + "." + col;
  }
}

class CApplication;

namespace database::tbl_gl_transactions
{
  struct record_t
  {
    index_t ID;
    date_t postDate;
    std::string shortText;
  };

  void insertRecord(CApplication &, record_t &);
  void updateRecord(CDatabaseSession &, std::int8_t, std::int32_t, std::int32_t, bool);

} // namespace database


#endif // TBL_MAINTENANCESCHEDULEMODIFICATIONS_H
