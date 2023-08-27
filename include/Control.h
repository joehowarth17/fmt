#ifndef CONTROL_H_
#define CONTROL_H_

#include "parameter.h"

class Control{

public:

    
    int addParam(Parameter* parameter);
    int removeParam();

protected:

    Parameter* param;

};


#endif