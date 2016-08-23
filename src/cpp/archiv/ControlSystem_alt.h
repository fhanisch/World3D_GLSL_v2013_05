#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include "main.h"

class PID
{
    public:
        PID(float k, float Ti, float Td, float y_min, float y_max, float e_start);
        float calc(float e, float h);

    protected:
    private:
        float k,Ti,Td,y_min,y_max,e_1;
        float P,I,D;
};

#endif // CONTROLSYSTEM_H
