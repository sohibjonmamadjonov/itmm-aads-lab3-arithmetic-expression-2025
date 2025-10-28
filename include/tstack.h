// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tstack.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TStack_H__
#define __TStack_H__

const int DefaultMemSize = 1024; // стандартный размер памяти для стека

template <typename T>
class TStack {
protected:
    T* pMem; // указатель на массив элементов
    int MemSize; // размер памяти для СД
    int DataCount; // количество элементов в СД
    int Hi; // индекс вершины стека

    int GetNextIndex(int index) // получить следующий индекс
    {

    }

public:
    TStack(int Size = DefaultMemSize) : MemSize(Size)
    {

    }

    ~Tstack()
    {

    }


    bool IsEmpty() const
    {
        return false;
    }

    bool IsFull() const
    {
        return false;
    }


    void Put(const T &Val) // добавить значение
    {
    
    }

    T Top() const // получить значение
    {
        return T{};
    }   

    void Get() // извлечь значение
    {

    }
};

#endif
