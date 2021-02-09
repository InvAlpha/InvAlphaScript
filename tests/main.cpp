// This file is used for test. In other words, it's useless to you.
#include "../include/IASinclude.h"

#include <iostream>

struct A
{
    std::string x;
};

int main(int argc, char* argv[])
{
    using namespace invalpha::script;
    IASVirtualMachine vm;
    vm.init();
    return 0;
}