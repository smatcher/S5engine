#ifndef ISCRIPTINTERPRETER_H
#define ISCRIPTINTERPRETER_H

#include <string>

namespace S5
{
    class IScriptInterpreter
    {
    public:
        IScriptInterpreter() {}
        virtual ~IScriptInterpreter() {}

        virtual void init() = 0;
        virtual void eval(const std::string& command) = 0;
    };
}

#endif // ISCRIPTINTERPRETER_H
