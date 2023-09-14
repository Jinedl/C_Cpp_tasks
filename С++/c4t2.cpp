#include <cstdio>

/*
struct Item
{
    Item *next;
    long long value;
};
*/

class Arena
{
    std::size_t size;
    int *empty;
    Item *space;
    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;
public:
    explicit Arena(std::size_t sz)
    {
        size = sz;
        sz /= sizeof(Item);
        space = new Item[sz];
        empty = new int[sz];
        while (sz) {
            empty[--sz] = 1;
        }
    }
    Item *get()
    {
        int i = 0;
        while (!empty[i]) {
            i++;
            if (i * sizeof(Item) >= size) {
                return nullptr;
            }
        }
        empty[i] = 0;
        return &space[i];
    }
    void put(Item *a)
    {
        empty[a - space] = 1;
    }
    ~Arena()
    {
        delete []empty;
        delete []space;
    }
};
