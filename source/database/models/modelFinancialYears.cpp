#include "include/database/models/modelFinancialYears.h"

  // Standard C++ library

#include <memory>

  // Wt++

  // Miscellaneous libraries

#include <GCL>

  // msmERP header files

#include "include/application.h"
#include "include/dbe.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/core/tbl_statusCodes.h"
#include "include/database/tables/core/tbl_workflowStatus.h"
#include "include/database/tables/tbl_financialYear.h"

namespace models
{
  /// @brief      Returns the number of columns in the model.
  /// @param[in]  parent:
  /// @returns    The number of columns in the model.
  /// @throws
  /// @version    2023-02-23/GGB - Function created.

  int CModelFinancialYears::columnCount(const Wt::WModelIndex &/*parent*/) const
  {
    int rv = 0;

    switch (modelUsage)
    {
      case MU_TABLE_NO_EDIT:
      {
        rv = 1;
        break;
      }
      default:
      {
        CODE_ERROR();
      }
    }

    return rv;
  }

  /// @brief      Function to return the data for the specified index.
  /// @param[in]  index: The index for the data.
  /// @param[in]  role: The role being queried.
  /// @returns    The data to display
  /// @throws
  /// @version    2023-02-23/GGB - Function created.

  std::any CModelFinancialYears::data(const Wt::WModelIndex &index, Wt::ItemDataRole role) const
  {
    std::any returnValue;
    size_t row, column;

    row = static_cast<size_t>(index.row());
    column = static_cast<size_t>(index.column());

//    switch (column)
//    {
//      case 0:
//      {
//        switch (role.value())
//        {
//          case Wt::ItemDataRole::Display:
//          case Wt::ItemDataRole::Edit:
//          {
//            if (tableModel || (row != 0))
//            {
//              returnValue = records_[row].shortText;
//            }
//            else
//            {
//              returnValue = Wt::WString("---");
//            }
//            break;
//          };
//          case Wt::ItemDataRole::User:
//          {
//            returnValue = records_[row].ID;
//            std::cout << "RecordID: " << records_[row].ID << std::endl;
//            break;
//          }
//          default:
//          {
//            //CODE_ERROR();
//            break;
//          }
//        }
//        break;
//      }
//      case 1:
//      {
//        switch (role.value())
//        {
//          //case Wt::ItemDataRole::Display:
//          case Wt::ItemDataRole::Checked:
//          case Wt::ItemDataRole::Edit:

//          {
//            returnValue = records_[row].enabled;
//            break;
//          };
//          default:
//          {
//            //CODE_ERROR();
//            break;
//          };
//        }
//        break;
//      };
//      default:
//      {
//        CODE_ERROR();
//        break;
//      }
//    }

    return returnValue;
  }

  /// @brief      Returns the item flags for the model. This is overloaded as the item flags need to be modified for different
  ///             cells in the model. The Cells corresponding to unallowed assignments need to be changed to not allow values.
  /// @param[in]  index: The index to get the flags for.
  /// @returns    The applicable item flags.
  /// @version    2023-02-23/GGB - Function created.

  Wt::WFlags<Wt::ItemFlag> CModelFinancialYears::flags(const Wt::WModelIndex &index) const
  {
    Wt::WFlags<Wt::ItemFlag> rv = Wt::WFlags<Wt::ItemFlag>();

//    switch (index.column())
//    {
//      case 0:
//      {
//        if (tableModel)
//        {
//          rv = Wt::WFlags<Wt::ItemFlag>(Wt::ItemFlag::Editable);
//        }
//        else
//        {
//          rv = Wt::WFlags<Wt::ItemFlag>(Wt::ItemFlag::Selectable);
//        }
//        break;
//      }
//      case 1:
//      {
//        rv = Wt::WFlags<Wt::ItemFlag>(Wt::ItemFlag::Selectable | Wt::ItemFlag::UserCheckable | Wt::ItemFlag::Editable);
//        break;
//      }
//      default:
//      {
//        CODE_ERROR();
//        break;
//      }
//    };

    return rv;
  }

  /// @brief      Returns the row or column header data.
  /// @param[in]  section: The row or column number to retrieve.
  /// @param[in]  orientation: Vertical is the row headers, Horizontal for column headers.
  /// @param[in]  role: The data role.
  /// @throws
  /// @version    2023-02-23/GGB - Function created.

