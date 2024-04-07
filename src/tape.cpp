#include "../include/tape.h"

void tape::head_next() {
  std::this_thread::sleep_for(std::chrono::milliseconds(tape_delay_one_position));
  file.seekg(size_element_t, std::ios_base::cur);
}

void tape::head_prev() {
  std::this_thread::sleep_for(std::chrono::milliseconds(tape_delay_one_position));
  file.seekg(-static_cast<std::ptrdiff_t>(size_element_t), std::ios_base::cur);
}

void tape::head_begin() {
  std::this_thread::sleep_for(std::chrono::milliseconds(tape_delay));
  file.seekg(0, std::ios_base::beg);
}

void tape::head_end() {
  std::this_thread::sleep_for(std::chrono::milliseconds(tape_delay));
  file.seekg(0, std::ios_base::end);
}

bool tape::has_next() {
  element_t res;
  std::this_thread::sleep_for(std::chrono::milliseconds(read_delay));
  if (file.read(reinterpret_cast<char*>(&res), sizeof(res))) {
    head_prev();
    return true;
  }
  return false;
}

tape::element_t tape::read_next() {
  std::this_thread::sleep_for(std::chrono::milliseconds(read_delay));
  element_t res;
  file.read(reinterpret_cast<char*>(&res), sizeof(res));
  return res;
}

tape::element_t tape::read_cur() {
  std::this_thread::sleep_for(std::chrono::milliseconds(read_delay));
  auto res = read_next();
  head_prev();
  return res;
}

tape::element_t tape::read_prev() {
  std::this_thread::sleep_for(std::chrono::milliseconds(read_delay));
  head_prev();
  auto res = read_next();
  head_prev();
  return res;
}

void tape::write(std::vector<tape::element_t>& v) {
  for (int& i : v) {
    write(i);
  }
}

void tape::write(tape::element_t& v) {
  std::this_thread::sleep_for(std::chrono::milliseconds(write_delay));
  file.write(reinterpret_cast<char*>(&v), sizeof(element_t));
}

void tape::parse_config(config& c) {
  write_delay = c.values["write_delay"];
  read_delay = c.values["read_delay"];
  tape_delay_one_position = c.values["tape_delay_one_position"];
  tape_delay = c.values["tape_delay"];
  ram_size = c.values["ram_size"];
}