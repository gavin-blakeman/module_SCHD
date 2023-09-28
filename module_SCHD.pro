#-----------------------------------------------------------------------------------------------------------------------------------
#
# PROJECT:            msmERP
# SUBSYSTEM:          msmERP - Scheduler
# FILE:								module_SCJD.pro
# LANGUAGE:						C++
# TARGET OS:          LINUX
# LIBRARY DEPENDANCE:	None.
# NAMESPACE:          N/A
# AUTHOR:							Gavin Blakeman.
# LICENSE:            GPLv2
#
#                     Copyright 2023 Gavin Blakeman.
#
# OVERVIEW:						Project file for compiling the investment management module.
#
# HISTORY:            2023-09-28/GGB - File Created
#
#-----------------------------------------------------------------------------------------------------------------------------------

TARGET = module_SCHD

DESTDIR = ../../engineeringShop/modules

TEMPLATE = lib

QT += core
QT -= gui

CONFIG += cmdline
CONFIG += plugin no_plugin_name_prefix
CONFIG -= app_bundle
CONFIG += object_parallel_to_source

QMAKE_CXXFLAGS += -std=c++20 -DWT_CPP17_ANY_IMPLEMENTATION=std
QMAKE_LFLAGS += -Wl,--version-script=$${PWD}/module.version

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  \
    "../../engineeringShop" \
    "../../GCL" \
    "../../MCL" \
    "../../PCL" \
    "../../SCL" \
    "/usr/local/lib" \
    "../../WtExtensions" \
    "include" \
    "../../modules/module_FM"

SOURCES += \
  source/database/tables/tbl_SCHD_audit.cpp \
  source/database/tables/tbl_SCHD_taskTypes.cpp \
  source/database/tables/tbl_SCHD_workflowStatus.cpp \
  source/module_SCHD.cpp \
  source/taskScheduler.cpp



HEADERS += \
  include/database/tables/tbl_SCHD_audit.h \
  include/database/tables/tbl_SCHD_taskTypes.h \
  include/database/tables/tbl_SCHD_workflowStatus.h \
  include/taskScheduler.h




LIBS += -L../../GCL -lGCL

DISTFILES += \
  module.version \
  schema_SCHD

