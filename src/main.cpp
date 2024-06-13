#include <sys/sysctl.h>

#include <cstdint>
#include <print>

size_t get_cachelinesize() {
    size_t cacheline = 0;
    size_t sizeof_cacheline = sizeof(cacheline);
    sysctlbyname("hw.cachelinesize", &cacheline, &sizeof_cacheline, 0, 0);
    return cacheline;
}

size_t get_l1icachesize() {
    size_t l1icache = 0;
    size_t sizeof_l1icache = sizeof(l1icache);
    sysctlbyname("hw.l1icachesize", &l1icache, &sizeof_l1icache, 0, 0);
    return l1icache;
}

size_t get_l1dcachesize() {
    size_t l1dcache = 0;
    size_t sizeof_l1dcache = sizeof(l1dcache);
    sysctlbyname("hw.l1dcachesize", &l1dcache, &sizeof_l1dcache, 0, 0);
    return l1dcache;
}

size_t get_l2cachesize() {
    size_t l2cache = 0;
    size_t sizeof_l2cache = sizeof(l2cache);
    sysctlbyname("hw.l1icachesize", &l2cache, &sizeof_l2cache, 0, 0);
    return l2cache;
}

int main(int argc, char *argv[]) {
    if (argc != 1) {
        std::print("Usage\n\t./cache\n");
        exit(EXIT_FAILURE);
    }

    std::print("Device Info\n{:=>36}\n", '=');
    std::print("\tCache Line Size: {:>8}  B\n", get_cachelinesize());
    std::print("\tL1i  Cache Size: {:>8} KB\n", get_l1icachesize() * 1e-3);
    std::print("\tL1d  Cache Size: {:>8} KB\n", get_l1dcachesize() * 1e-3);
    std::print("\tL2   Cache Size: {:>8} KB\n", get_l2cachesize() * 1e-3);
    exit(EXIT_SUCCESS);
}