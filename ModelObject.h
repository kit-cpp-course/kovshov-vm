#pragma once

#include <utility>
#include <string>
#include <vector>
#include <iostream>

#include "Chunk.h"

using namespace std;

class ModelObject {

private:

    vector<Chunk> data;

public:

    ModelObject() = default;

    explicit ModelObject(vector<Chunk> input) : data(std::move(input)) {};

    void draw() {
        for (auto &i : data) {
            cout << i.name << '|'
                 << i.valueType << '|'
                 << i.value << '\n';
        }
    }

    vector<Chunk> getData(){
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