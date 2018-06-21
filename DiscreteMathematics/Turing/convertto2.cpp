#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/convertto2.out");
    ofstream cout("convertto2.out");
    cout << "start: s\n"
            "accept: ac\n"
            "reject: rj\n"
            "blank: _\n"
            "\n"
            "s 0 -> Set# 0 <\n"
            "s 1 -> Set# 1 <\n"
            "s 2 -> Set# 2 <\n"
            "\n"
            "Set# _ -> Set3 # <\n"
            "\n"
            "Set3 _ -> ToSub 3 >\n"
            "\n"
            "ToSub 0 -> ToSub 0 >\n"
            "ToSub 1 -> ToSub 1 >\n"
            "ToSub 2 -> ToSub 2 >\n"
            "ToSub 3 -> ToSub 3 >\n"
            "ToSub 4 -> ToSub 4 >\n"
            "ToSub # -> ToSub # >\n"
            "ToSub _ -> Sub _ <\n"
            "\n"
            "Sub 0 -> Sub 2 <\n"
            "Sub 1 -> Check 0 <\n"
            "Sub 2 -> ToAdd 1 <\n"
            "Sub # -> Finn # >\n"
            "\n"
            "Finn 2 -> Fin _ <\n"
            "Finn _ -> Fin _ <\n"
            "\n"
            "Check 0 -> ToAdd 0 <\n"
            "Check 1 -> ToAdd 1 <\n"
            "Check 2 -> ToAdd 2 <\n"
            "Check # -> DelL # >\n"
            "\n"
            "DelL 0 -> ToAdd # <\n"
            "\n"
            "ToAdd 0 -> ToAdd 0 <\n"
            "ToAdd 1 -> ToAdd 1 <\n"
            "ToAdd 2 -> ToAdd 2 <\n"
            "ToAdd 3 -> ToSub 4 >\n"
            "ToAdd 4 -> Add 3 <\n"
            "ToAdd # -> ToAdd # <\n"
            "\n"
            "Add 3 -> ToSub 4 >\n"
            "Add 4 -> Add 3 <\n"
            "Add _ -> ToSub 4 >\n"
            "\n"
            "Fin 2 -> Fin _ <\n"
            "Fin 3 -> Fin 0 <\n"
            "Fin 4 -> Fin 1 <\n"
            "Fin # -> Fin _ <\n"
            "Fin _ -> ac _ >";
    return 0;
}