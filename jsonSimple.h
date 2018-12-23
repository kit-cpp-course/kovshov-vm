#pragma once

#include <string>
#include <vector>
#include <cstring>
#include <stack>

using namespace std;

/*
 * Класс для преобразования и хранения в памяти объектов типа JSON
 */
class JSON {

private:

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

    /*
     * Переменная для хранения полной записи в формате JSON
     */
    string formJSON;

    /*
     * Переменная для хранения записи в формате XML
     */
    string formXML;

    /*
     * Массив для хранения chunk
     */
    vector<chunk> data;

    /*
     * Проверка на число (нужна при парсинге)
     */
    bool isDigit(char c);

    /*
     * Проверка на корректный символ (нужна при парсинге)
     */
    bool isJsonChar(char c);

    /*
     * Функция преобразования JSON в вектор chunk
     */
    vector<chunk> parse(const string &input);

    /*
     * Избавление от переносов строк и лишних пробелов (нужна при парсинге)
     */
    string simplify(string &input);

    /*
     * Добавление в строку n табов (нужна для конвертации)
     */
    string addTabs(int n);

    /*
     * Вспомогательная функция для отображения массивов
     * при преобразовании JSON в XML
     */
    string printArray(const string &name, bool isBegin);

    /*
    * Преобразование в формат XML
    */
    string parseToXML();

public:

    /*
     * Конструктор класса JSON
     */
    explicit JSON(string &input);

    /*
     * Вывод объекта в формате JSON
     */
    string toJSON();

    /*
     * Вывод объекта в формате XML
     */
    string toXML();

};