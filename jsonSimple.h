#pragma once

#include <string>
#include <vector>
#include <cstring>

using namespace std;

/*
 * Мой обуительный класс
 */

class JSON {

public:

    class chunk {

    public:
        string name;
        string value;
        string valueType;

        chunk(string name, string value, string valueType) :
                name(std::move(name)),
                value(std::move(value)),
                valueType(std::move(valueType)) {}

        chunk(string name, string valueType) :
                name(std::move(name)),
                valueType(std::move(valueType)) {}
    };

    vector<chunk> data;

    bool isDigit(char c);

    bool isJsonChar(char c);

    vector<chunk> parseObject(const string &input);

    vector<chunk> parseArray(const string &input);

    string simplify(string &input);

    explicit JSON(string &input);
};


bool JSON::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool JSON::isJsonChar(char c) {
    char JsonChar[] = "{}[]:,\"";
    return strchr(JsonChar, c) != nullptr;
}

JSON::JSON(string &input) {
    input = simplify(input);
    data = parseObject(input);
}

string JSON::simplify(string &input) {
    string answer;
    bool inString = false;
    for (char i : input) {
        if (i == '\"') {
            answer += i;
            inString = !inString;
        } else if (inString) {
            answer += i;
        } else if (JSON::isDigit(i) ||
                   JSON::isJsonChar(i)) {
            answer += i;
        }
    }
    cout << answer << endl;
    return answer;
}

vector<JSON::chunk> JSON::parseObject(const string &input) {
    vector<JSON::chunk> data;
    bool isName = true;
    string name;
    for (unsigned int i = 1; i < input.length() - 1; ++i) {

        unsigned int startPos = i;

        if (input[i] == '\"') {
            do i++;
            while (input[i] != '\"');
            if (isName) {
                name = input.substr(startPos, i++ - startPos + 1);
                isName = false;
            } else {
                chunk addChunk(name, input.substr(startPos, i++ - startPos + 1), "string");
                data.push_back(addChunk);
                isName = true;
            }
        } else if (input[i] >= '0' && input[i] <= '9') {
            while (input[i] != ',' && input[i] != '}') {
                i++;
            }
            chunk addChunk(name, input.substr(startPos, i - startPos), "int");
            data.push_back(addChunk);
            isName = true;
        } else if (input[i] == '{') {
            do i++;
            while (input[i] != '}');
            chunk beginArray(name, "objectBegin");
            data.push_back(beginArray);
            vector<JSON::chunk> add = parseObject(input.substr(startPos, i - startPos + 1));
            data.insert(data.end(), add.begin(), add.end());
            chunk endArray(name, "objectEnd");
            data.push_back(endArray);
            isName = true;
        } else if (input[i] == '[') {
            do i++;
            while (input[i] != ']');
            chunk beginArray(name, "arrayBegin");
            data.push_back(beginArray);
            vector<JSON::chunk> add = parseObject(input.substr(startPos, i - startPos + 1));
            data.insert(data.end(), add.begin(), add.end());
            chunk endArray(name, "arrayEnd");
            data.push_back(endArray);
            isName = true;
        }
    }
    return data;
}

vector<JSON::chunk> JSON::parseArray(const string &input) {
    vector<JSON::chunk> data;
    return data;
}
