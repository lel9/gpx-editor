#ifndef MODELINDEXITERATOR_H
#define MODELINDEXITERATOR_H

#include "table_index.h"

class ModelIndexIterator
{
private:
    TableIndex _begin;
    TableIndex _end;
    TableIndex _current;

public:
    ModelIndexIterator(const TableIndex &begin, const TableIndex &end);
    TableIndex next();
    TableIndex begin();
    TableIndex end();
};

#endif // MODELINDEXITERATOR_H
