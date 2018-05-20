#include "edit_point_command.h"

EditPointCommand::EditPointCommand(const TableIndex &index, double val, RouteTableModel *model) :
    _model(model)
{
    _pos = index.row();
    _route = _model->currentRouteIndex();
    _point = _model->currentPoints()[_pos];
    switch (index.column())
    {
    case 0:
        _point.setLatitude(val);
        break;
    case 1:
        _point.setLongitude(val);
        break;
    case 2:
        _point.setAltitude(val);
        break;
    }
}

int EditPointCommand::execute()
{
    try
    {
        _model->setCurrentRouteIndex(_route);
        //_model->currentRouteChanged(_route);
        _oldPoint = _model->replacePointInCurrentRoute(_pos, _point);
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
        _model->setCurrentRouteIndex(_route);
        //_model->currentRouteChanged(_route);
        _model->replacePointInCurrentRoute(_pos, _oldPoint);
    }
    catch (std::exception &)
    {
        return 1;
    }
    return 0;
}

