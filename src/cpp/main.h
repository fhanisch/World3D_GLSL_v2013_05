#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <time.h>
#include "..\..\inc\glew.h"
#include <gl\gl.h>
#include "modelloader.h"
#include <vector.h>
#include <matrix.h>
#include <mathfunc.h>

#define WND_WIDTH	1680
#define WND_HEIGHT	1050
#define BIT_DEPTH	32;

typedef struct {
	double xPos;
	double yPos;
	double zPos;
	double xAngle;
	double yAngle;
	double zAngle;
	unsigned char viewIndex;
} CAMERA, ORIENTATION;

#endif
