#pragma once

namespace invalpha
{
    namespace script
    {
        enum class IASExitCode :unsigned char
        {
            INSTRUCTION_EXIT,
            UNDEFINED_INSTRUCTION,
            INSTRUCTION_NUMERICS_NEEDED
        };
    }
}