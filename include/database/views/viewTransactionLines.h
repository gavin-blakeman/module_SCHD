//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                viewTransactionLines
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

#ifndef VIEWTRANSACTIONLINES_H
#define VIEWTRANSACTIONLINES_H

  // Standard C++

  // msmERP header files

#include "include/database/views/viewRecord.h"
#include "include/database/tables/tbl_imm_transactionLines.h"
#include "include/database/tables/tbl_imm_workflowStatus.h"
#include "include/database/tables/core/tbl_objectTypes.h"

class CApplication;

namespace views
{
  class CViewTransactionLines final : public CViewRecord
  {
  public:
    CViewTransactionLines() = default;
    CViewTransactionLines &operator=(CViewTransactionLines const &) noexcept;
    CViewTransactionLines(CViewTransactionLines const &) = default;
    CViewTransactionLines(CViewTransactionLines &&other) = default;
    CViewTransactionLines(CApplication &a) : CViewRecord(a, TBL_IMM_WORKFLOWSTATUS::TABLE) { clearData(); }
    CViewTransactionLines(CApplication &a, database::tbl_imm_transactionLines::record_t const &r) : CViewRecord(a, TBL_CORE_WORKFLOWSTATUS::TABLE), record_(r) {}

    void transactionID(index_t tid) { record_.transactionID = tid; dirty(); }
    index_t transactionID() const { return record_.transactionID; }

    void sortOrder(index_t so) { record_.sortOrder = so; dirty(); }
    index_t sortOrder() const { return record_.sortOrder; }

    void typeID(index_t cid) { record_.costTypeID = cid; dirty(); }
    index_t typeID() const { return record_.costTypeID; }

    void value(money_t v) { record_.value = v; dirty(); }
    money_t value() const { return record_.value; }

    void shortText(std::string const &st) { record_.shortText = st; dirty(); }
    std::string const &shortText() const { return record_.shortText; }

  protected:
    virtual void processLoadData() override;
    virtual void processSaveData() override;
    virtual void processClearData() noexcept override;
    virtual void processBusinessTransaction(businessTransaction_e) override {};
    virtual std::set<businessTransaction_e> processAllowedBusinessTransactions() const override {};
    virtual void processID(index_t i) override { record_.ID = i; }
    virtual index_t processID() const override { return record_.ID; }
    virtual bool processAllowTransaction(businessTransaction_e) const override {};
    virtual void processActiveStatus() override {};
    virtual constexpr objectType_t objectType() const noexcept override { return OT_IMM_TRANSACTIONLINES; }

  private:
    database::tbl_imm_transactionLines::record_t record_;

  };
}


#endif // VIEWTRANSACTIONLINES_H
