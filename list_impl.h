#pragma once

template <typename T, class Allocator>
list<T, Allocator>::list(const Allocator& alloc)
    : m_nil(new node<T>(nullptr))
    , m_allocator(alloc)
{
}

template <typename T, class Allocator>
list<T, Allocator>::list(size_type count,
                        const_reference_type value,
                        const Allocator& alloc)
    : m_nil(new node<T>(nullptr))
    , m_allocator(alloc)
{
    for (size_type i = 0; i < count; ++i) {
        push_back(value);
    }
}

template <typename T, class Allocator>
template <class InputIt>
list<T, Allocator>::list(InputIt first, InputIt last, const Allocator& alloc)
    : m_nil(new node<T>(nullptr))
    , m_allocator(alloc)
{
    for (const auto& iter = first; iter != last; ++iter) {
        push_back(iter);
    }
}

template <typename T, class Allocator>
list<T, Allocator>::list(list&& other)
    : m_nil(other.m_nil)
    , m_allocator(other.m_allocator)
{
    other.m_nil->m_prev = nullptr;
    other.m_nil->m_next = nullptr;
}

template <typename T, class Allocator>
list<T, Allocator>::list(list<T, Allocator>&& other, const Allocator& alloc)
    : m_nil(other.m_nil)
    , m_allocator(alloc)
{
    other->m_nil->m_prev = nullptr;
    other->m_nil->m_next = nullptr;
}

template <typename T, class Allocator>
list<T, Allocator>::list(std::initializer_list<T> ilist, const Allocator& alloc)
    : m_nil(new node<T>(nullptr))
    , m_allocator(alloc)
{
    for (auto val : ilist) {
        push_back(val);
    }
}

template <typename T, class Allocator>
list<T, Allocator>::~list()
{
    clear();
}

template <typename T, class Allocator>
auto list<T, Allocator>::assign(size_type n, const_reference_type value) -> void
{
    clear();
    for (auto i = 0; i < n; ++i) {
        push_back(value);
    }
}

template <typename T, class Allocator>
template <class InputIt>
auto list<T, Allocator>::assign(InputIt first, InputIt last) -> void
{
    clear();
    for (auto it = first; it != last; ++it) {
        push_back(*it);
    }
}

template <typename T, class Allocator>
auto list<T, Allocator>::front() -> reference_type
{
    return *(m_nil->m_next->m_value);
}

template <typename T, class Allocator>
auto list<T, Allocator>::front() const -> const_reference_type
{
    return *(m_nil->m_next->m_value);
}

template <typename T, class Allocator>
auto list<T, Allocator>::back() -> reference_type
{
    return *(m_nil->m_prev->m_value);
}

template <typename T, class Allocator>
auto list<T, Allocator>::back() const -> const_reference_type
{
    return *(m_nil->m_prev->m_value);
}

template <typename T, class Allocator>
auto list<T, Allocator>::begin() noexcept -> iterator
{
    return iterator{m_nil->m_next};
}

template <typename T, class Allocator>
auto list<T, Allocator>::begin() const noexcept -> const_iterator
{
    return const_iterator{m_nil->m_next};
}

template <typename T, class Allocator>
auto list<T, Allocator>::cbegin() const noexcept -> const_iterator
{
    return begin();
}

template <typename T, class Allocator>
auto list<T, Allocator>::end() noexcept -> iterator
{
    return iterator{m_nil};
}

template <typename T, class Allocator>
auto list<T, Allocator>::end() const noexcept -> const_iterator
{
    return const_iterator{m_nil};
}

template <typename T, class Allocator>
auto list<T, Allocator>::cend() const noexcept -> const_iterator
{
    return end();
}

template <typename T, class Allocator>
auto list<T, Allocator>::rbegin() noexcept -> reverse_iterator
{
    return iterator{m_nil->m_prev};
}

template <typename T, class Allocator>
auto list<T, Allocator>::rbegin() const noexcept -> const_reverse_iterator
{
    return const_iterator{m_nil->m_prev};
}

template <typename T, class Allocator>
auto list<T, Allocator>::crbegin() const noexcept -> const_reverse_iterator
{
    return rbegin();
}

template <typename T, class Allocator>
auto list<T, Allocator>::rend() noexcept -> reverse_iterator
{
    return end();
}

template <typename T, class Allocator>
auto list<T, Allocator>::rend() const noexcept -> const_reverse_iterator
{
    return end();
}

template <typename T, class Allocator>
auto list<T, Allocator>::crend() const noexcept -> const_reverse_iterator
{
    return cend();
}

template <typename T, class Allocator>
auto list<T, Allocator>::get_allocator() const -> allocator_type
{
    return m_allocator;
}

template <typename T, class Allocator>
auto list<T, Allocator>::empty() const noexcept -> bool
{
    return m_nil->m_next == m_nil;
}

template <typename T, class Allocator>
auto list<T, Allocator>::size() const noexcept -> size_type
{
    auto first = begin();
    auto second = end();
    typename const_iterator::difference_type diff = 0;
    while (first != second) {
        ++first;
        ++diff;
    }
    return diff;
}

template <typename T, class Allocator>
auto list<T, Allocator>::max_size() const noexcept -> size_type
{
    return std::numeric_limits<size_type>::max();
}
//TODO
template <typename T, class Allocator>
auto list<T, Allocator>::clear() noexcept -> void
{
    auto it = begin();
    while (it != end()) {
        //m_allocator.deallocate(it.m_node, 1);
        ++it;
    }
}

