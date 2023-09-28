#include "include/database/models/modelSecurities.h"

  // Standard C++ library

#include <memory>

  // Miscellaneous libraries

#include <GCL>

  // msmERP header files

#include "include/application.h"
#include "include/dbe.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/core/tbl_statusCodes.h"
#include "include/database/tables/core/tbl_workflowStatus.h"
#include "include/database/tables/tbl_imm_securities.h"

namespace models
{
  /// @brief      Returns the number of columns in the model.
  /// @param[in]  parent:
  /// @returns    The number of columns in the model.
  /// @throws
  /// @version    2023-03-27/GGB - Function created.

  int CModelSecurities::columnCount(const Wt::WModelIndex &/*parent*/) const
  {
    int rv;

    switch (modelUsage)
    {
      case MU_COMBO_NULL:
      {
        rv = 2;
        break;
      };
      case MU_TABLE:
      {
        rv = 3;
        break;
      }
      default:
      {
        CODE_ERROR();
        break;
      }
    };

    return rv;
  }

  /// @brief      Function to return the data for the specified index.
  /// @param[in]  index: The index for the data.
  /// @param[in]  role: The role being queried.
  /// @returns    The data to display
  /// @throws
  /// @version    2023-07-27/GGB - Function created.

  std::any CModelSecurities::data(const Wt::WModelIndex &index, Wt::ItemDataRole role) const
  {
    std::any rv;

    std::size_t row = static_cast<std::size_t>(index.row());
    std::size_t column = static_cast<std::size_t>(index.column());

    switch (column)
    {
      case 0:
      {
        switch (role.value())
        {
          case Wt::ItemDataRole::Display:
          {
            switch(modelUsage)
            {
              case MU_COMBO_NULL:
              {
                if (row == 0)
                {
                  rv = "---";
                }
                else
                {
                  rv = records_[row-1].shortText;
                }
                break;
              }
              case MU_COMBO_NO_NULL:
              case MU_TABLE:
              {
                rv = records_[row].code;
                break;
              }
              default:
              {
                CODE_ERROR();
                break;
              }
            }
            break;
          };
          default:
          {
            //CODE_ERROR();
            break;
          }
        }
        break;
      }
      case 1:
      {
        switch (role.value())
        {
          case Wt::ItemDataRole::Display:
          {
            switch (modelUsage)
            {
              case MU_COMBO_NO_NULL:
              {
                break;
              }
              case MU_TABLE:
              {
                rv = records_[row].shortText;
                break;
              }
              default:
              {
                CODE_ERROR();
                break;
              }
            };
            break;
          };
          default:
          {
            break;
          };
        }
        break;
      };
      case 2:
      {
        switch (role.value())
        {
          case MU_TABLE:
          {
            rv = records_[row].enabled;
            break;
          }
          default:
          {
            break;
          };
        }
        break;
      }
      default:
      {
        CODE_ERROR();
        break;
      }
    }

    return rv;
  }

  /// @brief      Returns the item flags for the model. This is overloaded as the item flags need to be modified for different
  ///             cells in the model. The Cells corresponding to unallowed assignments need to be changed to not allow values.
  /// @param[in]  index: The index to get the flags for.
  /// @returns    The applicable item flags.
  /// @version    2023-03-27/GGB - Function created.

  Wt::WFlags<Wt::ItemFlag> CModelSecurities::flags(const Wt::WModelIndex &index) const
  {
    Wt::WFlags<Wt::ItemFlag> rv;

    std::size_t row = static_cast<std::size_t>(index.row());
    std::size_t column = static_cast<std::size_t>(index.column());

    switch (column)
    {
      case 0:
      case 1:
      case 2:
      {
        switch(modelUsage)
        {
          case MU_COMBO_NO_NULL:
          case MU_COMBO_NULL:
          case MU_TABLE:
          {
            rv = Wt::WFlags<Wt::ItemFlag>(Wt::ItemFlag::Selectable);
            break;
          }
          default:
          {
            CODE_ERROR();
            break;
          }
        }
        break;
      }
      default:
      {
        CODE_ERROR();
        break;
      }
    };

    return rv;
  }

  /// @brief      Returns the row or column header data.
  /// @param[in]  section: The row or column number to retrieve.
  /// @param[in]  orientation: Vertical is the row headers, Horizontal for column headers.
  /// @param[in]  role: The data role.
  /// @throws     std::runtime_error
  /// @version    2023-07-23/GGB - Function created.

