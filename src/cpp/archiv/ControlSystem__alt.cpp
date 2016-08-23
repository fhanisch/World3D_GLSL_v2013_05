#include "ControlSystem.h"

PID::PID(float k, float Ti, float Td, float y_min, float y_max, float e_start)
{
    this->k=k;
    this->Ti=Ti;
    this->Td=Td;
    this->y_min=y_min;
    this->y_max=y_max;
    I=0;
    e_1=e_start;
}

float PID::calc(float e, float h)
{
    float y;

    P=e;
    D=(e-e_1)/h;
    y=k*(P+1.0f/Ti*I+Td*D);
    y=min(max(y,y_min),y_max);
    I=I+e*h;
    e_1=e;
    return y;
}
