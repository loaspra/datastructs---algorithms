#pragma once

template<typename E>
class AVLNode
{
public:
    E* valor;
    AVLNode* hijo_iz;
    AVLNode* hijo_de;
    int altura;

    AVLNode()
    {
        hijo_iz = hijo_de = nullptr;
    }

    AVLNode(E value, AVLNode* left = nullptr, AVLNode* right = nullptr)
    {
        valor = new E(value);
        hijo_iz = left;
        hijo_de = right;
    }

    ~AVLNode()
    {
        this->hijo_iz = nullptr;
        this->hijo_de = nullptr;
        delete this->valor;
    }

    E elemento()
    {
        return this->valor;
    }

    void setValor(E e)
    {
        this->valor = new E(e);
    }

    AVLNode* izquierda()
    {
        return this->hijo_iz;
    }

    AVLNode* derecha()
    {
        return this->hijo_de;
    }
};
