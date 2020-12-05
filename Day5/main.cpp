// https://adventofcode.com/2020/day/5
// compiled with g++, -std=c++20

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include <set>
#include <algorithm>

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

std::set<uint16_t> ToBinary(std::vector<std::string>&& data) {
    std::set<uint16_t> out{};

    // Transforms the vector of strings into a set of unsigned integers
    std::transform(data.begin(), data.end(), std::inserter(out, out.begin()), [](auto&& line) {
        // Transforms the strings to a binary string
        std::transform(line.begin(), line.end(), line.begin(), [](uint8_t key) {
            return key == 'B' || key == 'R' ? '1' : '0';
        });

        // Converts the binary strings into integers of binary base
        return std::stoi(line, nullptr, 2);
    });

    return out;
}

namespace Part1 {
    uint16_t Solution(std::string_view filename) {
        // Reads the binary data and returns the last item (the greatest value)
        auto set = ToBinary(Read(filename));
        return *(--set.end());
    }
}

namespace Part2 {
    uint16_t Solution(std::string_view filename) {
        auto set = ToBinary(Read(filename));

        for (uint16_t prev = *set.begin(); int16_t current : set) {
            // If the difference between the previous and the current value is 2, then the answer is in the middle
            if (current - prev == 2)
                return prev + 1;

            // Otherwise keep updating the previous value
            prev = current;
        }
    
        return 0;
    }
}


int main() {
    std::cout << "Part 1: " << Part1::Solution("input.txt") << '\n';
    std::cout << "Part 1: " << Part2::Solution("input.txt") << '\n';
}