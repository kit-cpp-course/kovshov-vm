#include <iostream>
#include <fstream>

#include "ParserJSON.h"
#include "ParserXML.h"
#include "CmdArgs.h"

using namespace std;

int main(int argc, char *argv[]) {

    string in;
    string out;
    CmdArgs cmdArgs = CmdArgs::getInstance();
    int flag = cmdArgs.argParser(argc, argv, in, out);

    if (flag == 0)
        return -1;

    Parser *XML_P = new parserXML;
    Parser *JSON_P = new parserJSON;
    string data, line;

    switch (flag) {
        case 1 : {
            ifstream in_stream;
            in_stream.open(in);
            if (in_stream.is_open()) {
                while (getline(in_stream, line)) {
                    data += line;
                }
            }
            in_stream.close();
            ofstream out_stream(in.substr(0, in.length() - 3) + "json");
            if (out_stream.is_open()) {
                out_stream << JSON_P->parseFromObject(XML_P->parseToObject(data));
            }
            out_stream.close();
            break;
        }
        case 2 : {
            ifstream in_stream;
            in_stream.open(in);
            if (in_stream.is_open()) {
                while (getline(in_stream, line)) {
                    data += line;
                }
            }
            in_stream.close();
            ofstream out_stream(in.substr(0, in.length() - 4) + "xml");
            if (out_stream.is_open()) {
                out_stream << XML_P->parseFromObject(JSON_P->parseToObject(data));
            }
            out_stream.close();
            break;
        }
        case 3 : {
            ifstream in_stream;
            in_stream.open(in);
            if (in_stream.is_open()) {
                while (getline(in_stream, line)) {
                    data += line;
                }
            }
            in_stream.close();
            ofstream out_stream;
            out_stream.open(out);
            if (out_stream.is_open()) {
                out_stream << JSON_P->parseFromObject(XML_P->parseToObject(data));
            }
            out_stream.close();
            break;
        }
        case 4 : {
            ifstream in_stream;
            in_stream.open(in);
            if (in_stream.is_open()) {
                while (getline(in_stream, line)) {
                    data += line;
                }
            }
            in_stream.close();
            ofstream out_stream;
            out_stream.open(out);
            if (out_stream.is_open()) {
                out_stream << XML_P->parseFromObject(JSON_P->parseToObject(data));
            }
            out_stream.close();
            break;
        }
        default:
            break;
    }
    return 0;
}