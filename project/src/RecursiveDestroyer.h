#pragma once

#include <stdexcept>
#include <forward_list>

#include "Commons.h"


class RecursiveDestroyer
{
public:
    virtual ~RecursiveDestroyer()
    {
        for (RecursiveDestroyer *child : _children) {
            child->_parent = nullptr; //prevent removing from list if parent is deleting
            delete child;
        }

        if (_parent)
            _parent->removeFromDestroy(this);
    }

protected:
    inline RecursiveDestroyer* addToDestroy(RecursiveDestroyer *target)
    {
        if (target->_parent)
            throw std::runtime_error("RecursiveDestroyer: addToDestroy: parent is not null");

        target->_parent = this;
        _children.push_front(target);

        return target;
    }

    inline void removeFromDestroy(RecursiveDestroyer *target)   {_children.remove(target);}

private:
    RecursiveDestroyer *_parent = nullptr; //if nullptr, do not need to call removeFromDestroy
    std::forward_list<RecursiveDestroyer*> _children;
};
