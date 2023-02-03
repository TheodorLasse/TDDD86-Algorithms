TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES = $$files(*.cpp,true)
#SOURCES -= $$files(test-harness-myvector.cpp, true)
SOURCES -= $$files(test-harness-myvector.cpp, true)
SOURCES -= $$files(testharness-myprio.cpp, true)

HEADERS = $$files(*.h,true)
