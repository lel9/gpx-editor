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

    while (!inputStream.atEnd())
    {
        inputStream.readNext();
        QString name = inputStream.name().toString();
        if (inputStream.isStartElement())
        {
            if (name == "name")
                route->setName(inputStream.readElementText());
            if (name == "trkpt" || name == "wpt")
            {
                bool ok1, ok2;
                double lon = inputStream.attributes().value("lon").toDouble(&ok1);
                double lat = inputStream.attributes().value("lat").toDouble(&ok2);
                if (ok1 && ok2)
                {
                    if (name == "trkpt")
                        route->appendPoint(QGeoCoordinate(ROUND5(lat), ROUND5(lon)));
                    else
                        wpt << QGeoCoordinate(ROUND5(lat), ROUND5(lon));
                }
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

QVector<shared_ptr<Route>> PolylineLoader::load()
{
    QXmlStreamReader inputStream(&file);
    QVector<shared_ptr<Route>> routes;

    while (!inputStream.atEnd())
    {
        inputStream.readNext();
        if (inputStream.name() == "route" && !inputStream.attributes().isEmpty())
        {
            QString name = inputStream.attributes().value("name").toString();
            QDate date = QDate::fromString(inputStream.attributes().value("date").toString());
            QString polyline = inputStream.attributes().value("polyline").toString();

            shared_ptr<Route> route = Converter::polylineToRoute(QString(polyline));
            route->setName(name);
            route->setDate(date);
            route->setPolyline(polyline);
            routes << route;
        }

        if (inputStream.hasError())
            throw FileLoadException();
    }
    return routes;
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
