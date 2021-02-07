#include "parser.h"
#include <sstream>
#include <string>


int main(int argc, char* argv[]) {
    std::string str = 
            "3 4 2 3 2 10\n"
            "0 0 1 3 2 9\n"
            "1 2 1 0 0 9\n"
            "2 0 2 2 0 9\n";


    std::istringstream istr (str);

    auto f = ParseFile(istr);
    auto ans = Answer(f);
    ans.AddRide(0, 0);
    ans.AddRide(1, 2);
    ans.AddRide(1, 1);
    ans.ShowScore();
    return 0;
}
