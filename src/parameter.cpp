#include "parameter.h"
#include <iostream>
#include <fmt/format.h>

Parameter::Parameter(std::string paramName,double startVal, double min, double max, double increment)
{
    init = startVal;
    _min = min;
    _max = max;
    incrementCoarse = increment;
    name = paramName;

    if(startVal>_max || startVal<_min){
        std::cout << fmt::format("warning: parameter {} default value outside range [ {} , {} ]\n",name,min,max);
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

void Parameter::increment(double step)
{   
    if(value + step <= _max){
         value += step;
    }else if(wrap){
            value = (value+step) - (_max-_min+1);
    }else{
        value = _max;
    }
   std::cout << fmt::format("{}: {}\n",name.c_str(),value);
}


void Parameter::decrement(double step)
{
    if(value - step >= _min){ 
        value -= step;  
    }else if(wrap){
        value = (value-step) + (_max-_min+1);
    }else{
        value = _min;
    }
    //std::cout << std::format("{}: {}\n",name.c_str(),value);
}


double Parameter::getValue()
{
    return value;
}

int Parameter::setValue(double val)
{
    if(val <= _max && val >= _min){
        value = val;
        return 0;
    }
    else{
        //std::cout << std::format("Can't set parameter {} to {}, since outside range\n",name,val);
        return -1;
    }
}

std::string Parameter::getName(){ 
    return name;
    
}

void Parameter::setWrap(bool val){

    wrap = val;
}
bool Parameter::getWrap(){

    return wrap;
}