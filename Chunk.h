#pragma once

#include <string>

using namespace std;

/*
* Класс хранит информацию об одном поле в древовидном представлении (ModelObject)
*/
class Chunk {

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
     * Конструктор для Chunk с value
     */
    Chunk(string name, string value, string valueType) :
            name(std::move(name)),
            value(std::move(value)),
            valueType(std::move(valueType)) {}

    /*
    * Конструктор для Chunk без value
    */
    Chunk(string name, string valueType) :
            name(std::move(name)),
            valueType(std::move(valueType)) {}


    /*
    * Конструктор для Chunk без value и name
    */
    explicit Chunk(string valueType) :
            valueType(std::move(valueType)) {}
};