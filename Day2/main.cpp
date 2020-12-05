#include <fstream>
#include <string>
#include <vector>
#include <string_view>
#include <algorithm>
#include <iostream>

std::vector<std::string> Read(std::string_view file) {
    std::ifstream reader{ file.data() };
    if (reader) {
        std::vector<std::string> data{};
        for (std::string line{}; std::getline(reader, line);)
            data.emplace_back(line);

        return data;
    }

    throw std::invalid_argument("Failed to read the file!");
}

namespace Part1 {
    uint32_t Solution(std::string_view filename) {
        auto data = Read(filename);
        uint16_t valid{};

        for (std::string_view line : data) {
            uint16_t const min = std::stoi(line.substr(0, line.find('-')).data());
            uint16_t const max = std::stoi(line.substr(line.find('-') + 1, line.find(' ')).data());
            char const key = line[line.find(':') - 1];

            if (size_t count = std::ranges::count(line.substr(line.find(": ") + 2), key); count >= min && count <= max)
                ++valid;
        }

        return valid;
    }
}

namespace Part2 {
    uint32_t Solution(std::string_view filename) {
        auto data = Read(filename);
        uint16_t valid{};

        for (std::string_view line : data) {
            uint16_t const min = std::stoi(line.substr(0, line.find('-')).data());
            uint16_t const max = std::stoi(line.substr(line.find('-') + 1, line.find(' ')).data());
            char const key = line[line.find(':') - 1];
            
            std::string_view const password = line.substr(line.find(": ") + 2);

            if ((password[min - 1] == key && password[max - 1] != key) || (password[min - 1] != key && password[max - 1] == key))
                ++valid;
        }

        return valid;
    }
}

int main() {
    std::cout << Part1::Solution("input.txt") << '\n';
    std::cout << Part2::Solution("input.txt") << '\n';
}