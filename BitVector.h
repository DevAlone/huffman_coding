#pragma once
#include <cstddef>
#include <vector>

class BitVector {
    friend class Reference;

public:
    class Reference {
        friend class BitVector;
        //        BitVector& bitVector;
        unsigned char* word;
        size_t bitNumber;

    public:
        Reference(BitVector& bitVector, size_t position)
        {
            word = &bitVector.data[position / 8];
            bitNumber = position % 8;
        }

        Reference& operator=(bool value)
        {
            if (value)
                *word |= 1 << bitNumber;
            else
                *word &= ~(1 << bitNumber);
        }

        // TODO: Reference& operator= (const Reference& value)
        // TODO: bool opeartor~()
        operator bool() const
        {
            return *word & (1 << bitNumber);
        }
    };

    const std::vector<unsigned char>& getData() const
    {
        return data;
    }
    void push_back(bool value)
    {
        if (data.size() * 8 <= _size) {
            data.push_back(0);
        }

        if (value)
            data[_size / 8] |= 1 << (_size % 8);
        else
            data[_size / 8] &= ~(1 << (_size % 8));

        ++_size;
    }
    size_t size() const
    {
        return _size;
    }
    Reference operator[](size_t bitNumber)
    {
        return Reference(*this, bitNumber);
        //        return data[bitNumber / 8] & (1 << (bitNumber % 8));
    }

private:
    std::vector<unsigned char> data;
    size_t _size = 0;
};
