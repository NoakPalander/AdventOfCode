// https://adventofcode.com/2020/day/4
// compiled with g++ 10.2, -std=c++20

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <charconv>
#include <regex>

using namespace std::literals;

std::vector<std::string> Read(std::string_view file) {
    std::ifstream reader{ file.data() };
    if (reader) {
        std::vector<std::string> data{};
        std::string line{};

        // Reads the file line by line
        for (std::string substr{}; std::getline(reader, line);) {
            // If the line is empty, prepare next passport
            if (line.empty()) {
                data.emplace_back(substr);
                substr.clear();
            }
            else if (reader.eof())
                data.emplace_back(substr + line + ' ');
            else
                substr += line + ' ';
        }

        return data;
    }

    throw std::invalid_argument("Failed to read file..");
}

namespace Part1 {
    uint16_t Solution(std::string_view filename) {
        constexpr std::array fields {
            "byr"sv, "iyr"sv,
            "eyr"sv, "hgt"sv,
            "hcl"sv, "ecl"sv,
            "pid"sv, "cid"sv
        };

        uint16_t validCount{};

        std::vector<std::string> data = Read(filename);
        for (std::string_view passport : data) {
            std::stringstream stream{ passport.data() };
            std::unordered_map<std::string, std::string_view> keypair{};

            for (std::string pair{}; std::getline(stream, pair, ' ');)
                keypair.emplace(pair.substr(0, pair.find(':')), pair.substr(pair.find(':') + 1));

            if ((keypair.size() == fields.size()) || (!keypair.contains("cid") && (keypair.size() == fields.size() - 1)))
                ++validCount;
        }

        return validCount;
    }
}

namespace Part2 {
    struct Passport {
        uint16_t byr, iyr, eyr;
        std::string hgt, hcl, ecl, pid;

        [[nodiscard]] bool Validate() const noexcept {
            if (byr < 1920 || byr > 2002)
                return false;

            if (iyr < 2010 || iyr > 2020)
                return false;

            if (eyr < 2020 || eyr > 2030)
                return false;

            if (size_t const pos = hgt.find("cm"); pos != std::string::npos) {
                int16_t value{};
                std::from_chars(hgt.data(), hgt.data() + pos, value);

                if (value < 150 || value > 193)
                    return false;
            }
            else if (size_t const pos = hgt.find("in"); pos != std::string::npos) {
                int16_t value{};
                std::from_chars(hgt.data(), hgt.data() + pos, value);

                if (value < 59 || value > 76)
                    return false;
            }
            else
                return false;

            if (!std::regex_match(hcl, std::regex{ "#[0-9a-f]{6}" }))
                return false;

            if (!std::regex_match(ecl, std::regex{ "amb|blu|brn|gry|grn|hzl|oth" }))
                return false;

            if (pid.size() != 9)
                return false;

            return true;
        }
    };

    uint16_t Solution(std::string_view filename) {
        constexpr std::array fields {
            "byr"sv, "iyr"sv,
            "eyr"sv, "hgt"sv,
            "hcl"sv, "ecl"sv,
            "pid"sv, "cid"sv
        };

        std::vector<std::string> data = Read(filename);
        uint16_t validCount{};

        for (std::string_view passport : data) {
            std::stringstream stream{passport.data()};
            std::unordered_map<std::string, std::string> keypair{};

            for (std::string pair{}; std::getline(stream, pair, ' ');)
                keypair.emplace(pair.substr(0, pair.find(':')), pair.substr(pair.find(':') + 1));

            try {
                Passport p {
                    .byr = static_cast<uint16_t>(std::stoi(keypair.at("byr"))),
                    .iyr = static_cast<uint16_t>(std::stoi(keypair.at("iyr"))),
                    .eyr = static_cast<uint16_t>(std::stoi(keypair.at("eyr"))),
                    .hgt = keypair.at("hgt"),
                    .hcl = keypair.at("hcl"),
                    .ecl = keypair.at("ecl"),
                    .pid = keypair.at("pid")
                };

                if (p.Validate())
                    ++validCount;
            }
            catch (std::exception&) {}
        }

        return validCount;
    }
}

int main() {
    std::cout << "Part 1 answer: " << Part1::Solution("input.txt"sv) << "\n";
    std::cout << "Part 2 answer: " << Part2::Solution("input.txt"sv) << "\n";
}