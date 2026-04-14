//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_SET_H
#define LAB_02_SET_H

#include "BaseContainer.h"
#include "SetConstIterator.h"
#include "Concepts.h"

template <ContainerValue T>
class Set final : public BaseContainer<T>
{
public:
    using value_type = BaseContainer<T>::value_type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = BaseContainer<T>::size_type;
    using iterator = SetConstIterator<T>;
    // ConstIterator тут заглушка, просто реализовывать не const не имеет смысла для множества
    using const_iterator = SetConstIterator<T>;
    using difference_type = ptrdiff_t;

    friend class SetConstIterator<T>;

    // === Конструкторы ===
    Set();

    Set(const Set<T> &other);

    Set(Set<T> &&other);

    template <ContainerValue U>
        requires Convertible<U, T>
    Set(std::initializer_list<U> list);

    template <ForwardIterator I>
        requires Convertible<std::iter_value_t<I>, T>
    Set(const I &first, const I &last);

    template <Container C>
        requires Convertible<typename C::value_type, T>
    explicit Set(const C &container);

    template <ContainerValue U>
        requires Convertible<U, T>
    Set(size_type size, const U *array);

    // === Деструктор ===
    ~Set() override;

    // === Информация о множестве ===
    size_type size() const noexcept override;

    bool empty() const noexcept override;

    // === Итераторы ===
    iterator begin() const noexcept;
    iterator end() const noexcept;

    // === Операции над множеством ===
    // Очистка
    void clear();

    // Проверка вхождения в множество
    template <ContainerValue U>
        requires Convertible<U, T>
    bool contains(const U &value) const;

    // Добавление
    template <ContainerValue U>
        requires Convertible<U, T>
    void add(const U &value);

    template <Container C>
        requires Convertible<typename C::value_type, T>
    void add(const C &container);

    // Удаление
    template <ContainerValue U>
        requires Equatable<T, U>
    void erase(const U &value);

    template <Container C>
        requires Equatable<typename C::value_type, T>
    void erase(const C &container);

    // Пересечение
    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> intersect(const C &container) const;

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &intersect_update(const C &container);

    // Объединение
    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> unite(const C &container) const;

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &unite_update(const C &container);

    // Разность
    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> difference(const C &container) const;

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &difference_update(const C &container);

    // Симметрическая разность
    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> symmetric_difference(const C &container) const;

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &symmetric_difference_update(const C &container);

    // Отношения множеств
    template <ContainerValue U>
        requires Convertible<U, T>
    bool subset_of(const Set<U> &other) const noexcept;

    template <ContainerValue U>
        requires Convertible<U, T>
    bool superset_of(const Set<U> &other) const noexcept;

    template <ContainerValue U>
        requires Convertible<U, T>
    bool equal(const Set<U> &other) const noexcept;

    template <ContainerValue U>
        requires Convertible<U, T>
    bool not_equal(const Set<U> &other) const noexcept;

    // === Операторы ===
    //  Присваивание
    Set<T> &operator=(const Set<T> &other);

    template <ContainerValue U>
        requires Convertible<U, T>
    Set<T> &operator=(const Set<U> &other);

    Set<T> &operator=(Set<T> &&other);

    template <ContainerValue U>
        requires Convertible<U, T>
    Set<T> &operator=(std::initializer_list<U> list);

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &operator=(const C &container);

    // Сравнения
    template <ContainerValue U>
        requires Convertible<U, T>
    bool operator==(const Set<U>& other) const;

    template <ContainerValue U>
        requires Convertible<U, T>
    bool operator!=(const Set<U>& other) const;

    // Объединение
    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> operator+(const C &container) const;

    template <Container C>
        requires Convertible<typename C::value_type, T>
             && (!std::same_as<C, Set<T>>)
    friend Set<T> operator+(const C &container, const Set<T>& set)
    {
        return set + container;
    }

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &operator+=(const C &container);

    template <Container C>
        requires Convertible<typename C::value_type, T>
             && (!std::same_as<C, Set<T>>)
    friend Set<T> operator|(const C &container, const Set<T>& set)
    {
        return set | container;
    }

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> operator|(const C &container) const;

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &operator|=(const C &container);

    // Пересечение
    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> operator&(const C &container) const;

    template <Container C>
        requires Convertible<typename C::value_type, T>
             && (!std::same_as<C, Set<T>>)
    friend Set<T> operator&(const C &container, const Set<T>& set)
    {
        return set & container;
    }

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &operator&=(const C &container);

    // Разность
    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> operator-(const C &container) const;

    template <Container C>
        requires Convertible<typename C::value_type, T>
             && (!std::same_as<C, Set<T>>)
    friend Set<T> operator-(const C &container, const Set<T>& set)
    {
        Set<T> diff_set(container);
        diff_set.difference_update(set);
        return diff_set;
    }

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &operator-=(const C &container);

    // Симметрическая разность
    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> operator^(const C &container) const;

    template <Container C>
        requires Convertible<typename C::value_type, T>
             && (!std::same_as<C, Set<T>>)
    friend Set<T> operator^(const C &container, const Set<T>& set)
    {
        return set ^ container;
    }

    template <Container C>
        requires Convertible<typename C::value_type, T>
    Set<T> &operator^=(const C &container);

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
};

template <ContainerValue T>
std::ostream& operator<<(std::ostream& os, const Set<T>& set);


#include "Set.hpp"

#endif //LAB_02_SET_H
