//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                viewSecurity
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
// HISTORY:             2023-07-2/GGB - File created
//
//**********************************************************************************************************************************

#ifndef VIEWSECURITY_H
#define VIEWSECURITY_H

  // msmERP header files

#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/tbl_imm_securities.h"
#include "include/database/tables/tbl_imm_workflowStatus.h"
#include "include/database/views/viewRecord.h"

class CApplication;

namespace views
{
  class CViewSecurity : public CViewRecord
  {
  public:
    CViewSecurity(CApplication &a) : CViewRecord(a, TBL_IMM_WORKFLOWSTATUS::TABLE) {}

    std::string shortText() const { return record_.shortText; }
    void shortText(std::string const &st) { record_.shortText = st; }

    index_t exchangeID() const { return record_.exchangeID; }
    void exchangeID(index_t eid) { record_.exchangeID = eid; }

    std::string code() const { return record_.code; }
    void code(std::string const &stc) { record_.code= stc; }

    sindex_t currencyID() const { return record_.currencyID; }
    void currencyID(sindex_t cid) { record_.currencyID = cid; }

    std::string longText() const { return record_.longText; }
    void longText(std::string const &lt) { record_.longText = lt; }

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
    virtual objectType_t objectType() const override { return OT_IMM_SECURITIES; }

  private:
    CViewSecurity() = delete;
    CViewSecurity(CViewSecurity const &) = delete;
    CViewSecurity operator=(CViewSecurity const &) = delete;

    database::tbl_imm_securities::record_t record_;
  };


}

#endif // VIEWSECURITY_H
