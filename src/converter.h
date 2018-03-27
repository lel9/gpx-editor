#ifndef CONVERTER_H
#define CONVERTER_H

#include "route.h"

class Converter
{
private:
    // кодирование полилайна
    static QVector<double> encodeValues(const shared_ptr<Route> &route);
    static QString encodeChars(int value);
    static int encodeSign(double value);

    // декодирование полилайна
    static QVector<int> decodeIntegers(const QString &polyline);
    static int decodeSign(int value);

public:
    Converter();
    static shared_ptr<Route> polylineToRoute(const QString &polyline);
    static QString routeToPolyline(const shared_ptr<Route> &route);
};

#endif // CONVERTER_H
