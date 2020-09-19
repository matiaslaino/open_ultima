#include "Configuration.h"

tao::json::value Configuration::_value;

void Configuration::init() {
    _value = tao::json::parse_file<>("config.json");
}
