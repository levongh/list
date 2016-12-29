#pragma once

#include <memory>
#include <limits>
#include <initializer_list>


#include "node.h"
#include "iterator.h"

namespace eda {

template <typename T, class Allocator = std::allocator<T> >
class list
{
public:
    using value_type = T;
    using pointer_type = T*;
    using reference_type = T&;
    using const_pointer_type = const T*;
    using const_reference_type = const T&;
    using allocator_type = Allocator;
    using size_type = unsigned int;

    using iterator = list_iterator<T>;
    using const_iterator = const_list_iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /// @brief constructors and destructor
    /// @{
public:
    explicit list(const Allocator& alloc = Allocator());
    explicit list(const size_type count,
                  const_reference_type value,
                  const Allocator& alloc = Allocator());
    explicit list(const size_type count);

    template <class InputIt>
    list(InputIt first, InputIt last, const Allocator& alloc = Allocator());

    list(list<T, Allocator>&& other);
    list(list<T, Allocator>&& other, const Allocator& alloc);

    list(std::initializer_list<T> ilist, const Allocator& alloc = Allocator());

    ~list();
    /// @}

    /// @brief member functions
    /// @{
public:
    void assign(size_type count, const_reference_type value);

    template<class InputIt>
    void assign(InputIt first, InputIt last);

    allocator_type get_allocator() const;
    /// @}

    /// @element access
    /// @{
public:
    reference_type front();
    const_reference_type front() const;

    reference_type back();
    const_reference_type back() const;
    /// @}
    
    /// @brief iterators
    /// @{    
public:
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;
    /// @}    

    /// @brief capacity
    /// @{
public:
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    /// @}

    /// @brief modificators
    /// @{
public:
    void clear() noexcept;
    iterator insert(const_iterator pos, const_reference_type& value);

    iterator insert(const_iterator pos, size_type count, const_reference_type value);

    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);

    iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args);

    iterator erase(iterator pos);
    iterator erase(const_iterator pos);

    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);

    void push_back(const_reference_type& value);

    template <class... Args>
    void emplace_back(Args&&... args);

    void pop_back();

    void push_front(const_reference_type& value);

    template <class... Args>
    void emplace_front(Args&&... args);

    void pop_front();

    void resize(size_type count);
    void resize(size_type count, const_reference_type value);
    /// @}

    /// @brief operations
    /// @{
public:
    void merge(list& other);
    void merge(list&& other);

    template <typename Compare>
    void merge(list& other, Compare cmop);

    template <typename Compare>
    void merge(list&& other, Compare cmop);

    //void splice(const_iterator pos, lsit&& other);

    //void splice(const_iterator pos, lsit&& other, const_iterator it);

    //void splice(const_iterator pos, lsit&& other, const_iterator first, const_iterator last);

    void remove(const_reference_type value);

    template <class UnaryPredicate>
    void remove_if(UnaryPredicate pred);

    //void reverse();

    void unique();

    template <class BinaryPredicate>
    void unique(BinaryPredicate pred);

    /*void sort();
    template <class Compare>
    void sort(Compare comp);*/
    /// @}
private:
    node<T>* m_nil;
    Allocator m_allocator;
};

#include "list_impl.h"

}
