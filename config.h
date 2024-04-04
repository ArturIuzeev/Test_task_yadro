#pragma once

#include <fstream>
#include <map>
#include <sstream>
#include <string>

struct config {
  std::map<std::string, unsigned int> values{
      {        "recording_delay", 0},
      {             "read_delay", 0},
      {"tape_delay_one_position", 0},
      {             "tape_delay", 0}
  };

  void read_config(const std::string& file_name);

private:
  int check_correct_time(const std::string& time, const std::string& file_name);
  void check_correct_command(const std::string& command, const std::string& file_name);
};