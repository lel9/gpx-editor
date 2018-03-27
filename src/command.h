#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
    Command() = default;
    virtual ~Command() = default;
    virtual int execute() = 0;
    virtual int unExecute() = 0;
};

#endif // COMMAND_H
