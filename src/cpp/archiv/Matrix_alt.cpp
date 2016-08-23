#include "Matrix.h"

Vector3::Vector3()
{
    v[0]=0.0f; v[1]=0.0f; v[2]=0.0f;
}

Vector3::Vector3(float *vec)
{
	v[0]=vec[0]; v[1]=vec[1]; v[2]=vec[2];
}

Vector3::Vector3(float x, float y, float z)
{
	v[0]=x; v[1]=y; v[2]=z;
}

float Vector3::operator[](int index)
{
	return v[index];
}

Vector3 Vector3::cross(Vector3 a, Vector3 b)
{
	return Vector3(a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]);
}

Vector3 Vector3::operator+(Vector3 &rhs)
{
    return Vector3(v[0]+rhs[0], v[1]+rhs[1], v[2]+rhs[2]);
}

Vector3 Vector3::operator*(float scalar)
{
    return Vector3(v[0]*scalar, v[1]*scalar, v[2]*scalar);
}

float Vector3::length()
{
    return sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

Vector4::Vector4(float x,float y, float z)
{
    v[0]=x; v[1]=y; v[2]=z; v[3]=1.0;
}

Matrix4::Matrix4()
{
	setIdendity();
}

void Matrix4::setFrustum(float r, float t, float n, float f)
{
	m[0]=n/r;	m[4]=0;		m[8]=0;				m[12]=0;
	m[1]=0;		m[5]=n/t;	m[9]=0;				m[13]=0;
	m[2]=0;		m[6]=0;		m[10]=-(f+n)/(f-n); m[14]=-2*f*n/(f-n);
	m[3]=0;		m[7]=0;		m[11]=-1;			m[15]=0;
}

void Matrix4::setIdendity()
{
	for(int i=0;i<16;i++) m[i]=0;
	for(int i=0;i<4;i++) m[i*4+i]=1;
}

void Matrix4::translate(float dx, float dy, float dz)
{
	m[0]+=m[3]*dx; m[4]+=m[7]*dx;  m[8]+=m[11]*dx; m[12]+=m[15]*dx;
	m[1]+=m[3]*dy; m[5]+=m[7]*dy;  m[9]+=m[11]*dy; m[13]+=m[15]*dy;
	m[2]+=m[3]*dz; m[6]+=m[7]*dz; m[10]+=m[11]*dz; m[14]+=m[15]*dz;
}

void Matrix4::translate(Vector3 dx)
{
    m[0]+=m[3]*dx[0]; m[4]+=m[7]*dx[0];  m[8]+=m[11]*dx[0]; m[12]+=m[15]*dx[0];
	m[1]+=m[3]*dx[1]; m[5]+=m[7]*dx[1];  m[9]+=m[11]*dx[1]; m[13]+=m[15]*dx[1];
	m[2]+=m[3]*dx[2]; m[6]+=m[7]*dx[2]; m[10]+=m[11]*dx[2]; m[14]+=m[15]*dx[2];
}

void Matrix4::rotateX(float angle)
{
	float c = cosf(angle*DEG2RADf);
	float s = sinf(angle*DEG2RADf);
	float	m1=m[1], m5=m[5],   m9=m[9], m13=m[13],
			m2=m[2], m6=m[6], m10=m[10], m14=m[14];

	m[1]  =  m1*c -  m2*s;
	m[5]  =  m5*c -  m6*s;
	m[9]  =  m9*c - m10*s;
	m[13] = m13*c - m14*s;
	m[2]  =  m1*s +  m2*c;
	m[6]  =  m5*s +  m6*c;
	m[10] =  m9*s + m10*c;
	m[14] = m13*s + m14*c;
}

void Matrix4::rotateY(float angle)
{
	float c = cosf(angle*DEG2RADf);
	float s = sinf(angle*DEG2RADf);
	float	m0=m[0], m4=m[4],  m8=m[8],  m12=m[12],
			m2=m[2], m6=m[6], m10=m[10], m14=m[14];
	m[0]  =  m0*c +  m2*s;
	m[4]  =  m4*c +  m6*s;
	m[8]  =  m8*c + m10*s;
	m[12] = m12*c + m14*s;
	m[2]  =  -m0*s +  m2*c;
	m[6]  =  -m4*s +  m6*c;
	m[10] =  -m8*s + m10*c;
	m[14] = -m12*s + m14*c;
}

void Matrix4::rotateZ(float angle)
{
	float c = cosf(angle*DEG2RADf);
	float s = sinf(angle*DEG2RADf);
	float	m0=m[0], m4=m[4],  m8=m[8],  m12=m[12],
			m1=m[1], m5=m[5],   m9=m[9], m13=m[13];
	m[0]  =  m0*c -  m1*s;
	m[4]  =  m4*c -  m5*s;
	m[8]  =  m8*c -  m9*s;
	m[12] = m12*c - m13*s;
	m[1]  =  m0*s +  m1*c;
	m[5]  =  m4*s +  m5*c;
	m[9]  =  m8*s +  m9*c;
	m[13] = m12*s + m13*c;
}

void Matrix4::setScalarAtIndex(int index, float scalar)
{
	m[index]=scalar;
}

float Matrix4::operator[](int index)
{
	return m[index];
}

Matrix4 Matrix4::operator*( Matrix4 &rhs)
{
	Matrix4 out;
	float sum;

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			sum=0;
			for(int k=0;k<4;k++) sum+=m[i+k*4]*rhs[k+j*4];
			out.setScalarAtIndex(i+j*4,sum);
		}
	return out;
}

Vector3 Matrix4::getXAxis()
{
	return Vector3(&m[0]);
}

Vector3 Matrix4::getYAxis()
{
	return Vector3(&m[4]);
}

Vector3 Matrix4::getZAxis()
{
	return Vector3(&m[8]);
}
