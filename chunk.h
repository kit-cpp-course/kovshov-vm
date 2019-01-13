#pragma once

#include <string>

using namespace std;

/*
* JSON объект хранится в памяти как массив chunk
*/
class chunk {

public:
    /*
     * Имя поля
     */
    string name;
    /*
     * Значение поля. Только для полей типа string, int и null
     */
    string value;
    /*
     * Тип значения. Может принимать значения:
     * 1) string
     * 2) int
     * 3) objectBegin
     * 4) objectEnd
     * 5) arrayBegin
     * 6) arrayEnd
     * 7) null
     */
    string valueType;

    /*
     * Конструктор для chunk с value
     */
    chunk(string name, string value, string valueType) :
            name(std::move(name)),
            value(std::move(value)),
            valueType(std::move(valueType)) {}

    /*
    * Конструктор для chunk без value
    */
    chunk(string name, string valueType) :
            name(std::move(name)),
            valueType(std::move(valueType)) {}


    /*
    * Конструктор для chunk без value и name
    */
    explicit chunk(string valueType) :
            valueType(std::move(valueType)) {}
};