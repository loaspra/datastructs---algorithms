#pragma once

template<typename E>
class TNode
{
public:
    E* valor;
    TNode* hijo_iz;
    TNode* hijo_de;

    TNode()
    {
        hijo_iz = hijo_de = nullptr;
    }

    TNode(E value, TNode* left = nullptr, TNode* right = nullptr)
    {
        valor = new E(value);
        hijo_iz = left;
        hijo_de = right;
    }

    ~TNode()
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

    TNode* izquierda()
    {
        return this->hijo_iz;
    }

    TNode* derecha()
    {
        return this->hijo_de;
    }
};

