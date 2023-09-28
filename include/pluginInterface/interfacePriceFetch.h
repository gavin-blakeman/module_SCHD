//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Module: Investment Management
// FILE:                interfacePriceFetch
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
// HISTORY:             2023-09-26/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef INTERFACEPRICEFETCH_H
#define INTERFACEPRICEFETCH_H

  // Standard C++ libraries

#include <map>
#include <string>
#include <utility>
#include <vector>

  // Miscellaneous library header files

#include <GCL>

  // msmERP header files

#include "include/core/typeDefinitions.h"

namespace IMM::priceFetch
{
  using pricesVector_t = std::vector<std::pair<date_t, money_t>>;   ///< Vector to contain the retuened prices.
  struct securityExchange_t
  {
    std::string symbol;
    std::string exchange2;
    std::string exchange3;
    pricesVector_t prices;
  };

  using securityPrices_t = std::map<index_t, securityExchange_t>;

  using name_fn = std::string(void);
  using callback_fn = void(void *);
  using priceFetch_fn = void(callback_fn *, securityPrices_t *);


  extern "C"
  {
    std::string name();
    void priceFetch(callback_fn *, securityPrices_t *);
  }

}

#endif // INTERFACEPRICEFETCH_H
