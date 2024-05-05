#include <vector>
#include "parameter.h"
#include "Control.h"
#include <string>

/*
A ControlSurface is a collection of controls and parameters.
Paramers are values and Controls modify values.

The control surface allows for dynamic assigning of controls & parameters.

So for example a rotary encoder control can be assigned to modify a "chan1 volume" parameter.
Then on a button press, the rotary encoder can be re-assigned to modify the "chan2 volume" etc.

*/

class ControlSurface{

public:

ControlSurface();

int addControl(Control* Control);
int addParameter(Parameter* parameter);
int assign(std::string paramName,int controlId);
int remove(std::string paramName,int controlId);
void printControlSurface();

private:

Parameter* getParamByName(std::string name);
std::vector<Parameter*> params;
std::vector<Control*>  ctrls;

};