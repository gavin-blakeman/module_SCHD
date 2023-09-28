#ifndef MODELEDITCHARTOFACCOUNTS_H
#define MODELEDITCHARTOFACCOUNTS_H

  // Standard C++ library header files

#include <memory>
#include <string>

  // Wt++ framework header files

  // Miscellaneous library headers

#include <SCL>

  // msmERP application header files

#include "include/application.h"
#include "include/core/typeDefinitions.h"
#include "include/database/models/modelCustom.h"

namespace models
{

  class CModelEditChartOfAccounts : public CModelCustom
  {
  private:
    CModelEditChartOfAccounts() = delete;
    CModelEditChartOfAccounts(CModelEditChartOfAccounts const &) = delete;
    CModelEditChartOfAccounts &operator=(CModelEditChartOfAccounts const &) = delete;

  protected:
  public:
    CModelEditChartOfAccounts(CApplication &);

    void reload();
  };

} // namespace models

#endif // MODELEDITCHARTOFACCOUNTS_H
