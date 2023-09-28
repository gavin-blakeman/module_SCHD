//**********************************************************************************************************************************
//
// PROJECT:             Engineering Workshop Tracker (engineeringShop)
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
//                      This file is part of the engineeringShop Project
//
//                      engineeringShop is free software: you can redistribute it and/or modify it under the terms of the GNU
//                      General Public License as published by the Free Software Foundation, either version 2 of the License, or (at
//                      your option) any later version.
//
//                      engineeringShop is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
//                      even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
//                      Public License for more details.
//
//                      You should have received a copy of the GNU General Public License along with engineeringShop.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:
//
// HISTORY:             2022-05-24/GGB - File Created
//
//**********************************************************************************************************************************

#ifndef MODEL_CHARTOFACCOUNTS_H
#define MODEL_CHARTOFACCOUNTS_H

  // Standard C++ library header files

#include <memory>
#include <string>

  // Wt++ framework header files


  // Miscellaneous library headers

#include <SCL>

  // msmERP application header files

#include "include/application.h"
#include "include/core/typeDefinitions.h"
#include "include/database/models/modelCustom.h"

namespace models
{

  class CModelChartOfAccounts : public CModelCustom
  {
  private:
  protected:
  public:
    CModelChartOfAccounts(CApplication &);

    std::any headerData(int section, Wt::Orientation = Wt::Orientation::Horizontal, Wt::ItemDataRole = Wt::ItemDataRole::Display) const;
    void populateModel();


  };

} // namespace models

#endif // MODEL_CHARTOFACCOUNTS_H
