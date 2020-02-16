#pragma once

class Test
{
    int _a;
    int _b;
public:
    Test(int a, int b) : _a(a), _b(b) {}

    inline int a() const    {return _a;}
    int b() const;
};