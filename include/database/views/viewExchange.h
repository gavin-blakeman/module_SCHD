//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                viewExchange
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
// HISTORY:             2023-07-21/GGB - File created
//
//**********************************************************************************************************************************

#ifndef VIEWEXCHANGE_H
#define VIEWEXCHANGE_H

  // msmERP header files

#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/tbl_imm_exchanges.h"
#include "include/database/views/viewRecord.h"

class CApplication;

namespace views
{
  class CViewExchange : public CViewRecord
  {
  public:
    CViewExchange(CApplication &a) : CViewRecord(a, TBL_CORE_WORKFLOWSTATUS::TABLE) {}

    std::string shortText() const { return record_.shortText; }
    void shortText(std::string const &st) { record_.shortText = st; }

    std::string longText() const { return record_.longText; }
    void longText(std::string const &lt) { record_.longText = lt; }

    std::string suffix() const { return record_.suffix; }
    void suffix(std::string const &s) { record_.suffix = s; }

    sindex_t country() const { return record_.countryID; }
    void country(sindex_t c) { record_.countryID = c; }

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
    virtual objectType_t objectType() const override { return OT_IMM_EXCHANGES; }

  private:
    CViewExchange() = delete;
    CViewExchange(CViewExchange const &) = delete;
    CViewExchange operator=(CViewExchange const &) = delete;

    database::tbl_imm_exchanges::record_t record_;
  };


}

#endif // VIEWEXCHANGE_H
