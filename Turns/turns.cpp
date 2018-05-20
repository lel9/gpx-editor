#include "turns.h"
#include "qmath.h"

#include <QVector>

TurnVisitor::TurnVisitor() :
    Visitor("Количество поворотов по категориям")
{
}

TurnVisitor::~TurnVisitor()
{
}

QString TurnVisitor::visit(const QList<QGeoCoordinate> &points)
{
    int end = points.size() - 2;
    if (end < 1)
        return "Невозможно подсчитать количество поворотов.\n\n";

    int types[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < end; i++)
    {
        QGeoCoordinate p1 = points[i];
        QGeoCoordinate p2 = points[i+1];
        QGeoCoordinate p3 = points[i+2];
        double angle = angleBetweenPoints(p1, p2, p3);
        int type = chooseType(angle);
        if (type != 8)
            types[type]++;
    }

    return makeResult(types);
}


int TurnVisitor::chooseType(double angle)
{
    if (angle < 6.)
        return 0;
    else if (angle < 11.5)
        return 1;
    else if (angle < 34.)
        return 2;
    else if (angle < 56.5)
        return 3;
    else if (angle < 79.)
        return 4;
    else if (angle < 90.)
        return 5;
    else if (angle < 135.5)
        return 6;
    else if (angle < 160.)
        return 7;
    return 8;
}

double TurnVisitor::angleBetweenPoints(const QGeoCoordinate &p1,
                                       const QGeoCoordinate &p2,
                                       const QGeoCoordinate &p3)
{
    double ab = p1.distanceTo(p2);
    double bc = p2.distanceTo(p3);
    double ac = p1.distanceTo(p3);
    double alpha = qAcos((ab * ab + ac * ac - bc * bc) / (2 * ab * ac));
    return qRadiansToDegrees(alpha);
}


QString TurnVisitor::makeResult(int types[8])
{
    QString res;
    for (int i = 0; i < 8; i++)
    {
        res.append("Количество поворотов " + QString::number(i) + " категории: ");
        res.append(QString::number(types[i]));
        res.append("\n");
    }
    res.append("\n");
    return res;
}

TurnVisitor *buildVisitor()
{
    return new TurnVisitor();
}
