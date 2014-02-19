#ifndef VARIANT_H
#define VARIANT_H

namespace S5
{
    class Variant
    {
    public:
        enum Type
        {
            BOOL,
            INT,
            REAL,
            VECTOR_2,
            VECTOR_3,
            STRING,
            COLOR,
            TYPE_COUNT
        };

    private:
        Type _type;

        union Data
        {
            bool _bool;
            int _int;
            float _real;
            void* _ptr;
        };
        Data _data;
    };
}

#endif // VARIANT_H
