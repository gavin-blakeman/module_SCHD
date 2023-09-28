#ifndef TBL_IMM_SECURITYPRICES_H
#define TBL_IMM_SECURITYPRICES_H

  // Standard C++ library

#include <string>

  // msmERP header files

#include "include/core/typeDefinitions.h"
#include "include/pluginInterface/interfacePriceUpload.h"

namespace TBL_IMM_SECURITYPRICES
{
  extern std::string TABLE;

  extern std::string FK_SECURITY;
  extern std::string COL_DATE;
  extern std::string COL_CLOSE;
}

class CApplication;

namespace database::tbl_imm_securityPrices
{
  struct record_t
  {
    index_t ID;
    std::string shortText;
    index_t costElementID;
  };

  void createRecord(CApplication &, record_t &);
  void createRecords(CApplication &, index_t, IMM::priceUpload::pricesVector_t const &);
  void updateRecord(CApplication &, record_t const &);
  void deleteRecord(CApplication &, record_t const &);
  void readRecord(CApplication &, record_t &);
}

#endif // TBL_IMM_SECURITYPRICES_H
