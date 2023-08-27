#include "controlSurface.h"

ControlSurface::ControlSurface()
{
}

int ControlSurface::addControl(Control *Control)
{
    ctrls.push_back(Control);
    return 0;
}

int ControlSurface::addParameter(Parameter *parameter)
{
    params.push_back(parameter);
    return 0;
}

Parameter* ControlSurface::getParamByName(std::string name){

    for(int i=0; i<params.size();i++){

        if(params[i]->getName() == name) return params[i];
    }
    return NULL;
}
int ControlSurface::assign(std::string paramName, int controlId)
{
    Parameter* p = getParamByName(paramName);
    if(!p) return -1;
    ctrls[controlId]->addParam(p);
    return 0;
}

int ControlSurface::remove(std::string parmamName, int controlId)
{
    return 0;
}
