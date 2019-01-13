#pragma once

#include <string>
#include <vector>
#include <cstring>
#include <stack>
#include <utility>
#include "Parser.h"

using namespace std;

/*
 * Класс превращения XML в понятный компилятору ModelObject
 */
class parserXML : public Parser {

protected:
    /*
     * Избавление от нежелаттельных символов (например лидирующих пробелов или табов)
     */
    string simplify(string input) override;

public:
    /*
     * Преобразование из строки хранящей XML в ModelObject
     */
    string parseFromObject(ModelObject input) override;

    /*
    * Преобразование из ModelObject в строку хранящую XML
    */
    ModelObject parseToObject(string input) override;
};