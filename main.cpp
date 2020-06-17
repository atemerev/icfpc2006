#include <iostream>
#include <fstream>
#include "UM.h"
#include <string>

std::vector<uint32_t>* load_file(const std::string& file_name) {
    std::ifstream input(file_name.c_str(), std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    auto program = new std::vector<uint32_t>();
    for (uint32_t i = 0; i < buffer.size() / 4; i++) {
        const uint8_t b0 = buffer[i*4+3], b1 = buffer[i*4+2], b2 = buffer[i*4+1], b3 = buffer[i*4];
        uint32_t v = (b0 << 0) | (b1 << 8) | (b2 << 16) | (b3 << 24);
        program->push_back(v);
    }
    return program;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./um vmdata.um" << std::endl;
        exit(127);
    }
    std::string file_name(argv[1]);
    std::vector<uint32_t>* program = load_file(file_name);
    UM um(*program);
    um.run();

    return 0;
}

