#include <sys/sysctl.h>

#include <cstdint>
#include <print>
#include <string>

std::string get_cpu_type() {
    char buffer[128];
    size_t size = sizeof(buffer);

    if (sysctlbyname("machdep.cpu.brand_string", &buffer, &size, NULL, 0) < 0) {
        std::print("[ERROR] Unable to retrieve CPU Type!\n");
        exit(EXIT_FAILURE);
    }

    return std::string(buffer);
}

size_t get_cachelinesize() {
    size_t cacheline = 0;
    size_t size = sizeof(cacheline);

    if (sysctlbyname("hw.cachelinesize", &cacheline, &size, NULL, 0) < 0) {
        std::print("[ERROR] Unable to retrieve Cache Line Size\n");
        exit(EXIT_FAILURE);
    }

    return cacheline;
}

size_t get_l1icachesize() {
    size_t l1icache = 0;
    size_t size = sizeof(l1icache);

    if (sysctlbyname("hw.l1icachesize", &l1icache, &size, NULL, 0) < 0) {
        std::print("[ERROR] Unable to retrieve L1i Cache Size\n");
        exit(EXIT_FAILURE);
    }

    return l1icache;
}

size_t get_l1dcachesize() {
    size_t l1dcache = 0;
    size_t size = sizeof(l1dcache);

    if (sysctlbyname("hw.l1dcachesize", &l1dcache, &size, NULL, 0) < 0) {
        std::print("[ERROR] Unable to retrieve L1d Cache Size\n");
        exit(EXIT_FAILURE);
    }

    return l1dcache;
}

size_t get_l2cachesize() {
    size_t l2cache = 0;
    size_t size = sizeof(l2cache);

    if (sysctlbyname("hw.l2cachesize", &l2cache, &size, NULL, 0) < 0) {
        std::print("[ERROR] Unable to retrieve L2 Cache Size\n");
        exit(EXIT_FAILURE);
    }

    return l2cache;
}

int main(int argc, char *argv[]) {
    if (argc != 1) {
        std::print("Usage\n\t./cache\n");
        exit(EXIT_FAILURE);
    }

    std::print("{} CPU Info\n{:=>36}\n", get_cpu_type(), '=');
    std::print("\tCache Line Size: {:>8}  B\n", get_cachelinesize());
    std::print("\tL1i  Cache Size: {:>8} KB\n", get_l1icachesize() * 1e-3);
    std::print("\tL1d  Cache Size: {:>8} KB\n", get_l1dcachesize() * 1e-3);
    std::print("\tL2   Cache Size: {:>8} KB\n", get_l2cachesize() * 1e-3);
    exit(EXIT_SUCCESS);
}
