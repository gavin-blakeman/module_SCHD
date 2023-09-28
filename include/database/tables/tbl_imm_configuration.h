#ifndef TBL_IMM_CONFIGURATION_H
#define TBL_IMM_CONFIGURATION_H

  // Standard C++ library

#include <string>

  // msmERP header files

#include "include/core/typeDefinitions.h"
#include "include/database/database/databaseVariant.h"
#include "include/database/tables/core/tbl_core_valueTypes.h"

class CApplication;

namespace database::tbl_imm_configuration
{
  enum settings_e
  {
    ACCOUNT_DRIP,
    ACCOUNT_SECURITIES,
    ACCOUNT_TRADING,
    ACCOUNT_INCOME_BONDS,
    ACCOUNT_INCOME_DIVIDEND,
    ACCOUNT_INCOME_OTHER,
    ACCOUNT_INCOME_LTCG,
    ACCOUNT_INCOME_STCG,
    ACCOUNT_EXPENSE_BROKERAGE,
  };

  void getSetting(CApplication &, settings_e, CVariant &);
  void setSetting(CApplication &, settings_e, CVariant const &);
}

#endif // TBL_IMM_CONFIGURATION_H
