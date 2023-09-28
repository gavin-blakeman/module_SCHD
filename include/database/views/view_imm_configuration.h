//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                viewConfiguration
// SUBSYSTEM:           Module: Investement Management
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
// HISTORY:             2023-08-29/GGB - File created
//
//**********************************************************************************************************************************

#ifndef VIEW_IMM_CONFIGURATION_H
#define VIEW_IMM_CONFIGURATION_H

  // Standard C++ header files

#include <map>
#include <string>

  // msmERP header files

#include "include/core/typeDefinitions.h"
#include "include/database/tables/core/tbl_objectTypes.h"

class CApplication;

namespace views
{
  class CViewConfiguration final
  {
  public:
    CViewConfiguration(CApplication &a);

  protected:
    virtual void processLoadData();
    virtual void processSaveData();
    virtual void processClearData() noexcept;
//    virtual void processBusinessTransaction(businessTransaction_e);
//    virtual std::set<businessTransaction_e> processAllowedBusinessTransactions() const ;
//    virtual bool processAllowTransaction(businessTransaction_e) const;
    virtual void processActiveStatus(void) {}
    virtual objectType_t objectType() const { return OT_IMM_CONFIGURATION; }

  private:
    CViewConfiguration() = delete;
    CViewConfiguration(CViewConfiguration const &) = delete;
    CViewConfiguration operator=(CViewConfiguration const &) = delete;
  };
}

#endif // VIEW_IMM_CONFIGURATION_H
