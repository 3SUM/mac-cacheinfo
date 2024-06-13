#include <sys/sysctl.h>

#include <cstdint>
#include <print>

size_t get_size() {
    size_t cacheline = 0;
    size_t sizeof_cacheline = sizeof(cacheline);
    sysctlbyname("hw.cachelinesize", &cacheline, &sizeof_cacheline, 0, 0);
    return cacheline;
}

int main(int argc, char *argv[]) {
    if (argc != 1) {
        std::print("Usage\n\t./cache\n");
        exit(EXIT_FAILURE);
    }

    std::print("Device CPU Cache Line Size: {} bytes\n", get_size());
    exit(EXIT_SUCCESS);
}