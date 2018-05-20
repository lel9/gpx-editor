#ifndef POINTTABLEMODEL_H
#define POINTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QGeoCoordinate>

class PointTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PointTableModel(QObject *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;

    virtual QStringList headers() const;

    virtual QModelIndex topLeftIndex() const;
    virtual QModelIndex bottomRightIndex() const;

    void insertPoint(int row, const QGeoCoordinate &point);
    void addPoint(const QGeoCoordinate &point);
    QGeoCoordinate removePoint(int row);
    QGeoCoordinate replacePoint(int row, const QGeoCoordinate &point);

    QGeoCoordinate pointAt(int pos) const;
    const QList<QGeoCoordinate> &points() const;
    double distance() const;

private:
    QList<QGeoCoordinate> _points;
    QStringList _headers;
};

#endif // POINTTABLEMODEL_H
