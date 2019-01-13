#pragma once

#include <string>
#include <vector>
#include <cstring>
#include <stack>
#include <utility>
#include "Parser.h"

using namespace std;

class parserXML : public Parser {

protected:
    string simplify(string input) override;

public:
    string parseFromObject(ModelObject input) override;

    ModelObject parseToObject(string input) override;
};