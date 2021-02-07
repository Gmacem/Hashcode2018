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
    Point mid{f.R / 2, f.C / 2};

    for (int i = 0; i < f.N; ++i) {
        int best_id = -1;
        bool in_time = false;
        int worst_pos = 0;
        const auto& ride = f.rides[i];

        for (int j = 0; j < f.F; ++j) {
            Point& cur_pos = pos[j];
            int cur_t = t[j];
            if (!hasTime(cur_pos, cur_t, ride)) {
                continue;
            }
            int start_time = std::max(cur_t + dist(cur_pos, ride.from), ride.s);
            int pos_score = dist(mid, cur_pos);
            if (start_time == ride.s) {
                if (!in_time || worst_pos < pos_score) {
                    best_id = j;
                    in_time = true;
                    worst_pos = pos_score;
                }
            } else if (!in_time) {
                if (best_id == -1 || worst_pos < pos_score) {
                    best_id = j;
                    worst_pos = pos_score;
                }
            }
        }
        //std::cout << i << " " << best_id << '\n';
        if (best_id != -1) {
            //std::cout << pos[best_id].x << " " << pos[best_id].y << " " << t[best_id] << '\n';
            //std::cout << ride.from.x << " " << ride.from.y << " " << ride.s << '\n';
            //std::cout << ride.to.x << " " << ride.to.y << " " << ride.s << '\n';
            ans.AddRide(best_id, ride.id);
            moveVeh(pos[best_id], t[best_id], ride);
        }
    }

    ans.ShowScore();
    return 0;
}
