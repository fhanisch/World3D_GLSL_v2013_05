#ifndef VESSEL_H
#define VESSEL_H

#include "MeshBufferObject.h"
#include "controlsystem.h"

class Vessel
{
    public:
        Vessel(TessModel *model3d, vec3 startPosition, vec3 startRotation, ORIENTATION *orientation);
        ~Vessel();
        void startSimulation();

        vec3 F_Schub, M_rot;

        vec3 position, rotation, velocity, angularVelocity;
        double R,phi,psi;

        double R_soll, x_soll, v_soll, rotX_soll, rotY_soll;

        void render(mat4 *mProjection, mat4 *mView);

    protected:

    private:
        TessModel *model3d;
        HANDLE threadHandle;
        unsigned long threadid;
        ORIENTATION *ori;

};

int simulationThread(Vessel *vessel);

#endif // VESSEL_H
