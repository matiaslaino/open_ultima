#include "Configuration.h"
#include <iostream>

using namespace std;

tao::json::value Configuration::_value;

void Configuration::init() {
    _value = tao::json::parse_file<>("config.json");

    // validate that required configuration entries exist
    try {
        Configuration::getMapFilePath();
        Configuration::getScreenWidth();
        Configuration::getScreenHeight();
    } catch (exception &ex) {
        auto msg = "Error trying to parse configuration file";
        cout << msg;
        throw exception(msg);
    }
}
