#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <string>



class Parameter{

    public:

    Parameter(std::string paramName,float startVal,float min,float max,float increment);

    virtual void reset();
    virtual void increment();
    virtual void decrement();
    virtual void incrementMultiple(int steps);
    virtual void increment(float step);
    virtual void decrement(float step);
    virtual float getValue();
    virtual int setValue(float val);
    virtual std::string getName();
    virtual void setWrap(bool val);
    virtual bool getWrap();
    
    private:

    std::string name;
    float value;
    float init;
    float _max,_min;
    float incrementFine;
    float incrementCoarse;
    bool wrap = false;

};

// template <class T>
// class ParameterType<T>: public Parameter{


// };

#endif