  std::any CModelSecurities::headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const
  {
    std::any returnValue;

    if (orientation == Wt::Orientation::Horizontal)
    {
      switch (role.value())
      {
        case Wt::ItemDataRole::Display:
        {
            // Column Headers. The column headers need to be reversed and the highest (last) value needs to be dropped.

          switch (section)
          {
            case 0:
            {
              returnValue = "Code";
              break;
            };
            case 1:
            {
              returnValue = "Security";
              break;
            };
            case 2:
            {
              returnValue = "Enabled";
              break;
            }
            default:
            {
              CODE_ERROR();
            }
          };
          break;
        };
      };
    }
    else
    {
      CODE_ERROR();
    };

    return returnValue;
  }

  /// @brief      Returns the child index for the given row and column.
  /// @param[in]  row:
  /// @param[in]  column:
  /// @param[in]  parent:
  /// @returns    The child index for the given row and column.
  /// @throws
  /// @version    2023-07-23/GGB - Function created.

  Wt::WModelIndex CModelSecurities::index(int row, int column, const Wt::WModelIndex &/*parent*/) const
  {
    Wt::WModelIndex rv;

    switch (modelUsage)
    {
      case MU_COMBO_NO_NULL:
      case MU_COMBO_NULL:
      case MU_TABLE:
      {
        rv = createIndex(row, column, nullptr);
        break;
      }
      default:
      {
        CODE_ERROR();
        break;
      }
    }

    return rv;

  }


  Wt::WModelIndex CModelSecurities::parent(const Wt::WModelIndex &/*index*/) const
  {
    return Wt::WModelIndex();
  }

  /// @brief      Updates the model with information from the database.
  /// @throws
  /// @version    2023-07-23/GGB - Function created.

  void CModelSecurities::reload()
  {
    using namespace TBL_IMM_SECURITIES;
    using namespace GCL;

    sqlWriter sqlQuery;
    sqlQuery
        .select({PK, COL_SHORTTEXT, COL_SYMBOL })
        .from(TABLE)
        .where(FK_EXCHANGE, eq, exchangeID_)
        .orderBy(COL_SYMBOL, ASC);

    try
    {
      database::CRecordSet recordSet = application().session().recordSet(sqlQuery);

      clear();
      records_.clear();

      for (auto const &record: recordSet)
      {
        switch (modelUsage)
        {
          case MU_COMBO_NULL:
          {
            records_.emplace_back(static_cast<index_t>(record[0]), record[1].toString(), record[2].toString(),
                database::tbl_imm_securities::activeStatuses(application(), static_cast<sindex_t>(record[0])).contains(SC_ACTIVE));
            addItem(records_.size(), static_cast<index_t>(record[0]));
            break;
          };
          case MU_TABLE:
          {
            addItem(records_.size(), static_cast<index_t>(record[0]));
            records_.emplace_back(static_cast<index_t>(record[0]), record[1].toString(), record[2].toString(),
                database::tbl_imm_securities::activeStatuses(application(), static_cast<sindex_t>(record[0])).contains(SC_ACTIVE));
            break;
          }
          default:
          {
            CODE_ERROR();
            break;
          }
        };
      };

      reset();
    }
    catch(GCL::runtime_error const &e)
    {
      ERRORMESSAGE(e.what());
    }
  }

  /// @brief      Returns the number of rows in the model.
  /// @param[in]  parent:
  /// @returns    The number of rows in the model.
  /// @version    2023-03-27/GGB - Function created.

  int CModelSecurities::rowCount(const Wt::WModelIndex &/*parent*/) const
  {
    int rv;

    switch (modelUsage)
    {
      case MU_COMBO_NO_NULL:
      {
        rv = records_.size();
        break;
      }
      case MU_COMBO_NULL:
      {
        rv = records_.size() + 1;
        break;
      }
      case MU_TABLE:
      {
        rv = records_.size();
        break;
      }

      default:
      {
        CODE_ERROR();
        break;
      }
    }

    return rv;
  }

  /// @brief      Determines the index corresponding the symbol.
  /// @param[in]  symbol: The symbol to find.
  /// @returns    The item index (0 if not found)
  /// @throws
  /// @version    2023-09-23/GGB - Function created.

  int CModelSecurities::symbol2Index(std::string const &symbol)
  {
    return ID2Index(database::tbl_imm_securities::recordSymbol(application(), exchangeID_, symbol));
  }

}
