#include "IASClosure.h"

invalpha::script::IASClosure::IASClosure(const IASPrototype& proto)
{
    
}

void invalpha::script::IASClosure::allocVariable(const IASVariableType& type, const IASuint32& data_pos)
{
    if (variable_write_index < func_memory.size())
    {
        func_memory[variable_write_index] = IASVariable();
        func_memory[variable_write_index].data_pos = data_pos;
        func_memory[variable_write_index].v_type = type;
    }
    else
    {
        func_memory.emplace_back();
        func_memory[variable_write_index].data_pos = data_pos;
        func_memory[variable_write_index].v_type = type;
        ++variable_write_index;
    }
}
