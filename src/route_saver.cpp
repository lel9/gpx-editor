#include "route_saver.h"
#include "exceptions.h"

RouteSaver::~RouteSaver()
{
    if (file.isOpen())
        file.close();
}

void RouteSaver::setFileName(const QString &filename)
{
    file.setFileName(filename);
    if (!file.open(QIODevice::WriteOnly))
        throw FileOpenException();
}

#include <QXmlStreamWriter>
void SimpleRouteSaver::save(const QVector<shared_ptr<Route>> &routes)
{
    QXmlStreamWriter outputStream(&file);
    outputStream.setAutoFormatting(true);
    outputStream.writeStartDocument();
    outputStream.writeStartElement("routes");
    foreach (shared_ptr<Route> route, routes)
    {
        outputStream.writeStartElement("route");
        outputStream.writeAttribute("name", route->name().toUtf8());
        outputStream.writeAttribute("date", route->date().toString().toUtf8());
        outputStream.writeAttribute("polyline", route->polyline().toUtf8());
        for (int i = 0; i < route->length(); i++)
        {
            outputStream.writeStartElement("altitude");
            outputStream.writeAttribute("point", QString::number(i));
            outputStream.writeAttribute("value", QString::number(route->pointAt(i).altitude()));
            outputStream.writeEndElement();
        }
        outputStream.writeEndElement();
    }
    outputStream.writeEndElement();
    outputStream.writeEndDocument();
}
