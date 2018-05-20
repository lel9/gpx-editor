#ifndef TABLEINDEX_H
#define TABLEINDEX_H

class TableIndex
{
    int _row;
    int _column;
public:
    TableIndex();
    TableIndex(int row, int column);

    int column() const;
    int row() const;

    bool isValid(int maxRow, int maxColumn);
};

#endif // TABLEINDEX_H
