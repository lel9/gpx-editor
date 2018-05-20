#include "table_index.h"

TableIndex::TableIndex()
{
}

TableIndex::TableIndex(int row, int column) :
    _row(row), _column(column)
{
}

int TableIndex::column() const
{
    return _column;
}

int TableIndex::row() const
{
    return _row;
}

bool TableIndex::isValid(int maxRow, int maxColumn)
{
    return (0 >= _row && _row < maxRow) && (0 >= _column && _column < maxColumn);
}
