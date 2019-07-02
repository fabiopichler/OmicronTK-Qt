#*******************************************************************************
#  OmicronTK+Qt
#
#  Author: Fábio Pichler
#  Website: http://fabiopichler.net
#  License: MIT License
#
#  Copyright 2018-2019, Fábio Pichler
#
#  Permission is hereby granted, free of charge, to any person obtaining
#  a copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the Software
#  is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be
#  included in all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
#  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
#  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
#*******************************************************************************

include(../project.pri)

QT = core gui widgets
TARGET = OmicronTK+Qt_Lua$${DEBUG}
DEFINES += OTKQT_BUILD_LUA_LIB

unix:INCLUDEPATH += "$${OTKLUA_UNIX}/project/include"
win32:INCLUDEPATH += "$${OTKLUA_WIN}\\project\\include"

unix:LIBS += -ldl -llua
win32:LIBS +=  -llua53

LIBS += -lOmicronTK+Qt$${DEBUG} -lOmicronTK+Lua$${DEBUG}

contains(QMAKE_HOST.arch, x86_64) {

    unix:INCLUDEPATH += $${LUA_INCLUDE_PATH_UNIX64}
    unix:LIBS += -L$${LUA_LIB_PATH_UNIX64}

    win32:INCLUDEPATH += $${LUA_INCLUDE_PATH_WIN64}
    win32:LIBS += -L$${LUA_LIB_PATH_WIN64}

    unix:LIBS += -L"$${OTKLUA_UNIX}/linux64/build"
    win32:LIBS += -L"$${OTKLUA_WIN}/win64/build"

} else {

    unix:INCLUDEPATH += $${LUA_INCLUDE_PATH_UNIX32}
    unix:LIBS += -L$${LUA_LIB_PATH_UNIX32}

    win32:INCLUDEPATH += $${LUA_INCLUDE_PATH_WIN32}
    win32:LIBS += -L$${LUA_LIB_PATH_WIN32}

    unix:LIBS += -L"$${OTKLUA_UNIX}/linux32/build"
    win32:LIBS += -L"$${OTKLUA_WIN}/win32/build"

}

win32:RC_FILE = lua.rc

SOURCES += \
    LuaComboBox.cpp \
    LuaObject.cpp \
    LuaWidget.cpp \
    LuaLabel.cpp \
    LuaLayout.cpp \
    LuaSlider.cpp \
    LuaProgressBar.cpp \
    LuaLineEdit.cpp \
    LuaPushButton.cpp \
    base/LuaObjectBase.cpp \
    base/LuaWidgetBase.cpp

HEADERS += \
    ../../include/OmicronTK/Qt/Lua/LuaComboBox.hpp \
    ../../include/OmicronTK/Qt/Lua/LuaObject.hpp \
    ../../include/OmicronTK/Qt/Lua/LuaWidget.hpp \
    ../../include/OmicronTK/Qt/Lua/LuaLabel.hpp \
    ../../include/OmicronTK/Qt/Lua/LuaLayout.hpp \
    ../../include/OmicronTK/Qt/Lua/LuaSlider.hpp \
    ../../include/OmicronTK/Qt/Lua/LuaProgressBar.hpp \
    ../../include/OmicronTK/Qt/Lua/LuaLineEdit.hpp \
    ../../include/OmicronTK/Qt/Lua/LuaPushButton.hpp \
    base/LuaObjectBase.hpp \
    base/LuaWidgetBase.hpp


