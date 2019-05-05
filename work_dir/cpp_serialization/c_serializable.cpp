
#include <c_serializable.hpp>

void c_serializable_interface::set_buffer(uint8_t * new_buffer, uint32_t new_buffer_size)
{
    std::memcpy(m_binary_buffer, new_buffer, sizeof(uint8_t) * new_buffer_size);
    m_offset = new_buffer_size;
}


void c_serializable::show_buffer(void)
{
    std::cout << "m_offset = " << m_offset << std::endl;
    for(uint32_t i = 0; i < m_offset; i++)
    {
        if(i != 0 && i % 16 == 0)
        {
            std::cout << std::endl;
        }
        std::printf("%02X ", m_binary_buffer[i]);
    }
    std::cout << std::endl;
}

std::string c_serializable::to_hex_str(void)
{
    std::string hex_str("");
    char digit_map[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    for(uint32_t i = 0; i < m_offset; i++)
    {
        uint8_t tmp_byte;
        char first_digit;
        char second_digit;

        tmp_byte = m_binary_buffer[i];
        first_digit = digit_map[ ( tmp_byte >> 4 ) & 0x0F ];
        second_digit = digit_map[ ( tmp_byte ) & 0x0F ];
        hex_str.push_back(first_digit);
        hex_str.push_back(second_digit);
    }
    return hex_str;
}

uint8_t get_hex_digit(char hex_digit)
{
    if(hex_digit >= '0' && hex_digit <= '9')
    {
        return uint8_t(hex_digit - '0');
    }
    else
    {
        return uint8_t(hex_digit - 'A' + 10);
    }
}

void c_serializable::from_hex_str(std::string hex_str)
{
    uint32_t i;
    uint32_t j;

    j = 0;

    for(i = 0; i < hex_str.length(); i += 2)
    {
        char first_digit;
        char second_digit;
        first_digit = hex_str[i];
        second_digit = hex_str[i + 1];
        m_binary_buffer[j++] = get_hex_digit(first_digit) * 0x10 + get_hex_digit(second_digit);
    }
    deserialize();
}

uint32_t c_serializable::add(ser_func_t _serializer, ser_func_t _deserializer)
{
    m_serializers.push_back({_serializer, _deserializer});
    return 0;
}

void c_serializable::serialize(void)
{
    m_offset = 0;
    for(struct serializer_pair ser_pair : m_serializers)
    {
        ser_pair.serializer(&m_offset);
    }

}

void c_serializable::deserialize(void)
{
    m_offset = 0;
    for(struct serializer_pair ser_pair : m_serializers)
    {
        ser_pair.deserializer(&m_offset);
    }
}



