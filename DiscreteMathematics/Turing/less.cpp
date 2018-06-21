#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/less.out");
    ofstream cout("less.out");
    cout << "start: s\n"
            "accept: ac\n"
            "reject: rj\n"
            "blank: _\n"
            "s 0 -> gc 3 >\n"
            "s 1 -> gc 4 >\n"
            "s < -> ch < >\n"
            "gc 0 -> gc 0 >\n"
            "gc 1 -> gc 1 >\n"
            "gc < -> gs < >\n"
            "gs 0 -> gcb 3 <\n"
            "gs 1 -> gcb 4 <\n"
            "gs 3 -> gs 3 >\n"
            "gs 4 -> gs 4 >\n"
            "gs _ -> rj _ ^\n"
            "gcb < -> gsb < <\n"
            "gcb 3 -> gcb 3 <\n"
            "gcb 4 -> gcb 4 <\n"
            "gsb 0 -> gsb 0 <\n"
            "gsb 1 -> gsb 1 <\n"
            "gsb 3 -> s 3 >\n"
            "gsb 4 -> s 4 >\n"
            "ch 0 -> ac _ ^\n"
            "ch 1 -> ac _ ^\n"
            "ch 3 -> ch 3 >\n"
            "ch 4 -> ch 4 >\n"
            "ch _ -> gst _ <\n"
            "gst < -> gst < <\n"
            "gst 3 -> gst 3 <\n"
            "gst 4 -> gst 4 <\n"
            "gst _ -> rs _ >\n"
            "rs < -> rj _ ^\n"
            "rs 3 -> l3 _ >\n"
            "rs 4 -> l4 _ >\n"
            "l3 < -> r3 < >\n"
            "l3 3 -> l3 3 >\n"
            "l3 4 -> l3 4 >\n"
            "l4 < -> r4 < >\n"
            "l4 3 -> l4 3 >\n"
            "l4 4 -> l4 4 >\n"
            "r3 3 -> goc _ <\n"
            "r3 4 -> ac _ ^\n"
            "r3 _ -> r3 _ >\n"
            "r4 3 -> rj _ ^\n"
            "r4 4 -> goc _ <\n"
            "r4 _ -> r4 _ >\n"
            "goc < -> tk < <\n"
            "goc _ -> goc _ <\n"
            "tk 3 -> tk 3 <\n"
            "tk 4 -> tk 4 <\n"
            "tk _ -> rs _ >";
    return 0;
}