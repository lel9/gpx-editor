#ifndef SLOPETYPES_H
#define SLOPETYPES_H

#include "slopetypes_global.h"
#include "../src/visitor.h"

class SLOPETYPESSHARED_EXPORT SlopeTypesVisitor : public Visitor
{
public:
    SlopeTypesVisitor();
    virtual ~SlopeTypesVisitor();
    virtual QString visit(const QList<QGeoCoordinate> &points) override;

private:
    double slopeLength(const QGeoCoordinate &p1, const QGeoCoordinate &p2);
    double slopeAngle(const QGeoCoordinate &p1, const QGeoCoordinate &p2);
    int chooseSteepnessType(double angle);
    int chooseLenType(double len);
    QString makeResult(int lenTypes[], int steepnessTypes[]);
};

extern "C"
{
    SLOPETYPESSHARED_EXPORT SlopeTypesVisitor *buildVisitor();
}

#endif // SLOPETYPES_H
