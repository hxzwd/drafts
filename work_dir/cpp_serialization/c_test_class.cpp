
#include <c_test_class.hpp>



void c_test_class_2::print_info()
{
    std::cout << "test_uint = " << test_uint << std::endl;
    std::cout << "some_var = " << some_var << std::endl;
    std::cout << "some_int8 = " << some_int8 << std::endl;
    std::cout << "some_double = " << some_double << std::endl;

    std::cout << "some_arr = ";
    for(uint64_t i : some_arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}


void c_test_class::print_info()
{

    std::cout << "test_uint = " << test_uint << std::endl;
    std::cout << "some_var = " << some_var << std::endl;
    std::cout << "some_int8 = " << some_int8 << std::endl;
    std::cout << "some_double = " << some_double << std::endl;

    std::cout << "some_arr = ";
    for(uint64_t i : some_arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "some_arr_2 = ";
    for(uint32_t i : some_arr_2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "some_struct.x = " << some_struct.x << std::endl;
    std::cout << "some_struct.name = " << some_struct.name << std::endl;

    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "some_class = " << std::endl;
    some_class.print_info();
    std::cout << "----------------------------------------------" << std::endl;

    std::cout << "some_string.m_string = " << some_string.m_string << std::endl;
    std::cout << "some_std_string = " << some_std_string << std::endl;

    std::cout << "some_vec = ";
    for(double elem : some_vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

}
