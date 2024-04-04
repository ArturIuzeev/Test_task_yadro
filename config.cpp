#include "config.h"

int config::check_correct_time(const std::string& time, const std::string& file_name) {
  if (time.size() < 2 || !time.starts_with('<') || !time.ends_with('>')) {
    throw std::invalid_argument("Invalid arguments in : " + file_name +
                                " check on correct syntax of time, must be <time>");
  }

  int result;
  try {
    result = std::stoi(time.substr(1, time.size() - 1));
  } catch (...) {
    throw std::invalid_argument("Invalid arguments in : " + file_name +
                                " check on correct syntax of time, must be <time>");
  }

  return result;
}

void config::check_correct_command(const std::string& command, const std::string& file_name) {
  if (!values.contains(command)) {
    throw std::invalid_argument("Invalid arguments in : " + file_name);
  }
}

void config::read_config(const std::string& file_name) {
  std::ifstream in(file_name);

  if (!in.is_open()) {
    throw std::invalid_argument("Failed to open file: " + file_name);
  }
  std::string line;
  while (std::getline(in, line)) {
    if (line.size() >= 2 && std::equal(line.begin(), line.begin() + 2, "//")) {
      continue;
    }

    std::string command;
    std::string time;

    try {
      std::istringstream str_stream(line);
      getline(str_stream, command, ' ');
      getline(str_stream, time, ' ');

      check_correct_command(command, file_name);
      values[command] += check_correct_time(time, file_name);
    } catch (...) {
      in.close();
      throw;
    }
  }
  in.close();
}
