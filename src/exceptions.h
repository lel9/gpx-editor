#ifndef FILEOPENEXCEPTION_H
#define FILEOPENEXCEPTION_H

#include <exception>

class FileOpenException : public std::exception
{
public:
    FileOpenException() = default;
    ~FileOpenException() = default;
    virtual const char *what() const throw() override;
};

class FileLoadException : public std::exception
{
public:
    FileLoadException() = default;
    ~FileLoadException() = default;
    virtual const char *what() const throw() override;
};

class DecoderException : public std::exception
{
public:
    DecoderException() = default;
    ~DecoderException() = default;
    virtual const char *what() const throw() override;
};

class EncoderInvalidLatException : public std::exception
{
private:
    int _row;
public:
    EncoderInvalidLatException(int row);
    virtual const char *what() const throw() override;
};

class EncoderInvalidLonException : public std::exception
{
private:
    int _row;
public:
    EncoderInvalidLonException(int row);
    virtual const char *what() const throw() override;
};

#endif // FILEOPENEXCEPTION_H
