#include <iostream>
#include <string>
#include <vector>

using namespace std;


vector<int> getSubInput(string input) {
    input = input.substr(1, input.length() - 2);
    string delim(",");
    vector<int> out;
    auto idx = input.find(delim);
    while (idx != string::npos) {
        out.push_back(stoi(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        out.push_back(stoi(input));
    return out;
}


void printVectorOfVector(string VarName, auto inputs) {
    cout << VarName << " = [";
    bool outer = false;
    for (auto input: inputs) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << "[";
        bool inner = false;
        for (auto ele: input) {
            if (inner)
                cout << ",";
            else
                inner = true;
            cout << ele;
        }
        cout << "]";
    }
    cout << "]" << endl;
}


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 2);
    vector<vector<int>> inputVec;
    string delim(",[");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        inputVec.push_back(getSubInput(input.substr(0, idx)));
        input = input.substr(idx + 1);
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec.push_back(getSubInput(input));
    printVectorOfVector("input", inputVec);
}
