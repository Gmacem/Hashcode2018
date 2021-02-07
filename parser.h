#pragma once

#include <iostream>
#include <vector>
#include <istream>
#include <assert.h>

struct Point {
    int x, y;
};

struct Ride {
    Point from, to;
    int s, f, id;
};

struct TestConfig {
    int R, C, F, N, B, T;
    std::vector<Ride> rides;
};


TestConfig ParseFile(std::istream& in) {
    TestConfig config;
    in >> config.R >> config.C >> config.F >> config.N >> config.B >> config.T;

    for (int i = 0; i < config.N; ++i) {
        Ride ride;
        in >> ride.from.x >> ride.from.y >> ride.to.x >> ride.to.y >> ride.s >> ride.f;
        ride.id = i;
        config.rides.emplace_back(ride);
    }
    return config;
}


int dist(Point a, Point b) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    return dx + dy;
}

class Answer {
public:
    explicit Answer(TestConfig config): config_(config) {
        v_rides_.resize(config.F);
        pos_.resize(config.F, Point{0, 0});
        t_.resize(config.F, 0);
        used_.resize(config.N, false);
    }

    void AddRide(int veh, int r_id) {
        assert(veh >= 0 && veh < config_.F);
        assert(r_id >= 0 && r_id < config_.N);
        assert(!used_[r_id]);
        const Ride& ride = config_.rides[r_id];
        int start_time = std::max(t_[veh] + dist(pos_[veh], ride.from), ride.s);
        int d = dist(ride.from, ride.to);
        int finish_time = start_time + d;

        if (finish_time <= ride.f) {
            score_ += d;
        }

        if (start_time == ride.s) {
            score_ += config_.B;
        }

        pos_[veh] = ride.to;
        t_[veh] = finish_time;
        used_[r_id] = true;
    }

    void ShowScore() {
        std::cout << "Your score: " << score_ << '\n';
    }

private:
    TestConfig config_;
    std::vector<std::vector<int> > v_rides_;
    std::vector<Point> pos_; 
    std::vector<int> t_;
    std::vector<bool> used_; 
    long long score_ = 0;
};

inline bool hasTime(const Point& start_pos, int t, const Ride& ride) {
    int start_time = std::max(t + dist(start_pos, ride.from), ride.s);
    int d = dist(ride.from, ride.to);
    int finish_time = start_time + d;

    return finish_time <= ride.f;
}

void moveVeh(Point& start_pos, int& t, const Ride& ride) {
    int start_time = std::max(t + dist(start_pos, ride.from), ride.s);
    int d = dist(ride.from, ride.to);
    int finish_time = start_time + d;

    t = finish_time;
    start_pos = ride.to;
}
