#pragma once

#include <string>

#include "ModelObject.h"

using namespace std;

/*
 * Интерфейс - абстрактное предстваление процедуры преобразования древовидныч типов данных
 */
class Parser {

protected:

    /*
     * Избавление от нежелаттельных символов (например лидирующих пробелов или табов)
     */
    virtual string simplify(string input) = 0;

public:
    /*
     * Преобразование в из строки в ModelObject
     */
    virtual ModelObject parseToObject(string input) = 0;

    /*
     * Преобразование в из ModelObject в строку
     */
    virtual string parseFromObject(ModelObject input) = 0;
};