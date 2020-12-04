uint16_t Solution(uint16_t rightCount, uint16_t downCount) {
    std::ifstream reader{ "input.txt" };
    if (reader) {
        // Reading the file data into a vector of strings
        std::vector<std::string> data{};
        for(std::string line{}; std::getline(reader, line);)
            data.emplace_back(line);

        // Calculation ..
        uint16_t right{}, count{};
        for (size_t i = 0; i < data.size(); i += downCount) {
            if (data[i][right] == '#')
                ++count;

            right = (right + rightCount) % data[0].size();
        }

        return count;
    }
    
    // Idk somehow the file wasn't openable
    throw std::runtime_error("Not valid!");
}

int main() {
    // Part 1
    AdventOfCode(3, 1);

    // Part 2
    using coord_t = std::vector<std::pair<uint16_t, uint16_t>>;
    
    uint32_t count = 1;
    for (auto[x, y] : coord_t{{ 1, 1 }, { 3, 1 }, { 5, 1 }, { 7, 1 }, { 1, 2 }})
        count *= AdventOfCode(x, y);
}