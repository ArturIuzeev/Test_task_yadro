#pragma once

#include "tape.h"

#include <algorithm>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace tape_sort_details {
const std::string path_tmp = "../tmp/tmp_vector_";
const std::string file_format = ".txt";

void create_tmp() {
  fs::path tmp{"../"};
  fs::create_directories(tmp / "tmp");
}

void del_tmp() {
  fs::path tmp("../tmp");
  fs::remove_all(tmp);
}

void fill_array_by_nums_tape(std::vector<int>& v, tape& t, unsigned int max_array_size) {
  while (v.size() != max_array_size && t.has_next()) {
    v.push_back(t.read_next());
  }
}

template <typename Comp>
void merge_all_tmp(std::vector<std::unique_ptr<tape>>& tmp_tapes, tape& result,
                   Comp comparator = Comp{}) {
  std::vector<std::pair<int, int>> h;

  for (int i = 0; i < tmp_tapes.size(); ++i) {
    if (tmp_tapes[i]->has_next()) {
      h.emplace_back(tmp_tapes[i]->read_cur(), i);
    }
  }

  std::make_heap(h.begin(), h.end(),
                 [&comparator](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                   return !comparator(a.first, b.first);
                 });

  while (!h.empty()) {
    std::pop_heap(h.begin(), h.end(),
                  [&comparator](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                    return !comparator(a.first, b.first);
                  });

    auto item = *--h.end();
    h.pop_back();

    result.write(item.first);
    tmp_tapes[item.second]->read_next();

    if (tmp_tapes[item.second]->has_next()) {
      h.emplace_back(tmp_tapes[item.second]->read_cur(), item.second);
      std::push_heap(h.begin(), h.end(),
                     [&comparator](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                       return !comparator(a.first, b.first);
                     });
    }
  }
}

template <typename Comp>
void tape_sort_base(tape& t, tape& result, unsigned int max_array_size, config& c,
                    Comp comparator) {

  t.head_begin();
  result.head_begin();

  int count_arrays = 0;

  std::vector<int> buffer;
  std::vector<std::unique_ptr<tape>> tmp_tapes;

  create_tmp();
  while (t.has_next()) {
    fill_array_by_nums_tape(buffer, t, max_array_size);
    std::sort(buffer.begin(), buffer.end(), comparator);

    if (buffer.size() == max_array_size || (!t.has_next() && count_arrays != 0)) {
      std::string path_to_tmp = path_tmp + std::to_string(count_arrays) + file_format;

      std::ofstream out(path_to_tmp);
      out.close();

      std::unique_ptr<tape> ptr = std::make_unique<tape>(path_to_tmp, c, std::ios::trunc);

      ptr->write(buffer);
      ptr->head_begin();

      tmp_tapes.push_back(std::move(ptr));

      ++count_arrays;
      buffer = std::vector<int>();
    }
  }

  if (count_arrays == 0) {
    result.write(buffer);
    result.head_begin();
    t.head_begin();
  } else {
    merge_all_tmp(tmp_tapes, result, comparator);
  }

  del_tmp();
  result.head_begin();
}
} // namespace tape_sort_details

void tape_sort(tape& t, tape& res) {
  tape_sort_details::tape_sort_base(t, res, t.ram_size, t.cf, std::less<>());
}

template <typename Comp>
void tape_sort(tape& t, tape& res, Comp comparator) {
  tape_sort_details::tape_sort_base(t, res, t.ram_size, t.cf, comparator);
}
