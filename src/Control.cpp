#include "Control.h"

int Control::addParam(Parameter *parameter)
{
    param = parameter;
    return 0;
}

int Control::removeParam()
{
    param = NULL;
    return 0;
}
