//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                modelPortfolio
// SUBSYSTEM:           Investment Management Module
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
// HISTORY:             2023-07-22/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/models/modelPortfolio.h"

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
#include "include/database/tables/tbl_imm_portfolio.h"

namespace models
{
  /// @brief      Returns the number of columns in the model.
  /// @param[in]  parent:
  /// @returns    The number of columns in the model.
  /// @throws
  /// @version    2023-07-26/GGB - Function created.

  int CModelPortfolio::columnCount(const Wt::WModelIndex &/*parent*/) const
  {
    int rv;

    switch (modelUsage)
    {
      case MU_COMBO_NULL:
      case MU_COMBO_NO_NULL:
      {
        rv = 1;
        break;
      };
      case MU_TABLE:
      {
        rv = 2;
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
  /// @version    2023-07-26/GGB - Function created.

  std::any CModelPortfolio::data(const Wt::WModelIndex &index, Wt::ItemDataRole role) const
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
                  rv = records_[row - 1].shortText;
                }
                break;
              }
              case MU_COMBO_NO_NULL:
              {
                rv = records_[row].shortText;
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
            CODE_ERROR();
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

  Wt::WFlags<Wt::ItemFlag> CModelPortfolio::flags(const Wt::WModelIndex &index) const
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
          case MU_COMBO_NULL:
          case MU_COMBO_NO_NULL:
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

  std::any CModelPortfolio::headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const
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
              returnValue = "Portfolio";
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
  /// @version    2023-07-23/GGB - Function created.

  Wt::WModelIndex CModelPortfolio::index(int row, int column, const Wt::WModelIndex &/*parent*/) const
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


  Wt::WModelIndex CModelPortfolio::parent(const Wt::WModelIndex &/*index*/) const
  {
    return Wt::WModelIndex();
  }

  /// @brief      Updates the model with information from the database.
  /// @throws
  /// @version    2023-07-23/GGB - Function created.

  void CModelPortfolio::reload()
  {
    using namespace TBL_IMM_PORTFOLIO;
    using namespace GCL;

    sqlWriter sqlQuery;
    sqlQuery
        .select({PK, COL_SHORTTEXT })
        .from(TABLE)
        .where(FK_ENTERPRISE, eq, application().enterpriseID())
        .orderBy(COL_SHORTTEXT, ASC);

    try
    {
      database::CRecordSet recordSet = application().session().recordSet(sqlQuery);

      clear();
      records_.clear();

      for (auto const &record : recordSet)
      {
        switch (modelUsage)
        {
          case MU_COMBO_NULL:
          {
            std::cout << record[1].toString() << std::endl;
            records_.emplace_back(static_cast<index_t>(record[0]), record[1].toString(),
                database::tbl_imm_portfolio::activeStatuses(application(), static_cast<sindex_t>(record[0])).contains(SC_ACTIVE));
            addItem(records_.size(), static_cast<index_t>(record[0]));
            break;
          };
          case MU_TABLE:
          {
            for (auto const &record: recordSet)
            {
              addItem(records_.size(), static_cast<index_t>(record[0]));
              records_.emplace_back(static_cast<index_t>(record[0]), record[1].toString(),
                  database::tbl_imm_portfolio::activeStatuses(application(), static_cast<sindex_t>(record[0])).contains(SC_ACTIVE));
            };
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

  int CModelPortfolio::rowCount(const Wt::WModelIndex &/*parent*/) const
  {
    int rv;

    switch (modelUsage)
    {
      case MU_COMBO_NO_NULL:
      case MU_TABLE:
      {
        rv = records_.size();
        break;
      }
      case MU_COMBO_NULL:
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

  bool CModelPortfolio::setData(Wt::WModelIndex const &index, std::any const &value, Wt::ItemDataRole role)
  {
    //    using namespace database;

    //    std::size_t row = static_cast<std::size_t>(index.row());
    //    std::size_t column = static_cast<std::size_t>(index.column());

    //    switch (column)
    //    {
    //      case 0:
    //      {
    //        switch (modelUsage)
    //        {
    //          case MU_TABLE_EDIT:
    //          {
    //            // Updated the text.

    //            if (row >= records_.size())
    //            {
    //              records_.emplace_back(0, "", false);
    //            }

    //            records_[row].shortText = std::any_cast<Wt::WString>(value).toUTF8();
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
    //            break;
    //          };
    //          default:
    //          {
    //            CODE_ERROR();
    //            break;
    //          }
    //        };
    //        break;
    //      }
    //      case 1:
    //      {
    //        switch(modelUsage)
    //        {
    //          case MU_TABLE_EDIT:
    //          {
    //            if (records_[row].ID != 0)
    //            {
    //              records_[row].enabled = std::any_cast<bool>(value);
    //              database::tbl_core_workflowStatus::record_t record {
    //                OT_OEE_CATEGORY,
    //                    records_[row].ID,
    //                    records_[row].enabled ? SC_ACTIVE : SC_INACTIVE,
    //                    Wt::WDateTime::currentDateTime(),
    //                    application().userID()
    //              };
    //              database::tbl_core_workflowStatus::insertRecord(application(), record);
    //            };
    //            break;
    //          }
    //          default:
    //          {
    //            CODE_ERROR();
    //            break;
    //          }
    //        };
    //        break;
    //      }
    //      default:
    //      {
    //        CODE_ERROR();
    //        break;
    //      }
    //    }

    //    reset();
    //    return true;

  }

}
