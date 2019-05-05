
#include <cstdlib>
#include <cstdio>
#include <cstdint>


#include <iostream>
#include <string>

#include <c_test_class.hpp>

void func_test_1(std::string hex_str)
{
    c_test_class obj;

    obj.from_hex_str(hex_str);
    obj.show_buffer();
    obj.print_info();

}

int32_t main(void)
{
    std::cout << "[main.cpp]: cpp_serialization project" << std::endl;

    c_test_class obj;
    c_test_class obj_2;


    obj.test_uint = 5;
    obj.some_var = 13;
    obj.some_double = 3.14159265358979323846;
    obj.some_class.test_uint = 1;
    obj.some_class.some_var = 12;
    obj.some_class.some_arr[0] = (uint64_t)(-1);
    obj.some_class.some_double = 5.0f;
    obj.some_struct.x = 1337;
    obj.some_string.m_string = "HELLO!!!";
    obj.some_std_string = "HELLO FROM STD STRING!!!";
    obj.some_vec = { 3.0f, 5.0f, 8.0f };
    obj.serialize();

    obj.show_buffer();

    obj.print_info();
    std::cout << "########################################################" << std::endl;

    obj_2.set_buffer(obj.m_binary_buffer, obj.m_offset);
    obj_2.deserialize();

    obj_2.print_info();

    std::cout << "########################################################" << std::endl;
    std::cout << obj_2.to_hex_str() << std::endl;
    std::cout << "########################################################" << std::endl;

    std::string hex_str;
    hex_str = obj_2.to_hex_str();
    func_test_1(hex_str);


    std::cout << "########################################################" << std::endl;

    return 0;
}

