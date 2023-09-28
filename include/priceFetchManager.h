//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investment Management
// FILE:                priceFetchManager.h
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:
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
// HISTORY:             2023-09-26/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef PRICEFETCHMANAGER_H
#define PRICEFETCHMANAGER_H

  // Standard C++ library header files

#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <tuple>
#include <string>
#include <utility>
#include <vector>

  // Miscellaneous library header files

  // msmERP header files

#include "include/pluginInterface/interfacePriceFetch.h"

namespace IMM::priceFetch
{
  class CPriceFetchManager
  {
  public:
    static void loadPriceFetchPlugins(GCL::plugin::CPluginManager &pluginManager, GCL::CReaderSections &configReader);
    static void registerPlugin(std::string const &, priceFetch_fn *);

    static void priceFetch(std::string const &, callback_fn *, securityPrices_t *);

  private:
    using pluginMap_t = std::map<std::string, priceFetch_fn *>;

    CPriceFetchManager() {}
    CPriceFetchManager(CPriceFetchManager const &) = delete;              // Cannot copy
    CPriceFetchManager(CPriceFetchManager &&) = delete;                   // Cannot move
    CPriceFetchManager &operator =(CPriceFetchManager const &) = delete;  // Cannot copy.

    static pluginMap_t pluginMap;
  };

}

#endif // PRICEFETCHMANAGER_H
