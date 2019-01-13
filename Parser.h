#pragma once

#include <string>

#include "ModelObject.h"

using namespace std;

class Parser {

protected:

    virtual string simplify(string input) = 0;

public:
    virtual ModelObject parseToObject(string input) = 0;

    virtual string parseFromObject(ModelObject input) = 0;
};