//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investment Management
// FILE:                priceFetchManager.cpp
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

#include "include/priceFetchManager.h"

  // Miscellaneous library header files

#include <fmt/format.h>
#include <GCL>

  // msmERP header files

#include "include/configSettings.h"
#include "include/pluginInterface/interfacePriceFetch.h"

namespace IMM::priceFetch
{

  CPriceFetchManager::pluginMap_t CPriceFetchManager::pluginMap;

  /// @brief      Loads any plugins for the module.
  /// @param[in]  pm: The plugin manager instance.
  /// @param[in]  rs: The configuration file reader to use.
  /// @throws
  /// @version    2023-09-26/GGB - Function created.

  void CPriceFetchManager::loadPriceFetchPlugins(GCL::plugin::CPluginManager &pluginManager,
                                                   GCL::CReaderSections &configReader)
  {
    TRACEENTER();

    std::optional<std::string> pluginDirectory = configReader.tagValueString(PLUGINS_MODULES);

    if (pluginDirectory)
    {
      std::filesystem::path directory(*pluginDirectory);
      directory /= "module_IMM/priceFetch";

      if (std::filesystem::is_directory(directory))
      {
        for (auto const &dir_entry : std::filesystem::directory_iterator(directory))
        {
          if (dir_entry.is_regular_file())
          {
            GCL::plugin::pluginHandle_t pluginHandle = pluginManager.loadPlugin(dir_entry);

            // Map the functions.

            name_fn *nameFunction = reinterpret_cast<IMM::priceFetch::name_fn *>
                                               (pluginManager.mapSymbol(pluginHandle, "name"));

            registerPlugin(nameFunction(), reinterpret_cast<IMM::priceFetch::priceFetch_fn *>
                           (pluginManager.mapSymbol(pluginHandle, "priceFetch")));


          };
        };
      }
      else
      {
        RUNTIME_ERROR("The price fetch plugin directory specified is not a valid path.");
      }
    }
    else
    {
      RUNTIME_ERROR("No setting specified for the module plugins.");
    }
    TRACEEXIT();
  }

  /// @brief      Function to register a plugin with the plugin manager.
  /// @param[in]
  /// @throws     std::bad_alloc
  /// @version    2023-09-26/GGB - Function created.

  void CPriceFetchManager::registerPlugin(std::string const &pluginName, priceFetch_fn *priceFetchFN)
  {
    pluginMap.insert_or_assign(pluginName, priceFetchFN);
  }

  /// @brief      Attempts to validate the file. Each of the plugins are tried in turn until one manages to validate the file.
  /// @param[in\  pluginName: The name of the plugin to use.
  /// @param[in]  filePath: Path to the file to validate.
  /// @param[in]  securityPrices: Map containing the symbol information and prices to get. Also used for the return data.
  /// @returns    true - If the file was validated.
  /// @throws
  /// @version    2023-09-21/GGB - Function created.

  void CPriceFetchManager::priceFetch(std::string const &pluginName, callback_fn *callbackFunction,
                                      securityPrices_t *securityPrices)
  {
    if (pluginMap.contains(pluginName))
    {
      pluginMap[pluginName](callbackFunction, securityPrices);
    }
    else
    {
      RUNTIME_ERROR(fmt::format("Plugin not found: {:s}", pluginName));
    };
  }

}
