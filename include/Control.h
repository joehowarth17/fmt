#ifndef CONTROL_H_
#define CONTROL_H_

#include "parameter.h"
#include <memory>
#include <string>

class Control{

public:

    Control(std::string controlName):name(controlName){};
    int addParam(Parameter* parameter);
    int removeParam();
    Parameter* getParameter(){
        return param;
    }

    std::string getName(){
        return name;
    }


protected:
    
    Parameter* param = NULL;
    std::string name;
};


#endif