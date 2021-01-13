QT += testlib
QT += core gui widgets


CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test_rocords.cpp \
../draw_test/rocords.cpp \
../draw_test/extendedgraphicview.cpp \
../draw_test/drawmanager.cpp

HEADERS += \
../draw_test/rocords.h \
../draw_test/extendedgraphicview.h \
../draw_test/drawmanager.h
