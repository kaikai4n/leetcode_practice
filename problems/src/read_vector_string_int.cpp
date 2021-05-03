#include <iostream>
#include <string>
#include <vector>

using namespace std;


void printVector(string VarName, auto inputs) {
    cout << VarName << " = [";
    bool outer = false;
    for (auto input: inputs) {
        if (outer)
            cout << ",";
        else
            outer = true;
        cout << "\"" << input << "\"";
    }
    cout << "]" << endl;
}


int main() {
    string input;
    cin >> input >> input >> input;
    input = input.substr(1, input.length() - 3);
    cout << input << endl;
    vector<string> inputVec;
    string delim(",");
    auto idx = input.find(delim);
    while (idx != string::npos) {
        inputVec.push_back(input.substr(1, idx - 2));
        input = input.substr(idx + delim.length());
        idx = input.find(delim);
    }
    if (input.length() > 0)
        inputVec.push_back(input.substr(1, input.length() - 2));
    printVector("input", inputVec);
    
    cin >> input >> input >> input;
    int input2 = stoi(input);
    cout << "input 2 = " << input2 << endl;
}
