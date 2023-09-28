//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investment Management
// FILE:                priceUploadManager.cpp
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

#include "include/priceUploadManager.h"

  // Miscellaneous library header files

#include <GCL>

  // msmERP header files

#include "include/configSettings.h"
#include "include/pluginInterface/interfacePriceUpload.h"

namespace IMM::priceUpload
{
  CPriceUploadManager &CPriceUploadManager::priceUploadManager()
  {
    static CPriceUploadManager PUM;

    return PUM;
  }

  /// @brief      Loads any plugins for the module.
  /// @param[in]  pm: The plugin manager instance.
  /// @param[in]  rs: The configuration file reader to use.
  /// @throws
  /// @version    2023-09-21/GGB - Function created.

  void CPriceUploadManager::loadPriceUploadPlugins(GCL::plugin::CPluginManager &pluginManager,
                                                          GCL::CReaderSections &configReader)
  {
    TRACEENTER();

    std::optional<std::string> pluginDirectory = configReader.tagValueString(PLUGINS_MODULES);

    if (pluginDirectory)
    {
      std::filesystem::path directory(*pluginDirectory);
      directory /= "module_IMM/priceUpload";

      if (std::filesystem::is_directory(directory))
      {
        for (auto const &dir_entry : std::filesystem::directory_iterator(directory))
        {
          if (dir_entry.is_regular_file())
          {
            GCL::plugin::pluginHandle_t pluginHandle = pluginManager.loadPlugin(dir_entry);

              // Map the functions.

            IMM::priceUpload::name_fn name_fn = reinterpret_cast<IMM::priceUpload::name_fn>
                                                  (pluginManager.mapSymbol(pluginHandle, "name"));

            registerPlugin(name_fn(),
                           reinterpret_cast<IMM::priceUpload::validate_fn>(pluginManager.mapSymbol(pluginHandle, "validate")),
                           reinterpret_cast<IMM::priceUpload::parseFile_fn>(pluginManager.mapSymbol(pluginHandle, "parseFile")),
                           reinterpret_cast<IMM::priceUpload::exchange_fn>(pluginManager.mapSymbol(pluginHandle, "exchange")),
                           reinterpret_cast<IMM::priceUpload::exchange_fn>(pluginManager.mapSymbol(pluginHandle, "security"))
                           );


          };
        };
      }
      else
      {
        RUNTIME_ERROR("The price upload plugin directory specified is not a valid path.");
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
  /// @version    2023-09-21/GGB - Function created.

  void CPriceUploadManager::registerPlugin(std::string const &pluginName, validate_fn validateFN, parseFile_fn parseFN,
                                           exchange_fn exchangeFN, security_fn securityFN)
  {
    priceUploadManager().pluginMap.insert_or_assign(pluginName, std::make_tuple(validateFN, parseFN, exchangeFN, securityFN));
  }

  /// @brief      Attempts to parse the file. Each of the plugins are tried in turn until one manages to validate the file.
  /// @param[in]  originalFilename: The original name of the file. Due to the file spooler, the actual name will differ
  /// @param[in]  actualFilename: The actual name of the file. Assigned by the spooler.
  /// @throws
  /// @version    2023-09-21/GGB - Function created.

  void CPriceUploadManager::parseFile(std::filesystem::path const &originalFilename,
                                      std::filesystem::path const &actualFilename,
                                      pricesVector_t &priceVector,
                                      std::string const &plugin)
  {
    std::string tempPlugin{plugin};

    if (tempPlugin.empty())
    {
      tempPlugin = validateFile(originalFilename, actualFilename);
    }

    if (tempPlugin.empty())
    {
      RUNTIME_ERROR("No parser found for file");
    }

    std::cout << "CPriceUploadManager::parseFile - 1" << std::endl;
    std::cout << actualFilename.string() << std::endl;

    std::get<1>(priceUploadManager().pluginMap[tempPlugin])(originalFilename, actualFilename, priceVector);

    std::cout << "CPriceUploadManager::parseFile End" << std::endl;
  }

  /// @brief      Attempts to validate the file. Each of the plugins are tried in turn until one manages to validate the file.
  /// @param[in]  filePath: Path to the file to validate.
  /// @returns    true - If the file was validated.
  /// @throws
  /// @version    2023-09-21/GGB - Function created.

  std::string CPriceUploadManager::validateFile(std::filesystem::path const &originalFilename,
                                                std::filesystem::path const &actualFilename)
  {
    std::string returnValue;

    priceMap_t::const_iterator iterator = priceUploadManager().pluginMap.begin();

    while (iterator != priceUploadManager().pluginMap.end())
    {
      if (std::get<0>(iterator->second)(originalFilename, actualFilename))
      {
        returnValue = iterator->first;
        iterator = priceUploadManager().pluginMap.end();
      }
      else
      {
        iterator++;
      }
    };

    return returnValue;
  }

  /// @brief      Attempts to get the exchange string.
  /// @param[in]  filePath: Path to the file to validate.
  /// @returns    true - If the file was validated.
  /// @throws
  /// @version    2023-09-23/GGB - Function created.

  std::string CPriceUploadManager::exchange(std::filesystem::path const &originalFilename,
                                            std::filesystem::path const &actualFilename,
                                            std::string const &plugin)
  {
    std::string tempPlugin{plugin};

    if (tempPlugin.empty())
    {
      tempPlugin = validateFile(originalFilename, actualFilename);
    }

    if (tempPlugin.empty())
    {
      RUNTIME_ERROR("No parser found for file");
    }

    return std::get<2>(priceUploadManager().pluginMap[tempPlugin])(originalFilename, actualFilename);
  }

  /// @brief      Attempts to get the security string.
  /// @param[in]  filePath: Path to the file to validate.
  /// @returns    true - If the file was validated.
  /// @throws
  /// @version    2023-09-23/GGB - Function created.

  std::string CPriceUploadManager::security(std::filesystem::path const &originalFilename,
                                            std::filesystem::path const &actualFilename,
                                            std::string const &plugin)
  {
    std::string tempPlugin{plugin};

    if (tempPlugin.empty())
    {
      tempPlugin = validateFile(originalFilename, actualFilename);
    }

    if (tempPlugin.empty())
    {
      RUNTIME_ERROR("No parser found for file");
    }

    return std::get<3>(priceUploadManager().pluginMap[tempPlugin])(originalFilename, actualFilename);
  }

}  // namespace priceUpload
