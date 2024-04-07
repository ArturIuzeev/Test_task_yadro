#pragma once

#include "config.h"

#include <unistd.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

class tape {
  using element_t = int;
  static const size_t size_element_t = sizeof(element_t);

  std::fstream file;
  config cf;

  unsigned int ram_size;
  unsigned int write_delay;
  unsigned int read_delay;
  unsigned int tape_delay_one_position;
  unsigned int tape_delay;

  void parse_config(config& c);

  friend void tape_sort(tape& t, tape& res);

  template <typename Comp>
  friend void tape_sort(tape& t, tape& res, Comp comparator);

public:
  tape() = default;

  explicit tape(const std::string& name_file, config& c, std::ios::openmode extra_flags = 0)
      : cf(c) {
    file.open(name_file, std::ios::out | std::ios::in | std::ios::binary | extra_flags);
    parse_config(cf);
    if (!file.is_open()) {
      throw std::invalid_argument("Failed to open or create file: " + name_file);
    }
  }

  tape(const tape& other) = delete;
  tape& operator=(const tape& other) = delete;

  tape(tape&& other) = delete;
  tape& operator=(tape&& other) = delete;

  void head_next();
  void head_prev();

  void head_begin();
  void head_end();

  bool has_next();

  element_t read_next();
  element_t read_prev();
  element_t read_cur();

  void write(std::vector<element_t>& v);
  void write(element_t& v);

  ~tape() {
    file.close();
  };
};
