#pragma once
#include <vector>
#include <memory>

#include "IASClosure.h"
#include "IASPrototype.h"
#include "../IASDataType.h"

namespace invalpha
{
    namespace script
    {
        class IASClosureStack
        {
        public:
            // warning: the closure shouldn't be reused directly as it's managed by this Closure Stack
            void pushClosure(const IASPrototype& proto);
            // assume that we don't use pop() when the stack is empty
            void pop();
            std::shared_ptr<IASClosure> top() const;
        private:
            IASuint32 write_index = 0;
            std::vector<std::shared_ptr<IASClosure>> stack; // actually it's a vector:)
        };
    }
}