template <typename T, class Allocator>
auto list<T, Allocator>::insert(const_iterator pos, const_reference_type& value) -> iterator
{
    auto ret_val = m_allocator.allocate(1);
    m_allocator.construct(ret_val, value);
    auto new_node = new node<T>(ret_val);
    auto current_node = pos.m_node;
    new_node->m_next = current_node;
    new_node->m_prev = current_node->m_prev;
    current_node->m_prev->m_next = new_node;
    current_node->m_prev = new_node;
    return iterator {new_node};
}

template <typename T, class Allocator>
auto list<T, Allocator>::insert(const_iterator pos, size_type count, const_reference_type value) ->iterator
{
    for (size_type i = 0; i < count; ++i) {
        pos = insert(pos, value);
    }
    return pos;
}

template <typename T, class Allocator>
template <class InputIt>
auto list<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) -> iterator
{
    for (const auto iter = first; iter != last; ++last) {
        pos = insert(pos, *iter);
    }
    return pos;
}

template <typename T, class Allocator>
auto list<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> ilist) -> iterator
{
    for (const auto& val : ilist) {
        pos = insert(pos, val);
    }
    return pos;
}

template <typename T, class Allocator>
template <class... Args>
auto list<T, Allocator>::emplace(const_iterator pos, Args&&... args) -> iterator
{
    auto new_node = m_allocator.allocate(std::forward<Args>(args) ...);
    auto iter = insert(pos, new_node);
    return iter;
}

template <typename T, class Allocator>
auto list<T, Allocator>::erase(iterator pos) -> iterator
{
    auto to_del = pos.m_node;
    to_del->m_next->m_prev = to_del->m_prev;
    to_del->m_prev->m_next = to_del->m_next;
    auto to_return = to_del->m_next;
    //TODO
    return iterator{to_return};
}

template <typename T, class Allocator>
auto list<T, Allocator>::erase(const_iterator pos) -> iterator
{
    auto to_del = pos.m_node;
    to_del->m_next->m_prev = to_del->m_prev;
    to_del->m_prev->m_next = to_del->m_next;
    auto to_return = to_del->m_next;
    //TODO
    return const_iterator{to_return};
}

template <typename T, class Allocator>
auto list<T, Allocator>::erase(iterator first, iterator last) -> iterator
{
    iterator pos;
    for (auto iter = first; iter != last; ++iter) {
        erase(iter);
    }
    return pos;
}

template <typename T, class Allocator>
auto list<T, Allocator>::erase(const_iterator first, const_iterator last) -> iterator
{
    iterator pos;
    for (auto iter = first; iter != last; ++iter) {
        pos = erase(iter);
    }
    return pos;
}

template <typename T, class Allocator>
auto list<T, Allocator>::push_back(const_reference_type& value) -> void
{
    insert(end(), std::move(value));
}

template <typename T, class Allocator>
template <class... Args>
auto list<T, Allocator>::emplace_back(Args&&... args) -> void
{
    insert(end(), std::forward<Args>(args) ...);
}

template <typename T, class Allocator>
auto list<T, Allocator>::pop_back() -> void
{
    erase(end());
}


template <typename T, class Allocator>
auto list<T, Allocator>::push_front(const_reference_type& value) -> void
{
    insert(begin(), std::move(value));
}

template <typename T, class Allocator>
template <class... Args>
auto list<T, Allocator>::emplace_front(Args&&... args) -> void
{
    insert(begin(), std::forward<Args>(args) ...);
}

template <typename T, class Allocator>
auto list<T, Allocator>::pop_front() -> void
{
    erase(begin());
}
//TODO
template <typename T, class Allocator>
auto list<T, Allocator>::resize(size_type count) -> void
{
    clear();
}

template <typename T, class Allocator>
auto list<T, Allocator>::resize(size_type count, const_reference_type value) -> void
{
    clear();
    for (size_type i = 0; i < count; ++i) {
        push_back(value);
    }
}


template <typename T, class Allocator>
auto list<T, Allocator>::remove(const_reference_type value) -> void
{
    iterator first = begin();
    iterator last = end();

    while (first != last) {
        iterator curr = first;
        ++first;
        if (*curr == value) {
            erase(curr);
        }
    }
}

template <typename T, class Allocator>
template <class UnaryPredicate>
auto list<T, Allocator>::remove_if(UnaryPredicate pred) -> void
{
    iterator first = begin();
    iterator last = end();

    while (first != last) {
        iterator curr = first;
        ++first;
        if (pred(*curr)) {
            erase(curr);
        }
    }
}

template <typename T, class Allocator>
auto list<T, Allocator>::unique() -> void
{
    if (empty()) {
        return;
    }

    iterator current = begin();
    ++current;

    while (current != end()) {
        if (*current == *(--current)) {
            current = erase(++current);
        } else {
            ++(++current);
        }
    }
}

template <typename T, class Allocator>
template <class BinaryPredicate>
auto list<T, Allocator>::unique(BinaryPredicate pred) -> void
{
    if (empty()) {
        return;
    }

    iterator current = begin();
    ++current;

    while (current != end()) {
        if (pred(*current, *(--current))) {
            current = erase(++current);
        } else {
            ++(++current);
        }
    }
}
