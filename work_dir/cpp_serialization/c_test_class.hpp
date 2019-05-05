

#ifndef C_TEST_CLASS_HPP
#define C_TEST_CLASS_HPP


#include <c_serializable.hpp>
#include <c_string_wrap.hpp>

class c_test_class_2 : public c_serializable
{

public:

    uint32_t test_uint = 1338;
    uint32_t some_var = 229;
    int8_t some_int8 = 'B';
    double some_double;
    uint64_t some_arr[8] = { 1, 2, 3, 4, 5, 6, 7, (uint64_t)(-1) };

public:

    void print_info(void);

    SERIALIZE(test_uint, uint32_t);
    SERIALIZE(some_var, uint32_t);
    SERIALIZE_GENERIC(some_int8);
    SERIALIZE_GENERIC(some_double);
    SERIALIZE_P(some_arr, array);

};


class c_test_class : public c_serializable
{

public:

    struct some_struct_type
    {
        uint32_t x;
        char name = 'F';
    } __attribute__((packed));

public:

    uint32_t test_uint = 1337;
    uint32_t some_var = 228;
    int8_t some_int8 = 'A';
    double some_double;
    uint64_t some_arr[8] = { 1, 2, 3, 4, 5, 6, 7, (uint64_t)(-1) };
    uint32_t some_arr_2[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    struct some_struct_type some_struct;
    c_test_class_2 some_class;
    c_string_wrap some_string;
    std::string some_std_string;
    std::vector<double> some_vec;

public:

    void print_info(void);

    SERIALIZE(test_uint, uint32_t);
    SERIALIZE(some_var, uint32_t);
    SERIALIZE_GENERIC(some_int8);
    SERIALIZE_GENERIC(some_double);
    SERIALIZE_P(some_arr, array);
    SERIALIZE_P(some_arr_2, array);
    SERIALIZE_P(some_struct, struct);
    SERIALIZE_P(some_class, serializable);
    SERIALIZE_P(some_string, serializable);
    SERIALIZE_P(some_std_string, string);
    SERIALIZE_P(some_vec, vector);
};


#endif // C_TEST_CLASS_HPP
