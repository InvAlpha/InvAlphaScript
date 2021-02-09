#include "IASClosureStack.h"

void invalpha::script::IASClosureStack::pushClosure(const IASPrototype& proto)
{
    if (write_index < stack.size())
        stack[write_index] = std::make_shared<IASClosure>(proto);
    else
    {
        stack.push_back(std::make_shared<IASClosure>(proto));
        ++write_index;
    }
}

void invalpha::script::IASClosureStack::pop()
{
    --write_index;
}

std::shared_ptr<invalpha::script::IASClosure> invalpha::script::IASClosureStack::top() const
{
    if (write_index > 0)
        return stack[write_index - 1];
    return stack[0];
}
