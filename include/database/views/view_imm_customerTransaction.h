//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                view_imm_customerTransaction.h
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

#ifndef VIEW_IMM_CUSTOMERTRANSACTION_H
#define VIEW_IMM_CUSTOMERTRANSACTION_H

  // Standard C++ library

#include <string>
#include <vector>

  // msmERP header files

#include "include/core/typeDefinitions.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/tbl_imm_customerTransactions.h"
#include "include/database/tables/tbl_imm_workflowStatus.h"
#include "include/database/views/viewRecord.h"
#include "include/database/views/view_imm_customerTransactionLines.h"

class CApplication;

namespace views
{
  class CViewCustomerTransaction final: public CViewRecord
  {
  public:
    CViewCustomerTransaction(CApplication &a) : CViewRecord(a, TBL_IMM_WORKFLOWSTATUS::TABLE) {}

    tindex_t transactionTypeID() const { return record_.transactionTypeID; }
    void transactionTypeID(tindex_t ttid) { record_.transactionTypeID = ttid; }

    index_t customerID() const { return record_.customerID; }
    void customerID(index_t cid) { record_.customerID = cid; }

    date_t transactionDate() const { return record_.transactionDate; }
    void transactionDate(date_t const &dt) { record_.transactionDate = dt; }

    money_t totalValue() const;

    CViewCustomerTransactionLines *createLine();
    void deleteLine(std::size_t);
    CViewCustomerTransactionLines &transactionLine(std::size_t);
    std::size_t transactionLineCount() { return transactionLines_.size(); }

  protected:
    virtual void processLoadData() override;
    virtual void processSaveData() override;
    virtual void processClearData() noexcept override;
    virtual void processBusinessTransaction(businessTransaction_e) override;
    virtual std::set<businessTransaction_e> processAllowedBusinessTransactions() const override;
    virtual void processID(index_t id)  override { record_.ID = id; }
    virtual index_t processID() const  override { return record_.ID; }
    virtual bool processAllowTransaction(businessTransaction_e) const override;
    virtual void processActiveStatus() override;
    virtual constexpr objectType_t objectType() const noexcept override { return OT_IMM_CUSTOMERTRANSACTION; }

  private:
    CViewCustomerTransaction() = delete;
    CViewCustomerTransaction(CViewCustomerTransaction const &) = delete;
    CViewCustomerTransaction operator=(CViewCustomerTransaction const &) = delete;

    database::tbl_imm_customerTransactions::record_t record_;
    std::vector<CViewCustomerTransactionLines> transactionLines_;
    std::vector<CViewCustomerTransactionLines> deletedtransactionLines_;
  };


}

#endif // VIEW_IMM_CUSTOMERTRANSACTION_H
