
#include <c_string_wrap.hpp>

c_string_wrap::c_string_wrap()
{

}

c_string_wrap::c_string_wrap(std::string str)
{
    m_string = std::string(str);
}

c_string_wrap::c_string_wrap(uint8_t * buffer, uint32_t buffer_len)
{
    m_string = std::string((char *)(buffer), buffer_len);
}

c_string_wrap::c_string_wrap(const char * str)
{
    m_string = std::string(str);
}

void c_string_wrap::serialize()
{
    std::cout << "DBG 1" << std::endl;
    m_offset = 0;
    uint32_t data_size;
    data_size = m_string.length();
    std::memcpy(m_binary_buffer, m_string.data(), data_size);
    m_offset = data_size;
}

void c_string_wrap::deserialize()
{
    uint32_t data_size;
    data_size = m_offset;
    m_offset = 0;
    m_string = std::string((char *)(m_binary_buffer), data_size);
}
