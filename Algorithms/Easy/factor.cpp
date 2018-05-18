#include <iostream>
#include <vector>

using namespace std;

vector<int> easy;

int main() {
    easy.assign(1000000, -1);
    for (int i = 1; i < 1000000; ++i) {
        if (easy[i] == -1) {
            for (int j = i + i + 1; j < 1000000; j += i + 1) {
                if (easy[j] == -1) {
                    easy[j] = i + 1;
                }
            }
            easy[i] = i + 1;
        }
    }

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);
        while (k != 1) {
            printf("%d ", easy[k - 1]);
            k /= easy[k - 1];
        }
        printf("\n");
    }
    return 0;
}