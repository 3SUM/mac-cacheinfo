#include <sys/sysctl.h>

#include <cstdint>
#include <print>

int main(int argc, char *argv[]) {
    if (argc != 1) {
        std::print("Usage\n\t./cache\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}