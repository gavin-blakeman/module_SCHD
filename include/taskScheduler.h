//**********************************************************************************************************************************
//
// PROJECT:             msmERP
// SUBSYSTEM:           Core Application
// FILE:                taskScheduler.h
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
// HISTORY:             2023-09-28/GGB - File created.
//
//**********************************************************************************************************************************

#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

  // Standard C++ library header files

  // Miscellaneous library header files.

#include <GCL>

  // msmERP header files

#include "include/core/typeDefinitions.h"

namespace scheduler
{
  class CScheduler
  {
  public:
    CScheduler();

  private:
    CScheduler(CScheduler const &) = delete;
    CScheduler &operator=(CScheduler const &) = delete;
    CScheduler(CScheduler &&) = delete;
    CScheduler &operator=(CScheduler &&) = delete;

    GCL::alarm::CAlarmCore alarmCore;

    void loadScheduledTasks();
  };
}

#endif // TASKSCHEDULER_H
