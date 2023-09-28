//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           msmERP: Module Scheduler
// FILE:                tbl_schd_taskTypes.cpp
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
// OVERVIEW:						Classes for interating with the financial years table.
//
// HISTORY:             2023-09-28/GGB - File created
//
//**********************************************************************************************************************************

#include "include/database/tables/tbl_SCHD_taskTypes.h"

  // Wt framework header files


  // Miscellaneous library header files

#include <GCL>

  // msmERP

#include "include/application.h"
#include "include/dbe.h"
#include "include/database/tables/core/tbl_statusCodes.h"

namespace database::tbl_schd_taskTypes
{
  using taskText_t = std::map<taskType_t, std::string>;

  static taskText_t transactionsText =
  {
    { TT_NONE, "None" },
    { TT_SCRIPT, "Script" },
    { TT_PLUGIN, "Plugin" },

  };

  /// @brief      Builds a model for the task types.
  /// @param[in]  unused.
  /// @param[out] model: The model to build.
  /// @throws
  /// @version    2023-09-28/GGB - Function created.

  void createModel(CApplication &, models::CModelComboBox<tindex_t> &model)
  {
    model.clear();

    for (auto const &record: transactionsText)
    {
      std::unique_ptr<Wt::WStandardItem> item = std::make_unique<Wt::WStandardItem>(record.second);
      model.appendRow(std::move(item), record.first);
    }
  }

  /// @brief      Returns the short text associated with a business transaction.
  /// @param[in]  ignored.
  /// @param[in]  bt: The business transaction code.
  /// @returns    Human readable string
  /// @throws
  /// @version    2023-09-28/GGB - Function created.

  std::string const &shortText(CApplication &, taskType_t tt)
  {
    RUNTIME_ASSERT(transactionsText.contains(tt), "Unknown code for Scheduler Task Types");

    return transactionsText[tt];
  }


} // namespace database
