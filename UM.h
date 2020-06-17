#ifndef BOUNDVAR_UM_H
#define BOUNDVAR_UM_H

#include <vector>
#include <list>

class UM {
public:
    uint32_t ip = 0;
    uint32_t registers[8] = {};
    std::vector<std::vector<uint32_t>*> arrays;
    std::list<uint32_t> free_list;
    explicit UM(std::vector<uint32_t> &program);
    ~UM();
    void run();
    void do_cycle();
    void op_cond_move(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c);
    void op_array_index(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c);
    void op_array_amend(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c);
    void op_add(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c);
    void op_mul(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c);
    void op_div(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c);
    void op_nand(uint8_t reg_a, uint8_t reg_b, uint8_t reg_c);
    static void op_halt();
    void op_allocate(uint8_t reg_b, uint8_t reg_c);
    void op_abandon(uint8_t reg_c);
    void op_in(uint8_t reg_c);
    void op_out(uint8_t reg_c);
    void op_load(uint8_t reg_b, uint8_t reg_c);
    void op_orth(uint32_t value);
    static void die();
};


#endif //BOUNDVAR_UM_H
