#ifndef VISITORMANAGER_H
#define VISITORMANAGER_H

#include <QVector>
#include <QObject>

#include "visitor.h"

class VisitorManager : public QObject
{
    Q_OBJECT

    QVector<Visitor*> visitors;
public:
    VisitorManager();
    void manage();
    QString accept(const QList<QGeoCoordinate> &points, int operationIndex);

signals:
    void addVisitor(Visitor*);
    void removeVisitor(Visitor*);
};

#endif // VISITORMANAGER_H
