#pragma once

#include <string>
#include <vector>
#include <cstring>
#include <stack>
#include "parser.h"

using namespace std;

class parserXML : public parser {

protected:
    string simplify(string input) override;

public:
    string parseFromObject(modelObject input) override;

    modelObject parseToObject(string input) override;
};