#pragma once

#include <string>

#include "modelObject.h"

using namespace std;

class parser {

protected:

    virtual string simplify(string input) = 0;

public:
    virtual modelObject parseToObject(string input) = 0;

    virtual string parseFromObject(modelObject input) = 0;
};