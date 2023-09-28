//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investment Management
// FILE:                interfacePriceUpload
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           core::priceUpload
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

#ifndef INTERFACEPRICEUPLOAD_H
#define INTERFACEPRICEUPLOAD_H

  // Standard C++ libraries

#include <filesystem>
#include <string>
#include <vector>

  // Miscellaneous library header files

#include <GCL>

  // msmERP header files

#include "include/core/typeDefinitions.h"

namespace IMM::priceUpload
{
  using pricesVector_t = std::vector<std::pair<date_t, money_t>>;


  typedef std::string (*name_fn)();
  typedef bool (*validate_fn)(std::filesystem::path const &, std::filesystem::path const &);
  typedef void (*parseFile_fn)(std::filesystem::path const &, std::filesystem::path const &, pricesVector_t &);
  typedef std::string (*exchange_fn)(std::filesystem::path const &, std::filesystem::path const &);
  typedef std::string (*security_fn)(std::filesystem::path const &, std::filesystem::path const &);

  extern "C"
  {
    std::string nameFunction();
    bool validate(std::filesystem::path const &, std::filesystem::path const &);
    void parseFile(std::filesystem::path const &, std::filesystem::path const &, pricesVector_t &);
    std::string exchange(std::filesystem::path const &, std::filesystem::path const &);
    std::string security(std::filesystem::path const &, std::filesystem::path const &);
  }

}

#endif // INTERFACEPRICEUPLOAD_H
