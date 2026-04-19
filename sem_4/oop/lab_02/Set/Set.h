//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_SET_H
#define LAB_02_SET_H

#include "BaseSet.h"
#include "SetConstIterator.h"
#include "Concepts.h"

template <ContainerValue T>
class Set final : public BaseSet
{
public:
    using value_type = T;
    using iterator = SetConstIterator<T>;
    using const_iterator = SetConstIterator<T>;

    friend class SetConstIterator<T>;

    // === Конструкторы ===
    Set();

    Set(const Set<T> &other);
    Set<T> &operator=(const Set<T> &other);

    template <ConvertableContainerValue<T> U>
    explicit Set(const Set<U> &other);

    template <ConvertableContainerValue<T> U>
    Set<T> &operator=(const Set<U> &other);

    Set(Set<T> &&other) noexcept(std::is_nothrow_move_constructible_v<T>);
    Set<T> &operator=(Set<T> &&other) noexcept(std::is_nothrow_move_constructible_v<T>);

    template <ConvertableContainerValue<T> U>
    Set(std::initializer_list<U> list);

    template <ConvertableContainerValue<T> U>
    Set<T> &operator=(std::initializer_list<U> list);

    template <ConvertableContainer<T> C>
    explicit Set(const C &container);

    template <ConvertableContainer<T> C>
    Set<T> &operator=(const C &container);

    template <ConvertibleRange<T> R>
    explicit Set(const R &range);

    template <ConvertibleRange<T> R>
    Set<T> &operator=(const R &range);

    template <ConvertableForwardIterator<T> I, Sentinel<I> S>
    Set(const I &first, const S &last);

    template <ConvertableContainerValue<T> U>
    Set(size_type size, const U *array);

    // === Деструктор ===
    ~Set() override;

    // === Информация о множестве ===
    size_type size() const noexcept override;

    bool empty() const noexcept override;

    // === Итераторы ===
    iterator begin() const noexcept;
    iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    // === Операции над множеством ===
    // Очистка
    void clear() noexcept;

    // Проверка вхождения в множество
    template <ConvertableContainerValue<T> U>
    bool contains(const U &value) const noexcept;

    // Добавление
    template <ConvertableContainerValue<T> U>
    bool add(const U &value);

    template <ConvertableContainer<T> C>
    bool add(const C &container);

    // Удаление
    template <EquatableContainerValue<T> U>
    bool erase(const U &value) noexcept;

    template <EquatableContainer<T> C>
    bool erase(const C &container) noexcept;

    // Пересечение
    template <EquatableContainer<T> C>
    Set<T> &intersect_update(const C &container) noexcept;

    template <EquatableContainer<T> C>
    Set<T> &operator&=(const C &container) noexcept;

    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> intersect(const C &container) const;

    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator&(const C &container) const;

    template <NotSetCommonContainer<T> C>
    friend Set<std::common_type_t<T, typename C::value_type>> operator&(const C &container, const Set<T>& set)
    {
        return set & container;
    }

    // Объединение
    template <ConvertableContainer<T> C>
    Set<T> &unite_update(const C &container);

    template <ConvertableContainer<T> C>
    Set<T> &operator|=(const C &container);

    template <ConvertableContainer<T> C>
    Set<T> &operator+=(const C &container);

    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> unite(const C &container) const;

    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator|(const C &container) const;

    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator+(const C &container) const;

    template <NotSetCommonContainer<T> C>
    friend Set<std::common_type_t<T, typename C::value_type>> operator|(const C &container, const Set<T>& set)
    {
        return set | container;
    }

    template <NotSetCommonContainer<T> C>
    friend Set<std::common_type_t<T, typename C::value_type>> operator+(const C &container, const Set<T>& set)
    {
        return set + container;
    }

    // Разность
    template <ConvertableContainer<T> C>
    Set<T> &difference_update(const C &container);

    template <ConvertableContainer<T> C>
    Set<T> &operator-=(const C &container);

    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> difference(const C &container) const;

    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator-(const C &container) const;

    template <NotSetConvertableContainer<T> C>
    friend Set<std::common_type_t<T, typename C::value_type>> operator-(const C &container, const Set<T>& set)
    {
        Set<std::common_type_t<T, typename C::value_type>> diff_set(container);
        diff_set.difference_update(set);
        return diff_set;
    }

    // Симметрическая разность
    template <ConvertableContainer<T> C>
    Set<T> &symmetric_difference_update(const C &container);

    template <ConvertableContainer<T> C>
    Set<T> &operator^=(const C &container);

    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> symmetric_difference(const C &container) const;

    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator^(const C &container) const;

    template <NotSetConvertableContainer<T> C>
    friend Set<std::common_type_t<T, typename C::value_type>> operator^(const C &container, const Set<T>& set)
    {
        return set ^ container;
    }

    // Отношения множеств
    template <EquatableContainerValue<T> U>
    bool subset_of(const Set<U> &other) const noexcept;

    template <EquatableContainerValue<T> U>
    bool superset_of(const Set<U> &other) const noexcept;

    template <EquatableContainerValue<T> U>
    bool equal(const Set<U> &other) const noexcept;

    template <EquatableContainerValue<T> U>
    bool operator==(const Set<U> &other) const;

    template <EquatableContainerValue<T> U>
    bool not_equal(const Set<U> &other) const noexcept;

    template <EquatableContainerValue<T> U>
    std::partial_ordering operator<=>(const Set<U> &other) const noexcept;

    // === Операторы ===
    explicit operator bool() const noexcept;
protected:
    class Node
    {
        friend Set<T>::iterator;
        friend Set<T>::const_iterator;

    public:
        Node();
        explicit Node(const T &value);
        explicit Node(T &&value);
        Node(const Node &node);
        Node(Node &&node);
        explicit Node(std::shared_ptr<Node> node);

        ~Node() = default;

        void set_value(const T& new_value);
        void set_next(const std::shared_ptr<Node>& new_next);
        void set_next_null();

        const T& get_value() const;
        std::weak_ptr<Node> get_next() const;

        bool operator==(const Node &node) const;
        bool operator==(const std::shared_ptr<Node> &node) const;
        bool operator!=(const Node &node) const;
        bool operator!=(const std::shared_ptr<Node> &node) const;

    private:
        T value;
        std::shared_ptr<Node> next;
    };

private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

    bool add(std::shared_ptr<Node> &node);
};

template <ContainerValue T>
std::ostream& operator<<(std::ostream& os, const Set<T>& set);


#include "Set.hpp"

#endif //LAB_02_SET_H
