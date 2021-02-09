#pragma once
#include <vector>

#include "IASVariable.h"
#include "IASPrototype.h"

namespace invalpha
{
    namespace script
    {
        class IASClosure
        {
        public:
            explicit IASClosure(const IASPrototype& proto);
        private:
            IASuint32 pc = 0;
            bool is_cpp_function = false;
            IASuint32 register_max_index = 0;
            std::vector<IASVariable> func_mem;
        };
    }
}