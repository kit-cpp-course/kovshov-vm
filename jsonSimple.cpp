#include "jsonSimple.h"

bool JSON::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool JSON::isJsonChar(char c) {
    char JsonChar[] = "{}[]:,\"";
    return strchr(JsonChar, c) != nullptr;
}

JSON::JSON(string &input) {
    formJSON = simplify(input);
    try {
        data = parse(formJSON);
        formXML = parseToXML();
    } catch (exception e) {
        throw ("Parsing exception");
    }
}

string JSON::simplify(string &input) {
    //cout << input << endl;
    string answer;
    bool inString = false;
    for (unsigned int i = 0; i < input.length(); i++) {
        if (input[i] == '\"') {
            answer += input[i];
            inString = !inString;
        } else if (inString) {
            answer += input[i];
        } else if (JSON::isDigit(input[i]) ||
                   JSON::isJsonChar(input[i])) {
            answer += input[i];
        } else if (input.substr(i, 4) == "null") {
            answer += input.substr(i, 4);
            i += 3;
        }
    }
    //cout << answer << endl;
    return answer;
}

vector<JSON::chunk> JSON::parse(const string &input) {
    vector<JSON::chunk> data;
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
                vector<JSON::chunk> add = parse(input.substr(startPos, i - startPos + 1));
                data.insert(data.end(), add.begin(), add.end());
                chunk endArray(name, "objectEnd");
                data.push_back(endArray);
                isName = true;
            } else {
                chunk beginArray("objectBegin");
                data.push_back(beginArray);
                //cout << input.substr(startPos, i - startPos + 1) << endl;
                vector<JSON::chunk> add = parse(input.substr(startPos, i - startPos + 1));
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
                vector<JSON::chunk> add = parse(input.substr(startPos, i - startPos + 1));
                data.insert(data.end(), add.begin(), add.end());
                chunk endArray(name, "arrayEnd");
                data.push_back(endArray);
                isName = true;
            } else {
                chunk beginArray("arrayBegin");
                data.push_back(beginArray);
                //cout << input.substr(startPos, i - startPos + 1) << endl;
                vector<JSON::chunk> add = parse(input.substr(startPos, i - startPos + 1));
                data.insert(data.end(), add.begin(), add.end());
                chunk endArray("arrayEnd");
                data.push_back(endArray);
            }
        }
    }
    return data;
}

string JSON::addTabs(int n) {
    string ans;
    for (int i = 0; i < n; ++i) {
        ans += '\t';
    }
    return ans;
}

string JSON::parseToXML() {

    vector<pair<string, int>> activeArray;
    stack<string> activeObject;
    string answer, help;
    bool inArr;
    int tabs = 0;

    for (auto &i : data) {
        inArr = false;
        for (auto &j : activeArray) {
            if (tabs - 1 == j.second) {
                inArr = true;
                help = j.first;
            }
        }

        if (i.valueType == "string") {

            if (inArr)
                answer += addTabs(tabs - 1) + printArray(help, true);
            answer += addTabs(tabs) +
                      '<' + i.name.substr(1, i.name.length() - 2) + '>' +
                      i.value.substr(1, i.value.length() - 2) +
                      "</" + i.name.substr(1, i.name.length() - 2) + ">\n";
            if (inArr)
                answer += addTabs(tabs - 1) + printArray(help, false);

        } else if (i.valueType == "int") {

            if (inArr)
                answer += addTabs(tabs - 1) + printArray(help, true);
            answer += addTabs(tabs) +
                      '<' + i.name.substr(1, i.name.length() - 2) + '>' +
                      i.value +
                      "</" + i.name.substr(1, i.name.length() - 2) + ">\n";
            if (inArr)
                answer += addTabs(tabs - 1) + printArray(help, false);

        } else if (i.valueType == "null") {

            if (inArr)
                answer += addTabs(tabs - 1) + printArray(help, true);
            if (!i.name.empty()) {
                answer += "</" + i.name.substr(1, i.name.length() - 2) + ">\n";
            }
            if (inArr)
                answer += addTabs(tabs - 1) + printArray(help, false);

        } else if (i.valueType == "objectBegin") {

            if (inArr)
                answer += addTabs(tabs - 1) + printArray(help, true);
            if (i.name.empty())
                activeObject.push("");
            else {
                answer += addTabs(tabs) + '<' + i.name.substr(1, i.name.length() - 2) + ">\n";
                activeObject.push(i.name);
            }
            tabs++;

        } else if (i.valueType == "objectEnd") {

            help = activeObject.top();
            activeObject.pop();
            tabs--;
            if (!help.empty())
                answer += addTabs(tabs) + "</" + help.substr(1, i.name.length() - 2) + ">\n";
            inArr = false;
            for (auto &j : activeArray) {
                if (tabs - 1 == j.second) {
                    inArr = true;
                    help = j.first;
                }
            }
            if (inArr)
                answer += addTabs(tabs - 1) + printArray(help, false);

        } else if (i.valueType == "arrayBegin") {

            if (i.name.empty())
                activeArray.emplace_back("", tabs);
            else
                activeArray.emplace_back(i.name, tabs);
            tabs++;

        } else if (i.valueType == "arrayEnd") {

            tabs--;
            auto pair = activeArray[activeArray.size() - 1];
            activeArray.pop_back();

        }
    }

    if (!activeArray.empty() || !activeObject.empty())
        throw ("Parsing exception");

    return answer;
}

string JSON::printArray(const string &name, bool isBegin) {
    if (isBegin)
        return '<' + name.substr(1, name.length() - 2) + ">\n";
    else
        return "</" + name.substr(1, name.length() - 2) + ">\n";
}

string JSON::toJSON() {
    return formJSON;
}

string JSON::toXML() {
    return formXML;
}