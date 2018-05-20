#ifndef SLOPES_H
#define SLOPES_H

#include "slopes_global.h"

#include "..//src//visitor.h"

class SLOPESSHARED_EXPORT SlopesVisitor : public Visitor
{
public:
    SlopesVisitor();
    ~SlopesVisitor();
    virtual QString visit(const QList<QGeoCoordinate> &points) override;

private:
    bool isSteep(double angle, double len);
    double slopeLength(const QGeoCoordinate &p1, const QGeoCoordinate &p2);
    double slopeAngle(const QGeoCoordinate &p1, const QGeoCoordinate &p2);
};

extern "C"
{
    SLOPESSHARED_EXPORT SlopesVisitor *buildVisitor();
}

#endif // SLOPES_H
