#pragma once

template <typename T, class Allocator>
list<T, Allocator>::list(const Allocator& alloc)
    : list_base<T, Allocator>()
{
}

template <typename T, class Allocator>
list<T, Allocator>::list(size_type count,
                        const_reference_type value,
                        const Allocator& alloc)
    : list_base<T, Allocator>(alloc)
{
    for (size_type i = 0; i < count; ++i) {
        push_back(value);
    }
}

template <typename T, class Allocator>
template <class InputIt>
list<T, Allocator>::list(InputIt first, InputIt last, const Allocator& alloc)
    : list_base<T, Allocator>(alloc)
{
    for (const auto& iter = first; iter != last; ++iter) {
        push_back(iter);
    }
}

template <typename T, class Allocator>
list<T, Allocator>::list(list&& other, const Allocator& alloc)
    : list_base<T, Allocator>(std::forward<list_base>(other))
{
    get_allocator() = alloc;
//    other->m_nil->m_prev = nullptr;
//    other->m_nil->m_next = nullptr;
}

template <typename T, class Allocator>
list<T, Allocator>::list(std::initializer_list<T> ilist, const Allocator& alloc)
    : list_base<T, Allocator>(alloc)
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
    return *(this->m_base_impl.m_nil->m_next->m_value);
}

template <typename T, class Allocator>
auto list<T, Allocator>::front() const -> const_reference_type
{
    return *(this->m_base_impl.m_nil->m_next->m_value);
}

template <typename T, class Allocator>
auto list<T, Allocator>::back() -> reference_type
{
    return *(this->m_base_impl.m_nil->m_prev->m_value);
}

template <typename T, class Allocator>
auto list<T, Allocator>::back() const -> const_reference_type
{
    return *(this->m_base_impl.m_nil->m_prev->m_value);
}

template <typename T, class Allocator>
auto list<T, Allocator>::begin() noexcept -> iterator
{
    return iterator{this->m_base_impl.m_nil->m_next};
}

template <typename T, class Allocator>
auto list<T, Allocator>::begin() const noexcept -> const_iterator
{
    return const_iterator{this->m_base_impl.m_nil->m_next};
}

template <typename T, class Allocator>
auto list<T, Allocator>::cbegin() const noexcept -> const_iterator
{
    return begin();
}

template <typename T, class Allocator>
auto list<T, Allocator>::end() noexcept -> iterator
{
    return iterator{this->m_base_impl.m_nil};
}

template <typename T, class Allocator>
auto list<T, Allocator>::end() const noexcept -> const_iterator
{
    return const_iterator{this->m_base_impl.m_nil};
}

template <typename T, class Allocator>
auto list<T, Allocator>::cend() const noexcept -> const_iterator
{
    return end();
}

template <typename T, class Allocator>
auto list<T, Allocator>::rbegin() noexcept -> reverse_iterator
{
    return iterator{this->m_base_impl.m_nil->m_prev};
}

template <typename T, class Allocator>
auto list<T, Allocator>::rbegin() const noexcept -> const_reverse_iterator
{
    return const_iterator{this->m_base_impl.m_nil->m_prev};
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
auto list<T, Allocator>::empty() const noexcept -> bool
{
    return this->m_base_impl.m_nil->m_next == this->m_base_impl.m_nil;
}

template <typename T, class Allocator>
auto list<T, Allocator>::size() const noexcept -> size_type
{
    return std::distance(begin(), end());
}

template <typename T, class Allocator>
auto list<T, Allocator>::max_size() const noexcept -> size_type
{
    return std::numeric_limits<size_type>::max();
}

template <typename T, class Allocator>
auto list<T, Allocator>::clear() noexcept -> void
{
    auto first = begin();
    auto second = end();
    while (first != second) {
        auto to_del = first.m_node;
        get_allocator().destroy(to_del);
        get_allocator().deallocate(to_del->m_value, 1);
        ++first;
    }
}

template <typename T, class Allocator>
auto list<T, Allocator>::insert(const_iterator pos, const_reference_type& value) -> iterator
{
    auto ret_val = get_allocator().allocate(1);
    get_allocator().construct(ret_val, value);
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
    auto iter = insert(pos, std::forward<Args>(args) ...);
    return iter;
}

template <typename T, class Allocator>
auto list<T, Allocator>::erase(iterator pos) -> iterator
{
    auto to_del = pos.m_node;
    to_del->m_next->m_prev = to_del->m_prev;
    to_del->m_prev->m_next = to_del->m_next;
    auto to_return = to_del->m_next;

    get_allocator().destroy(to_del);
    get_allocator().deallocate(to_del->m_value, 1);
    return iterator{to_return};
}

template <typename T, class Allocator>
auto list<T, Allocator>::erase(const_iterator pos) -> iterator
{
    auto to_del = pos.m_node;
    to_del->m_next->m_prev = to_del->m_prev;
    to_del->m_prev->m_next = to_del->m_next;
    auto to_return = to_del->m_next;
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
