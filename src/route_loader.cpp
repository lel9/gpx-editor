#include "route_loader.h"
#include "exceptions.h"
#include "converter.h"

#include <QFile>
#include <QFileInfo>

#define ROUND5(x) (qRound((x)*1e5)/(double)1e5)

QVector<shared_ptr<Route>> GPXLoader::load()
{
    shared_ptr<Route> route = make_shared<Route>();
    QXmlStreamReader inputStream(&file);
    QVector<QGeoCoordinate> wpt;
    bool ok;

    while (!inputStream.atEnd())
    {
        while (!inputStream.atEnd() && !inputStream.hasError() &&
               inputStream.name().toString() != "wpt" && inputStream.name().toString() != "trk")
            inputStream.readNext();

        if (inputStream.name().toString() == "wpt")
        {
            QGeoCoordinate point = loadPoint(inputStream, &ok);
            if (ok)
                wpt << point;
            else
                inputStream.readNext();
        }

        else if (inputStream.name().toString() == "trk")
        {
            inputStream.readNextStartElement();
            if (inputStream.name() == "name")
                route->setName(inputStream.readElementText());

            while (!inputStream.atEnd() && !inputStream.hasError() &&
                   inputStream.name().toString() != "trkseg")
                inputStream.readNext();

            while (!inputStream.atEnd() && !inputStream.hasError())
            {
                if (inputStream.name().toString() == "trkpt" && !inputStream.attributes().isEmpty())
                {
                    QGeoCoordinate point = loadPoint(inputStream, &ok);
                    if (ok)
                        route->appendPoint(point);
                    else
                        inputStream.readNext();
                }
                else
                    inputStream.readNext();
            }
        }

        if (inputStream.hasError())
            throw FileLoadException();
    }

    if (wpt.length() == 2)
    {
        route->insertPoint(0, wpt.first());
        route->insertPoint(route->length(), wpt.last());
    }

    QFileInfo info(file);
    route->setDate(info.created().date());

    QVector<shared_ptr<Route>> routes;
    routes << route;
    return routes;
}

bool GPXLoader::loadAltitude(QXmlStreamReader &inputStream, QGeoCoordinate &point)
{
    inputStream.readNextStartElement();
    bool ok = false;
    if (inputStream.name().toString() == "ele")
    {
        double alt = inputStream.readElementText().toDouble(&ok);
        if (ok)
            point.setAltitude(alt);
    }
    return ok;
}

QGeoCoordinate GPXLoader::loadPoint(QXmlStreamReader &inputStream, bool *ok)
{
    QGeoCoordinate point;
    bool ok1, ok2;
    double lon = inputStream.attributes().value("lon").toDouble(&ok1);
    double lat = inputStream.attributes().value("lat").toDouble(&ok2);
    *ok = ok1 && ok2;
    if (*ok)
    {
        point.setLatitude(ROUND5(lat));
        point.setLongitude(ROUND5(lon));
        if (loadAltitude(inputStream, point))
            inputStream.readNextStartElement();
    }
    return point;
}

QVector<shared_ptr<Route>> PolylineLoader::load()
{
    QXmlStreamReader inputStream(&file);
    QVector<shared_ptr<Route>> routes;

    while (!inputStream.atEnd())
    {
        if (inputStream.name() == "route" && !inputStream.attributes().isEmpty())
        {
            QString name = inputStream.attributes().value("name").toString();
            QDate date = QDate::fromString(inputStream.attributes().value("date").toString());
            QString polyline = inputStream.attributes().value("polyline").toString();

            shared_ptr<Route> route = Converter::polylineToRoute(QString(polyline));
            route->setName(name);
            route->setDate(date);
            route->setPolyline(polyline);
            loadAltitudes(inputStream, route);
            routes << route;
        }
        else
            inputStream.readNext();

        if (inputStream.hasError())
            throw FileLoadException();
    }
    return routes;
}

bool PolylineLoader::loadAltitudes(QXmlStreamReader &inputStream, shared_ptr<Route> &route)
{
    inputStream.readNextStartElement();
    bool res = false;
    while (inputStream.name() == "altitude")
    {
        if (inputStream.hasError())
            throw FileLoadException();

        if (!inputStream.attributes().isEmpty())
        {
            bool ok1, ok2;
            int pos = inputStream.attributes().value("point").toInt(&ok1);
            double alt = inputStream.attributes().value("value").toDouble(&ok2);

            if (ok1 && ok2 && pos >= 0 && pos < route->length())
            {
                QGeoCoordinate point = route->pointAt(pos);
                point.setAltitude(alt);
                route->replacePoint(pos, point);
            }
        }

        inputStream.readNextStartElement();
        res = true;
    }
    return res;
}

RouteLoader::~RouteLoader()
{
    if (file.isOpen())
        file.close();
}

void RouteLoader::setFileName(const QString &filename)
{
    file.setFileName(filename);
    if (!file.open(QIODevice::ReadWrite))
        throw FileOpenException();
}
