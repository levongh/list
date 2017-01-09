#pragma once

template <typename T>
struct node
{
    using value_type = T*;

    explicit node()
        : m_prev(this)
        , m_next(this)
        , m_value(value_type())
    {
    }

    template <typename... Args>
    node(Args... args)
        : m_prev(this)
        , m_next(this)
        , m_value(std::forward<Args>(args)...)
    {
    }

    node(const node& n) = default;
    node& operator=(const node& n) = default;
    node(node&& n) = delete;
    node& operator=(node&& n) = delete;

    node* m_prev;
    node* m_next;
    value_type m_value;
};
