#ifndef ITERATORM_HPP
#define ITERATORM_HPP

#include "Matriz/Matriz.hpp"

class Matriz;

class IteratorM
{
    friend class Matriz;

private:
    Node *cabecalho;
    Node *current;

public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = double;
    using pointer = double *;
    using reference = double &;

    IteratorM() : cabecalho(nullptr), current(nullptr) {}

    IteratorM(Node *cabecalho, Node *current = nullptr) : cabecalho(cabecalho), current(current) {}

    reference operator*()
    {
        return current->valor;
    }

    reference operator*() const
    {
        return current->valor;
    }

    pointer operator->()
    {
        return &current->valor;
    }

    pointer operator->() const
    {
        return &current->valor;
    }

    IteratorM &operator++()
    {
    }
};

#endif