//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investment Management
// FILE:                modelCostTypes
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

#ifndef MODELCOSTTYPES_H
#define MODELCOSTTYPES_H

  // Standard C++ library header files

#include <map>
#include <memory>
#include <string>

  // Miscellaneous library headers


  // msmERP application header files

#include "include/application.h"
#include "include/core/typeDefinitions.h"
#include "include/database/models/modelAbstract.h"

namespace models
{

  class CModelCostTypes final : public CModelAbstract<index_t>
  {
  public:
    enum modelUsage_e
    {
      MU_NONE,
      MU_COMBO_NULL,
      MU_COMBO_NO_NULL,
    };

    CModelCostTypes(CApplication &a, modelUsage_e mu) :CModelAbstract(a), modelUsage(mu) {}
    virtual void reload();

  protected:
    virtual std::any headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const override;
    virtual Wt::WModelIndex index(int row, int column, const Wt::WModelIndex &parent = Wt::WModelIndex()) const override;
    virtual Wt::WModelIndex parent(const Wt::WModelIndex &) const override {return Wt::WModelIndex(); }
    virtual int columnCount(const Wt::WModelIndex &) const override;
    virtual int rowCount(const Wt::WModelIndex &) const override;
    virtual std::any data(const Wt::WModelIndex &, Wt::ItemDataRole) const override;
    virtual Wt::WFlags<Wt::ItemFlag> flags(const Wt::WModelIndex &index) const override;
    virtual bool setData(Wt::WModelIndex const &index, std::any const &value, Wt::ItemDataRole role) override;

  private:
    CModelCostTypes(int rows, int columns) = delete;
    CModelCostTypes() = delete;
    CModelCostTypes(CModelCostTypes const &) = delete;
    CModelCostTypes & operator=(CModelCostTypes const &) = delete;

    struct record_t
    {
      index_t ID;
      std::string shortText;
      bool enabled;
    };

    modelUsage_e modelUsage;
    std::vector<record_t> records_;
  };

} // namespace models

#endif // MODELCOSTTYPES_H
