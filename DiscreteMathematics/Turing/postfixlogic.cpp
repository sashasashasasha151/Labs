#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/postfixlogic.out");
    ofstream cout("postfixlogic.out");
    cout << "2\n"
            "S 0 _ -> S _ > 0 >\n"
            "S 1 _ -> S _ > 1 >\n"
            "S o _ -> ad o ^ _ <\n"
            "S a _ -> mu a ^ _ <\n"
            "S _ _ -> end _ ^ _ <\n"
            "ad o 0 -> adf o ^ _ <\n"
            "ad o 1 -> adt o ^ _ <\n"
            "adf o 0 -> S _ > 0 >\n"
            "adf o 1 -> S _ > 1 >\n"
            "adt o 0 -> S _ > 1 >\n"
            "adt o 1 -> S _ > 1 >\n"
            "mu a 0 -> muf a ^ _ <\n"
            "mu a 1 -> mut a ^ _ <\n"
            "muf a 0 -> S _ > 0 >\n"
            "muf a 1 -> S _ > 0 >\n"
            "mut a 0 -> S _ > 0 >\n"
            "mut a 1 -> S _ > 1 >\n"
            "end _ 1 -> AC 1 ^ _ ^\n"
            "end _ 0 -> AC 0 ^ _ ^";
    return 0;
}