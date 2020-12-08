// https://adventofcode.com/2020/day/8
// Compiled with 3d party libraries using g++, -std=c++20
#include <fstream>
#include <vector>
#include <string>
#include <string_view>

// These libraries are 3d party, the str_split and flat_hash_set could be replaced by native split methods, and std::unordered_set
#include <fmt/format.h>
#include <absl/strings/str_split.h>
#include <absl/container/flat_hash_set.h>


std::vector<std::string> Read(std::string_view filename) {
    std::ifstream reader{filename.data()};
    if (reader) {
        std::vector<std::string> out;

        for (std::string line{}; std::getline(reader, line);)
            out.emplace_back(line);

        return out;
    }

    throw std::runtime_error("Invalid file!");
}

std::pair<bool, size_t> IsInfinite(std::vector<std::string> const& data) {
    absl::flat_hash_set<size_t> visited;
    size_t acc{};

    for (size_t index = 0; index < data.size(); ++index) {
        auto[instruction, count] = std::pair<std::string, std::string>{ absl::StrSplit(data[index], ' ') };

        if (instruction != "nop")
            instruction == "jmp" ? index += std::stoi(count) - 1 : acc += std::stoi(count);

        if (!visited.emplace(index).second)
            return std::pair{ true, acc };
    }

    return std::pair{ false, acc };
}

namespace Part1 {
    [[nodiscard]] inline size_t Solution(std::string_view filename) {
        return IsInfinite(Read(filename)).second;
    }
}

namespace Part2 {
    [[nodiscard]] size_t Solution(std::string_view filename) {
        std::vector<std::string> data = Read(filename);

        for (std::string& line : data) {
            auto[instruction, count] = std::pair<std::string, std::string>{ absl::StrSplit(line, ' ') };
            if (instruction == "nop") {
                line = fmt::format("{} {}", "jmp", count);
                if (auto[inf, count] = IsInfinite(data); !inf)
                    return count;

                line = fmt::format("{} {}", "nop", count);
            }
            else if (instruction == "jmp") {
                line = fmt::format("{} {}", "nop", count);
                if (auto[inf, count] = IsInfinite(data); !inf)
                    return count;

                line = fmt::format("{} {}", "jmp", count);
            }
        }

        return 0;
    }
}

int main() {
    fmt::print("{}\n", Part1::Solution("input.txt"));
    fmt::print("{}\n", Part2::Solution("input.txt"));
}