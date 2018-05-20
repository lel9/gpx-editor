#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QStack>
#include <QObject>

#include "command.h"
class CommandManager : public QObject
{    
    Q_OBJECT

private:
    QStack<Command*> commandUndoStack;
    QStack<Command*> commandRedoStack;

public:
    CommandManager();

    void addCommand(Command *command);
    void undoCommand();
    void redoCommand();

signals:
    void undoStackIsNotEmpty(bool);
    void redoStackIsNotEmpty(bool);
};

#endif // COMMANDMANAGER_H
