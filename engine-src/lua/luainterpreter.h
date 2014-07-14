#ifndef LUAINTERPRETER_H
#define LUAINTERPRETER_H

#include <abstraction/iscriptinterpreter.h>

#include <memory>

namespace S5
{
    class LuaInterpreter : public IScriptInterpreter
    {
    public:
        LuaInterpreter();
        virtual ~LuaInterpreter();

        virtual void init();
        virtual void eval(const std::string &command);

    private:
        struct Pimpl;
        std::unique_ptr<Pimpl> _p;
    };
}

#endif // LUAINTERPRETER_H
