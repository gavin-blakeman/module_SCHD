//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                view_imm_customerTransactionLines.h
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

#ifndef VIEW_IMM_CUSTOMERTRANSACTIONLINES_H
#define VIEW_IMM_CUSTOMERTRANSACTIONLINES_H

  // Standard C++

  // msmERP header files

#include "include/database/views/viewRecord.h"
#include "include/database/tables/tbl_imm_customerTransactionLines.h"
#include "include/database/tables/tbl_imm_workflowStatus.h"
#include "include/database/tables/core/tbl_objectTypes.h"

class CApplication;

namespace views
{
  class CViewCustomerTransactionLines final : public CViewRecord
  {
  public:
    CViewCustomerTransactionLines() = default;
    CViewCustomerTransactionLines &operator=(CViewCustomerTransactionLines const &) noexcept;
    CViewCustomerTransactionLines(CViewCustomerTransactionLines const &) = default;
    CViewCustomerTransactionLines(CViewCustomerTransactionLines &&other) = default;
    CViewCustomerTransactionLines(CApplication &a) : CViewRecord(a, TBL_IMM_WORKFLOWSTATUS::TABLE) { clearData(); }
    CViewCustomerTransactionLines(CApplication &a, database::tbl_imm_customerTransactionLines::record_t const &r)
      : CViewRecord(a, TBL_IMM_WORKFLOWSTATUS::TABLE), record_(r) {}

    void transactionID(index_t tid) { record_.customerTransactionID= tid; dirty(); }
    index_t transactionID() const { return record_.customerTransactionID; }

    void sortOrder(tindex_t so) { record_.sortOrder = so; dirty(); }
    tindex_t sortOrder() const { return record_.sortOrder; }

    index_t portfolioID() const { return record_.portfolioID; }
    void portfolioID(index_t pid) { record_.portfolioID = pid; }

    void quantity(decimal_t v) { record_.quantity= v; dirty(); }
    decimal_t quantity() const { return record_.quantity; }

    void value(money_t v) { record_.value = v; dirty(); }
    money_t value() const { return record_.value; }

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
    database::tbl_imm_customerTransactionLines::record_t record_;

  };
}


#endif // VIEW_IMM_CUSTOMERTRANSACTIONLINES_H
