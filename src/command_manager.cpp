#include "command_manager.h"

CommandManager::CommandManager()
{

}

void CommandManager::addCommand(Command *command)
{
    if (command->execute() == 0)
    {
        commandUndoStack.push(command);
        emit undoStackIsNotEmpty(true);
    }
}

void CommandManager::undoCommand()
{
    Command *command = commandUndoStack.pop();
    if (command->unExecute() == 0)
    {
        commandRedoStack.push(command);
        emit redoStackIsNotEmpty(true);
        if (commandUndoStack.isEmpty())
            emit undoStackIsNotEmpty(false);
    }
}

void CommandManager::redoCommand()
{
    Command *command = commandRedoStack.pop();
    if (command->execute() == 0)
    {
        commandUndoStack.push(command);
        emit undoStackIsNotEmpty(true);
        if (commandRedoStack.isEmpty())
            redoStackIsNotEmpty(false);
    }
}

