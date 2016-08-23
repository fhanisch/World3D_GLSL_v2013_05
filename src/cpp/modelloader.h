#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "main.h"

typedef struct {
	unsigned int verticesLength;
	unsigned int indicesLength;
	float *vertices;
	unsigned int *indices;
} MODELDATA;

int loadModel(MODELDATA *md, char *filename);
int readString(char *string);
int readInteger(int *z, char *sign);
int readGleitkommazahl(void *g, unsigned char precession);

#endif