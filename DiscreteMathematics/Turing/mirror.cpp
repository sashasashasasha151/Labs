#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/mirror.out");
    ofstream cout("mirror.out");
    cout << "start: s\n"
            "accept: ac\n"
            "reject: rj\n"
            "blank: _\n"
            "\n"
            "s 0 -> s 0 >\n"
            "s 1 -> s 1 >\n"
            "s _ -> Tk _ <\n"
            "\n"
            "Tk 0 -> St0 3 >\n"
            "Tk 1 -> St1 4 >\n"
            "\n"
            "St0 0 -> St0 0 >\n"
            "St0 1 -> St0 1 >\n"
            "St0 3 -> St0 3 >\n"
            "St0 4 -> St0 4 >\n"
            "St0 _ -> Go4 0 <\n"
            "\n"
            "St1 0 -> St1 0 >\n"
            "St1 1 -> St1 1 >\n"
            "St1 3 -> St1 3 >\n"
            "St1 4 -> St1 4 >\n"
            "St1 _ -> Go4 1 <\n"
            "\n"
            "Go4 0 -> Go4 0 <\n"
            "Go4 1 -> Go4 1 <\n"
            "Go4 3 -> Go1 3 <\n"
            "Go4 4 -> Go1 4 <\n"
            "\n"
            "Go1 0 -> St0 3 >\n"
            "Go1 1 -> St1 4 >\n"
            "Go1 3 -> Go1 3 <\n"
            "Go1 4 -> Go1 4 <\n"
            "Go1 _ -> E _ >\n"
            "\n"
            "E 0 -> ToS 0 <\n"
            "E 1 -> ToS 1 <\n"
            "E 3 -> E 0 >\n"
            "E 4 -> E 1 >\n"
            "\n"
            "ToS 0 -> ToS 0 <\n"
            "ToS 1 -> ToS 1 <\n"
            "ToS _ -> ac _ >";
    return 0;
}