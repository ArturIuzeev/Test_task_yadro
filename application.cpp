#include "config.h"

const std::string path_to_config_file = "../config.txt";

void app() {
    config c;

    c.read_config(path_to_config_file);
}

