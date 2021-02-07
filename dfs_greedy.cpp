#include "parser.h"
#include <iostream>
#include <unordered_set>
#include <algorithm>

struct RideHash
{
    size_t operator()(const Ride &ride) const
    {
        return ride.id;
    }
};

struct NodeComparer
{
    bool operator()(const Ride &first, const Ride &second) const
    {
        return first.id == second.id;
    }
};

using std::unordered_set;

unordered_set<Ride, RideHash, NodeComparer> claimedRides;

bool IsRideAppropriate(const Ride &ride, const int &currentTime, const Point &currentPos)
{
    int startTime = currentTime + dist(currentPos, ride.from);
    int endTime = startTime + dist(ride.from, ride.to);
    return ride.s <= startTime && ride.f >= endTime && claimedRides.count(ride) == 0;
}

void dfs(Point &currentPos, int &currentTime, TestConfig &config, int &vehicleId, Answer &ans)
{
    sort(config.rides.begin(), config.rides.end(), [currentPos, currentTime](const Ride &a, const Ride &b) -> bool {
        if (!IsRideAppropriate(a, currentTime, currentPos))
            return false;

        if (!IsRideAppropriate(b, currentTime, currentPos))
            return true;

        return dist(currentPos, a.from) < dist(currentPos, b.from);
    });

    Ride chosenRide = config.rides.front();

    if (IsRideAppropriate(chosenRide, currentTime, currentPos))
    {
        ans.AddRide(vehicleId, chosenRide.id);
        claimedRides.emplace(chosenRide);
        int nextTime = currentTime + dist(currentPos, chosenRide.from) + dist(chosenRide.from, chosenRide.to);
        dfs(chosenRide.to, nextTime, config, vehicleId, ans);
    }
}

Point zeroPoint{0, 0};
int zero = 0;

int main(int argc, char const *argv[])
{
    TestConfig config = ParseFile(std::cin);
    Answer ans(config);

    for (int carId = 0; carId < config.F; ++carId)
    {
        dfs(zeroPoint, zero, config, carId, ans);
    }

    ans.ShowScore();

    return 0;
}
