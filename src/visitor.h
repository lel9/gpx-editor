#ifndef VISITOR_H
#define VISITOR_H

#include <QGeoCoordinate>

class Visitor
{
protected:
    QString _operationName;
public:
    Visitor() { }
    Visitor(const QString &name) { _operationName = name; }
    virtual ~Visitor() { }

    virtual QString operationName() { return _operationName; }
    virtual void setOperationName(const QString &name) { _operationName = name; }

    virtual QString visit(const QList<QGeoCoordinate> &points) = 0;
};

#endif // VISITOR_H
