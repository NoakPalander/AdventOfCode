// https://adventofcode.com/2020/day/6
// Compiled using g++, -std=c++20

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <numeric>
#include <algorithm>
#include <unordered_set>

using namespace std::literals;

namespace Part1 {
    [[nodiscard]] uint32_t Solve(std::string_view file) {
        auto const getResult = [](std::string substr) {
            std::ranges::sort(substr);
            substr.erase(std::unique(substr.begin(), substr.end()), substr.end());

            return substr.size() - std::ranges::count(substr, '\n');
        };

        std::ifstream reader{ file.data() };
        if (reader) {
            std::vector<size_t> data{};
            std::string line{};

            for (std::string substr{}; std::getline(reader, line);) {
                if (line.empty()) {
                    data.emplace_back(getResult(substr));
                    substr.clear();
                }
                else if (reader.eof())
                    data.emplace_back(getResult(substr + line + '\n'));
                else
                    substr += line + '\n';
            }

            return std::accumulate(data.cbegin(), data.cend(), 0ul);
        }

        throw std::invalid_argument("Failed to read file.."s);
    }
}

namespace Part2 {
    [[nodiscard]] uint32_t Solve(std::string_view file) {
        auto const getResult = [](std::string_view substr) {
            // Count the number of people in each group
            uint32_t people = std::ranges::count(substr, '\n');
            uint32_t count{};

            // Iterate over unique keys
            for (char key : std::unordered_set<char>{ substr.begin(), substr.end() })
                // Ignore newlines and null terminations that might have been picked up
                if (key != '\n' && key != '\0')
                    if (std::ranges::count(substr, key) == people)
                        ++count;

            return count;
        };

        std::ifstream reader{file.data()};
        if (reader) {
            std::vector<uint32_t> data{};
            std::string line{};

            for (std::string substr{}; std::getline(reader, line);) {
                if (line.empty()) {
                    data.emplace_back(getResult(substr));
                    substr.clear();
                }
                else if (reader.eof())
                    data.emplace_back(getResult(substr + line + '\n'));
                else
                    substr += line + '\n';
            }

            return std::accumulate(data.cbegin(), data.cend(), 0ul);
        }

        throw std::invalid_argument("Failed to read file.."s);
    }
}

int main() {
    std::cout << "Part 1: " << Part1::Solve("input.txt") << '\n';
    std::cout << "Part 2: " << Part2::Solve("input.txt") << '\n';
}