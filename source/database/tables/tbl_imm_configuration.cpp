#include "include/database/tables/tbl_imm_configuration.h"

  // Standard C++ library

#include <map>

  // msmERP header files

#include "include/application.h"
#include "include/database/tables/core/tbl_settings.h"

namespace database::tbl_imm_configuration
{
  using namespace database::tbl_core_valueTypes;

  struct settings_t
  {
    std::string setting;
    std::string comments;
    valueTypes_e valueTypeID;
  };

  using settingsMap_t = std::map<settings_e, settings_t>;
  using recordMap_t = std::map<settings_e, database::CVariant>;

  recordMap_t recordMap;    // Settings values are cached as they are requested.

  settingsMap_t settingsMap =
  {
    { ACCOUNT_DRIP, { "IMM:Account:DRIP", "Parent for DRIP accounts", VT_U32 }},
    { ACCOUNT_SECURITIES, { "IMM:Account:Securities", "", VT_U32 }},
    { ACCOUNT_TRADING, { "IMM:Account:Trading", "", VT_U32 }},
    { ACCOUNT_INCOME_BONDS, { "IMM:Account:Income:Bonds", "", VT_U32 }},
    { ACCOUNT_INCOME_DIVIDEND, { "IMM:Account:Income::Dividend", "", VT_U32 }},
    { ACCOUNT_INCOME_OTHER, { "IMM:Account:Income:Other", "", VT_U32 }},
    { ACCOUNT_INCOME_LTCG, { "IMM:Account:Income:LTCG", "", VT_U32 }},
    { ACCOUNT_INCOME_STCG, { "IMM:Account:Income:STCG", "", VT_U32 }},
    { ACCOUNT_EXPENSE_BROKERAGE, { "IMM:Account:Expense:Brokerage", "", VT_U32 }},
  };

  void getSetting(CApplication &application, settings_e setting, CVariant &value)
  {
    if (!recordMap.contains(setting))
    {

    }
    value = recordMap[setting];
  }

  void setSetting(CApplication &, settings_e, CVariant const &)
  {

  }


}
