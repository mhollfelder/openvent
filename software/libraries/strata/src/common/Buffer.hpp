/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <cstddef>


namespace stdext
{
    template <typename T>
    inline std::size_t size_aligned(std::size_t size)
    {
        return (size + sizeof(T) - 1) / sizeof(T);
    }

    template <typename T>
    inline T *new_aligned(std::size_t size)
    {
        return new T[size_aligned<T>(size)];
    }

    template <typename T>
    class buffer
    {
        using size_type = std::size_t;
        using iterator = T*;
        using const_iterator = T const*;

    public:
        buffer(const buffer &) = delete;
        buffer &operator= (const buffer &) = delete;

        buffer() :
            m_size {0},
            m_data {nullptr}
        {}

        buffer(size_type size) :
            m_size {size},
            m_data {new T[size]}
        {}

        ~buffer()
        {
            if (m_data)
            {
                delete[] m_data;
            }
        }

        void resize(size_type size)
        {
            if (m_data)
            {
                delete[] m_data;
            }
            m_size = size;
            if (m_size)
            {
                m_data = new T[m_size];
            }
            else
            {
                m_data = nullptr;
            }
        }

        inline size_type size() const
        {
            return m_size;
        }

        inline size_type sizeOf() const
        {
            return m_size * sizeof(T);
        }

        inline T *data()
        {
            return m_data;
        }

        inline T &operator[](size_type x)
        {
            return m_data[x];
        }

        iterator begin()
        {
            return m_data;
        }

        iterator end()
        {
            return m_data + m_size;
        }

        const_iterator begin() const
        {
            return m_data;
        }

        const_iterator end() const
        {
            return m_data + m_size;
        }

    private:
        size_type m_size;
        T *m_data;
    };

    template <typename T>
    class buffer_aligned :
        public buffer<T>
    {
    public:
        buffer_aligned(std::size_t size) :
            buffer<T>(size_aligned<T>(size))
        {}
    };

}
