/*******************************************************************************
  OmicronTK+Qt

  Author: Fábio Pichler
  Website: http://fabiopichler.net
  License: MIT License

  Copyright 2018-2019, Fábio Pichler

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the Software
  is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#include "OmicronTK/Qt/Lua/LuaProgressBar.hpp"
#include "OmicronTK/Qt/Lua/base/LuaWidgetBase.hpp"

#include <OmicronTK/lua/util/ObjectUtil.hpp>
#include <iostream>

#include <QProgressBar>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace QT {

static const char tableName[] = "ProgressBar";

int ProgressBar_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
        return luaL_error(L, "QProgressBar: expecting 0 arguments");

    ObjectUtil<QProgressBar, tableName>::newUserData(L, 1, new QProgressBar);

    return 0;
}

int ProgressBar_setOrientation(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QProgressBar *self = ObjectUtil<QProgressBar, tableName>::checkUserData(L, 1);
    int orientation = static_cast<int>(lua_tointegerx(L, 2, nullptr));

    self->setOrientation(static_cast<Qt::Orientation>(orientation));

    return 0;
}

int ProgressBar_setInvertedAppearance(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QProgressBar *self = ObjectUtil<QProgressBar, tableName>::checkUserData(L, 1);
    self->setInvertedAppearance(lua_toboolean(L, 2));

    return 0;
}

int ProgressBar_setTextVisible(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QProgressBar *self = ObjectUtil<QProgressBar, tableName>::checkUserData(L, 1);
    self->setTextVisible(lua_toboolean(L, 2));

    return 0;
}

void LuaProgressBar::require(lua::Lua *state)
{
    lua::Class luaClass(tableName);

    luaClass.setMembers(LuaWidgetBase::methods());

    luaClass.addConstructor(ProgressBar_new);

    luaClass.addMember("setOrientation", ProgressBar_setOrientation);
    luaClass.addMember("setInvertedAppearance", ProgressBar_setInvertedAppearance);
    luaClass.addMember("setTextVisible", ProgressBar_setTextVisible);

    state->createClass(luaClass);
}

}
}
