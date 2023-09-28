#-----------------------------------------------------------------------------------------------------------------------------------
#
# PROJECT:            msmERP
# FILE:								module_organsiation.pro
# SUBSYSTEM:          Project File - O
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
# HISTORY:            2023-07-18/GGB - File Created
#
#-----------------------------------------------------------------------------------------------------------------------------------

TARGET = module_IMM

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
  source/database/models/modelCostTypes.cpp \
  source/database/models/modelExchanges.cpp \
  source/database/models/modelPortfolio.cpp \
  source/database/models/modelSecurities.cpp \
  source/database/tables/tbl_imm_audit.cpp \
  source/database/tables/tbl_imm_configuration.cpp \
  source/database/tables/tbl_imm_costTypes.cpp \
  source/database/tables/tbl_imm_customerTransactionLines.cpp \
  source/database/tables/tbl_imm_customerTransactionType.cpp \
  source/database/tables/tbl_imm_customerTransactions.cpp \
  source/database/tables/tbl_imm_exchanges.cpp \
  source/database/tables/tbl_imm_portfolio.cpp \
  source/database/tables/tbl_imm_portfolioValue.cpp \
  source/database/tables/tbl_imm_securities.cpp \
  source/database/tables/tbl_imm_securityPrices.cpp \
  source/database/tables/tbl_imm_securityTypes.cpp \
  source/database/tables/tbl_imm_tradingLedger.cpp \
  source/database/tables/tbl_imm_transactionLines.cpp \
  source/database/tables/tbl_imm_transactionTypes.cpp \
  source/database/tables/tbl_imm_transactions.cpp \
  source/database/tables/tbl_imm_workflowStatus.cpp \
  source/database/views/viewCostType.cpp \
  source/database/views/viewExchange.cpp \
  source/database/views/viewPortfolio.cpp \
  source/database/views/viewSecurity.cpp \
  source/database/views/viewTransaction.cpp \
  source/database/views/viewTransactionLines.cpp \
  source/database/views/view_imm_configuration.cpp \
  source/database/views/view_imm_customerTransaction.cpp \
  source/database/views/view_imm_customerTransactionLines.cpp \
  source/module_IMM.cpp \
  source/priceFetchManager.cpp \
  source/priceUploadManager.cpp \
  source/processBusinessTransactions.cpp


HEADERS += \
  include/database/models/modelCostTypes.h \
  include/database/models/modelExchanges.h \
  include/database/models/modelPortfolio.h \
  include/database/models/modelSecurities.h \
  include/database/tables/tbl_imm_audit.h \
  include/database/tables/tbl_imm_customerTransactionLines.h \
  include/database/tables/tbl_imm_customerTransactionType.h \
  include/database/tables/tbl_imm_customerTransactions.h \
  include/database/tables/tbl_imm_portfolioValue.h \
  include/database/tables/tbl_imm_tradingLedger.h \
  include/database/views/view_imm_customerTransaction.h \
  include/database/views/view_imm_customerTransactionLines.h \
  include/pluginInterface/interfacePriceFetch.h \
  include/pluginInterface/interfacePriceUpload.h \
  include/priceFetchManager.h \
  include/priceUploadManager.h \
  include/processBusinessTransactions.h \
  include/database/tables/tbl_imm_configuration.h \
  include/database/tables/tbl_imm_costTypes.h \
  include/database/tables/tbl_imm_exchanges.h \
  include/database/tables/tbl_imm_portfolio.h \
  include/database/tables/tbl_imm_securities.h \
  include/database/tables/tbl_imm_securityPrices.h \
  include/database/tables/tbl_imm_securityTypes.h \
  include/database/tables/tbl_imm_transactionLines.h \
  include/database/tables/tbl_imm_transactionTypes.h \
  include/database/tables/tbl_imm_transactions.h \
  include/database/tables/tbl_imm_workflowStatus.h \
  include/database/views/viewCostType.h \
  include/database/views/viewExchange.h \
  include/database/views/viewPortfolio.h \
  include/database/views/viewSecurity.h \
  include/database/views/viewTransaction.h \
  include/database/views/viewTransactionLines.h \
  include/database/views/view_imm_configuration.h



LIBS += -L../../GCL -lGCL

DISTFILES += \
  module.version \
  pluginTransaction.version \
  schema_IMM

