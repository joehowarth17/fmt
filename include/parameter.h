#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <string>

class Parameter{

    public:

    Parameter(std::string paramName,double startVal,double min,double max,double increment);

    void reset();
    void increment();
    void decrement();
    void increment(double step);
    void decrement(double step);
    double getValue();
    int setValue(double val);
    std::string getName();
    void setWrap(bool val);
    bool getWrap();
    
    private:

    std::string name;
    double value;
    double init;
    double _max,_min;
    double incrementFine;
    double incrementCoarse;
    bool wrap = false;

};

#endif