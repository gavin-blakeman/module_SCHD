#include "include/database/tables/tbl_imm_securityPrices.h"

  // Miscellaneous library header files

#include <GCL>

  // msmERP header files

#include "include/application.h"
#include "include/dbe.h"

namespace TBL_IMM_SECURITYPRICES
{
  std::string TABLE = "IMM_securityPrices";

  std::string FK_SECURITY = "SecurityID";
  std::string COL_DATE = "Date";
  std::string COL_CLOSE = "Close";
}

namespace database::tbl_imm_securityPrices
{

  void createRecord(CApplication &, record_t &)
  {

  }

  /// @brief      Stores a number of price records in the database.
  /// @param[in]  application:
  /// @param[in]  securityID:
  /// @param[in]  prices:
  /// @throws
  /// @version    2023-09-23/GGB - Function created.

  void createRecords(CApplication &application, index_t securityID, IMM::priceUpload::pricesVector_t const &prices)
  {
    using namespace TBL_IMM_SECURITYPRICES;
    using namespace GCL;

    sqlWriter sqlQuery;
    sqlWriter::valueStorage_t values;

    sqlQuery.insertInto(TABLE, {FK_SECURITY, COL_DATE, COL_CLOSE});

    for (auto const & price: prices)
    {
      sqlWriter::parameterStorage params = {securityID, price.first, static_cast<decimal_t>(price.second)};
      values.emplace_back(std::move(params));
    }

    sqlQuery.values(std::move(values));

    try
    {
      application.session().exec(sqlQuery);
    }
    catch (GCL::runtime_error &e)
    {
      ERRORMESSAGE(e.what());
    }

  }

  void updateRecord(CApplication &, record_t const &)
  {

  }
  void deleteRecord(CApplication &, record_t const &)
  {

  }
  void readRecord(CApplication &, record_t &)
  {

  }
}
