#include "IASVirtualMachine.h"

invalpha::script::IASVirtualMachine::~IASVirtualMachine()
{
    releaseResources();
}

void invalpha::script::IASVirtualMachine::init()
{
    ins_action_table.push_back(ins_action::ins_add);
    ins_action_table.push_back(ins_action::ins_sub);
    ins_action_table.push_back(ins_action::ins_mul);
    ins_action_table.push_back(ins_action::ins_div);
    ins_action_table.push_back(ins_action::ins_intdiv);
    ins_action_table.push_back(ins_action::ins_call);
    ins_action_table.push_back(ins_action::ins_pushparm);
    ins_action_table.push_back(ins_action::ins_pop);
    ins_action_table.push_back(ins_action::ins_jmp);
    ins_action_table.push_back(ins_action::ins_jmpz);
    ins_action_table.push_back(ins_action::ins_exit);
    ins_action_table.push_back(ins_action::ins_end);
    ins_action_table.push_back(ins_action::ins_eq);
    ins_action_table.push_back(ins_action::ins_le);
    ins_action_table.push_back(ins_action::ins_lt);
    ins_action_table.push_back(ins_action::ins_load);
    ins_action_table.push_back(ins_action::ins_mov);
}

void invalpha::script::IASVirtualMachine::loadByteCodes(const std::string& bytecode_path)
{

}

void invalpha::script::IASVirtualMachine::getInstructionOpCode(const IASuint32& instruction)
{
    opcode_buffer = instruction >> 26;
}

void invalpha::script::IASVirtualMachine::executeInstuction(const IASuint32& instruction)
{
    getInstructionOpCode(instruction);
    if (opcode_buffer >= ins_action_table.size())
    {
        releaseResources();
        std::exit((int)IASExitCode::UNDEFINED_INSTRUCTION);
    }
    ins_action_table[opcode_buffer](this, instruction);
}

invalpha::script::IASuint32 invalpha::script::IASVirtualMachine::allocVariable(const IASVariableType& type)
{
    switch (type)
    {
    case IASVariableType::INTEGER:
        mem_real.emplace_back();
        return mem_real.size() - 1;
    case IASVariableType::DOUBLE:
        mem_real.emplace_back();
        return mem_real.size() - 1;
    case IASVariableType::STRING:
        mem_string.emplace_back();
        return mem_string.size() - 1;
    default: break;
    }
}

void invalpha::script::IASVirtualMachine::releaseResources()
{

}

void invalpha::script::ins_action::aux_getInsParmA(const IASuint32& instruction)
{
    aux_getInsParm(instruction);
    global::parm_bufferA = global::parm_buffer >> 13;
}

void invalpha::script::ins_action::aux_getInsParmB(const IASuint32& instruction)
{
    global::parm_bufferB = (instruction << 19) >> 19;
}

void invalpha::script::ins_action::aux_getInsParm(const IASuint32& instruction)
{
    global::parm_buffer = (instruction << 6) >> 6;
}

void invalpha::script::ins_action::ins_exit(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    vm_ptr->releaseResources();
    std::exit((int)IASExitCode::INSTRUCTION_EXIT);
}

void invalpha::script::ins_action::ins_add(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
    auto closure_ptr = vm_ptr->closure_stack.top();
    if (!((IASuint8)closure_ptr->func_memory[global::parm_bufferA].v_type +
        (IASuint8)closure_ptr->func_memory[global::parm_bufferB].v_type < 3))
        std::exit((int)IASExitCode::INSTRUCTION_NUMERICS_NEEDED);
    vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos] +=
        vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferB].data_pos];
}

void invalpha::script::ins_action::ins_sub(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
    auto closure_ptr = vm_ptr->closure_stack.top();
    if (!((IASuint8)closure_ptr->func_memory[global::parm_bufferA].v_type +
        (IASuint8)closure_ptr->func_memory[global::parm_bufferB].v_type < 3))
        std::exit((int)IASExitCode::INSTRUCTION_NUMERICS_NEEDED);
    vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos] -=
        vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferB].data_pos];
}

void invalpha::script::ins_action::ins_div(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
    auto closure_ptr = vm_ptr->closure_stack.top();
    if (!((IASuint8)closure_ptr->func_memory[global::parm_bufferA].v_type +
        (IASuint8)closure_ptr->func_memory[global::parm_bufferB].v_type < 3))
        std::exit((int)IASExitCode::INSTRUCTION_NUMERICS_NEEDED);
    vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos] /=
        vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferB].data_pos];
}

