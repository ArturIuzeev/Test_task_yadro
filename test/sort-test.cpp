#include "../include/tape.h"
#include "../include/tape_utilities.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <functional>
#include <random>

namespace fs = std::filesystem;

const std::string in_file = "in.txt";
const std::string out_file = "out.txt";
const std::string config_file = "config.txt";

const std::string path = "../";

const std::string c_file = "// API: \"command <time_in_seconds>\"\n"
                           "ram_size <0>\n"
                           "write_delay <0>\n"
                           "read_delay <0>\n"
                           "tape_delay_one_position <0>\n"
                           "tape_delay <0>";

const std::string c_file_hard = "// API: \"command <time_in_seconds>\"\n"
                                "ram_size <26214400>\n"
                                "write_delay <5>\n"
                                "read_delay <5>\n"
                                "tape_delay_one_position <1>\n"
                                "tape_delay <1>";

void create_files(bool flag = false) {
  std::ofstream i(in_file);
  i.close();

  std::ofstream o(out_file);
  o.close();

  std::ofstream c(config_file);
  if (!flag) {
    c << c_file;
  } else {
    c << c_file_hard;
  }
  o.close();
}

void del(std::string f) {
  fs::path filePath = fs::current_path() / f;
  if (fs::exists(f)) {
    fs::remove(f);
  }
}

void del_files() {
  del(in_file);
  del(out_file);
  del(c_file);
}

TEST(test_head_tape, simple_sort_1) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 10; ++i) {
    v.push_back(distrib(gen));
  }

  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);

  tape t(in_file, c, std::ios_base::trunc);

  t.write(v);

  t.head_begin();
  EXPECT_EQ(t.read_cur(), v[0]);
  EXPECT_EQ(t.read_cur(), v[0]);

  t.read_next();
  EXPECT_EQ(t.read_cur(), v[1]);

  t.read_next();
  EXPECT_EQ(t.read_cur(), v[2]);

  t.head_prev();
  EXPECT_EQ(t.read_cur(), v[1]);

  t.head_end();
  t.head_prev();
  EXPECT_EQ(t.read_cur(), v[v.size() - 1]);

  del_files();
}

TEST(sort_test, simple_sort_1) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 10; ++i) {
    v.push_back(distrib(gen));
  }

  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }

  del_files();

  EXPECT_EQ(v, res_v);
}

TEST(sort_test, simple_sort_2) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 20; ++i) {
    v.push_back(distrib(gen));
  }
  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}

TEST(sort_test, simple_sort_3) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 15; ++i) {
    v.push_back(distrib(gen));
  }

  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}

TEST(sort_test, hard_sort_1) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 100; ++i) {
    v.push_back(distrib(gen));
  }
  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}

TEST(sort_test, hard_sort_2) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 1000; ++i) {
    v.push_back(distrib(gen));
  }

  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}

TEST(sort_test, hard_sort_3) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 10000; ++i) {
    v.push_back(distrib(gen));
  }
  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}

TEST(sort_test_delay, simple_sort_delay_1) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 10; ++i) {
    v.push_back(distrib(gen));
  }

  create_files(true);
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }

  del_files();

  EXPECT_EQ(v, res_v);
}

TEST(sort_test_delay, simple_sort_delay_2) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 20; ++i) {
    v.push_back(distrib(gen));
  }
  create_files(true);
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}

TEST(sort_test_tmp, simple_sort_with_tmp_1) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 10; ++i) {
    v.push_back(distrib(gen));
  }

  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);
  c.values["ram_size"] = 2;

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }

  del_files();

  EXPECT_EQ(v, res_v);
}

TEST(sort_test_tmp, simple_sort_with_tmp_2) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 100; ++i) {
    v.push_back(distrib(gen));
  }
  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);
  c.values["ram_size"] = 10;

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}

TEST(sort_test_tmp, simple_sort_with_tmp_3) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 1000; ++i) {
    v.push_back(distrib(gen));
  }

  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);
  c.values["ram_size"] = 100;

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res);
  std::sort(v.begin(), v.end());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}

TEST(sort_test_tmp_comparator, simple_sort_1) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 10; ++i) {
    v.push_back(distrib(gen));
  }

  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);
  c.values["ram_size"] = 2;

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res, std::less<>());
  std::sort(v.begin(), v.end(), std::less<>());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }

  del_files();

  EXPECT_EQ(v, res_v);
}

TEST(sort_test_tmp_comparator, simple_sort_2) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 100; ++i) {
    v.push_back(distrib(gen));
  }
  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);
  c.values["ram_size"] = 10;

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res, std::less<>());
  std::sort(v.begin(), v.end(), std::less<>());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}

TEST(sort_test_tmp_comparator, simple_sort_3) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(INT32_MIN, INT32_MAX);

  std::vector<int> v;

  for (int i = 0; i < 1000; ++i) {
    v.push_back(distrib(gen));
  }

  create_files();
  std::vector<int> res_v;

  config c;
  c.read_config(config_file);
  c.values["ram_size"] = 100;

  tape t(in_file, c, std::ios_base::trunc);
  tape res(out_file, c, std::ios_base::trunc);

  t.write(v);
  t.head_begin();

  tape_sort(t, res, std::less<>());
  std::sort(v.begin(), v.end(), std::less<>());

  while (res.has_next()) {
    res_v.push_back(res.read_next());
  }
  del_files();
  EXPECT_EQ(v, res_v);
}