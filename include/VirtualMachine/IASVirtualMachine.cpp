#include "IASVirtualMachine.h"

void invalpha::script::IASVirtualMachine::init()
{
    ins_action_table.push_back(ins_action::ins_add);
    ins_action_table.push_back(ins_action::ins_sub);
    ins_action_table.push_back(ins_action::ins_mul);
    ins_action_table.push_back(ins_action::ins_div);
    ins_action_table.push_back(ins_action::ins_intdiv);
    ins_action_table.push_back(ins_action::ins_call);
    ins_action_table.push_back(ins_action::ins_pushparmf);
    ins_action_table.push_back(ins_action::ins_pushparm);
    ins_action_table.push_back(ins_action::ins_pop);
    ins_action_table.push_back(ins_action::ins_jmp);
    ins_action_table.push_back(ins_action::ins_jmpz);
    ins_action_table.push_back(ins_action::ins_exit);
    ins_action_table.push_back(ins_action::ins_eq);
    ins_action_table.push_back(ins_action::ins_le);
    ins_action_table.push_back(ins_action::ins_lt);
    ins_action_table.push_back(ins_action::ins_load);
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
}

void invalpha::script::ins_action::ins_sub(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
}

void invalpha::script::ins_action::ins_div(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
}

void invalpha::script::ins_action::ins_intdiv(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
}

void invalpha::script::ins_action::ins_mul(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
    aux_getInsParmA(instruction);
    aux_getInsParmB(instruction);
}

void invalpha::script::ins_action::ins_call(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_pushparmf(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_pushparm(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_pop(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_jmp(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_jmpz(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_eq(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_le(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_lt(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_load(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_mov(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}

void invalpha::script::ins_action::ins_alloc(IASVirtualMachine* vm_ptr, const IASuint32& instruction)
{
}
