#include "Vessel.h"

Vessel::Vessel(TessModel *m3d, vec3 startPosition, vec3 startRotation, ORIENTATION *orientation)
{
    model3d=m3d;
    position=startPosition;
    rotation=startRotation;
    ori=orientation;
    velocity=vec3(0.0,0,-398.0);
    x_soll=100010.0;
    v_soll=-50.0;
    rotX_soll=0.0;
    rotY_soll=0.0;
    R_soll=100010.0;
}

Vessel::~Vessel()
{
    //dtor
}

void Vessel::startSimulation()
{
    threadHandle = CreateThread(
					NULL,
					0,
					(LPTHREAD_START_ROUTINE)simulationThread,
					this,
					0,
					&threadid);
    //SetThreadPriority(threadHandle,1);
}

void Vessel::render(mat4 *mProjection, mat4 *mView)
{
    if (ori->viewIndex==1)
    {
        mView[1].setIdentity();
        mView[1].translate(-position);
        //mView[1].translate(vec3((mat4().getXrotMatrix(vessel->rotation[0])*vec4(0.0,-0.5,-2.5)).get()));
        mView[1].rotateY(ori->yAngle);
        mView[1].rotateX(-rotation[0]);
        mView[1].translate(0.0,-0.5,-2.5);
    }
    model3d->mModel.setIdentity();
    model3d->mModel.rotateX(rotation[0]+PI/2);
    model3d->mModel.rotateY(rotation[1]);
    model3d->mModel.translate(position[0], position[1], position[2]);

    model3d->renderVBO(*mProjection,mView[ori->viewIndex]);
}


int simulationThread(Vessel *vessel)
{
    double h=0.001;
    double h1;
    double e;
    vec4 F;
    vec3 g;
    double Mx,My;

    vessel->R=vessel->position.length();
    Sphere::getAngles(&vessel->phi,&vessel->psi,vessel->position);
    if (vessel->position[1]<0) vessel->psi=-vessel->psi;

    e=vessel->R_soll-vessel->R;
    PID altControl(1.0,20.0,3.0,-7.0,7.0,e);

//    e=vessel->v_soll-vessel->velocity[2];
//    PID vControl(2.5,100.0,3.0,-1.0,1.0,e);

    e=vessel->rotX_soll-vessel->rotation[0];
    PID rotXControl(1.0,20.0,3.0,-1.0,1.0,e);

    e=vessel->rotY_soll-vessel->rotation[1];
    PID rotYControl(1.0,20.0,3.0,-1.0,1.0,e);

    double overallStartTime=(double)clock()/(double)CLOCKS_PER_SEC;
    double startTime=0;

    while(1)
    {
        double currentTime=(double)clock()/(double)CLOCKS_PER_SEC-overallStartTime;
        if ((double)(currentTime-startTime)>(double)h)
        {
            h1=(double)(currentTime-startTime);
            startTime=currentTime;

            /**
                Modellgleichungen:
                der_x=v
                der_v=1/m*(F_Schub-m*g)
                der_phi=w;
                der_w=1/J*M_rot;
            **/

            e=vessel->R_soll-vessel->R;
            //F.get()[1]=altControl.calc(e,h1);

//            e=vessel->v_soll-vessel->velocity[2];
//            Fz=vControl.calc(e,h1);

            e=vessel->rotX_soll-vessel->rotation[0];
            Mx=rotXControl.calc(e,h1);

            e=vessel->rotY_soll-vessel->rotation[1];
            My=rotYControl.calc(e,h1);

            vessel->rotX_soll=-acos(vec3::dot(vec3(0.0,0.0,-1.0),Sphere::fpsi(vessel->phi,vessel->psi).normalize()));
            if (vessel->position[2]>0) vessel->rotX_soll=-vessel->rotX_soll-2*PI;

            g=gravity(0.25e+21,6.67384e-11,vessel->position);
            vessel->F_Schub=vec3((mat4().getXrotMatrix(vessel->rotation[0])*F).get());
            vessel->position=vessel->position+vessel->velocity*h1;
            vessel->velocity=vessel->velocity+(vessel->F_Schub+g)*h1;

            vessel->M_rot=vec3(Mx,My,0.0);
            vessel->rotation=vessel->rotation+vessel->angularVelocity*h1;
            vessel->angularVelocity=vessel->angularVelocity+vessel->M_rot*h1;

            vessel->R=vessel->position.length();
            Sphere::getAngles(&vessel->phi,&vessel->psi,vessel->position);
            if (vessel->position[1]<0) vessel->psi=-vessel->psi;
        }
    }
    return 0;
}
