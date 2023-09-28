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

#include "include/database/views/view_imm_customerTransaction.h"

  // Standard C++ library

#include <functional>

  // msmERP header files.

#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/tbl_imm_securities.h"
#include "include/database/tables/tbl_imm_transactions.h"
#include "include/database/tables/tbl_imm_transactionLines.h"

namespace views
{

  void CViewCustomerTransaction::processActiveStatus()
  {

  }

  /// @brief      Returns a set containing the allowed business transactions based on the current status train.
  /// @returns    Set containing the allowed busines transactions.
  /// @throws
  /// @version    2023-08-31/GGB - Function created.

  std::set<businessTransaction_e> CViewCustomerTransaction::processAllowedBusinessTransactions() const
  {
    /* SC_DELETED -> None
   * SC_NONE    -> SC_CREATED (Handled by save)
   * SC_CREATED -> BT_DELETE
   *            -> BT_POST
   *  SC_POSTED -> BT_ROLLBACK
   *  Note: Only 1 active status allowd at a time.
   */

    std::set<businessTransaction_e> rv;

    if (activeStatus_.contains(SC_CREATED))
    {
      rv.emplace(BT_DELETE);
      rv.emplace(BT_POST);
    }
    else if (activeStatus_.contains(SC_POSTED))
    {
      rv.emplace(BT_ROLLBACK);
    };

    return rv;
  }

  /// @brief      Processes the specified business transaction for the current transaction.
  /// @param[in]  bt: The transaction to process.
  /// @throws
  /// @version    2023-08-31/GGB - Function created.

  void CViewCustomerTransaction::processBusinessTransaction(businessTransaction_e bt)
  {
    switch (bt)
    {
      case BT_DELETE:
      {
        break;
      }
      case BT_POST:
      {
        break;
      }
      default:
      {
        CODE_ERROR;
        break;
      }
    }
  }

  /// @brief      Checks to see if the specfied business transaction is allowed.
  /// @returns    true - Editing is allowed.
  /// @throws     None.
  /// @version    2023-07-25/GGB - Function created.

  bool CViewCustomerTransaction::processAllowTransaction(businessTransaction_e businessTransaction) const
  {
    bool returnValue = false;
    switch (lastStatusCode())
    {
      case SC_NONE:
      case SC_CREATED:
      {
        returnValue = true;
        break;
      }
      default:
      {
      }
    }

    return returnValue;
  }

  /// @brief      Clears all data. (As when creating a new record)
  /// @throws
  /// @version    2023-07-25/GGB - Function created.

  void CViewCustomerTransaction::processClearData() noexcept
  {
    record_.ID = 0;
    record_.transactionTypeID = 0;
    record_.customerID = 0;
    //record_.transactionDate = std::chrono::n

    transactionLines_.clear();
  }


  /// @brief    Create a new transaction line.
  /// @throws
  /// @version  2023-09-19/GGB - Function created.

  CViewCustomerTransactionLines *CViewCustomerTransaction::createLine()
  {
    transactionLines_.emplace_back(application());
    transactionLines_.back().transactionID(ID());

    return &transactionLines_.back();
  }

  /// @brief      Deletes teh specified transaction line.
  /// @param[in]  index: The index of the line to delete.
  /// @throws
  /// @version    2023-07-25/GGB - Function created.

  void CViewCustomerTransaction::deleteLine(std::size_t index)
  {
    RUNTIME_ASSERT(index < transactionLines_.size(), "index needs to be less than the size of the container.");

    if (transactionLines_[index].ID() != 0)
    {
      deletedtransactionLines_.emplace_back(transactionLines_[index]);
    };

    transactionLines_.erase(transactionLines_.begin() + index);
  }

  /// @brief      Loads the data from the database.
  /// @throws
  /// @version    2023-07-25/GGB - Function created.

  void CViewCustomerTransaction::processLoadData()
  {
    using namespace database;

    tbl_imm_customerTransactions::readRecord(application(), record_);

    tbl_imm_customerTransactionLines::records_t lines;
    tbl_imm_customerTransactionLines::readRecords(application(), ID(), lines);

    transactionLines_.clear();

    for (auto const &line: lines)
    {
      transactionLines_.emplace_back(application(), line);
    }

    dirty_ = false;
  }

  /// @brief      Saves the timesheet data
  /// @version    2023-07-25/GGB - Function created.

  void CViewCustomerTransaction::processSaveData()
  {
    using namespace database;

    if (ID() != 0)
    {
      tbl_imm_customerTransactions::updateRecord(application(), record_);
    }
    else
    {
      tbl_imm_customerTransactions::createRecord(application(), record_);

      std::for_each(transactionLines_.begin(), transactionLines_.end(), [this](CViewCustomerTransactionLines &l)
      {
        l.transactionID(ID());
      });
    }

    std::for_each(transactionLines_.begin(), transactionLines_.end(), std::mem_fn(&CViewCustomerTransactionLines::saveData));

    updateStatus(SC_CREATED);

    dirty_ = false;
  }

  /// @brief      Returns a const reference to the specified timesheet line.
  /// @param[in]  line: Number of the line to return.
  /// @returns    A reference to the line.
  /// @throws
  /// @version    2023-07-25/GGB - Function created.

  CViewCustomerTransactionLines &CViewCustomerTransaction::transactionLine(std::size_t line)
  {
    return transactionLines_[line];
  }

  /// @brief      Calculate the total costs for the tranaction.
  /// @throws
  /// @version    2023-08-08/GGB - Function created.

  money_t CViewCustomerTransaction::totalValue() const
  {
    //return brokerageCost() + securityCost();
  }

}

