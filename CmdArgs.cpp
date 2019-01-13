#include "CmdArgs.h"

int CmdArgs::argParser(int argc, char *argv[], string &in, string &out) {
    if (argc < 2) {
        cout << "Enter input file\n";
        return 0;
    }
    if (argc == 2) {
        string input = argv[1];
        if (input.substr(input.length() - 4, 4) == ".xml") {
            in = input;
            return 1;
        }
        if (input.substr(input.length() - 5, 5) == ".json") {
            in = input;
            return 2;
        }
    }
    if (argc == 3) {
        string input = argv[1];
        string output = argv[2];
        if (input.substr(input.length() - 4, 4) == ".xml" && output.substr(input.length() - 5, 5) == ".json") {
            in = input;
            out = output;
            return 3;
        }
        if (input.substr(input.length() - 5, 5) == ".json" && output.substr(input.length() - 4, 4) == ".xml") {
            in = input;
            out = output;
            return 4;
        }
    }
    cout << "Enter file in in format JSON or XML [output file]\n";
    return 0;
}