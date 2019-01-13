#include "ParserXML.h"

string parserXML::simplify(string input) {
    string answer;
    char XMLChar[] = R"(<>:,. \/'")";
    for (char i : input) {
        if (i == '\n' || i == '\t')
            continue;
        if ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') || (i >= '0' && i <= '9') || strchr(XMLChar, i) != nullptr)
            answer += i;
    }
    return answer;
}

string addTab(int n) {
    string ans;
    for (int i = 0; i < n; ++i) {
        ans += '\t';
    }
    return ans;
}

string printArray(const string &name, bool isBegin) {
    if (isBegin)
        return '<' + name.substr(1, name.length() - 2) + ">\n";
    else
        return "</" + name.substr(1, name.length() - 2) + ">\n";
}

string parseToXML(vector<Chunk> data) {

    vector<pair<string, int>> activeArray;
    stack<string> activeObject;
    string
            answer, help;
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
                answer += addTab(tabs - 1) + printArray(help, true);
            answer += addTab(tabs) +
                      '<' + i.name.substr(1, i.name.length() - 2) + '>' +
                      i.value.substr(1, i.value.length() - 2) +
                      "</" + i.name.substr(1, i.name.length() - 2) + ">\n";
            if (inArr)
                answer += addTab(tabs - 1) + printArray(help, false);

        } else if (i.valueType == "int") {

            if (inArr)
                answer += addTab(tabs - 1) + printArray(help, true);
            answer += addTab(tabs) +
                      '<' + i.name.substr(1, i.name.length() - 2) + '>' +
                      i.value +
                      "</" + i.name.substr(1, i.name.length() - 2) + ">\n";
            if (inArr)
                answer += addTab(tabs - 1) + printArray(help, false);

        } else if (i.valueType == "null") {

            if (inArr)
                answer += addTab(tabs - 1) + printArray(help, true);
            if (!i.name.empty()) {
                answer += "</" + i.name.substr(1, i.name.length() - 2) + ">\n";
            }
            if (inArr)
                answer += addTab(tabs - 1) + printArray(help, false);

        } else if (i.valueType == "objectBegin") {

            if (inArr)
                answer += addTab(tabs - 1) + printArray(help, true);
            if (i.name.empty())
                activeObject.push("");
            else {
                answer += addTab(tabs) + '<' + i.name.substr(1, i.name.length() - 2) + ">\n";
                activeObject.push(i.name);
            }
            tabs++;

        } else if (i.valueType == "objectEnd") {

            help = activeObject.top();
            activeObject.pop();
            tabs--;
            if (!help.empty())
                answer += addTab(tabs) + "</" + help.substr(1, i.name.length() - 2) + ">\n";
            inArr = false;
            for (auto &j : activeArray) {
                if (tabs - 1 == j.second) {
                    inArr = true;
                    help = j.first;
                }
            }
            if (inArr)
                answer += addTab(tabs - 1) + printArray(help, false);

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

vector<string> preParse(string input) {
    vector<string> ans;
    unsigned int start = 0;
    for (unsigned int i = 0; i < input.length(); ++i) {
        if (i != start && input[i] == '<') {
            ans.push_back(input.substr(start, i - 1 - start + 1));
            start = i;
        }
        if (input[i] == '>') {
            if (ans.size() > 1)
                if (ans[ans.size() - 1][0] == ' ' && ans[ans.size() - 2][0] == '<')
                    ans.pop_back();
            ans.push_back(input.substr(start, i - start + 1));
            start = i + 1;
        }
    }
    for (const auto &an : ans) {
        cout << an << endl;
    }
    return ans;
}

vector<Chunk> parseXML(string input) {
    cout << input << endl;
    vector<string> in = preParse(std::move(input));
    vector<Chunk> data;
    for (int i = 0; i < in.size(); ++i) {
        if (i + 2 < in.size())
            if (in[i][0] == '<' && in[i][1] != '\\' && in[i + 1][0] != '<' && in[i + 2][0] == '<' &&
                in[i + 2][1] == '/') {
                Chunk addChunk("\"" + in[i].substr(1, in[i].length() - 2) + "\"", "\"" + in[i + 1] + "\"", "string");
                data.push_back(addChunk);
            }
    }
    return data;
}

ModelObject parserXML::parseToObject(string input) {
    cout << input << endl;
    string ans = simplify(input);
    try {
        return ModelObject(parseXML(ans));
    } catch (...) {
        throw ("Parsing exception");
    }
}

string parserXML::parseFromObject(ModelObject input) {
    return parseToXML(input.getData());
}