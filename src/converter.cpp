#include "converter.h"
#include "exceptions.h"

Converter::Converter()
{
}

shared_ptr<Route> Converter::polylineToRoute(const QString &polyline)
{
    shared_ptr<Route> route = make_shared<Route>();
    QVector<int> values = decodeIntegers(polyline);
    if (values.length() % 2)
        throw DecoderException();

    double lat, lon;

    if (!values.isEmpty())
    {
        lat = values[0] / 1e5;
        lon = values[1] / 1e5;
        if (lat < -90 || lat > 90)
            throw DecoderException();
        if (lon < -180 || lon > 180)
            throw DecoderException();
        route->appendPoint(QGeoCoordinate(lat, lon));

        for (int i = 2; i < values.length(); i += 2 )
        {
            lat = (values[i] += (values[i-2])) / 1e5;
            lon = (values[i+1] += (values[i-1])) / 1e5;

            if (lat < -90 || lat > 90)
                throw DecoderException();
            if (lon < -180 || lon > 180)
                throw DecoderException();
            route->appendPoint(QGeoCoordinate(lat, lon));
        }
    }

    return route;
}

QString Converter::routeToPolyline(const shared_ptr<Route> &route)
{
    QVector<double> values = encodeValues(route);
    double px = 0, py = 0;
    QString str;

    for(int i = 0; i < values.length(); i += 2)
    {
        str += encodeChars(encodeSign(values[i] - px));
        str += encodeChars(encodeSign(values[i+1] - py));
        px = values[i];
        py = values[i+1];
    }
    return str;
}

QVector<double> Converter::encodeValues(const shared_ptr<Route> &route)
{
    QVector<double> vals;
    for(int i = 0; i < route->length(); i++)
    {
        QGeoCoordinate point = route->pointAt(i);
        double lat = point.latitude();
        double lon = point.longitude();
        if (lat < -90 || lat > 90)
            throw EncoderInvalidLatException(i);
        if (lon < -180 || lon > 180)
            throw EncoderInvalidLonException(i);
        vals << lat << lon;
    }
    return vals;
}

QString Converter::encodeChars(int value)
{
    QString str;
    while( value >= 0x20 )
    {
        str += QChar(((value & 0x1F) | 0x20) + 63);
        value = value >> 5;
    }
    str += QChar(value + 63);
    return str;
}

int Converter::encodeSign(double value)
{
    int ivalue = qRound(value * 1e5);
    return (ivalue < 0) ? ~(ivalue << 1) : (ivalue << 1);
}

QVector<int> Converter::decodeIntegers(const QString &polyline)
{
    QVector<int> values;
    int byte = 0;
    int current = 0;
    int bits = 0;

    for (int i = 0; i < polyline.length(); i++)
    {
        byte = polyline.toUtf8()[i] - 63;
        current |= (( byte & 0x1F) << bits);
        bits += 5;

        if (byte < 0x20)
        {
            values << decodeSign(current);
            current = 0;
            bits = 0;
        }
    }

    return values;
}

int Converter::decodeSign(int value)
{
   return (value & 1) ? ~(value >> 1) : (value >> 1);
}

