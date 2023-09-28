//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                tbl_imm_portfolio
// SUBSYSTEM:           Module: Investment Management
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
// OVERVIEW:						Table definitions and interface for metering points.
//
// HISTORY:             2022-07-26/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TBL_IMM_PORTFOLIO_H
#define TBL_IMM_PORTFOLIO_H

  // Standard C++ library

#include <map>
#include <string>

  // Wt++ header files

#include <Wt/WStandardItemModel.h>

  // msmERP header files

#include "include/core/typeDefinitions.h"
#include "include/database/models/modelComboBox.h"
#include "include/database/tables/core/tbl_workflowStatus.h"

class CApplication;

namespace TBL_IMM_PORTFOLIO
{
  extern std::string TABLE;

  extern std::string PK;
  extern std::string FK_ENTERPRISE;
  extern std::string FK_BROKERAGEACCOUNT;
  extern std::string FK_SECURITYLEDGER;
  extern std::string COL_SHORTTEXT;
  extern std::string FK_TRADINGACCOUNT;
  extern std::string FK_DRIPACCOUNT;
}

namespace database::tbl_imm_portfolio
{
  struct record_t
  {
    index_t ID = 0;
    index_t BrokerageAccountID;
    index_t securityLedgerID;
    index_t tradingAccountID;
    index_t DRIPAccountID;
    std::string shortText;
  };
  using recordSet_t = std::vector<record_t>;

  std::set<workFlowStatus_t> activeStatuses(CApplication &, index_t);

  void createRecord(CApplication &, record_t &);
  void readRecord(CApplication &, record_t &);
  index_t tradingAccountID(CApplication &, index_t);
  index_t brokerageAccountID(CApplication &, index_t);
}


#endif // TBL_IMM_PORTFOLIO_H
