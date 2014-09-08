#include "luainterpreter.h"

#include <lua.hpp>

#include <iostream>

namespace S5
{
    static int l_my_print(lua_State* L)
    {
        int nargs = lua_gettop(L);

        for (int i=1; i <= nargs; i++)
        {
            if (lua_isstring(L, i))
            {
                /* Pop the next arg using lua_tostring(L, i) and do your print */
            }
            else
            {
                /* Do something with non-strings if you like */
            }
        }

        return 0;
    }

    static const struct luaL_Reg printlib [] = {
      {"print", l_my_print},
      {NULL, NULL} /* end of array */
    };

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

        /* uncomment to register print */
        /*
        lua_getglobal(_p->lua_state, "_G");
        luaL_register(_p->lua_state, NULL, printlib);
        lua_pop(_p->lua_state, 1);
        */
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
