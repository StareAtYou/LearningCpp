#include "test.hpp"
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"


using namespace std;


void nlohmann_json_test()
{
    using json = nlohmann::json;

    std::ifstream f("../data/test.json");
    json data = json::parse(f);

    cout << data["success"] << endl;
    cout << data["result"][0]["days"] << endl;
}
