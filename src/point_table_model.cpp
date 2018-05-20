#include "point_table_model.h"
#include "exceptions.h"

PointTableModel::PointTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    _headers << "Широта" << "Долгота" << "Высота";
}

int PointTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _points.count();
}

int PointTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant PointTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Vertical)
        return section;

    switch(section)
    {
    case 0:
        return trUtf8("Широта");
    case 1:
        return trUtf8("Долгота");
    case 2:
        return trUtf8("Высота");
    }

    return QVariant();
}

QVariant PointTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || _points.count() <= index.row() ||
        (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    switch(index.column())
    {
    case 0:
        return _points[index.row()].latitude();
    case 1:
        return _points[index.row()].longitude();
    case 2:
        return _points[index.row()].altitude();
    }
    return QVariant();
}

bool PointTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    if(!index.isValid() || role != Qt::EditRole || _points.count() <= row)
        return false;

    bool ok;
    double val = value.toDouble(&ok);
    if (ok)
    {
        switch(index.column())
        {
        case 0:
            _points[row].setLatitude(val);
            break;
        case 1:
             _points[row].setLongitude(val);
            break;
        case 2:
            _points[row].setAltitude(val);
            break;
        default:
            return false;
        }
    }
    return ok;
}

Qt::ItemFlags PointTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return flags |= Qt::ItemIsEditable;
}

QStringList PointTableModel::headers() const
{
    return _headers;
}

QModelIndex PointTableModel::topLeftIndex() const
{
    return createIndex(0,0);
}

QModelIndex PointTableModel::bottomRightIndex() const
{
    return createIndex(rowCount()-1, columnCount()-1);
}

void PointTableModel::insertPoint(int row, const QGeoCoordinate &point)
{
    _points.insert(row, point);
}

void PointTableModel::addPoint(const QGeoCoordinate &point)
{
    _points.append(point);
}

QGeoCoordinate PointTableModel::removePoint(int row)
{
    if (row < 0 || row >= _points.length())
        throw std::out_of_range("Невозможно удалить точку: некорректный индекс");
    QGeoCoordinate point = _points.at(row);
    _points.removeAt(row);
    return point;
}

QGeoCoordinate PointTableModel::replacePoint(int row, const QGeoCoordinate &point)
{
    if (row < 0 || row >= _points.length())
        throw std::out_of_range("Невозможно отредактировать точку: некорректный индекс");
    QGeoCoordinate oldPoint = _points.at(row);
    _points[row] = point;
    return oldPoint;
}

QGeoCoordinate PointTableModel::pointAt(int pos) const
{
    return _points[pos];
}

const QList<QGeoCoordinate> &PointTableModel::points() const
{
    return _points;
}

double PointTableModel::distance() const
{
    double dist = 0;
    int n = _points.length() - 1;
    for (int i = 0; i < n; i++)
        dist += _points[i].distanceTo(_points[i+1]);
    return dist / 1000.;
}

