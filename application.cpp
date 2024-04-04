#include "config.h"

const std::string config_file_name = "config.txt";

void app() {
    config c;

    c.read_config(config_file_name);
}

