#include "parameter.h"

Parameter::Parameter(std::string paramName,float startVal, float min, float max, float increment)
{
    init = startVal;
    _min = min;
    _max = max;
    incrementCoarse = increment;
    name = paramName;

    if(startVal>_max || startVal<_min){
        printf("warning: parameter %s default value outside range [%f,%f]\n",name,min,max);
    }

    reset();
}

void Parameter::reset()
{
    value = init;
}

void Parameter::increment()
{
    increment(incrementCoarse);
}

void Parameter::decrement()
{
    decrement(incrementCoarse);
}

void Parameter::increment(float step)
{   
    if(value + step <= _max){
         value += step;
    }else{
        value = _max;
    }
    printf("%s: %f\n",name.c_str(),value);
}

void Parameter::decrement(float step)
{
        if(value - step >= _min){ 
        value -= step;  
    }
    else{
        value = _min;
    }
    printf("%s: %f\n",name.c_str(),value);
}

float Parameter::getValue()
{
    return value;
}

int Parameter::setValue(float val)
{
    if(val <= _max && val >= _min){
        value = val;
        return 0;
    }
    else{
        printf("Can't set parameter %s to %f, since outside range\n",name,val);
        return -1;
    }
}

std::string Parameter::getName()
{
    return name;
}
