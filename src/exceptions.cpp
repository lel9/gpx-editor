#include "exceptions.h"

#include <QString>

const char* FileOpenException::what() const throw()
{
    return "Невозможно открыть файл";
}


const char* DecoderException::what() const throw()
{
    return "Невозможно декодировать полилайн";
}

EncoderInvalidLatException::EncoderInvalidLatException(int row) : _row(row)
{
}

const char* EncoderInvalidLatException::what() const throw()
{
    QString msg = "Некорректное значение широты: точка " + QString::number(_row+1);
    return msg.toUtf8().data();
}

EncoderInvalidLonException::EncoderInvalidLonException(int row) : _row(row)
{
}

const char* EncoderInvalidLonException::what() const throw()
{
    QString msg = "Некорректное значение долготы: точка " + QString::number(_row+1);
    return msg.toUtf8().data();
}

const char* FileLoadException::what() const throw()
{
    return "Ошибка загрузки файла: некорректные данные";
}
