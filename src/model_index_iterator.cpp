#include "model_index_iterator.h"

ModelIndexIterator::ModelIndexIterator(const TableIndex &begin, const TableIndex &end) :
    _begin(begin),
    _end(end),
    _current(begin)
{

}

TableIndex ModelIndexIterator::next()
{
    if (_current.column() == _end.column())
        _current = TableIndex(_current.row()+1, 0);
    else
        _current = TableIndex(_current.row(), _current.column()+1);
    return _current;
}

TableIndex ModelIndexIterator::begin()
{
    return _begin;
}

TableIndex ModelIndexIterator::end()
{
    return _end;
}

