#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <string>

class Parameter{

    public:

    Parameter(std::string paramName,float startVal,float min,float max,float increment);

    void reset();
    void increment();
    void decrement();
    void increment(float step);
    void decrement(float step);
    float getValue();
    int setValue(float val);
    std::string getName();
    
    private:

    std::string name;
    float value;
    float init;
    float _max,_min;
    float incrementFine;
    float incrementCoarse;

};

#endif