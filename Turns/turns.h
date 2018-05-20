#ifndef TURNS_H
#define TURNS_H

#include "turns_global.h"
#include "../src/visitor.h"

class TURNSSHARED_EXPORT TurnVisitor : public Visitor
{
public:
    TurnVisitor();
    virtual ~TurnVisitor();
    virtual QString visit(const QList<QGeoCoordinate> &points) override;

private:
    int chooseType(double angle);
    double angleBetweenPoints(const QGeoCoordinate &p1,
                              const QGeoCoordinate &p2,
                              const QGeoCoordinate &p3);
    QString makeResult(int types[]);
};

extern "C"
{
    TURNSSHARED_EXPORT TurnVisitor *buildVisitor();
}

#endif // TURNS_H
