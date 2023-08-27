#include <vector>
#include "parameter.h"
#include "Control.h"
#include <string>


class ControlSurface{


public:

ControlSurface();

int addControl(Control* Control);
int addParameter(Parameter* parameter);
int assign(std::string paramName,int controlId);
int remove(std::string paramName,int controlId);

private:

Parameter* getParamByName(std::string name);
std::vector<Parameter*> params;
std::vector<Control*>  ctrls;

};