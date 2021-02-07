#include <algorithm>
#include "parser.h"

using namespace std;

int main() {
    auto f = ParseFile(std::cin);
    auto ans = Answer(f);

    vector<bool> used(f.N, false);

    sort(f.rides.begin(), f.rides.end(), [](const Ride& lhs, const Ride& rhs) {
        return lhs.s < rhs.s;
    });

    vector<int> t(f.F, 0);
    vector<Point> pos(f.F, Point{0, 0});

    for (int i = 0; i < f.N; ++i) {
        int best_id = -1;
        int worst_pos = 0;
        const auto& ride = f.rides[i];

        for (int j = 0; j < f.F; ++j) {
            Point& cur_pos = pos[j];
            int cur_t = t[j];
            if (!hasTime(cur_pos, cur_t, ride)) {
                continue;
            }
            int start_time = std::max(cur_t + dist(cur_pos, ride.from), ride.s);
            if (best_id == -1 || worst_pos > start_time) {
                best_id = j;
                worst_pos = start_time;
            }
        }
        if (best_id != -1) {
            ans.AddRide(best_id, ride.id);
            moveVeh(pos[best_id], t[best_id], ride);
        }
    }

    ans.ShowScore();
    return 0;
}
