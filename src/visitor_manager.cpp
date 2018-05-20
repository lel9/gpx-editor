#include "visitor_manager.h"
#include <QDir>
#include <QLibrary>

typedef Visitor* (*Builder)();

VisitorManager::VisitorManager()
{
}

void VisitorManager::manage()
{
    QDir dir = QDir::current();
    dir.cd("..");
    dir.cd("libs");
    dir.setFilter(QDir::Files);
    QFileInfoList fl = dir.entryInfoList();

    Visitor *visitor;
    for (int i = 0; i < fl.size(); i++)
    {
        QFileInfo fileInfo = fl.at(i);
        QString fname = fileInfo.fileName();

        if (QLibrary::isLibrary(fname) && fname.endsWith(".dll"))
        {
            QLibrary lib(fname);
            if(!lib.load())
                continue;

            Builder builder = (Builder) lib.resolve("buildVisitor");
            if(builder)
            {
                visitor = builder();
                QString name = visitor->operationName();
                for (Visitor* v : visitors)
                    if (name == v->operationName())
                        continue;
                visitors.append(visitor);
                emit addVisitor(visitor);
            }
        }
    }
}

QString VisitorManager::accept(const QList<QGeoCoordinate> &points, int operationIndex)
{
    if (operationIndex >= 0 && operationIndex < visitors.length())
        return visitors.at(operationIndex)->visit(points);
    return "";
}

