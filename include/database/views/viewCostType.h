//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                viewCostType
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
// HISTORY:             2023-07-25/GGB - File created
//
//**********************************************************************************************************************************

#ifndef VIEWCOSTTYPE_H
#define VIEWCOSTTYPE_H

  // msmERP header files

#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/tbl_imm_costTypes.h"
#include "include/database/views/viewRecord.h"

class CApplication;

namespace views
{
  class CViewCostType : public CViewRecord
  {
  public:
    CViewCostType(CApplication &a) : CViewRecord(a, TBL_CORE_WORKFLOWSTATUS::TABLE) {}

    std::string shortText() const { return record_.shortText; }
    void shortText(std::string const &st) { record_.shortText = st; }

    index_t costElement() const { return record_.costElementID; }
    void costElement(index_t ci) { record_.costElementID = ci; }

  protected:
    virtual void processLoadData() override;
    virtual void processSaveData() override;
    virtual void processClearData() noexcept override;
    virtual void processBusinessTransaction(businessTransaction_e) override;
    virtual std::set<businessTransaction_e> processAllowedBusinessTransactions() const override;
    virtual void processID(index_t id)  override { record_.ID = id; }
    virtual index_t processID() const  override { return record_.ID; }
    virtual bool processAllowTransaction(businessTransaction_e) const override;
    virtual void processActiveStatus(void) override;
    virtual objectType_t objectType() const override { return OT_IMM_COSTTYPES; }

  private:
    CViewCostType() = delete;
    CViewCostType(CViewCostType const &) = delete;
    CViewCostType operator=(CViewCostType const &) = delete;

    database::tbl_imm_costTypes::record_t record_;
  };


}

#endif // VIEWCOSTTYPE_H
