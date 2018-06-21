#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
//    ofstream cout("../DiscreteMathematics/Turing/factorial.out");
    ofstream cout("factorial.out");
    cout << "start: s\n"
            "accept: ac\n"
            "reject: rj\n"
            "blank: _\n"
            "\n"
            "s 1 -> MP0 1 <\n"
            "MP0 _ -> MP1 _ <\n"
            "MP1 _ -> MP2 _ <\n"
            "MP2 _ -> MP3 _ <\n"
            "MP3 _ -> MP4 _ <\n"
            "MP4 _ -> MP5 _ <\n"
            "MP5 _ -> MP6 _ <\n"
            "MP6 _ -> MSet* _ <\n"
            "\n"
            "MSet* _ -> MGo1 * >\n"
            "\n"
            "MGo1 1 -> MGetS 1 >\n"
            "MGo1 4 -> MToSub 4 >\n"
            "MGo1 _ -> MGo1 _ >\n"
            "\n"
            "MGetS 0 -> MGetS 0 >\n"
            "MGetS 1 -> MGetS 1 >\n"
            "MGetS 3 -> MTakeS 3 <\n"
            "MGetS 4 -> MTakeS 4 <\n"
            "MGetS _ -> MTakeS _ <\n"
            "\n"
            "MTakeS 0 -> ML*0 3 <\n"
            "MTakeS 1 -> ML*1 4 <\n"
            "\n"
            "ML*0 0 -> ML*0 0 <\n"
            "ML*0 1 -> ML*0 1 <\n"
            "ML*0 * -> MSet0 * <\n"
            "ML*0 _ -> ML*0 _ <\n"
            "\n"
            "ML*1 0 -> ML*1 0 <\n"
            "ML*1 1 -> ML*1 1 <\n"
            "ML*1 * -> MSet1 * <\n"
            "ML*1 _ -> ML*1 _ <\n"
            "\n"
            "MSet0 0 -> MSet0 0 <\n"
            "MSet0 1 -> MSet0 1 <\n"
            "MSet0 _ -> MGo* 0 >\n"
            "\n"
            "MSet1 0 -> MSet1 0 <\n"
            "MSet1 1 -> MSet1 1 <\n"
            "MSet1 _ -> MGo* 1 >\n"
            "\n"
            "MGo* 0 -> MGo* 0 >\n"
            "MGo* 1 -> MGo* 1 >\n"
            "MGo* * -> MGo1 * >\n"
            "\n"
            "MToSub 3 -> MToSub 3 >\n"
            "MToSub 4 -> MToSub 4 >\n"
            "MToSub _ -> MSub _ <\n"
            "\n"
            "MSub 3 -> MSub 1 <\n"
            "MSub 4 -> MCheckL 0 <\n"
            "\n"
            "MCheckL 3 -> MGoS 0 <\n"
            "MCheckL 4 -> MGoS 1 <\n"
            "MCheckL _ -> MDelL _ >\n"
            "\n"
            "MDelL 0 -> MAddS _ >\n"
            "\n"
            "MGoS 3 -> MGoS 0 <\n"
            "MGoS 4 -> MGoS 1 <\n"
            "MGoS _ -> MAddS _ >\n"
            "\n"
            "MAddS 0 -> MSet*0 3 <\n"
            "MAddS 1 -> MSet*1 4 <\n"
            "MAddS _ -> Finish _ <\n"
            "\n"
            "MSet*0 0 -> MSett0 0 >\n"
            "MSet*0 1 -> MSett0 1 >\n"
            "MSet*0 3 -> MSet*0 3 <\n"
            "MSet*0 4 -> MSet*0 4 <\n"
            "MSet*0 * -> MSett0 * >\n"
            "MSet*0 _ -> MSet*0 _ <\n"
            "\n"
            "MSet*1 0 -> MSett1 0 >\n"
            "MSet*1 1 -> MSett1 1 >\n"
            "MSet*1 3 -> MSet*1 3 <\n"
            "MSet*1 4 -> MSet*1 4 <\n"
            "MSet*1 * -> MSett1 * >\n"
            "MSet*1 _ -> MSet*1 _ <\n"
            "\n"
            "MSett0 _ -> MGo34 0 >\n"
            "\n"
            "MSett1 _ -> MGo34 1 >\n"
            "\n"
            "MGo34 3 -> MFind10 3 >\n"
            "MGo34 4 -> MFind10 4 >\n"
            "MGo34 _ -> MGo34 _ >\n"
            "\n"
            "MFind10 0 -> MSet*0 3 <\n"
            "MFind10 1 -> MSet*1 4 <\n"
            "MFind10 3 -> MFind10 3 >\n"
            "MFind10 4 -> MFind10 4 >\n"
            "MFind10 _ -> ML* _ <\n"
            "\n"
            "ML* 0 -> ML* 0 <\n"
            "ML* 1 -> ML* 1 <\n"
            "ML* 3 -> ML* 3 <\n"
            "ML* 4 -> ML* 4 <\n"
            "ML* * -> MGoStrt * <\n"
            "ML* _ -> ML* _ <\n"
            "\n"
            "MGoStrt 0 -> MGoStrt 0 <\n"
            "MGoStrt 1 -> MGoStrt 1 <\n"
            "MGoStrt _ -> MulS _ >\n"
            "\n"
            "MulS 0 -> Set# 3 <\n"
            "MulS 1 -> Set# 4 <\n"
            "MulS 3 -> MulS 3 >\n"
            "MulS 4 -> MulS 4 >\n"
            "MulS * -> Set# & <\n"
            "MulS & -> MulS & >\n"
            "MulS # -> MulS # >\n"
            "MulS _ -> Set+ _ <\n"
            "\n"
            "Set# 3 -> Set# 3 <\n"
            "Set# 4 -> Set# 4 <\n"
            "Set# & -> Set# & <\n"
            "Set# # -> Set# # <\n"
            "Set# _ -> MulS # >\n"
            "\n"
            "Set+ 3 -> Set+ 3 <\n"
            "Set+ 4 -> Set+ 4 <\n"
            "Set+ & -> Set+ & <\n"
            "Set+ # -> Set+ # <\n"
            "Set+ _ -> Set0 + <\n"
            "\n"
            "Set0 # -> GetS 0 >\n"
            "Set0 _ -> GetS 0 >\n"
            "\n"
            "GetS 3 -> Set+0 # <\n"
            "GetS 4 -> Set+1 # <\n"
            "GetS & -> End & >\n"
            "GetS + -> GetS + >\n"
            "GetS # -> GetS # >\n"
            "\n"
            "Set+0 0 -> Set0 0 >\n"
            "Set+0 1 -> Set0 1 >\n"
            "Set+0 3 -> Set+0 3 <\n"
            "Set+0 4 -> Set+0 4 <\n"
            "Set+0 & -> Set+0 & <\n"
            "Set+0 + -> Set0 + >\n"
            "Set+0 # -> Set+0 # <\n"
            "\n"
            "Set+1 0 -> Set1 0 >\n"
            "Set+1 1 -> Set1 1 >\n"
            "Set+1 3 -> Set+1 3 <\n"
            "Set+1 4 -> Set+1 4 <\n"
            "Set+1 & -> Set+1 & <\n"
            "Set+1 + -> Set1 + >\n"
            "Set+1 # -> Set+1 # <\n"
            "\n"
            "Set1 # -> GetS 1 >\n"
            "\n"
            "End 3 -> End 3 >\n"
            "End 4 -> End 4 >\n"
            "End & -> End & >\n"
            "End # -> End # >\n"
            "End _ -> If _ <\n"
            "\n"
            "If 3 -> Set+0 _ <\n"
            "If 4 -> Add 3 <\n"
            "If & -> Del+ _ <\n"
            "\n"
            "Add 0 -> Add 0 <\n"
            "Add 1 -> Add 1 <\n"
            "Add 3 -> Add 3 <\n"
            "Add 4 -> Add 4 <\n"
            "Add + -> Add + <\n"
            "Add & -> Add & <\n"
            "Add # -> Add # <\n"
            "Add _ -> AddS _ >\n"
            "\n"
            "AddS 0 -> AddS 3 >\n"
            "AddS 1 -> AddS 4 >\n"
            "AddS + -> End0 + >\n"
            "\n"
            "End0 0 -> End0 0 >\n"
            "End0 1 -> End0 1 >\n"
            "End0 # -> Take0 # <\n"
            "End0 3 -> Take0 3 <\n"
            "End0 4 -> Take0 4 <\n"
            "End0 + -> End0 + >\n"
            "\n"
            "End1 0 -> End1 0 >\n"
            "End1 1 -> End1 1 >\n"
            "End1 # -> Take1 # <\n"
            "End1 3 -> Take1 3 <\n"
            "End1 4 -> Take1 4 <\n"
            "End1 + -> End1 + >\n"
            "\n"
            "Take0 0 -> Add00 3 <\n"
            "Take0 1 -> Add01 4 <\n"
            "Take0 + -> St0 + <\n"
            "\n"
            "Take1 0 -> Add10 3 <\n"
            "Take1 1 -> Add11 4 <\n"
            "Take1 + -> St1 + <\n"
            "\n"
            "St0 0 -> St0 0 <\n"
            "St0 1 -> St0 1 <\n"
            "St0 3 -> St0 0 <\n"
            "St0 4 -> St0 1 <\n"
            "St0 _ -> Go+ _ >\n"
            "\n"
            "St1 0 -> St1 0 <\n"
            "St1 1 -> St1 1 <\n"
            "St1 3 -> St0 1 <\n"
            "St1 4 -> St1 0 <\n"
            "St1 _ -> Go+ 1 >\n"
            "\n"
            "Add00 0 -> Add00 0 <\n"
            "Add00 1 -> Add00 1 <\n"
            "Add00 3 -> End0 0 >\n"
            "Add00 4 -> End0 1 >\n"
            "Add00 + -> Add00 + <\n"
            "Add00 _ -> End0 0 >\n"
            "\n"
            "Add01 0 -> Add01 0 <\n"
            "Add01 1 -> Add01 1 <\n"
            "Add01 3 -> End0 1 >\n"
            "Add01 4 -> End1 0 >\n"
            "Add01 + -> Add01 + <\n"
            "Add01 _ -> End0 1 >\n"
            "\n"
            "Add10 0 -> Add10 0 <\n"
            "Add10 1 -> Add10 1 <\n"
            "Add10 3 -> End0 1 >\n"
            "Add10 4 -> End1 0 >\n"
            "Add10 + -> Add10 + <\n"
            "Add10 _ -> End0 1 >\n"
            "\n"
            "Add11 0 -> Add11 0 <\n"
            "Add11 1 -> Add11 1 <\n"
            "Add11 3 -> End1 0 >\n"
            "Add11 4 -> End1 1 >\n"
            "Add11 + -> Add11 + <\n"
            "Add11 _ -> End1 0 >\n"
            "\n"
            "Go+ 0 -> Go+ 0 >\n"
            "Go+ 1 -> Go+ 1 >\n"
            "Go+ + -> Chg + >\n"
            "\n"
            "Chg 3 -> Chg 0 >\n"
            "Chg 4 -> Chg 1 >\n"
            "Chg # -> End # >\n"
            "\n"
            "Del+ 0 -> Del+ _ <\n"
            "Del+ 1 -> Del+ _ <\n"
            "Del+ 3 -> Del+ _ <\n"
            "Del+ 4 -> Del+ _ <\n"
            "Del+ # -> Del+ _ <\n"
            "Del+ + -> MGo1 * >\n"
            "\n"
            "Finish 0 -> Finish _ <\n"
            "Finish 1 -> Finish _ <\n"
            "Finish 3 -> Finish _ <\n"
            "Finish 4 -> Finish _ <\n"
            "Finish * -> LLL _ <\n"
            "Finish & -> Finish _ <\n"
            "Finish + -> Finish _ <\n"
            "Finish # -> Finish _ <\n"
            "Finish _ -> Finish _ <\n"
            "\n"
            "LLL 0 -> LLL 0 <\n"
            "LLL 1 -> LLL 1 <\n"
            "LLL _ -> ac _ >";
    return 0;
}