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
        virtual void doString(const std::string& command) = 0;
        virtual void doFile(const std::string& filepath) = 0;
    };
}

#endif // ISCRIPTINTERPRETER_H
