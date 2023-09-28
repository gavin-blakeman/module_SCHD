//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investement Management
// FILE:                viewTransaction
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

#ifndef VIEW_IMM_TRANSACTION_H
#define VIEW_IMM_TRANSACTION_H

  // Standard C++ library

#include <string>
#include <vector>

  // msmERP header files

#include "include/core/typeDefinitions.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/tbl_imm_transactions.h"
#include "include/database/tables/tbl_imm_workflowStatus.h"
#include "include/database/views/viewRecord.h"
#include "include/database/views/viewTransactionLines.h"


class CApplication;

namespace views
{
  class CViewTransaction final: public CViewRecord
  {
  public:
    CViewTransaction(CApplication &a) : CViewRecord(a, TBL_IMM_WORKFLOWSTATUS::TABLE) {}

    index_t portfolioID() const { return record_.portfolioID; }
    void portfolioID(index_t pid) { record_.portfolioID = pid; }

    index_t securityID() const { return record_.securityID; }
    void securityID(index_t sid) { record_.securityID = sid; }
    std::string security();

    tindex_t transactionTypeID() const { return record_.transactionTypeID; }
    void transactionTypeID(tindex_t ttid) { record_.transactionTypeID = ttid; }

    date_t postingDate() const { return record_.postingDate; }
    void postingDate(date_t const &dt) { record_.postingDate = dt; }

    decimal_t quantity() const { return record_.quantity; }
    void quantity(decimal_t const &qty) { record_.quantity = qty; }

    money_t price() const { return record_.price; }
    void price(money_t const &prc) { record_.price = prc; }

    money_t totalCost() const;
    money_t securityCost() const;
    money_t brokerageCost() const;

    CViewTransactionLines *createLine();
    void deleteLine(std::size_t);
    CViewTransactionLines &transactionLine(std::size_t);
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
    virtual constexpr objectType_t objectType() const noexcept override { return OT_IMM_TRANSACTION; }

  private:
    CViewTransaction() = delete;
    CViewTransaction(CViewTransaction const &) = delete;
    CViewTransaction operator=(CViewTransaction const &) = delete;

    database::tbl_imm_transactions::record_t record_;
    std::vector<CViewTransactionLines> transactionLines_;
    std::vector<CViewTransactionLines> deletedtransactionLines_;
  };


}

#endif // VIEW_IMM_TRANSACTION_H
