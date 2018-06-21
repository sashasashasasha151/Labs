#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/infixlogic.out");
    ofstream cout("infixLogic.out");
    cout << "3\n"
            "S 0 _ _ -> S _ > _ ^ 0 >\n"
            "S 1 _ _ -> S _ > _ ^ 1 >\n"
            "S o _ _ -> so o ^ _ < _ ^\n"
            "S a _ _ -> sa a ^ _ < _ ^\n"
            "S ( _ _ -> S _ > ( > _ ^\n"
            "S ) _ _ -> ss ) ^ _ < _ ^\n"
            "S _ _ _ -> st _ ^ _ < _ ^\n"
            "so o o _ -> so o ^ _ < o >\n"
            "so o a _ -> so o ^ _ < a >\n"
            "so o ( _ -> so o ^ ( > _ ^\n"
            "so o _ _ -> S _ > o > _ ^\n"
            "sa a o _ -> sa a ^ o > _ ^\n"
            "sa a a _ -> sa a ^ _ < a >\n"
            "sa a ( _ -> sa a ^ ( > _ ^\n"
            "sa a _ _ -> S _ > a > _ ^\n"
            "ss ) o _ -> ss ) ^ _ < o >\n"
            "ss ) a _ -> ss ) ^ _ < a >\n"
            "ss ) ( _ -> S _ > _ ^ _ ^\n"
            "st _ o _ -> st _ ^ _ < o >\n"
            "st _ a _ -> st _ ^ _ < a >\n"
            "st _ _ _ -> gos _ ^ _ ^ _ <\n"
            "gos _ _ 0 -> gos _ ^ _ ^ 0 <\n"
            "gos _ _ 1 -> gos _ ^ _ ^ 1 <\n"
            "gos _ _ o -> gos _ ^ _ ^ o <\n"
            "gos _ _ a -> gos _ ^ _ ^ a <\n"
            "gos _ _ _ -> str _ ^ _ ^ _ >\n"
            "str _ _ 0 -> str 0 > _ ^ _ >\n"
            "str _ _ 1 -> str 1 > _ ^ _ >\n"
            "str _ _ o -> ad _ < _ ^ o ^\n"
            "str _ _ a -> mu _ < _ ^ a ^\n"
            "str _ _ _ -> AC _ < _ ^ _ ^\n"
            "ad 0 _ o -> adf _ < _ ^ o ^\n"
            "ad 1 _ o -> adt _ < _ ^ o ^\n"
            "adf 0 _ o -> str 0 > _ ^ _ >\n"
            "adf 1 _ o -> str 1 > _ ^ _ >\n"
            "adt 0 _ o -> str 1 > _ ^ _ >\n"
            "adt 1 _ o -> str 1 > _ ^ _ >\n"
            "mu 0 _ a -> muf _ < _ ^ a ^\n"
            "mu 1 _ a -> mut _ < _ ^ a ^\n"
            "muf 0 _ a -> str 0 > _ ^ _ >\n"
            "muf 1 _ a -> str 0 > _ ^ _ >\n"
            "mut 0 _ a -> str 0 > _ ^ _ >\n"
            "mut 1 _ a -> str 1 > _ ^ _ >";
    return 0;
}