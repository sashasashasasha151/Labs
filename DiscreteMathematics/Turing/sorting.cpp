#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/sorting.out");
    ofstream cout("sorting.out");
    cout << "5\n"
            "S 0 _ _ _ _ -> S 0 > _ ^ _ ^ _ ^ _ ^\n"
            "S 1 _ _ _ _ -> S 1 > _ ^ _ ^ _ ^ _ ^\n"
            "S | _ _ _ _ -> S | > _ ^ _ ^ _ ^ | >\n"
            "S _ _ _ _ _ -> GoS _ < _ ^ _ ^ _ ^ _ <\n"
            "GoS 0 _ _ _ | -> GoS 0 < _ ^ _ ^ _ ^ | ^\n"
            "GoS 1 _ _ _ | -> GoS 1 < _ ^ _ ^ _ ^ | ^\n"
            "GoS | _ _ _ | -> GoS | < _ ^ _ ^ _ ^ | ^\n"
            "GoS _ _ _ _ | -> for _ ^ _ ^ _ ^ _ ^ | ^\n"
            "GoS 0 _ _ _ _ -> GoS 0 < _ ^ _ ^ _ ^ _ ^\n"
            "GoS 1 _ _ _ _ -> GoS 1 < _ ^ _ ^ _ ^ _ ^\n"
            "GoS | _ _ _ _ -> GoS | < _ ^ _ ^ _ ^ _ ^\n"
            "GoS _ _ _ _ _ -> for _ ^ _ ^ _ ^ _ ^ _ ^\n"
            "for _ _ _ _ | -> SetF _ > _ ^ _ ^ _ ^ | ^\n"
            "for _ _ _ _ _ -> end _ ^ _ ^ _ ^ _ ^ _ ^\n"
            "SetF 0 _ _ _ | -> SetF _ > _ ^ 0 > 0 > | ^\n"
            "SetF 1 _ _ _ | -> SetF _ > _ ^ 1 > 1 > | ^\n"
            "SetF | _ _ _ | -> SetN _ > _ ^ < > < > | ^\n"
            "SetN 0 _ _ _ | -> SetN _ > _ ^ 0 > 0 > | ^\n"
            "SetN 1 _ _ _ | -> SetN _ > _ ^ 1 > 1 > | ^\n"
            "SetN | _ _ _ | -> GoLess _ ^ _ ^ _ < _ < | ^\n"
            "SetN _ _ _ _ | -> GoLess _ ^ _ ^ _ < _ < # ^\n"
            "GoLess _ _ 0 0 | -> GoLess _ ^ _ ^ 0 < 0 < | ^\n"
            "GoLess _ _ 1 1 | -> GoLess _ ^ _ ^ 1 < 1 < | ^\n"
            "GoLess _ _ < < | -> GoLess _ ^ _ ^ < < < < | ^\n"
            "GoLess _ _ _ _ | -> Less _ ^ _ ^ _ > _ ^ | ^\n"
            "GoLess _ _ 0 0 # -> GoLess _ ^ _ ^ 0 < 0 < # ^\n"
            "GoLess _ _ 1 1 # -> GoLess _ ^ _ ^ 1 < 1 < # ^\n"
            "GoLess _ _ < < # -> GoLess _ ^ _ ^ < < < < # ^\n"
            "GoLess _ _ _ _ # -> Less _ ^ _ ^ _ > _ ^ # ^\n"
            "Less _ _ 0 _ | -> gc _ ^ _ ^ 3 > _ ^ | ^\n"
            "Less _ _ 1 _ | -> gc _ ^ _ ^ 4 > _ ^ | ^\n"
            "Less _ _ < _ | -> ch _ ^ _ ^ < > _ ^ | ^\n"
            "Less _ _ 0 _ # -> gc _ ^ _ ^ 3 > _ ^ # ^\n"
            "Less _ _ 1 _ # -> gc _ ^ _ ^ 4 > _ ^ # ^\n"
            "Less _ _ < _ # -> ch _ ^ _ ^ < > _ ^ # ^\n"
            "gc _ _ 0 _ | -> gc _ ^ _ ^ 0 > _ ^ | ^\n"
            "gc _ _ 1 _ | -> gc _ ^ _ ^ 1 > _ ^ | ^\n"
            "gc _ _ < _ | -> gs _ ^ _ ^ < > _ ^ | ^\n"
            "gc _ _ 0 _ # -> gc _ ^ _ ^ 0 > _ ^ # ^\n"
            "gc _ _ 1 _ # -> gc _ ^ _ ^ 1 > _ ^ # ^\n"
            "gc _ _ < _ # -> gs _ ^ _ ^ < > _ ^ # ^\n"
            "gs _ _ 0 _ | -> gcb _ ^ _ ^ 3 < _ ^ | ^\n"
            "gs _ _ 1 _ | -> gcb _ ^ _ ^ 4 < _ ^ | ^\n"
            "gs _ _ 3 _ | -> gs _ ^ _ ^ 3 > _ ^ | ^\n"
            "gs _ _ 4 _ | -> gs _ ^ _ ^ 4 > _ ^ | ^\n"
            "gs _ _ _ _ | -> No _ ^ _ ^ _ > _ ^ | ^\n"
            "gs _ _ 0 _ # -> gcb _ ^ _ ^ 3 < _ ^ # ^\n"
            "gs _ _ 1 _ # -> gcb _ ^ _ ^ 4 < _ ^ # ^\n"
            "gs _ _ 3 _ # -> gs _ ^ _ ^ 3 > _ ^ # ^\n"
            "gs _ _ 4 _ # -> gs _ ^ _ ^ 4 > _ ^ # ^\n"
            "gs _ _ _ _ # -> No _ ^ _ ^ _ > _ ^ # ^\n"
            "gcb _ _ < _ | -> gsb _ ^ _ ^ < < _ ^ | ^\n"
            "gcb _ _ 3 _ | -> gcb _ ^ _ ^ 3 < _ ^ | ^\n"
            "gcb _ _ 4 _ | -> gcb _ ^ _ ^ 4 < _ ^ | ^\n"
            "gcb _ _ < _ # -> gsb _ ^ _ ^ < < _ ^ # ^\n"
            "gcb _ _ 3 _ # -> gcb _ ^ _ ^ 3 < _ ^ # ^\n"
            "gcb _ _ 4 _ # -> gcb _ ^ _ ^ 4 < _ ^ # ^\n"
            "gsb _ _ 0 _ | -> gsb _ ^ _ ^ 0 < _ ^ | ^\n"
            "gsb _ _ 1 _ | -> gsb _ ^ _ ^ 1 < _ ^ | ^\n"
            "gsb _ _ 3 _ | -> Less _ ^ _ ^ 3 > _ ^ | ^\n"
            "gsb _ _ 4 _ | -> Less _ ^ _ ^ 4 > _ ^ | ^\n"
            "gsb _ _ 0 _ # -> gsb _ ^ _ ^ 0 < _ ^ # ^\n"
            "gsb _ _ 1 _ # -> gsb _ ^ _ ^ 1 < _ ^ # ^\n"
            "gsb _ _ 3 _ # -> Less _ ^ _ ^ 3 > _ ^ # ^\n"
            "gsb _ _ 4 _ # -> Less _ ^ _ ^ 4 > _ ^ # ^\n"
            "ch _ _ 0 _ | -> Yes _ ^ _ ^ _ > _ ^ | ^\n"
            "ch _ _ 1 _ | -> Yes _ ^ _ ^ _ > _ ^ | ^\n"
            "ch _ _ 3 _ | -> ch _ ^ _ ^ 3 > _ ^ | ^\n"
            "ch _ _ 4 _ | -> ch _ ^ _ ^ 4 > _ ^ | ^\n"
            "ch _ _ _ _ | -> gst _ ^ _ ^ _ < _ ^ | ^\n"
            "ch _ _ 0 _ # -> Yes _ ^ _ ^ _ > _ ^ # ^\n"
            "ch _ _ 1 _ # -> Yes _ ^ _ ^ _ > _ ^ # ^\n"
            "ch _ _ 3 _ # -> ch _ ^ _ ^ 3 > _ ^ # ^\n"
            "ch _ _ 4 _ # -> ch _ ^ _ ^ 4 > _ ^ # ^\n"
            "ch _ _ _ _ # -> gst _ ^ _ ^ _ < _ ^ # ^\n"
            "gst _ _ < _ | -> gst _ ^ _ ^ < < _ ^ | ^\n"
            "gst _ _ 3 _ | -> gst _ ^ _ ^ 3 < _ ^ | ^\n"
            "gst _ _ 4 _ | -> gst _ ^ _ ^ 4 < _ ^ | ^\n"
            "gst _ _ _ _ | -> rs _ ^ _ ^ _ > _ ^ | ^\n"
            "gst _ _ < _ # -> gst _ ^ _ ^ < < _ ^ # ^\n"
            "gst _ _ 3 _ # -> gst _ ^ _ ^ 3 < _ ^ # ^\n"
            "gst _ _ 4 _ # -> gst _ ^ _ ^ 4 < _ ^ # ^\n"
            "gst _ _ _ _ # -> rs _ ^ _ ^ _ > _ ^ # ^\n"
            "rs _ _ < _ | -> No _ ^ _ ^ _ > _ ^ | ^\n"
            "rs _ _ 3 _ | -> l3 _ ^ _ ^ _ > _ ^ | ^\n"
            "rs _ _ 4 _ | -> l4 _ ^ _ ^ _ > _ ^ | ^\n"
            "rs _ _ < _ # -> No _ ^ _ ^ _ > _ ^ # ^\n"
            "rs _ _ 3 _ # -> l3 _ ^ _ ^ _ > _ ^ # ^\n"
            "rs _ _ 4 _ # -> l4 _ ^ _ ^ _ > _ ^ # ^\n"
            "l3 _ _ < _ | -> r3 _ ^ _ ^ < > _ ^ | ^\n"
            "l3 _ _ 3 _ | -> l3 _ ^ _ ^ 3 > _ ^ | ^\n"
            "l3 _ _ 4 _ | -> l3 _ ^ _ ^ 4 > _ ^ | ^\n"
            "l3 _ _ < _ # -> r3 _ ^ _ ^ < > _ ^ # ^\n"
            "l3 _ _ 3 _ # -> l3 _ ^ _ ^ 3 > _ ^ # ^\n"
            "l3 _ _ 4 _ # -> l3 _ ^ _ ^ 4 > _ ^ # ^\n"
            "l4 _ _ < _ | -> r4 _ ^ _ ^ < > _ ^ | ^\n"
            "l4 _ _ 3 _ | -> l4 _ ^ _ ^ 3 > _ ^ | ^\n"
            "l4 _ _ 4 _ | -> l4 _ ^ _ ^ 4 > _ ^ | ^\n"
            "l4 _ _ < _ # -> r4 _ ^ _ ^ < > _ ^ # ^\n"
            "l4 _ _ 3 _ # -> l4 _ ^ _ ^ 3 > _ ^ # ^\n"
            "l4 _ _ 4 _ # -> l4 _ ^ _ ^ 4 > _ ^ # ^\n"
            "r3 _ _ 3 _ | -> goc _ ^ _ ^ _ < _ ^ | ^\n"
            "r3 _ _ 4 _ | -> Yes _ ^ _ ^ _ > _ ^ | ^\n"
            "r3 _ _ _ _ | -> r3 _ ^ _ ^ _ > _ ^ | ^\n"
            "r3 _ _ 3 _ # -> goc _ ^ _ ^ _ < _ ^ # ^\n"
            "r3 _ _ 4 _ # -> Yes _ ^ _ ^ _ > _ ^ # ^\n"
            "r3 _ _ _ _ # -> r3 _ ^ _ ^ _ > _ ^ # ^\n"
            "r4 _ _ 3 _ | -> No _ ^ _ ^ _ > _ ^ | ^\n"
            "r4 _ _ 4 _ | -> goc _ ^ _ ^ _ < _ ^ | ^\n"
            "r4 _ _ _ _ | -> r4 _ ^ _ ^ _ > _ ^ | ^\n"
            "r4 _ _ 3 _ # -> No _ ^ _ ^ _ > _ ^ # ^\n"
            "r4 _ _ 4 _ # -> goc _ ^ _ ^ _ < _ ^ # ^\n"
            "r4 _ _ _ _ # -> r4 _ ^ _ ^ _ > _ ^ # ^\n"
            "goc _ _ < _ | -> tk _ ^ _ ^ < < _ ^ | ^\n"
            "goc _ _ _ _ | -> goc _ ^ _ ^ _ < _ ^ | ^\n"
            "goc _ _ < _ # -> tk _ ^ _ ^ < < _ ^ # ^\n"
            "goc _ _ _ _ # -> goc _ ^ _ ^ _ < _ ^ # ^\n"
            "tk _ _ 3 _ | -> tk _ ^ _ ^ 3 < _ ^ | ^\n"
            "tk _ _ 4 _ | -> tk _ ^ _ ^ 4 < _ ^ | ^\n"
            "tk _ _ _ _ | -> rs _ ^ _ ^ _ > _ ^ | ^\n"
            "tk _ _ 3 _ # -> tk _ ^ _ ^ 3 < _ ^ # ^\n"
            "tk _ _ 4 _ # -> tk _ ^ _ ^ 4 < _ ^ # ^\n"
            "tk _ _ _ _ # -> rs _ ^ _ ^ _ > _ ^ # ^\n"
            "Yes _ _ 0 _ | -> Yes _ ^ _ ^ _ > _ ^ | ^\n"
            "Yes _ _ 1 _ | -> Yes _ ^ _ ^ _ > _ ^ | ^\n"
            "Yes _ _ 3 _ | -> Yes _ ^ _ ^ _ > _ ^ | ^\n"
            "Yes _ _ 4 _ | -> Yes _ ^ _ ^ _ > _ ^ | ^\n"
            "Yes _ _ < _ | -> Yes _ ^ _ ^ _ > _ ^ | ^\n"
            "Yes _ _ _ _ | -> Add _ ^ _ ^ _ ^ _ > | ^\n"
            "Yes _ _ 0 _ # -> Yes _ ^ _ ^ _ > _ ^ # ^\n"
            "Yes _ _ 1 _ # -> Yes _ ^ _ ^ _ > _ ^ # ^\n"
            "Yes _ _ 3 _ # -> Yes _ ^ _ ^ _ > _ ^ # ^\n"
            "Yes _ _ 4 _ # -> Yes _ ^ _ ^ _ > _ ^ # ^\n"
            "Yes _ _ < _ # -> Yes _ ^ _ ^ _ > _ ^ # ^\n"
            "Yes _ _ _ _ # -> Add _ ^ _ ^ _ ^ _ > # ^\n"
            "No _ _ 0 _ | -> No _ ^ _ ^ _ > _ ^ | ^\n"
            "No _ _ 1 _ | -> No _ ^ _ ^ _ > _ ^ | ^\n"
            "No _ _ 3 _ | -> No _ ^ _ ^ _ > _ ^ | ^\n"
            "No _ _ 4 _ | -> No _ ^ _ ^ _ > _ ^ | ^\n"
            "No _ _ < _ | -> No _ ^ _ ^ _ > _ ^ | ^\n"
            "No _ _ _ _ | -> GoD _ ^ _ ^ _ ^ _ > | ^\n"
            "No _ _ 0 _ # -> No _ ^ _ ^ _ > _ ^ # ^\n"
            "No _ _ 1 _ # -> No _ ^ _ ^ _ > _ ^ # ^\n"
            "No _ _ 3 _ # -> No _ ^ _ ^ _ > _ ^ # ^\n"
            "No _ _ 4 _ # -> No _ ^ _ ^ _ > _ ^ # ^\n"
            "No _ _ < _ # -> No _ ^ _ ^ _ > _ ^ # ^\n"
            "No _ _ _ _ # -> GoD _ ^ _ ^ _ ^ _ > # ^\n"
            "GoD _ _ _ 0 | -> GoD _ ^ _ ^ 0 > 0 > | ^\n"
            "GoD _ _ _ 1 | -> GoD _ ^ _ ^ 1 > 1 > | ^\n"
            "GoD _ _ _ < | -> Add _ ^ _ ^ < > < > | ^\n"
            "GoD _ _ _ 0 # -> GoD _ ^ _ ^ _ ^ 0 > # ^\n"
            "GoD _ _ _ 1 # -> GoD _ ^ _ ^ _ ^ 1 > # ^\n"
            "GoD _ _ _ < # -> Add _ ^ _ ^ _ ^ < > # ^\n"
            "Add _ _ _ 0 | -> Add _ ^ 0 > _ ^ _ > | ^\n"
            "Add _ _ _ 1 | -> Add _ ^ 1 > _ ^ _ > | ^\n"
            "Add _ _ _ < | -> SvdE _ ^ | > _ ^ _ > | ^\n"
            "Add _ _ _ _ | -> SvdS _ ^ | > _ ^ _ < | ^\n"
            "Add _ _ _ 0 # -> Add _ ^ 0 > 0 > _ > # ^\n"
            "Add _ _ _ 1 # -> Add _ ^ 1 > 1 > _ > # ^\n"
            "Add _ _ _ < # -> SvdE _ ^ | > _ > _ > # ^\n"
            "Add _ _ _ _ # -> SvdS _ ^ | > _ > _ < # ^\n"
            "SvdE _ _ _ 0 | -> SvdE _ ^ _ ^ 0 > 0 > | ^\n"
            "SvdE _ _ _ 1 | -> SvdE _ ^ _ ^ 1 > 1 > | ^\n"
            "SvdE _ _ _ _ | -> SetN _ > _ ^ < > < > | ^\n"
            "SvdE _ _ _ 0 # -> SetL _ ^ _ ^ _ ^ 0 ^ # ^\n"
            "SvdE _ _ _ 1 # -> SetL _ ^ _ ^ _ ^ 1 ^ # ^\n"
            "SvdS _ _ _ < | -> SetN _ > _ ^ _ ^ < > | ^\n"
            "SvdS _ _ _ _ | -> SvdS _ ^ _ ^ _ ^ _ < | ^\n"
            "SvdS _ _ _ < # -> SvdSS _ ^ _ ^ _ ^ _ < # ^\n"
            "SvdS _ _ _ _ # -> SvdS _ ^ _ ^ _ ^ _ < # ^\n"
            "SvdSS _ _ _ 0 # -> SvdSS _ ^ _ ^ _ ^ 0 < # ^\n"
            "SvdSS _ _ _ 1 # -> SvdSS _ ^ _ ^ _ ^ 1 < # ^\n"
            "SvdSS _ _ _ _ # -> SetL _ ^ _ ^ _ ^ _ > # ^\n"
            "SetL _ _ _ 0 # -> SetL _ ^ 0 > _ ^ _ > # ^\n"
            "SetL _ _ _ 1 # -> SetL _ ^ 1 > _ ^ _ > # ^\n"
            "SetL _ _ _ _ # -> Ans _ ^ _ < _ ^ _ ^ # ^\n"
            "Ans _ 0 _ _ # -> Ans 0 < _ < _ ^ _ ^ # ^\n"
            "Ans _ 1 _ _ # -> Ans 1 < _ < _ ^ _ ^ # ^\n"
            "Ans _ | _ _ # -> Ans | < _ < _ ^ _ ^ # ^\n"
            "Ans _ _ _ _ # -> for _ ^ _ ^ _ ^ _ ^ _ <\n"
            "end _ _ _ _ _ -> AC _ > _ ^ _ ^ _ ^ _ ^";
    return 0;
}