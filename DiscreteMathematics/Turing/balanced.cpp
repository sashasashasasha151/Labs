#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/balanced.out");
    ofstream cout("balanced.out");
    cout << "start: s\n"
            "accept: ac\n"
            "reject: rj\n"
            "blank: _\n"
            "s ( -> sa ( <\n"
            "s ) -> rj _ ^\n"
            "s _ -> ac _ ^\n"
            "sa _ -> sb A >\n"
            "sb ( -> sb ( >\n"
            "sb ) -> sb ) >\n"
            "sb _ -> gs B <\n"
            "gs ( -> gs ( <\n"
            "gs ) -> gs ) <\n"
            "gs A -> op A >\n"
            "op ( -> op ( >\n"
            "op ) -> cl _ <\n"
            "op _ -> op _ >\n"
            "op B -> ch B <\n"
            "cl ( -> op _ >\n"
            "cl _ -> cl _ <\n"
            "cl A -> rj _ ^\n"
            "ch ( -> rj _ ^\n"
            "ch _ -> ch _ <\n"
            "ch A -> ac _ ^";
    return 0;
}