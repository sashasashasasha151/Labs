#include <iostream>
#include <vector>

using namespace std;

vector<bool> is_easy;
vector<int> easy;

int main() {
    std::ios::sync_with_stdio(false);
    int n, x;
    cin >> n >> x;

    is_easy.assign(100000, true);
    is_easy[0] = false;
    for (int i = 1; i < 100000; ++i) {
        if (is_easy[i]) {
            for (int j = i + i + 1; j < 100000; j += i + 1) {
                is_easy[j] = false;
            }
            easy.push_back(i + 1);
        }
    }

    int h = 0;
    int block = 100000;
    int k = 0;
    vector<bool> is_easy_block;
    bool out = false;
    while (true) {
        is_easy_block.assign(100000, true);
        for (int i = 0; i < easy.size(); ++i) {
            int mod = (block * k + 2) % easy[i];
            int start = (mod == 0) ? 0 : easy[i] - mod;
            if((block * k + 2+start)/easy[i]==1) {
                start+=easy[i];
            }
            for (int j = start; j < block; j+=easy[i]) {
                is_easy_block[j] = false;
            }
        }
        for (int i = 0; i < block; ++i) {
            int some = block * k + 2 + i;
            if (some > n) {
                out = true;
                break;
            }
            if (is_easy_block[i]) {
                h = h * x + some;
            }
        }
        if (out) {
            break;
        }
        k++;
    }

    cout << h;

    return 0;
}