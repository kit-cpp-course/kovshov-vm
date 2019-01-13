#pragma once

#include <string>
#include <vector>
#include <cstring>
#include <stack>

#include "Parser.h"

using namespace std;

class parserJSON : public Parser {

protected:
    string simplify(string input) override;

public:
    string parseFromObject(ModelObject input) override;

    ModelObject parseToObject(string input) override;
};