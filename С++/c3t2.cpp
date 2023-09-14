#include <iostream>
#include <cstring>

namespace numbers {
    class complex_stack {
        std::size_t stack_size;
        complex *stack;
    public:
        complex_stack(): stack_size(0), stack(nullptr) {}
        std::size_t size() const
        {
            return stack_size;
        }
        complex operator [] (std::size_t num) const
        {
            return stack[num];
        }
        complex_stack(complex_stack &a)
        {
            stack_size = a.stack_size;
            stack = new complex[stack_size];
            memcpy(stack, a.stack, stack_size * sizeof(complex));
        }
        complex_stack& operator = (const complex_stack &a)
        {
            if (this != &a) {
                stack_size = a.stack_size;
                delete []stack;
                stack = new complex[stack_size];
                memcpy(stack, a.stack, stack_size * sizeof(complex));
            }
            return *this;
        }
        complex_stack operator << (complex a) const
        {
            complex_stack h;
            h.stack_size = stack_size + 1;
            h.stack = new complex[h.stack_size];
            memcpy(h.stack, stack, stack_size * sizeof(complex));
            h.stack[h.stack_size - 1] = a;
            return h;
        }
        complex operator + () const
        {
            return stack[stack_size - 1];
        }
        complex_stack operator ~ () const
        {
            complex_stack h;
            h.stack_size = stack_size - 1;
            h.stack = new complex[h.stack_size];
            memcpy(h.stack, stack, h.stack_size * sizeof(complex));
            return h;
        }
        ~complex_stack()
        {
            delete []stack;
        }
    };
}

