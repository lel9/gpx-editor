#include "slopes.h"
#include "qmath.h"

SlopesVisitor::SlopesVisitor() :
    Visitor("Количество крутых спусков и подъемов")
{
}

SlopesVisitor::~SlopesVisitor()
{
}

QString SlopesVisitor::visit(const QList<QGeoCoordinate> &points)
{
    QString res = QString("Невозможно подсчитать количество крутых спусков и подъемов.\n\n");
    int end = points.size()-1;
    if (end < 1)
        return res;

    int count = 0;
    bool ok = false;

    for (int i = 0; i < end; i++)
    {
        QGeoCoordinate p1 = points[i];
        QGeoCoordinate p2 = points[i+1];

        if (qIsNaN(p1.altitude()) || qIsNaN(p2.altitude()))
            continue;

        ok = true;

        double len = slopeLength(p1, p2);
        double angle = slopeAngle(p1, p2);

        if (isSteep(angle, len))
            count++;
    }

    if (ok)
        res = "Количество крутых спусков и подъемов: " + QString::number(count) + "\n\n";
    return res;
}

double SlopesVisitor::slopeAngle(const QGeoCoordinate &p1, const QGeoCoordinate &p2)
{
    double dl = p1.distanceTo(p2);
    if (dl == 0)
        return 0;
    double dh = qAbs(p2.altitude() - p1.altitude());
    return dh / dl * 100;
}

double SlopesVisitor::slopeLength(const QGeoCoordinate &p1, const QGeoCoordinate &p2)
{
    double dl = p1.distanceTo(p2);
    double dh = qAbs(p2.altitude() - p1.altitude());
    return qSqrt(dl * dl + dh * dh);
}

bool SlopesVisitor::isSteep(double angle, double len)
{
    if (angle >= 8 && len > 270)
        return true;
    if (angle >= 7 && len > 300)
        return true;
    if (angle >= 6 && len > 350)
        return true;
    if (angle >= 5 && len > 450)
        return true;
    if (angle >= 4 && len > 600)
        return true;
    return false;
}

SlopesVisitor *buildVisitor()
{
    return new SlopesVisitor();
}
