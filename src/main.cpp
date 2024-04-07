#include <iostream>
#include <vector>

extern void app(int argc, char* argv[]);

int main(int argc, char* argv[]) {
  try {
    app(argc, argv);
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
  }
  return 0;
}
