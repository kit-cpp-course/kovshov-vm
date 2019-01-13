#pragma once

#include <utility>
#include <string>
#include <vector>
#include <iostream>

#include "chunk.h"

using namespace std;

class modelObject {

private:

    vector<chunk> data;

public:

    modelObject() = default;

    explicit modelObject(vector<chunk> input) : data(std::move(input)) {};

    void draw() {
        for (auto &i : data) {
            cout << i.name << '|'
                 << i.valueType << '|'
                 << i.value << '\n';
        }
    }

    vector<chunk> getData(){
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