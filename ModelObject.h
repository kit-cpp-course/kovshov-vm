#pragma once

#include <utility>
#include <string>
#include <vector>
#include <iostream>

#include "Chunk.h"

using namespace std;

/*
 * Класс - модель древовидного типа данных
 */
class ModelObject {

private:
    /*
     * Массив элементов, у каждого из которых есть имя, значени и тип (подробнее в Chunk.h)
     */
    vector<Chunk> data;

public:

    ModelObject() = default;

    explicit ModelObject(vector<Chunk> input) : data(std::move(input)) {};

    vector<Chunk> getData() {
        return data;
    }

    string toString() {
        string ans;
        for (auto &i : data) {
            ans += i.name + "|"
                   + i.valueType + "|"
                   + i.value + "\n";
        }
        return ans;
    }

};