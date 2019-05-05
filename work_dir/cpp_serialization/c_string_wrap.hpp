

#ifndef C_STRING_WRAP_HPP
#define C_STRING_WRAP_HPP

#include <c_serializable.hpp>

class c_string_wrap : public c_serializable_interface
{

public:

    std::string m_string;

public:

    c_string_wrap();
    c_string_wrap(std::string str);
    c_string_wrap(uint8_t * buffer, uint32_t buffer_len);
    c_string_wrap(const char * str);

public:

    void serialize();
    void deserialize();

};


#endif // C_STRING_WRAP_HPP