void invalpha::script::ins_action::ins_intdiv(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
    auto closure_ptr = vm_ptr->closure_stack.top();
    if (!((IASuint8)closure_ptr->func_memory[global::parm_bufferA].v_type +
        (IASuint8)closure_ptr->func_memory[global::parm_bufferB].v_type < 3))
        std::exit((int)IASExitCode::INSTRUCTION_NUMERICS_NEEDED);
    vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos] /=
        vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferB].data_pos];
    vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos] =
        (IASuint64)vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos];
}

void invalpha::script::ins_action::ins_mul(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
    auto closure_ptr = vm_ptr->closure_stack.top();
    if (!((IASuint8)closure_ptr->func_memory[global::parm_bufferA].v_type +
        (IASuint8)closure_ptr->func_memory[global::parm_bufferB].v_type < 3))
        std::exit((int)IASExitCode::INSTRUCTION_NUMERICS_NEEDED);
    vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos] *=
        vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferB].data_pos];
}

void invalpha::script::ins_action::ins_call(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParm(instruction);
    vm_ptr->closure_stack.pushClosure(vm_ptr->prototypes[global::parm_buffer]);
    for (IASuint32 i = 0; i < vm_ptr->closure_stack.top()->parm_num; i++)
    {
        vm_ptr->closure_stack.top()->loadParm(vm_ptr->parm_stack.top());
        vm_ptr->parm_stack.pop();
    }

}

void invalpha::script::ins_action::ins_pushparm(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParm(instruction);
    vm_ptr->parm_stack.push(vm_ptr->closure_stack.top()->func_memory[global::parm_buffer]);
}

void invalpha::script::ins_action::ins_pop(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{

}

void invalpha::script::ins_action::ins_jmp(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParm(instruction);
    vm_ptr->pc = global::parm_buffer;
}

void invalpha::script::ins_action::ins_jmpz(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParm(instruction);
    if (vm_ptr->mem_real[vm_ptr->closure_stack.top()->func_memory[(IASuint32)IASRegister::JMP_FLAG].data_pos] == 0)
        vm_ptr->pc = global::parm_buffer;
}

void invalpha::script::ins_action::ins_eq(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
    auto closure_ptr = vm_ptr->closure_stack.top();
    if (vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos] ==
        vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferB].data_pos])
        vm_ptr->mem_real[vm_ptr->closure_stack.top()->func_memory[(IASuint32)IASRegister::CMP_FLAG].data_pos] = true;
}

void invalpha::script::ins_action::ins_le(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
    auto closure_ptr = vm_ptr->closure_stack.top();
    if (!((IASuint8)closure_ptr->func_memory[global::parm_bufferA].v_type +
        (IASuint8)closure_ptr->func_memory[global::parm_bufferB].v_type < 3))
        std::exit((int)IASExitCode::INSTRUCTION_NUMERICS_NEEDED);
    if (vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos] <=
        vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferB].data_pos])
        vm_ptr->mem_real[vm_ptr->closure_stack.top()->func_memory[(IASuint32)IASRegister::CMP_FLAG].data_pos] = true;
}

void invalpha::script::ins_action::ins_lt(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
    auto closure_ptr = vm_ptr->closure_stack.top();
    if (!((IASuint8)closure_ptr->func_memory[global::parm_bufferA].v_type +
        (IASuint8)closure_ptr->func_memory[global::parm_bufferB].v_type < 3))
        std::exit((int)IASExitCode::INSTRUCTION_NUMERICS_NEEDED);
    if (vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferA].data_pos] <
        vm_ptr->mem_real[closure_ptr->func_memory[global::parm_bufferB].data_pos])
        vm_ptr->mem_real[vm_ptr->closure_stack.top()->func_memory[(IASuint32)IASRegister::CMP_FLAG].data_pos] = true;
}

void invalpha::script::ins_action::ins_load(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{

}

void invalpha::script::ins_action::ins_mov(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{


}

void invalpha::script::ins_action::ins_alloc(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmB(instruction);
    global::parm_bufferA = vm_ptr->allocVariable((IASVariableType)global::parm_bufferB); // resource saving
    vm_ptr->closure_stack.top()->allocVariable((IASVariableType)global::parm_bufferB, global::parm_bufferA);
}

void invalpha::script::ins_action::ins_end(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    auto closure_ptr = vm_ptr->closure_stack.top();
    if (closure_ptr->has_return_val)
        vm_ptr->parm_stack.push(closure_ptr->func_memory[closure_ptr->variable_write_index - 1]);
    vm_ptr->closure_stack.pop();
}
