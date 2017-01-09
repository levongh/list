#pragma once

#include <cstddef>
#include <iterator>

template <typename I>
class const_list_iterator;

template <typename T, class Allocator>
class list;

template <typename T>
class node;

template <typename T>
class list_iterator
{
    /// @brief public typedefs
    /// @{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using self = list_iterator<T>;
    using pointer = T*;
    using reference = T;
    /// @}

    /// @brief constructors
    /// @{
public:
    /// @brief default constructor
    list_iterator()
        : m_node()
    {
    }

    /// @brief constructor with node argument
    explicit list_iterator(node<T>* n)
        : m_node(n)
    {
    }
    /// @}

    /// @brief operators
    /// @{ 
 public:
    reference operator*() const
    {
        return *m_node->m_value;
    }

    pointer operator->() const
    {
        return m_node->m_value;
    }

    /// @brief prefix operator ++
    self& operator++()
    {
        m_node = m_node->m_next;
        return *this;
    }

    /// @brief postfix operator ++
    self operator++(int)
    {
        self temp = *this;
        m_node = m_node->m_node;
        return temp;
    }

    /// @brief prefix operator --
    self& operator--()
    {
        m_node = m_node->m_prev;
        return *this;
    }

    /// @brief postfix operator --
    self operator--(int)
    {
        self temp = *this;
        m_node = m_node->m_prev;
        return temp;
    }

    bool operator==(const self& other)
    {
        return m_node == other.m_node;
    }

    bool operator!=(const self& other)
    {
        return m_node != other.m_node;
    }
    /// @}

private:
    template <typename Tp, class Allocator>
    friend class list;

    template <typename I>
    friend class const_list_iterator;
    node<T>* m_node;

};

template <typename T>
class const_list_iterator
{
    /// @brief public typedefs
    /// @{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using self = const_list_iterator<T>;
    using pointer = const T*;
    using reference = const T&;
    /// @}

    /// @brief constructos
    /// @{
private:
    const_list_iterator()
        : m_node()
    {
    }

    explicit const_list_iterator(const node<T>* n)
        : m_node(const_cast<node<T>*>(n))
    {
    }

    const_list_iterator(const list_iterator<T> iter)
        : m_node(iter.m_node)
    {
    }
    /// @}

    /// @brief operators
    /// @{
public:
    reference& operator*() const
    {
        return m_node->m_value;
    }

    pointer operator->() const
    {
        return *m_node.m_value;
    }

    /// @brief prefix operator ++
    self& operator++()
    {
        m_node = m_node->m_next;
        return *this;
    }

    /// @brief postfix operator ++
    self operator++(int)
    {
        self temp = *this;
        m_node = m_node->m_node;
        return temp;
    }

    /// @brief prefix operator --
    self& operator--()
    {
        m_node = m_node->m_prev;
        return *this;
    }

    /// @brief postfix operator --
    self operator--(int)
    {
        self temp = *this;
        m_node = m_node->m_prev;
        return temp;
    }

    bool operator==(const self& other)
    {
        return m_node == other.m_node;
    }

    bool operator!=(const self& other)
    {
        return m_node != other.m_node;
    }
    /// @}

private:
    template <typename Tp, class Allocator>
    friend class list;

    node<T>* m_node;
};
