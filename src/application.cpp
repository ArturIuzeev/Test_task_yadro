#include "../include/config.h"
#include "../include/tape_utilities.h"

#include <iostream>

std::string config_file_name;
std::string input_file_name;
std::string output_file_name;

void get_info_about_file(int argc, char* argv[]) {
  if (argc == 4) {
    input_file_name = argv[0];
    output_file_name = argv[1];
    config_file_name = argv[2];
    return;
  }

  std::cout << "Enter the input file name: " << '\n';
  std::cin >> input_file_name;

  std::cout << "Enter the output file name: " << '\n';
  std::cin >> output_file_name;

  std::cout << "Enter the config file name: " << '\n';
  std::cin >> config_file_name;
}

void app(int argc, char* argv[]) {
  get_info_about_file(argc, argv);

  config c;
  c.read_config(config_file_name);

  tape t(input_file_name, c, std::ios::trunc);
  tape res(output_file_name, c, std::ios::trunc);

  tape_sort(t, res);
}
