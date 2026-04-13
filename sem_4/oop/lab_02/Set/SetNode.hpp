//
// Created by Dmitriy Dudurev on 12.04.2026.
//

#ifndef LAB_02_SETNODE_HPP
#define LAB_02_SETNODE_HPP

#include "Set.h"

template <ContainerValue T>
Set<T>::Node::Node() : value(), next(nullptr)
{ }

template <ContainerValue T>
Set<T>::Node::Node(const T &value) : value(value), next(nullptr)
{ }

template <ContainerValue T>
Set<T>::Node::Node(T &&value) : value(std::move(value)), next(nullptr)
{ }

template <ContainerValue T>
Set<T>::Node::Node(const Node& node) : value(node.value), next(node.next)
{ }

template <ContainerValue T>
Set<T>::Node::Node(Node &&node) : value(std::move(node.value)), next(std::move(node.next))
{ }

template <ContainerValue T>
Set<T>::Node::Node(std::shared_ptr<Node> node) : value(node->value), next(node->next)
{ }

template <ContainerValue T>
void Set<T>::Node::set_value(const T &new_value)
{
    value = new_value;
}

template <ContainerValue T>
void Set<T>::Node::set_next(const std::shared_ptr<Node> &new_next)
{
    next = new_next;
}

template <ContainerValue T>
void Set<T>::Node::set_next_null()
{
    set_next(nullptr);
}

template <ContainerValue T>
const T& Set<T>::Node::get_value() const
{
    return value;
}

template <ContainerValue T>
std::weak_ptr<typename Set<T>::Node> Set<T>::Node::get_next() const
{
    return next;
}

template <ContainerValue T>
bool Set<T>::Node::operator==(const Node &node) const
{
    return (value == node.value && next == node.next);
}

template <ContainerValue T>
bool Set<T>::Node::operator==(const std::shared_ptr<Node> &node) const
{
    return *this == *node;
}

template <ContainerValue T>
bool Set<T>::Node::operator!=(const Node &node) const
{
    return !(*this == node);
}

template <ContainerValue T>
bool Set<T>::Node::operator!=(const std::shared_ptr<Node> &node) const
{
    return !(*this == *node);
}

#endif //LAB_02_SETNODE_HPP