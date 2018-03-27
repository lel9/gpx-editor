#include "route_table_model.h"
#include "point_table_model.h"

RouteTableModel::RouteTableModel(QObject *parent) :
    QAbstractTableModel(parent), currentRouteIndex(0)
{
}

RouteTableModel::RouteTableModel(const RouteTableModel &model) :
    QAbstractTableModel(),
    _routes(model._routes), currentRouteIndex(model.currentRouteIndex)
{
}

int RouteTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _routes.count();
}

int RouteTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant RouteTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Vertical)
        return section;

    switch(section)
    {
    case 0:
        return trUtf8("Имя");
    case 1:
        return trUtf8("Длина, м");
    case 2:
        return trUtf8("Дата создания");
    }

    return QVariant();
}

QVariant RouteTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || _routes.count() <= index.row() ||
        (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    switch(index.column())
    {
    case 0:
        return _routes[index.row()]->name();
    case 1:
        return _routes[index.row()]->distance();
    case 2:
        return _routes[index.row()]->date();
    }
    return QVariant();
}

bool RouteTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || role != Qt::EditRole || _routes.count() <= index.row())
        return false;

    switch(index.column())
    {
    case 0:
        _routes[index.row()]->setName(value.toString());
        break;
    default:
        return false;
    }
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags RouteTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == 0)
        flags |= Qt::ItemIsEditable;
    return flags;
}

void RouteTableModel::addRoute(const shared_ptr<Route> &route)
{
    int row = _routes.count();
    beginInsertRows(QModelIndex(), row, row);
    _routes.append(route);
    endInsertRows();
}

void RouteTableModel::insertRoute(int row, const shared_ptr<Route> &route)
{
    beginInsertRows(QModelIndex(), row, row);
    _routes.insert(row, route);
    endInsertRows();
}

shared_ptr<Route> RouteTableModel::removeRoute(int row)
{
    if (row < 0 || row >= _routes.length())
        throw out_of_range("Невозможно удалить маршрут: некорректный индекс");

    shared_ptr<Route> route = _routes.at(row);
    beginRemoveRows(QModelIndex(), row, row);
    _routes.remove(row);
    endRemoveRows();
    return route;
}

void RouteTableModel::saveRoutes(const shared_ptr<RouteSaver> &saver)
{
    saver->save(_routes);
}

shared_ptr<Route> RouteTableModel::currentRoute()
{
    if (currentRouteIndex < 0 || currentRouteIndex >= _routes.length())
        throw std::out_of_range("Некорректный индекс");
    return _routes[currentRouteIndex];
}

void RouteTableModel::setCurrentRoute(int row)
{
    if (row >=0 && row < _routes.length())
        currentRouteIndex = row;
    else
        currentRouteIndex = 0;
}

RouteTableModel& RouteTableModel::operator =(const RouteTableModel &model)
{
    _routes = model._routes;
    currentRouteIndex = model.currentRouteIndex;
    return *this;
}

bool operator ==(const RouteTableModel &first, const RouteTableModel &second)
{
    if (first._routes.length() != second._routes.length())
        return false;
    int n = first._routes.length();
    for (int i = 0; i < n; i++)
        if (*(first._routes[i]) != *(second._routes[i]))
            return false;
    return true;
}
