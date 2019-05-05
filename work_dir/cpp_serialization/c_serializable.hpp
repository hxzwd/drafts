

#ifndef C_SERIALIZABLE_HPP
#define C_SERIALIZABLE_HPP



#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <functional>

#define BINARY_BUFFER_SIZE  1048576
#define BINARY_BUFFER_SIZE  8192

#define NEW_VARIABLE_NAME_1(X) NEW_MACRO_VALUE_##X
#define NEW_VARIABLE_NAME_0(X) NEW_VARIABLE_NAME_1(X)
#define NEW_VARIABLE_NAME NEW_VARIABLE_NAME_0(__LINE__)

#define SERIALIZE(N, T) uint32_t NEW_VARIABLE_NAME = add        \
(                                                               \
    [this]( uint32_t * offset )                                 \
    {                                                           \
        serialize_##T##_func(offset, this->N);                  \
    },                                                          \
    [this]( uint32_t * offset )                                 \
    {                                                           \
        this->N = deserialize_##T##_func(offset);               \
    }                                                           \
)

#define SERIALIZE_P(N, T) uint32_t NEW_VARIABLE_NAME = add      \
(                                                               \
    [this]( uint32_t * offset )                                 \
    {                                                           \
        serialize_##T##_func(offset, this->N,                   \
                                sizeof(this->N));               \
    },                                                          \
    [this]( uint32_t * offset )                                 \
    {                                                           \
        deserialize_##T##_func(offset, &(this->N),              \
                                sizeof(this->N));               \
    }                                                           \
)


#define SERIALIZE_GENERIC(N) uint32_t NEW_VARIABLE_NAME = add   \
(                                                               \
    [this]( uint32_t * offset )                                 \
    {                                                           \
        serialize_generic_func(offset, this->N);                \
    },                                                          \
    [this]( uint32_t * offset )                                 \
    {                                                           \
        auto auto_v = deserialize_generic_func(                 \
                    offset, &(this->N));                        \
        this->N = auto_v;                                       \
    }                                                           \
)

class c_serializable_interface
{

public:

    uint32_t m_offset;
    uint8_t m_binary_buffer[BINARY_BUFFER_SIZE];

public:

    virtual void serialize() = 0;
    virtual void deserialize() = 0;

    void set_buffer(uint8_t * new_buffer, uint32_t new_buffer_size);

};

class c_serializable : public c_serializable_interface
{

public:

    typedef std::function<void(uint32_t *)> ser_func_t;

    struct serializer_pair
    {
        ser_func_t serializer;
        ser_func_t deserializer;
    };


    std::vector<struct serializer_pair> m_serializers;

public:

    void show_buffer(void);
    std::string to_hex_str(void);
    void from_hex_str(std::string hex_str);
    uint32_t add(ser_func_t _serializer, ser_func_t _deserializer);

    virtual void serialize(void);
    virtual void deserialize(void);

public:


    void serialize_uint32_t_func(uint32_t * offset, uint32_t value)
    {
        std::memcpy(&(m_binary_buffer[*offset]), &value, sizeof(uint32_t));
        *offset = *offset + sizeof(uint32_t);
    }

    uint32_t deserialize_uint32_t_func(uint32_t * offset)
    {
        uint32_t value;
        std::memcpy(&value, &(m_binary_buffer[*offset]), sizeof(uint32_t));
        *offset = *offset + sizeof(uint32_t);
        return value;
    }

    void serialize_string_func(uint32_t * offset, std::string value, uint32_t size_)
    {
        uint32_t data_size;
        data_size = value.length();
        std::memcpy(&(m_binary_buffer[*offset]), &data_size, sizeof(uint32_t));
        *offset = *offset + sizeof(uint32_t);
        std::memcpy(&(m_binary_buffer[*offset]), value.data(), data_size);
        *offset = *offset + data_size;
    }

    void deserialize_string_func(uint32_t * offset, std::string * value, uint32_t size_)
    {
        uint32_t data_size;
        std::memcpy(&data_size, &(m_binary_buffer[*offset]), sizeof(uint32_t));
        *offset = *offset + sizeof(uint32_t);
        char tmp_buffer[1024] = { 0 };
        std::memcpy(tmp_buffer, &(m_binary_buffer[*offset]), data_size);
        *offset = *offset + data_size;
        value->assign(std::string(tmp_buffer));
    }

