#include "parserJSON.h"

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isJsonChar(char c) {
    char JsonChar[] = "{}[]:,\"";
    return strchr(JsonChar, c) != nullptr;
}

string parserJSON::simplify(string input) {
    string answer;
    bool inString = false;
    for (unsigned int i = 0; i < input.length(); i++) {
        if (input[i] == '\"') {
            answer += input[i];
            inString = !inString;
        } else if (inString) {
            answer += input[i];
        } else if (isDigit(input[i]) ||
                   isJsonChar(input[i])) {
            answer += input[i];
        } else if (input.substr(i, 4) == "null") {
            answer += input.substr(i, 4);
            i += 3;
        }
    }
    return answer;
}

vector<chunk> parseJSON(const string &input) {
    vector<chunk> data;
    bool isName = true;
    string name = input;
    int counter;
    for (unsigned int i = 1; i < input.length() - 1; ++i) {
        unsigned int startPos = i;
        if (input[i] == '\"') {
            //cout << "cin str\n";
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
            //cout << "cin int\n";
            while (input[i] != ',' && input[i] != '}') {
                i++;
            }
            chunk addChunk(name, input.substr(startPos, i - startPos), "int");
            data.push_back(addChunk);
            isName = true;
        } else if (input.substr(i, 4) == "null" ||
                   input.substr(i, 4) == "NULL") {
            //cout << "cin null\n";
            if (isName) {
                chunk addChunk("null");
                data.push_back(addChunk);
            } else {
                chunk addChunk(name, "null");
                data.push_back(addChunk);
                isName = true;
            }
        } else if (input[i] == '{') {
            //cout << "cin obj\n";
            counter = 1;
            do {
                i++;
                if (input[i] == '}')
                    counter--;
                if (input[i] == '{')
                    counter++;
            } while (counter > 0);
            if (!isName) {
                chunk beginArray(name, "objectBegin");
                data.push_back(beginArray);
                //cout << input.substr(startPos, i - startPos + 1) << endl;
                vector<chunk> add = parseJSON(input.substr(startPos, i - startPos + 1));
                data.insert(data.end(), add.begin(), add.end());
                chunk endArray(name, "objectEnd");
                data.push_back(endArray);
                isName = true;
            } else {
                chunk beginArray("objectBegin");
                data.push_back(beginArray);
                //cout << input.substr(startPos, i - startPos + 1) << endl;
                vector<chunk> add = parseJSON(input.substr(startPos, i - startPos + 1));
                data.insert(data.end(), add.begin(), add.end());
                chunk endArray("objectEnd");
                data.push_back(endArray);
            }
        } else if (input[i] == '[') {
            //cout << "cin arr\n";
            counter = 1;
            do {
                i++;
                if (input[i] == ']')
                    counter--;
                if (input[i] == '[')
                    counter++;
            } while (counter > 0);
            if (!isName) {
                chunk beginArray(name, "arrayBegin");
                data.push_back(beginArray);
                //cout << input.substr(startPos, i - startPos + 1) << endl;
                vector<chunk> add = parseJSON(input.substr(startPos, i - startPos + 1));
                data.insert(data.end(), add.begin(), add.end());
                chunk endArray(name, "arrayEnd");
                data.push_back(endArray);
                isName = true;
            } else {
                chunk beginArray("arrayBegin");
                data.push_back(beginArray);
                //cout << input.substr(startPos, i - startPos + 1) << endl;
                vector<chunk> add = parseJSON(input.substr(startPos, i - startPos + 1));
                data.insert(data.end(), add.begin(), add.end());
                chunk endArray("arrayEnd");
                data.push_back(endArray);
            }
        }
    }
    return data;
}

string addTabs(int n) {
    string
            ans;
    for (int i = 0; i < n; ++i) {
        ans += '\t';
    }
    return ans;
}

string parserJSON::parseFromObject(modelObject input) {
    vector<chunk> data = input.getData();
    string ans = "{\n";
    int tabs = 1;
    for (auto &i : data) {

        if (i.valueType == "string") {
            ans += addTabs(tabs) + i.name + ":" + i.value + ",\n";
        } else if (i.valueType == "int") {
            ans += addTabs(tabs) + i.name + "\":" + i.value + ",\n";
        } else if (i.valueType == "objectBegin") {
            if (!i.name.empty())
                ans += addTabs(tabs) + i.name + ":{\n";
            else
                ans += addTabs(tabs) + "{\n";
            tabs++;
        } else if (i.valueType == "objectEnd") {
            tabs--;
            ans += addTabs(tabs) + "},\n";
        } else if (i.valueType == "arrayBegin") {
            if (!i.name.empty())
                ans += addTabs(tabs) + i.name + ":[\n";
            else
                ans += addTabs(tabs) + "[\n";
            tabs++;
        } else if (i.valueType == "arrayEnd") {
            tabs--;
            ans += addTabs(tabs) + "],\n";
        }
    }
    ans += "}";
    return ans;
}

modelObject parserJSON::parseToObject(string input) {
    string ans = simplify(input);
    try {
        return modelObject(parseJSON(ans));
    } catch (...) {
        throw ("Parsing exception");
    }
}