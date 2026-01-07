#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <filesystem>
#include <expected>

namespace fs = std::filesystem;

auto read_file(const fs::path& path) -> std::expected<void, std::string> {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return std::unexpected("Failed to open file: " + path.string());
    }

    char buffer[4096];

    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        std::cout.write(buffer, file.gcount());
    }

    if (!file.eof()) {
        return std::unexpected("Error reading file: " + path.string());
    }

    return {};
}

auto write_file(const fs::path& path) -> std::expected<void, std::string> {
    std::ofstream file(path);
    if (!file) {
        return std::unexpected("Failed to open file: " + path.string());
    }

    std::cout << "Enter \":q\" on a new line to exit:" << std::endl;

    for (std::string text; std::getline(std::cin, text); ) {
        if (text == ":q") {
            break;
        }

        file << text << std::endl;

        if (!file) {
            return std::unexpected("Error writing to file: " + path.string());
        }
    }

    return {};
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Use:\n"
                  << "  " << argv[0] << " --read <file>\n"
                  << "  " << argv[0] << " --write <file>\n";
        return 1;
    }

    std::string_view command = argv[1];
    fs::path path = argv[2];

    if (command == "--read") {
        if (auto result = read_file(path); !result) {
            std::cerr << result.error() << std::endl;
            return 1;
        }
    } else if (command == "--write") {
        if (auto result = write_file(path); !result) {
            std::cerr << result.error() << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }
    
    return 0;
}