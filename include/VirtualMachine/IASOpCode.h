#pragma once

namespace invalpha
{
    namespace script
    {
        enum class IASOpCode :unsigned char
        {
            // for numeric types
            OP_ADD,
            OP_SUB,
            OP_MUL,
            OP_DIV,
            OP_INTDIV,
            
            // for functions
            OP_CALL,
            OP_PUSHPARM,
            OP_POP,

            // execution logic
            OP_JMP,
            OP_JMPZ,
            OP_EXIT,
            OP_END,

            // logic
            OP_EQ,
            OP_LE,
            OP_LT,

            // registers
            OP_LOAD,
            OP_MOV,

            // memory
            OP_ALLOC,

            // easter egg XD
            OP_EASTEREGG
        };
    }
}