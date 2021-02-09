#pragma once
#include "../IASDataType.h"

namespace invalpha
{
    namespace script
    {
        enum class IASRegister :IASuint8
        {
            JMP_FLAG,
            CMP_FLAG
        };
    }
}