// This file is used for test. In other words, it's useless to you.
#include "../include/IASinclude.h"

#include <iostream>

int main(int argc, char* argv[])
{
    using namespace invalpha::script;
    IASVirtualMachine vm;
    vm.init();
    IASLexer lexer;
    lexer.init();
    lexer.loadSource("helloworld.ias");
    lexer.dbg_analyzeAll();
    std::cin.get();
    return 0;
}