#pragma once
#include <vector>

#include "IASVariable.h"
#include "IASPrototype.h"

namespace invalpha
{
    namespace script
    {
        struct IASClosure
        {
            explicit IASClosure(const IASPrototype& proto);
            void allocVariable(const IASVariableType& type, const IASuint32& data_pos);
            void loadParm(IASVariable& variable);
            std::vector<IASVariable> func_memory;
            IASuint32 pc = 0;
            bool is_cpp_function = false;
            bool has_return_val = false;
            IASuint32 register_max_index = 0;
            IASuint32 parm_num = 0;
            IASuint32 variable_write_index = 0;
        };
    }
}