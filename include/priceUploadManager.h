//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investment Management
// FILE:                priceUploadManager.h
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
// HISTORY:             2023-09-21/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef PRICEUPLOADMANAGER_H
#define PRICEUPLOADMANAGER_H

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

#include "include/pluginInterface/interfacePriceUpload.h"

namespace IMM::priceUpload
{
  class CPriceUploadManager
  {
  public:
    static CPriceUploadManager &priceUploadManager();
    static void loadPriceUploadPlugins(GCL::plugin::CPluginManager &pluginManager, GCL::CReaderSections &configReader);
    static void registerPlugin(std::string const &, validate_fn, parseFile_fn, exchange_fn, security_fn);

    static std::string validateFile(std::filesystem::path const &, std::filesystem::path const &);
    static void parseFile(std::filesystem::path const &, std::filesystem::path const &, pricesVector_t &, std::string const & = "");
    static std::string exchange(std::filesystem::path const &, std::filesystem::path const &, std::string const & = "");
    static std::string security(std::filesystem::path const &, std::filesystem::path const &, std::string const & = "");

  private:
    using plugin_t = std::tuple<validate_fn, parseFile_fn, exchange_fn, security_fn>;
    using priceMap_t = std::map<std::string, plugin_t>;

    CPriceUploadManager() {}
    CPriceUploadManager(CPriceUploadManager const &) = delete;              // Cannot copy
    CPriceUploadManager(CPriceUploadManager &&) = delete;                   // Cannot move
    CPriceUploadManager &operator =(CPriceUploadManager const &) = delete;  // Cannot copy.

    priceMap_t pluginMap;
  };

} // namespace priceUpload

#endif // PRICEUPLOADMANAGER_H
