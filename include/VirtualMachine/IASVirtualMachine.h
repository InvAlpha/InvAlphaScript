#pragma once
#include <vector>
#include <string>
#include <functional>
#include <fstream>

#include "../IASDataType.h"
#include "IASClosureStack.h"
#include "../IASExitCode.h"

namespace invalpha
{
    namespace script
    {

        class IASVirtualMachine
        {
        public:
            void init();
            void loadByteCodes(const std::string& bytecode_path);
            void getInstructionOpCode(const IASuint32& instruction);
            void executeInstuction(const IASuint32& instruction);
            void releaseResources();

            // they are exposed for more elegant codes(or you need to set tons of friends:)
            IASuint32 pc = 0;
            IASClosureStack closure_stack;
        private:
            IASuint32 opcode_buffer = 0;

            std::vector<std::string> mem_string;
            std::vector<double> mem_real;
            std::vector<std::function<void(IASVirtualMachine*, const IASint32&)>> ins_action_table;

            std::vector<IASuint32> bytecodes;
        };

        namespace global
        {
            namespace
            {
                IASuint32 parm_buffer;
                IASuint32 parm_bufferA;
                IASuint32 parm_bufferB;
            }
        }

        namespace ins_action
        {
            void aux_getInsParmA(const IASuint32& instruction);
            void aux_getInsParmB(const IASuint32& instruction);
            void aux_getInsParm(const IASuint32& instruction);
            void ins_exit(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_add(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_sub(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_div(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_intdiv(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_mul(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_call(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_pushparmf(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_pushparm(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_pop(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_jmp(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_jmpz(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_eq(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_le(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_lt(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_load(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_mov(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
            void ins_alloc(IASVirtualMachine* vm_ptr, const IASuint32& instruction);
        }
    }
}