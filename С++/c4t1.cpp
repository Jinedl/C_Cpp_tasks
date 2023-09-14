class C {
    int val;
public:
    C(int a)
    {
        val = a * 2;
    }
    int operator+(C &a)
    {
        return this->val + a.val;
    }
    int get()
    {
        return this->val;
    }
};
