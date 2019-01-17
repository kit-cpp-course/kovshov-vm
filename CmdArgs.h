#pragma once

#include <string>
#include <iostream>

using namespace std;

/*
 * Singleton класс
 */
class CmdArgs {
private:
    CmdArgs() = default;

public:
    /*
     * Статичный метод, для создания единственного экземпляра класса
     */
    static CmdArgs &getInstance() {
        static CmdArgs inst;
        return inst;
    }

    /* Парсер аргументов командной строки, также определяет корректность ввода цвета
	 * @param1 кол-во параметров командной строки
	 * @param2 параметры командной строки
	 * @param3 ссылка на переменную, в которой хранится путь к входному файлу
	 * @param4 ссылка на переменную, в которой хранится путь к выходному файлу
	 * @return 0, если входные параметры не верны
     * @return 1, если требуется превратить xml файл в новый json файл
     * @return 2, если требуется превратить json файл в новый xml файл
     * @return 3, если требуется превратить xml файл в json файл
     * @return 4, если требуется превратить json файл в xml файл
	 */
    int argParser(int argc, char *argv[], string &in, string &out);
};