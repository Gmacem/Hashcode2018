#include <algorithm>
#include "parser.h"

using namespace std;

const int MAX_FORWARD = 100;

int main() {
    auto f = ParseFile(std::cin);
    auto ans = Answer(f);

    vector<bool> used(f.N, false);

    sort(f.rides.begin(), f.rides.end(), [](const Ride& lhs, const Ride& rhs) {
        return lhs.s < rhs.s;
    });


    for (int i = 0; i < f.F; ++i) {
        Point pos{0, 0};
        int t = 0;
        for (int j = 0; j < f.N; ++j) {
            if (used[j] || !hasTime(pos, t, f.rides[j])) {
                continue;
            }
            int best_id = j;
            for (int z = j, k = 0; k < MAX_FORWARD && z < f.N; ++z, ++k) {
                if (used[z] || !hasTime(pos, t, f.rides[z])) {
                    continue;
                }
                int start_time = t + dist(pos, f.rides[z].from);
                if (start_time <= f.rides[z].s) {
                    best_id = z;
                    break;
                }
            }
            moveVeh(pos, t, f.rides[best_id]);
            used[best_id] = true;
            ans.AddRide(i, f.rides[best_id].id);
        }
    }

    ans.ShowScore();
    return 0;
}
