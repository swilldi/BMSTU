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
    using iterator = SetConstIterator<T>;
    // ConstIterator тут заглушка, просто реализовывать не const не имеет смысла для множества
    using const_iterator = SetConstIterator<T>;

    // === Конструкторы ===
    Set();;

    explicit Set(const Set<T> &other);

    Set(Set<T> &&other);

    template <ContainerValue U>
        requires Convertable<U, T>
    Set(std::initializer_list<U> list);

    template <ForwardIterator I>
        requires Convertable<typename I::value_type, T>
    Set(const I &first, const I &last);

    template <Container C>
        requires Convertable<typename C::value_type, T>
    explicit Set(const C &container);

    template <ContainerValue U>
        requires Convertable<U, T>
    Set(size_type size, const U *array);

    // === Деструктор ===
    ~Set() override;

    // === Информация о множестве ===
    size_type get_size() override;

    bool empty() override;

    // === Итератора ===
    const_iterator begin() const noexcept;

    const_iterator end() const noexcept;

    // === Операции над множеством ===
    // Очитка
    void clear();

    // Проверка вхождения в множество
    template <ContainerValue U>
        requires Convertable<U, T>
    bool contains(const U &value) const;

    // Добавление
    template <ContainerValue U>
        requires Convertable<U, T>
    void add(const U &value);

    template <Container C>
        requires Convertable<typename C::value_type, T>
    void add(const C &container);

    // Удаление
    template <ContainerValue U>
        requires Equatable<T, U>
    void erase(const U &value);

    template <Container С>
        requires Equatable<typename С::value_type, T>
    void erase(const С &container);

    // Пересечение
    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> intersect(const C &container) const;

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &intersect_update(const C &container);

    // Объединение
    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> unite(const C &container) const;

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &unite_update(const C &container);

    // Разность
    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> difference(const C &container) const;

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &difference_update(const C &container);

    // Симетрическая разность
    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> symmetric_difference(const C &container) const;

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &symmetric_difference_update(const C &container);

    // === Операторы ===
    //  Присваивание
    template <ContainerValue U>
        requires Convertable<U, T>
    Set<T> &operator=(const Set<U> &other);

    Set<T> &operator=(Set<T> &&other);

    template <ContainerValue U>
        requires Convertable<U, T>
    Set<T> &operator=(std::initializer_list<U> list);

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &operator=(const C &container);

    // Объединение
    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> operator+(const C &container) const;

    template <Container C>
        requires Convertable<typename C::value_type, T>
    friend Set<T> operator+(const C &container, const Set<T>& set);

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &operator+=(const C &container);

    template <Container C>
        requires Convertable<typename C::value_type, T>
    friend Set<T> operator|(const C &container, const Set<T>& set);

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> operator|(const C &container) const;

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &operator|=(const C &container);

    // Пересечение
    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> operator&(const C &container) const;

    template <Container C>
        requires Convertable<typename C::value_type, T>
    friend Set<T> operator&(const C &container, const Set<T>& set);

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &operator&=(const C &container);

    // Разность
    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> operator-(const C &container) const;

    template <Container C>
        requires Convertable<typename C::value_type, T>
    friend Set<T> operator-(const C &container, Set<T> &set);

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &operator-=(const C &container);

    // Симетрическая разность
    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> operator^(const C &container) const;

    template <Container C>
        requires Convertable<typename C::value_type, T>
    friend Set<T> operator^(const C &container, Set<T> &set);

    template <Container C>
        requires Convertable<typename C::value_type, T>
    Set<T> &operator^=(const C &container);

    operator bool() const noexcept;
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

#include "Set.hpp"

#endif //LAB_02_SET_H
