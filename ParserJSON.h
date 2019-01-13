#pragma once

#include <string>
#include <vector>
#include <cstring>
#include <stack>

#include "Parser.h"

using namespace std;

/*
 * Класс превращения JSON в понятный компилятору ModelObject
 */
class parserJSON : public Parser {

protected:
    /*
     * Избавление от нежелаттельных символов (например лидирующих пробелов или табов)
     */
    string simplify(string input) override;

public:
    /*
     * Преобразование из строки хранящей JSON в ModelObject
     */
    string parseFromObject(ModelObject input) override;

    /*
    * Преобразование из ModelObject в строку хранящую JSON
    */
    ModelObject parseToObject(string input) override;
};