  std::any CModelFinancialYears::headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const
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
              returnValue = "Year";
              break;
            };
            case 1:
            {
              returnValue = "Enabled";
              break;
            }
            case 2:
            {
              returnValue = "Hidden";
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
  /// @version 2023-02-23/GGB - Function created.

  Wt::WModelIndex CModelFinancialYears::index(int row, int column, const Wt::WModelIndex &/*parent*/) const
  {
    if ( (static_cast<size_t>(row) >= records_.size()) || (row < 0) || (column < 0) || (column > 1) )
    {
      return Wt::WModelIndex();
    }
    else
    {
      return createIndex(row, column, nullptr);
    };

  }


  Wt::WModelIndex CModelFinancialYears::parent(const Wt::WModelIndex &/*index*/) const
  {
    return Wt::WModelIndex();
  }

  /// @brief      Updates the model with information from the database.
  /// @details    This is more complex than the normal read of items linked to status. As the hidden and enabled statuses may or
  ///             may not be displayed. As the statuses are also used as
  /// @param[in]  reasonID: The reasonID that the categories are connected to.
  /// @param[in]  enterpriseID: The enterpriseID.
  /// @throws
  /// @version    2023-02-21/GGB - Function created.

  void CModelFinancialYears::reload()
  {
    using namespace TBL_FI_FINANCIALYEAR;
    using namespace GCL;

    sqlWriter sqlQuery;

    sqlQuery
        .select({ PK, COL_SHORTTEXT })
        .from(TABLE)
        .where(FK_ENTERPRISE, eq, application().enterpriseID())
        .orderBy(COL_SHORTTEXT, ASC);

    try
    {
      database::CRecordSet recordSet = application().session().recordSet(sqlQuery);

      records_.clear();
      clear();

      for (auto const &record: recordSet)
      {
        addItem(records_.size(), static_cast<index_t>(record[0]));
        records_.emplace_back(static_cast<index_t>(record[0]), record[1].toString());
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
  /// @version    2023-02-23/GGB - Function created.

  int CModelFinancialYears::rowCount(const Wt::WModelIndex &/*parent*/) const
  {
    int rv = 0;
    switch (modelUsage)
    {
      case MU_TABLE_NO_EDIT:
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

  /// @brief      Called to update the data.
  /// @param[in]  index:
  /// @param[in]  value:
  /// @param[in]  role:
  /// @returns    true - if succesfull
  /// @throws
  /// @version    2023-02-23/GGB - Function created.

  bool CModelFinancialYears::setData(Wt::WModelIndex const &index, std::any const &value, Wt::ItemDataRole role)
  {
//    using namespace database;

//    size_t row = static_cast<size_t>(index.row());
//    size_t column = static_cast<size_t>(index.column());

//    switch (column)
//    {
//      case 0:
//      {
//        // Updated the text.

//        records_[row].shortText = std::any_cast<Wt::WString>(value).toUTF8();
//        database::tbl_oee_categories::record_t record {records_[row].ID, reasonID_, records_[row].shortText };
//        if (record.ID == 0)
//        {
//          // Inserting a record

//          database::tbl_oee_categories::createRecord(application_.session(), record);
//          records_[row].ID = record.ID;

//          records_.emplace_back(0, "", 0);  // New clean record at the back.
//          reset();
//        }
//        else
//        {
//          database::tbl_oee_categories::updateRecord(application_.session(), record);
//        }
//        break;
//      }
//      case 1:
//      {
//        // Updating the enabled value.

//        if (records_[row].ID != 0)
//        {
//          records_[row].enabled = std::any_cast<bool>(value);
//          database::tbl_core_workflowStatus::record_t record {
//            OT_OEE_CATEGORY,
//                records_[row].ID,
//                records_[row].enabled ? SC_ACTIVE : SC_INACTIVE,
//                Wt::WDateTime::currentDateTime(),
//                application_.userID()
//          };
//          database::tbl_core_workflowStatus::insertRecord(application_.session(), record);
//        };

//        break;
//      }
//      default:
//      {
//        CODE_ERROR();
//        break;
//      }
//    }

    return true;

  }

}
