/*
* Copyright (c) 2025-present Henri Michelon
*
* This software is released under the MIT License.
* https://opensource.org/licenses/MIT
*/
module;
#include "lua.h"
export module lysa.ui.lua;

import std;
export import lua_bridge;

export namespace lysa::ui {

    struct LuaBindings {
        static inline bool registered{false};
        static void _register(lua_State* L);
    };

}
