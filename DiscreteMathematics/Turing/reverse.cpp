#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/reverse.out");
    ofstream cout("reverse.out");
    cout << "start: s\n"
            "accept: ac\n"
            "reject: rj\n"
            "blank: _\n"
            "s 0 -> sa 0 <\n"
            "s 1 -> sa 1 <\n"
            "s _ -> ac _ ^\n"
            "sa _ -> sb A >\n"
            "sb 0 -> sb 0 >\n"
            "sb 1 -> sb 1 >\n"
            "sb _ -> st B <\n"
            "st 0 -> t0 _ >\n"
            "st 1 -> t1 _ >\n"
            "t0 _ -> t0 _ >\n"
            "t0 B -> s0 B >\n"
            "t1 _ -> t1 _ >\n"
            "t1 B -> s1 B >\n"
            "s0 0 -> s0 0 >\n"
            "s0 1 -> s0 1 >\n"
            "s0 _ -> gb 0 <\n"
            "s1 0 -> s1 0 >\n"
            "s1 1 -> s1 1 >\n"
            "s1 _ -> gb 1 <\n"
            "gb 0 -> gb 0 <\n"
            "gb 1 -> gb 1 <\n"
            "gb B -> gt B <\n"
            "gt 0 -> t0 _ >\n"
            "gt 1 -> t1 _ >\n"
            "gt _ -> gt _ <\n"
            "gt A -> ta _ >\n"
            "ta _ -> ta _ >\n"
            "ta B -> ac _ >";
    return 0;
}