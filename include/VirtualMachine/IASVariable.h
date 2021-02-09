#pragma once
#include "../IASDataType.h"

namespace invalpha
{
    namespace script
    {
        enum class IASVariableType : unsigned char
        {
            INTEGER,
            DOUBLE,
            STRING
        };

        struct IASVariable
        {
            IASuint32 data_pos;
            IASVariableType v_type;
        };
    }
}