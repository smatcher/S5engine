#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include <string>
#include <memory>

#include "variant.h"

namespace S5
{
    class ObjectModel
    {
    public:
        ObjectModel(const std::string& class_name);
        virtual ~ObjectModel();

        const std::string& className() const;

        bool hasProperty(const std::string& property_name) const;
        const Variant& getProperty(const std::string& property_name) const;
        void setProperty(const std::string& property_name, const Variant& variant) const;

    protected:
        void setClassName(const std::string& class_name);
        void registerProperty(const std::string& property_name);

    private:
        struct Pimpl;
        std::unique_ptr<Pimpl> _p;
    };
}

#endif // OBJECTMODEL_H
