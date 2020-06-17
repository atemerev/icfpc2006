#include "UM.h"
#include <iostream>
#include <algorithm>

UM::UM(std::vector<uint32_t> &program) {
    arrays.clear();
    arrays.push_back(&program);
    this->ip = 0;
    for (unsigned int &i : this->registers) {
        i = 0;
    }
}

UM::~UM() {
    for (std::vector<uint32_t> *array : this->arrays) {
        delete array;
    }
}

void UM::run() {
    while (this->ip < arrays.at(0)->size()) {
        do_cycle();
    }
}

void UM::do_cycle() {
    std::vector<uint32_t> *program = arrays[0];
    uint32_t plate = program->at(ip);
    uint8_t opcode = plate >> 28 & 15u;
    uint8_t reg_a = plate >> 6 & 7u;
    uint8_t reg_b = plate >> 3 & 7u;
    uint8_t reg_c = plate & 7u;
    ip++;
    switch (opcode) {
        case 0:
            op_cond_move(reg_a, reg_b, reg_c);
            break;
        case 1:
            op_array_index(reg_a, reg_b, reg_c);
            break;
        case 2:
            op_array_amend(reg_a, reg_b, reg_c);
            break;
        case 3:
            op_add(reg_a, reg_b, reg_c);
            break;
        case 4:
            op_mul(reg_a, reg_b, reg_c);
            break;
        case 5:
            op_div(reg_a, reg_b, reg_c);
            break;
        case 6:
            op_nand(reg_a, reg_b, reg_c);
            break;
        case 7:
            op_halt();
            break;
        case 8:
            op_allocate(reg_b, reg_c);
            break;
        case 9:
            op_abandon(reg_c);
            break;
        case 10:
            op_out(reg_c);
            break;
        case 11:
            op_in(reg_c);
            break;
        case 12:
            op_load(reg_b, reg_c);
            break;
        case 13:
            op_orth(plate);
            break;
        default:
            die();
    }
}

void UM::op_allocate(uint8_t reg_b, uint8_t reg_c) {
    uint32_t size = registers[reg_c];
    auto *new_array = new std::vector<uint32_t>(size);
    uint32_t index;
    if (!this->free_list.empty()) {
        index = free_list.front();
        free_list.pop_front();
        arrays[index] = new_array;
    } else {
        arrays.push_back(new_array);
        index = arrays.size() - 1;
    }
    registers[reg_b] = index;
}

void UM::op_abandon(uint8_t reg_c) {
    uint32_t index = registers[reg_c];
    if (index != 0) {
        if (index >= arrays.size()) {
            die();
        }
        delete arrays.at(index);
        free_list.push_back(index);
    } else {
        die();
    }
}

void UM::op_load(uint8_t reg_b, uint8_t reg_c) {
    uint32_t index = registers[reg_b];
    if (index == 0) {
        this->ip = registers[reg_c];
    } else {
        std::vector<uint32_t> *src = arrays[index];
        auto copy = new std::vector<uint32_t>(*src);
        delete arrays[0];
        arrays[0] = copy;
        this->ip = registers[reg_c];
    }
}

void UM::die() {
    std::cerr << "WHOOPS!!" << std::endl;
    exit(255);
}

void UM::op_cond_move(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c) {
    if (registers[reg_c] != 0) {
        registers[reg_a] = registers[reg_b];
    }
}

void UM::op_array_index(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c) {
    uint32_t idx = registers[reg_b];
    uint32_t offset = registers[reg_c];
    if (idx >= arrays.size()) {
        die();
    }
    auto arr = arrays.at(idx);
    if (offset >= arr->size()) {
        die();
    }
    registers[reg_a] = arr->at(offset);
}

void UM::op_array_amend(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c) {
    uint32_t idx = registers[reg_a];
    uint32_t offset = registers[reg_b];
    if (idx >= arrays.size()) {
        die();
    }
    auto arr = arrays.at(idx);
    if (offset >= arr->size()) {
        die();
    }
    arr->at(offset) = registers[reg_c];
}

void UM::op_add(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c) {
    registers[reg_a] = registers[reg_b] + registers[reg_c];
}

void UM::op_mul(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c) {
    registers[reg_a] = registers[reg_b] * registers[reg_c];
}

void UM::op_div(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c) {
    registers[reg_a] = registers[reg_b] / registers[reg_c];
}

void UM::op_nand(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c) {
    registers[reg_a] = ~(registers[reg_b] & registers[reg_c]);
}

void UM::op_halt() {
    std::exit(0);
}

void UM::op_in(uint8_t reg_c) {
    registers[reg_c] = std::getchar();
}

void UM::op_out(uint8_t reg_c) {
    std::putchar(static_cast<char>(registers[reg_c]));
}

void UM::op_orth(uint32_t value) {
    uint8_t reg_a = value >> 25 & 7;
    registers[reg_a] = value & 0x1ffffff;
}
