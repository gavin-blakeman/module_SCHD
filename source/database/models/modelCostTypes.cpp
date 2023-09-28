//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// FILE:                modelCostTypes
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
// OVERVIEW:
//
// HISTORY:             2023-08-08/GGB - File created.
//
//**********************************************************************************************************************************

#include "include/database/models/modelCostTypes.h"

  // Standard C++ library header files

#include <stdexcept>
#include <tuple>

  // Miscellaneous library header files

#include <GCL>

  // msmERP application header files.

#include "include/dbe.h"
#include "include/database/tables/core/tbl_objectTypes.h"
#include "include/database/tables/core/tbl_statusCodes.h"
#include "include/database/tables/core/tbl_workflowStatus.h"
#include "include/database/tables/tbl_imm_costTypes.h"

namespace models
{

  /// @brief      Returns the number of columns.
  /// @param[in]
  /// @returns    The number of columns.
  /// @throws
  /// @version    2023-07-22/GGB - Function created.

  int CModelCostTypes::columnCount(const Wt::WModelIndex &) const
  {
    int rv;

    switch (modelUsage)
    {
      case MU_COMBO_NULL:
      case MU_COMBO_NO_NULL:
      {
        rv = 1;
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

  /// @brief      Function to return the data for the specified index.
  /// @param[in]  index: The index for the data.
  /// @param[in]  role: The role being queried.
  /// @returns    The data to display
  /// @throws
  /// @version    2023-03-14/GGB - Function created.

  std::any CModelCostTypes::data(const Wt::WModelIndex &index, Wt::ItemDataRole role) const
  {
    std::any returnValue;
    size_t row, column;

    row = static_cast<size_t>(index.row());
    column = static_cast<size_t>(index.column());

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
                  returnValue = "---";
                }
                else
                {
                  returnValue = records_[row - 1].shortText;
                }
                break;
              }
              case MU_COMBO_NO_NULL:
              {
                returnValue = records_[row].shortText;
                break;
              }
              default:
              {
                CODE_ERROR();
                break;
              };
            }
          };
          default:
          {
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
            switch(modelUsage)
            {
              default:
              {
                CODE_ERROR();
                break;
              }
            }
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

    return returnValue;
  }

  /// @brief      Returns the item flags for the model. This is overloaded as the item flags need to be modified for different
  ///             cells in the model. The Cells corresponding to unallowed assignments need to be changed to not allow values.
  /// @param[in]  index: The index to get the flags for.
  /// @returns    The applicable item flags.
  /// @version    2023-03-14/GGB - Function created.

  Wt::WFlags<Wt::ItemFlag> CModelCostTypes::flags(const Wt::WModelIndex &index) const
  {
    Wt::WFlags<Wt::ItemFlag> rv = Wt::WFlags<Wt::ItemFlag>();

    switch (index.column())
    {
      case 0:
      {
        switch(modelUsage)
        {
          case MU_COMBO_NULL:
          case MU_COMBO_NO_NULL:
          {
            rv = Wt::WFlags<Wt::ItemFlag>(Wt::ItemFlag::Selectable);
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
      case 1:
      {
        rv = Wt::WFlags<Wt::ItemFlag>(Wt::ItemFlag::Selectable | Wt::ItemFlag::UserCheckable);
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
  /// @version 2023-03-14/GGB - Function created.

  std::any CModelCostTypes::headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const
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
              returnValue = "Cost Type";
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
  /// @version    2023-03-14/GGB - Function created.

  Wt::WModelIndex CModelCostTypes::index(int row, int column, const Wt::WModelIndex &/*parent*/) const
  {
    if ( (static_cast<size_t>(row) > records_.size()) || (row < 0) || (column < 0) || (column > 1) )
    {
      return Wt::WModelIndex();
    }
    else
    {
      return createIndex(row, column, nullptr);
    };

  }

  /// @brief      Updates the model with the relevant data.
  /// @throws
  /// @version    2022-08-01/GGB - Function created.

  void CModelCostTypes::reload()
  {
    using namespace TBL_IMM_COSTTYPES;
    using namespace GCL;

    sqlWriter sqlQuery;

    sqlQuery
        .select({PK, COL_SHORTTEXT})
        .from(TABLE)
        .where(FK_ENTERPRISE, eq, application().enterpriseID());

    try
    {
      database::CRecordSet recordSet = application().session().recordSet(sqlQuery);

      clear();
      records_.clear();

      switch (modelUsage)
      {
        case MU_COMBO_NULL:
        {
          for (auto const &record: recordSet)
          {
            if (database::tbl_imm_costTypes::activeStatuses(application(), static_cast<sindex_t>(record[0])).contains(SC_ACTIVE))
            {
              records_.emplace_back(static_cast<index_t>(record[0]), record[1].toString(), true);
              addItem(records_.size(), static_cast<index_t>(record[0]));
            };
          };
          break;
        };
        case MU_COMBO_NO_NULL:
        {
          for (auto const &record: recordSet)
          {
            if (database::tbl_imm_costTypes::activeStatuses(application(), static_cast<sindex_t>(record[0])).contains(SC_ACTIVE))
            {
              addItem(records_.size(), static_cast<index_t>(record[0]));
              records_.emplace_back(static_cast<index_t>(record[0]), record[1].toString(), true);
            };
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

  /// @brief      Returns the number of rows on the model.
  /// @param[in]  row:
  /// @returns    The number of rows.
  /// @throws
  /// @version    2023-03-14/GGB - Function created.

  int CModelCostTypes::rowCount(const Wt::WModelIndex &) const
  {
    int rv = 0;

    switch(modelUsage)
    {
      case MU_COMBO_NULL:
      {
        rv = records_.size() + 1;
        break;
      }
      case MU_COMBO_NO_NULL:
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
  /// @version    2023-03-14/GGB - Function created.

  bool CModelCostTypes::setData(Wt::WModelIndex const &index, std::any const &value, Wt::ItemDataRole role)
  {
    using namespace database;

    size_t row = static_cast<size_t>(index.row());
    size_t column = static_cast<size_t>(index.column());

    switch (column)
    {
      case 0:
      {
        // Updated the text.

        //        records_[row].shortText = std::any_cast<Wt::WString>(value).toUTF8();
        //        database::tbl_oee_categories::record_t record {records_[row].ID, reasonID_, records_[row].shortText };
        //        if (record.ID == 0)
        //        {
        //            // Inserting a record

        //          database::tbl_oee_categories::createRecord(application_, record);
        //          records_[row].ID = record.ID;

        //          records_.emplace_back(0, "", 0);  // New clean record at the back.
        //          reset();
        //        }
        //        else
        //        {
        //          database::tbl_oee_categories::updateRecord(application_.session(), record);
        //        }
        break;
      }
      case 1:
      {

        switch (modelUsage)
        {
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

    return true;

  }

}
