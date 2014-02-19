#include "objectmodel.h"

#include <exception>

namespace S5
{
    struct ObjectModel::Pimpl
    {
        std::string class_name;
    };

    ObjectModel::ObjectModel(const std::string& class_name)
    {
        _p = std::unique_ptr<Pimpl>(new Pimpl());

        _p->class_name = class_name;
    }

    ObjectModel::~ObjectModel()
    {}

    const std::string& ObjectModel::className() const
    {
        return _p->class_name;
    }

    bool ObjectModel::hasProperty(const std::string& property_name) const
    {
        return false;
    }
    const Variant& ObjectModel::getProperty(const std::string& property_name) const
    {
        throw std::exception();
    }

    void ObjectModel::setProperty(const std::string& property_name, const Variant& variant) const
    {
        throw std::exception();
    }

    void ObjectModel::setClassName(const std::string& class_name)
    {
        _p->class_name = class_name;
    }

    void ObjectModel::registerProperty(const std::string& property_name)
    {
        throw std::exception();
    }

}
