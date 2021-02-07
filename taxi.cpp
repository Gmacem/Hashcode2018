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
    long long sum_x = 0;
    long long sum_y = 0;
    for (int i = 0; i < f.rides.size(); ++i) {
        sum_x += f.rides[i].from.x;
        sum_y += f.rides[i].from.y;
    }
    
    int mid_x = sum_x / f.rides.size();
    int mid_y = sum_y / f.rides.size();
    Point mid{mid_x, mid_y};

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
        if (best_id != -1) {
            ans.AddRide(best_id, ride.id);
            moveVeh(pos[best_id], t[best_id], ride);
        }
    }

    ans.ShowScore();
    return 0;
}
