#pragma once

namespace eda {

template <typename T>
struct node
{
    using value_type = const T*;

    explicit node()
        : m_prev(this)
        , m_next(this)
        , m_value(value_type())
    {
    }

    explicit node(value_type value,
         node* prev = nullptr,
         node* next = nullptr)
        : m_prev(this)
        , m_next(this)
        , m_value(value)
    {}

    node(const node& n) = default;
    node& operator=(const node& n) = default;
    node(node&& n) = delete;
    node& operator=(node&& n) = delete;

    node* m_prev;
    node* m_next;
    value_type m_value;
};

} //namespace eda
