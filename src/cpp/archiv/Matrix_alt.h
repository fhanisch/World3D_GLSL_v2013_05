//	All matrices are column major. (OpenGL uses column-major matrix)
//
//		| 0  4  8 12 |
//		| 1  5  9 13 |
//		| 2  6 10 14 |
//		| 3  7 11 15 |
//
//		Rotation um die x-Achse		Rotation um die y-Achse		Rotation um die z-Achse
//		| 1	     0       0 0 |		|  cos(a) 0 sin(a) 0 |		| cos(a) -sin(a) 0 0 |
//		| 0 cos(a) -sin(a) 0 |		|       0 1      0 0 |		| sin(a)  cos(a) 0 0 |
//		| 0 sin(a)  cos(a) 0 |		| -sin(a) 0 cos(a) 0 |		|      0       0 1 0 |
//		| 0      0       0 1 |		|       0 0      0 1 |		|      0       0 0 1 |
//

#ifndef MATRIX4_H
#define MATRIX4_H

#include <math.h>

const float DEG2RADf = 3.14159f/180.0f;
const float RAD2DEGf = 180.0f/3.14159f;

class Vector3
{
private:
	float v[3];
public:
	Vector3();
	Vector3(float *vec);
	Vector3(float x, float y, float z);
	static Vector3 cross(Vector3 a, Vector3 b);
	float operator[](int index);
	float *get() {return v;};
	Vector3 operator+(Vector3 &rhs);
	Vector3 operator*(float scalar);
	float length();
};

class Vector4
{
private:
    float v[4];
public:
    Vector4(float x, float y, float z);
    float *get() {return v;};
};

class Matrix4
{
private:
	float m[16];

public:
	Matrix4();
	void setFrustum(float r, float t, float n, float f);
	void setIdendity();
	void translate(float dx, float dy, float dz);
	void translate(Vector3 dx);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void setScalarAtIndex(int index, float scalar);
	Matrix4 operator*(Matrix4 &rhs);
	float operator[](int index);
	float *get() {return m;}
	Vector3 getXAxis();
	Vector3 getYAxis();
	Vector3 getZAxis();
};


#endif