    template <typename T> void serialize_generic_func(uint32_t * offset, T value)
    {
        std::memcpy(&(m_binary_buffer[*offset]), &value, sizeof(T));
        *offset = *offset + sizeof(T);
    }

    template <typename T> T deserialize_generic_func(uint32_t * offset, T * value_addr)
    {
        T value;
        std::memcpy(&value, &(m_binary_buffer[*offset]), sizeof(T));
        *offset = *offset + sizeof(T);
        return value;
    }

    template <typename T> void serialize_array_func(uint32_t * offset, T value, uint32_t size_)
    {
        uint32_t size;
        uint32_t elem_len;
        size = size_;
        elem_len = sizeof(value[0]);
        elem_len = 1;
        std::memcpy(&(m_binary_buffer[*offset]), (void *)&(value[0]), size * elem_len);
        *offset = *offset + size * elem_len;
    }

    template <typename T> void deserialize_array_func(uint32_t * offset, T * value, uint32_t size_)
    {
        uint32_t size;
        uint32_t elem_len;
        size = size_;
        elem_len = sizeof((*value)[0]);
        elem_len = 1;
        std::memcpy(value, &(m_binary_buffer[*offset]), size * elem_len);
        *offset = *offset + size * elem_len;
    }

    template <typename T> void serialize_struct_func(uint32_t * offset, T value, uint32_t size_)
    {
        uint32_t size;
        size = size_;
        std::memcpy(&(m_binary_buffer[*offset]), &value, size);
        *offset = *offset + size;
    }

    template <typename T> void deserialize_struct_func(uint32_t * offset, T * value, uint32_t size_)
    {
        uint32_t size;
        size = size_;
        std::memcpy(value, &(m_binary_buffer[*offset]), size);
        *offset = *offset + size;
    }

    template <typename T> void serialize_serializable_func(uint32_t * offset, T & value, uint32_t size_)
    {
        value.serialize();
        uint32_t data_size = value.m_offset;
        uint8_t * data_ptr = value.m_binary_buffer;
        std::memcpy(&(m_binary_buffer[*offset]), &data_size, sizeof(uint32_t));
        *offset = *offset + sizeof(uint32_t);
        std::memcpy(&(m_binary_buffer[*offset]), data_ptr, data_size);
        *offset = *offset + data_size;
    }

    template <typename T> void deserialize_serializable_func(uint32_t * offset, T * value, uint32_t size_)
    {
        uint32_t size;
        std::memcpy(&size, &(m_binary_buffer[*offset]), sizeof(uint32_t));
        *offset = *offset + sizeof(uint32_t);
        value->set_buffer(&(m_binary_buffer[*offset]), size);
        *offset = *offset + size;
        value->deserialize();
    }

    template <typename T> void serialize_vector_func(uint32_t * offset, std::vector<T> value, uint32_t size_)
    {
        uint32_t data_size;
        data_size = value.size();
        std::memcpy(&(m_binary_buffer[*offset]), &data_size, sizeof(uint32_t));
        *offset = *offset + sizeof(uint32_t);
        for(T elem : value)
        {
            std::memcpy(&(m_binary_buffer[*offset]), &elem, sizeof(T));
            *offset = *offset + sizeof(T);
        }

    }

    template <typename T> void deserialize_vector_func(uint32_t * offset, std::vector<T> * value, uint32_t size_)
    {
        uint32_t data_size;
        std::memcpy(&data_size, &(m_binary_buffer[*offset]), sizeof(uint32_t));
        *offset = *offset + sizeof(uint32_t);
        for(uint32_t i = 0; i < data_size; i++)
        {
            T tmp_var;
            std::memcpy(&tmp_var, &(m_binary_buffer[*offset]), sizeof(T));
            *offset = *offset + sizeof(T);
            value->push_back(tmp_var);
        }
    }


};

#endif // C_SERIALIZABLE_HPP
