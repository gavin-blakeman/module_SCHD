#include "include/database/models/modelCostElementGroups.h"

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
#include "include/database/tables/tbl_fi_costElementGroups.h"

namespace models
{
  /// @brief Returns the number of columns in the model.
  /// @param[in] parent:
  /// @returns The number of columns in the model.
  /// @throws
  /// @version 2023-02-23/GGB - Function created.

  int CModelCostElementGroups::columnCount(Wt::WModelIndex const &/*parent*/) const
  {
    int rv;

    switch (modelUsage)
    {
      case MU_COMBO:
      {
        rv = 1;
        break;
      };
      case MU_TABLE_EDIT:
      {
        rv = 2;
        break;
      };
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
  /// @version 2023-02-23/GGB - Function created.

  std::any CModelCostElementGroups::data( Wt::WModelIndex const &index, Wt::ItemDataRole role) const
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
          case Wt::ItemDataRole::Edit:
          {
            switch(modelUsage)
            {
              case MU_TABLE_EDIT:
              {
                if (row < records_.size())
                {
                  rv = records_[row].shortText;
                }
                else
                {
                  rv = std::string("");
                }
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
          case Wt::ItemDataRole::Display:
          {
            switch(modelUsage)
            {
              case MU_COMBO:
              {
                if (row == 0)
                {
                  rv = "---";
                }
                else
                {
                  rv = records_[row - 1].shortText;
                }
                break;
              }
              case MU_TABLE_EDIT:
              {
                if (row < records_.size())
                {
                  rv = records_[row].shortText;
                }
                else
                {
                  rv = std::string("");
                }
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
          case Wt::ItemDataRole::Checked:
          {
            switch (modelUsage)
            {
              case MU_TABLE_EDIT:
              {
                if (row < records_.size())
                {
                  rv = records_[row].enabled;
                }
                else
                {
                  rv = false;
                }
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
  /// @version    2023-02-23/GGB - Function created.

  Wt::WFlags<Wt::ItemFlag> CModelCostElementGroups::flags(Wt::WModelIndex const &index) const
  {
    Wt::WFlags<Wt::ItemFlag> rv;

    std::size_t row = static_cast<std::size_t>(index.row());
    std::size_t column = static_cast<std::size_t>(index.column());

    switch (column)
    {
      case 0:
      {
        switch(modelUsage)
        {
          case MU_TABLE_EDIT:
          {
            rv = Wt::WFlags<Wt::ItemFlag>(Wt::ItemFlag::Editable);
            break;
          }
          case MU_COMBO:
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
      case 1:
      {
        switch(modelUsage)
        {
          case MU_TABLE_EDIT:
          {
            rv = Wt::WFlags<Wt::ItemFlag>(Wt::ItemFlag::UserCheckable);
            break;
          };
          case MU_COMBO:
          default:
          {
            CODE_ERROR();
            break;
          }
        };
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

  /// @brief Returns the row or column header data.
  /// @param[in] section: The row or column number to retrieve.
  /// @param[in] orientation: Vertical is the row headers, Horizontal for column headers.
  /// @param[in] role: The data role.
  /// @throws std::runtime_error
  /// @version 2023-02-23/GGB - Function created.

  std::any CModelCostElementGroups::headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const
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
              returnValue = "Category";
              break;
            };
            case 1:
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
  /// @version 2023-02-23/GGB - Function created.

  Wt::WModelIndex CModelCostElementGroups::index(int row, int column, Wt::WModelIndex const &/*parent*/) const
  {
    Wt::WModelIndex rv;

    switch (modelUsage)
    {
      case MU_COMBO:
      case MU_TABLE_EDIT:
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

  Wt::WModelIndex CModelCostElementGroups::parent(const Wt::WModelIndex &/*index*/) const
  {
    return Wt::WModelIndex();
  }

  /// @brief Updates the model with information from the database.
  /// @param[in] reasonID: The reasonID that the categories are connected to.
  /// @param[in] tableView: true if this needs to be for the table view.
  /// @throws
  /// @version 2023-02-21/GGB - Function created.

  void CModelCostElementGroups::reload(index_t reasonID)
  {
    using namespace TBL_FI_COSTELEMENTGROUPS;
    using namespace GCL;

    reasonID_ = reasonID;

    sqlWriter sqlQuery;
    sqlQuery
        .select({PK, COL_SHORTTEXT})
        .from(TABLE)
        .where(FK_ENTERPRISE, eq, application().enterpriseID())
        .orderBy(COL_SHORTTEXT, ASC);

    try
    {
      database::CRecordSet recordSet = application().session().recordSet(sqlQuery);

      clear();
      records_.clear();

      switch(modelUsage)
      {
        case MU_TABLE_EDIT:
        {
          for (auto const &record: recordSet)
          {
//            addItem(records_.size(), static_cast<index_t>(record[0]));
//            records_.emplace_back(static_cast<index_t>(record[0]),
//                record[1].toString(),
//                database::tbl_::activeStatuses(application(),
//                                                             static_cast<index_t>(record[0])).contains(SC_ACTIVE));

          };
          break;
        }
        case MU_COMBO:
        {
          for (auto const &record: recordSet)
          {
//            if (database::tbl_oee_categories::activeStatuses(application(), static_cast<index_t>(record[0])).contains(SC_ACTIVE))
//            {
//              records_.emplace_back(static_cast<index_t>(record[0]), record[1].toString(), true);
//              addItem(records_.size(), static_cast<index_t>(record[0]));
//            };
          };

          break;
        };
        default:
        {
          CODE_ERROR();
          break;
        }
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

  int CModelCostElementGroups::rowCount(const Wt::WModelIndex &/*parent*/) const
  {
    int rv;

    switch (modelUsage)
    {
      case MU_COMBO:
      case MU_TABLE_EDIT:
      {
        rv = records_.size() + 1;
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

  bool CModelCostElementGroups::setData(Wt::WModelIndex const &index, std::any const &value, Wt::ItemDataRole role)
  {
    using namespace database;

    std::size_t row = static_cast<std::size_t>(index.row());
    std::size_t column = static_cast<std::size_t>(index.column());

    switch (column)
    {
      case 0:
      {
        switch (modelUsage)
        {
          case MU_TABLE_EDIT:
          {
            // Updated the text.

            if (row >= records_.size())
            {
              records_.emplace_back(0, "", false);
            }

            records_[row].shortText = std::any_cast<Wt::WString>(value).toUTF8();
//            database::tbl_oee_categories::record_t record {records_[row].ID, reasonID_, records_[row].shortText };
//            if (record.ID == 0)
//            {
//              database::tbl_oee_categories::createRecord(application(), record);
//              records_[row].ID = record.ID;
//            }
//            else
//            {
//              database::tbl_oee_categories::updateRecord(application(), record);
//            }
            break;
          };
          default:
          {
            CODE_ERROR();
            break;
          }
        };
        break;
      }
      case 1:
      {
        switch(modelUsage)
        {
          case MU_TABLE_EDIT:
          {
            if (records_[row].ID != 0)
            {
              records_[row].enabled = std::any_cast<bool>(value);
              database::tbl_core_workflowStatus::record_t record {
                OT_OEE_CATEGORY,
                    records_[row].ID,
                    records_[row].enabled ? SC_ACTIVE : SC_INACTIVE,
                    dateTime_t(),
                    application().userID()
              };
              database::tbl_core_workflowStatus::insertRecord(application(), record);
            };
            break;
          }
          default:
          {
            CODE_ERROR();
            break;
          }
        };
        break;
      }
      default:
      {
        CODE_ERROR();
        break;
      }
    }

    reset();
    return true;

  }

}
