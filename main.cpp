#include <iostream>

extern void app();

int main() {
    try {
        app();
    } catch (std::exception const& error) {
        std::cerr << error.what() << '\n';
    }
    return 0;
}
