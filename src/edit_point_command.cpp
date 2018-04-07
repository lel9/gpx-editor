#include "edit_point_command.h"

EditPointCommand::EditPointCommand(QModelIndex index, double val, RouteTableModel *model) :
    _index(index), _val(val), _model(model)
{
    _route = _model->currentRoute();
}

int EditPointCommand::execute()
{
    try
    {
        _model->setCurrentRoute(_route);
        _model->currentRouteChanged(_route);
        _oldVal = _model->replacePointInCurrentRoute(_index, _val);
    }
    catch (std::exception &)
    {
        return 1;
    }

    return 0;
}

int EditPointCommand::unExecute()
{
    try
    {
        _model->setCurrentRoute(_route);
        _model->currentRouteChanged(_route);
        _model->replacePointInCurrentRoute(_index, _oldVal);
    }
    catch (std::exception &)
    {
        return 1;
    }
    return 0;
}

