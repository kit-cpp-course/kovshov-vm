#pragma once

#include <string>

using namespace std;

class CmdArgs {
private:
    CmdArgs() = default;

public:
    static CmdArgs &getInstance() {
        static CmdArgs inst;
        return inst;
    }

    int argParser(int argc, char *argv[], string &path);
};