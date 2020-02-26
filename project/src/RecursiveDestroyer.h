#pragma once


class RecursiveDestroyer
{
public:
    virtual void destroy() = 0;

protected:
    inline void addToDestroy(RecursiveDestroyer *target)
    {
        //list push_front target
    }

    inline void recursiveDestroy()
    {
        //call recursiveDestroy() for every element of list

        destroy();
    }
private:
    //list of RecursiveDestroyer*
};
