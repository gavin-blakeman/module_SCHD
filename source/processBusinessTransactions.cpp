//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investment Management
// FILE:                processBusinessTransactions.h
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
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
// HISTORY:             2023-08-31/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/processBusinessTransactions.h"

  // Miscellaneous library header files

#include <GCL>

  // msmERP header files

#include "include/application.h"
#include "include/database/database/session.h"
#include "include/ledgerTransaction.h"
#include "include/database/tables/tbl_imm_portfolio.h"
#include "include/database/tables/tbl_imm_transactionTypes.h"
#include "include/database/tables/tbl_imm_tradingLedger.h"

namespace IMM
{
  static void postTransactionBuy(CApplication &, views::CViewTransaction &);


  /// @brief      Processes the specified transaction.
  /// @param[in]  application: Application instance.
  /// @param[in]  ttp: Transaction to process.
  /// @throws
  /// @version    2023-08-31/GGB - Function created.

  void postTransaction(CApplication &application, views::CViewTransaction &ttp)
  {
    using namespace database::tbl_imm_transactionTypes;

    switch (ttp.transactionTypeID())
    {
      case TT_BUY:
      {
        postTransactionBuy(application, ttp);
        break;
      }
      case TT_SELL:
      case TT_DIVIDEND:
      case TT_INTEREST:
      default:
      {
        CODE_ERROR();
        break;
      }
    }
  }


  /// @brief      Processes a buy specified transaction.
  /// @param[in]  application: Application instance.
  /// @param[in]  ttp: Transaction to process.
  /// @throws
  /// @version    2023-08-31/GGB - Function created.

  void postTransactionBuy(CApplication &application, views::CViewTransaction &ttp)
  {
    using namespace database;

    tbl_imm_portfolio::record_t portfolioRecord;

    portfolioRecord.ID = ttp.portfolioID();
    tbl_imm_portfolio::readRecord(application, portfolioRecord);

      /* Two parts to the transaction.
       *  Financial:
       *    > Post total cost to the Trading Account (Portfolio) (C)
       *    > Post any costs to the relevant expenses accounts (Portfolio, Security) (D)
       *    > Post the security to the investment account (Portfolio) (D)
       *
       *  Investment Management:
       *    > Post the transaction to the trading ledger.
       */

      /* Financial */

    FM::ledgerTransaction_t ledgerTransaction;
    ledgerTransaction.transaction.postDate = ttp.postingDate();
    ledgerTransaction.transaction.shortText = "Share Purchase: " + ttp.security();

      // Trading account: Full amount to be credited.

    ledgerTransaction.transactionLines.emplace_back(0,
                                                    0,
                                                    portfolioRecord.tradingAccountID,
                                                    "",
                                                    -ttp.totalCost());

      // BrokerageAccount: Share Value to be debited.

    ledgerTransaction.transactionLines.emplace_back(0,
                                                    0,
                                                    portfolioRecord.BrokerageAccountID,
                                                    "",
                                                    ttp.securityCost());

      // Now the additional costs lines.

    for (std::size_t indx = 0; indx < ttp.transactionLineCount(); indx++)
    {
//      ledgerTransaction.transactionLines.emplace_back(0,
//                                                      0,
//                                                      ttp.transactionLine(indx).
//                                                      )
    }


  //  index_t ID;
  //  index_t transactionID;
  //  index_t accountID;
  //  std::string shortText;
  //  money_t value;

      /* Trading Transactons */

    tbl_imm_tradingLedger::record_t tradeRecord;
    tradeRecord.portfolioID = ttp.portfolioID();
    tradeRecord.securityID = ttp.securityID();
    tradeRecord.transactionDate = ttp.postingDate();
    tradeRecord.quantity = ttp.quantity();
    tradeRecord.value = ttp.totalCost();

    try
    {
      CDatabaseSession session;

      //FM::processLedgerTransaction(application, ledgerTransaction);
      tbl_imm_tradingLedger::createRecord(application, tradeRecord);
    }
    catch(...)
    {

    }
  }


}
