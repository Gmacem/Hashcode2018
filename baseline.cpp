#include "parser.h"

using namespace std;

int main() {
    auto f = ParseFile(std::cin);
    auto ans = Answer(f);

    vector<bool> used(f.N, false);
    for (int i = 0; i < f.F; ++i) {
        Point pos{0, 0};
        int t = 0;
        for (int j = 0; j < f.N; ++j) {
            if (used[j]) {
                continue;
            }
            if (hasTime(pos, t, f.rides[j])) {
                moveVeh(pos, t, f.rides[j]);
                used[j] = true;
                ans.AddRide(i, j);
            }
        }
    }

    ans.ShowScore();
    return 0;
}
