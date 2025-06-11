#include <sys/sysctl.h>

#include <cstdint>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>

constexpr size_t BUFFER_SIZE = 128;

std::string get_cpu_type() {
    char buffer[BUFFER_SIZE];
    size_t size = sizeof(buffer);

    if (sysctlbyname("machdep.cpu.brand_string", &buffer, &size, nullptr, 0) < 0) {
        throw std::runtime_error("Unable to retrieve CPU Type");
    }

    return std::string(buffer);
}

std::optional<size_t> get_sysctl_value(const char *name) {
    size_t value = 0;
    size_t size = sizeof(value);

    if (sysctlbyname(name, &value, &size, nullptr, 0) < 0) {
        return std::nullopt;
    }

    return value;
}

size_t get_cachelinesize() {
    if (auto value = get_sysctl_value("hw.cachelinesize"); value) {
        return *value;
    }

    throw std::runtime_error("Unable to retreive Cache Line Size");
}

size_t get_l1icachesize() {
    if (auto value = get_sysctl_value("hw.l1icachesize"); value) {
        return *value;
    }

    throw std::runtime_error("Unable to retreive L1i Cache Size");
}

size_t get_l1dcachesize() {
    if (auto value = get_sysctl_value("hw.l1dcachesize"); value) {
        return *value;
    }

    throw std::runtime_error("Unable to retrieve L1d Cache Size");
}

size_t get_l2cachesize() {
    if (auto value = get_sysctl_value("hw.l2cachesize"); value) {
        return *value;
    }

    throw std::runtime_error("Unable to retrieve L2 Cache Size");
}

int main(int argc, char *argv[]) {
    if (argc != 1) {
        std::print("Usage\n\t./cache\n");
        return EXIT_FAILURE;
    }

    try {
        std::print("{} CPU Info\n{:=>36}\n", get_cpu_type(), '=');
        std::print("\tCache Line Size: {:>8}  B\n", get_cachelinesize());
        std::print("\tL1i  Cache Size: {:>8} KB\n", get_l1icachesize() * 1e-3);
        std::print("\tL1d  Cache Size: {:>8} KB\n", get_l1dcachesize() * 1e-3);
        std::print("\tL2   Cache Size: {:>8} KB\n", get_l2cachesize() * 1e-3);
    } catch (const std::exception &e) {
        std::print("[ERROR] {}\n", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
