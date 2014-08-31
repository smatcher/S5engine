#include "luainterpreter.h"

#include <lua.hpp>

#include <iostream>

namespace S5
{
    struct LuaInterpreter::Pimpl
    {
       lua_State* lua_state;
    };

    LuaInterpreter::LuaInterpreter()
        : IScriptInterpreter()
    {
        _p = std::unique_ptr<Pimpl>(new Pimpl());
    }

    LuaInterpreter::~LuaInterpreter()
    {
        lua_close(_p->lua_state);
    }

   void LuaInterpreter::init()
   {
        _p->lua_state = luaL_newstate();

        // load Lua libraries
        static const luaL_Reg lualibs[] =
        {
            { "base", luaopen_base },
            { NULL, NULL}
        };

        const luaL_Reg *lib = lualibs;
        for(; lib->func != NULL; lib++)
        {
            lib->func(_p->lua_state);
            lua_settop(_p->lua_state, 0);
        }
   }

   void LuaInterpreter::doString(const std::string &command)
   {
       luaL_dostring(_p->lua_state, command.c_str());
   }

   void LuaInterpreter::doFile(const std::string &filepath)
   {
       luaL_dofile(_p->lua_state, filepath.c_str());
   }
}
