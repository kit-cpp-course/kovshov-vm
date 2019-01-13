#pragma once

#include <string>
#include <iostream>
#include <cstring>

using namespace std;

class CmdArgs {
private:
    CmdArgs() = default;

public:
    static CmdArgs &getInstance() {
        static CmdArgs inst;
        return inst;
    }

    int argParser(int argc, char *argv[], string &in, string &out);
};