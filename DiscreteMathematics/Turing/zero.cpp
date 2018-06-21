#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/zero.out");
    ofstream cout("zero.out");
    cout << "start: s\n"
            "accept: ac\n"
            "reject: rj\n"
            "blank: _\n"
            "s _ -> ac _ ^\n"
            "s 0 -> n 0 >\n"
            "n 0 -> s 0 >\n"
            "n _ -> rj _ >";
    return 0;
}