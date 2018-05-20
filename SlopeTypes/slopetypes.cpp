#include "slopetypes.h"
#include "qmath.h"

#include <QVector>

SlopeTypesVisitor::SlopeTypesVisitor() :
    Visitor("Количество склонов по длине и крутизне")
{
}

SlopeTypesVisitor::~SlopeTypesVisitor()
{
}

QString SlopeTypesVisitor::visit(const QList<QGeoCoordinate> &points)
{
    QString res = QString("Невозможно подсчитать типы склонов.\n\n");
    int end = points.size()-1;
    if (end < 1)
        return res;

    int lenTypes[3] = {0, 0, 0};
    int steepnessTypes[5] = {0, 0, 0, 0, 0};

    bool ok = false;

    for (int i = 0; i < end; i++)
    {
        QGeoCoordinate p1 = points[i];
        QGeoCoordinate p2 = points[i + 1];

        if (qIsNaN(p1.altitude()) || qIsNaN(p2.altitude()))
            continue;

        ok = true;

        double angle = slopeAngle(p1, p2);
        double len = slopeLength(p1, p2);

        int lenType = chooseLenType(len);
        int steepnessType = chooseSteepnessType(angle);

        lenTypes[lenType]++;
        if (steepnessType != 5)
            steepnessTypes[steepnessType]++;
    }

    if (ok)
        res = makeResult(lenTypes, steepnessTypes);
    return res;
}

int SlopeTypesVisitor::chooseLenType(double len)
{
    if (len > 500)
        return 0;
    else if (len >= 50)
        return 1;
    return 2;
}

int SlopeTypesVisitor::chooseSteepnessType(double angle)
{
    if (angle >= 35)
        return 0;
    else if(angle >= 15)
        return 1;
    else if (angle >= 8)
        return 2;
    else if (angle >= 4)
        return 3;
    else if (angle >= 2)
        return 4;
    return 5;
}

double SlopeTypesVisitor::slopeAngle(const QGeoCoordinate &p1, const QGeoCoordinate &p2)
{
    double dl = p1.distanceTo(p2);
    if (dl == 0)
        return 0;
    double dh = qAbs(p2.altitude() - p1.altitude());
    double ang = qAtan(dh / dl);
    return qRadiansToDegrees(ang);
}

double SlopeTypesVisitor::slopeLength(const QGeoCoordinate &p1, const QGeoCoordinate &p2)
{
    double dl = p1.distanceTo(p2);
    double dh = qAbs(p2.altitude() - p1.altitude());
    return qSqrt(dl * dl + dh * dh);
}

QString SlopeTypesVisitor::makeResult(int lenTypes[3], int steepnessTypes[5])
{
    QString res;

    res.append("Количество очень крутых склонов: ");
    res.append(QString::number(steepnessTypes[0]));
    res.append("\n");

    res.append("Количество крутых склонов: ");
    res.append(QString::number(steepnessTypes[1]));
    res.append("\n");

    res.append("Количество склонов средней крутизны: ");
    res.append(QString::number(steepnessTypes[2]));
    res.append("\n");

    res.append("Количество пологих склонов: ");
    res.append(QString::number(steepnessTypes[3]));
    res.append("\n");

    res.append("Количество очень пологих склонов: ");
    res.append(QString::number(steepnessTypes[4]));
    res.append("\n\n");

    res.append("Количество длинных склонов: ");
    res.append(QString::number(lenTypes[0]));
    res.append("\n");

    res.append("Количество склонов средней длины: ");
    res.append(QString::number(lenTypes[1]));
    res.append("\n");

    res.append("Количество коротких склонов: ");
    res.append(QString::number(lenTypes[2]));
    res.append("\n\n");

    return res;
}

SlopeTypesVisitor *buildVisitor()
{
    return new SlopeTypesVisitor();
}

