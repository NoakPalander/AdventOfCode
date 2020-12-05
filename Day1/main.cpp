#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string_view>
#include <algorithm>
#include <functional>

using namespace std::literals;

template<typename T>
std::vector<T> Read(std::string_view file, std::function<T(std::string const&)> const& func) {
    std::ifstream reader{ file.data() };
    if (reader) {
        std::vector<T> data{};
        for (std::string line{}; std::getline(reader, line);)
            data.emplace_back(func(line));

        return data;
    }

    throw std::invalid_argument("Failed to read the file!");
}

namespace Part1 {
    uint32_t Solution(std::string_view filename) {
        auto data = Read<uint16_t>(filename, [](auto&& str) { return std::stoi(str); });
        std::ranges::sort(data);

        for (auto it = data.cbegin(); uint16_t val : data)
            if (std::binary_search(++it, data.cend(), 2020 - val))
                return (2020 - val) * val;

        return 0;
    }
}

namespace Part2 {
    uint32_t Solution(std::string_view filename) {
        auto data = Read<uint16_t>(filename, [](auto&& str) { return std::stoi(str); });
        std::ranges::sort(data);

        for (auto it = data.cbegin(); uint16_t first : data)
            for (auto inner = it; uint16_t second : data)
                if (std::binary_search(++inner, data.cend(), 2020 - first - second))
                    return (2020 - first - second) * first * second;

        return 0;
    }
}

int main() {
    std::cout << Part1::Solution("input.txt") << '\n';
    std::cout << Part2::Solution("input.txt") << '\n';
}