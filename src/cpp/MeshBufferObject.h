#ifndef MESHBUFFEROBJECT_H
#define MESHBUFFEROBJECT_H

#include "main.h"
#include "Shader.h"

void createMeshGrid(int m, int n);
void createMeshGridIndices();
void createMeshGridGradients();
void createMBO(); // Mesh Grid Buffer Object
void createMeshGridIBO(); // Index Buffer Object
void createGBO(); // Gradients Buffer Object
void setVertices(GLfloat *ptr);
void setNormals(GLfloat *ptr);
void setIndices(GLuint *ptr);

static GLfloat	*vertices;
static GLfloat	*normals;
static GLuint	*indices;
static GLfloat	*gradients;
static GLfloat	*texCoords;
static GLubyte  *texture;

static GLuint indicesMeshLength;
static GLuint gradientsLength;
static GLfloat *u, *v;
static GLuint u_max, v_max;
static GLuint mboID[2];
static GLuint iboMeshID;
static GLuint gboID;

class BufferObject
{
protected:
	GLuint vboID, nboID, iboID, tcoID, texID;

	GLint	mProjectionHandle, mViewHandle, mModelHandle, mModelViewHandle, vColorHandle, fArg1Handle,
			vVertexHandle, vNormalHandle, fMeshHandleU, fMeshHandleV,
			vArg1Handle, vArg2Handle, vTexCoordHandle, vGradientHandle, textureHandle;

	GLuint	verticesLength;
	GLuint	normalsLength;
	GLuint	indicesLength;
	GLuint	texCoordsLength;
	long	tex_x_size, tex_y_size;
	GLfloat color[4];
	GLuint	vertexShader, fragmentShader,
			tesselationControlShader, tesselationEvaluationShader,
			geometryShader, shaderProgram;
	GLenum	renderMode, depthFunc;
	GLint	maxPatchVertices;

	BufferObject();
	void createVBO(); // Vertex Buffer Object
	void createNBO(); // Normal Buffer Object
	void createIBO(); // Index Buffer Object
	void createTCO(); // TexCoord Buffer Object

public:
	mat4 mModel;
	float arg1;
	float vArg1[4];
	float vArg2[4];

	int loadTexture(char *filename);
	void bindTexture();
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	void setDepthFunc(GLenum func);
	void renderVBO(mat4 mProjection, mat4 mView);
	void renderVBOTex(mat4 mProjection, mat4 mView);
	void renderMBO(mat4 mProjection, mat4 mView);
	void renderMBOGrad(mat4 mProjection, mat4 mView);
};

class Curve : public BufferObject
{
public:
	Curve();
};

class Bezier : public BufferObject
{
public:
	Bezier();
};

class BezierCurveTesselator : public BufferObject
{
public:
	BezierCurveTesselator();
};

class Perlin1d : public BufferObject
{
public:
	Perlin1d(char *vertexShaderName, char *geometryShaderName);
};

class Dreieck : public BufferObject
{

public:
	Dreieck();
};

class Rechteck : public BufferObject
{

public:
	Rechteck();
};

class TessPlane : public BufferObject
{
public:
	TessPlane(GLuint vertexShader, GLuint fragmentShader);
};

class TessModel : public BufferObject
{
public:
	TessModel(GLuint vertexShader, GLuint fragmentShader);
	TessModel(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);
};

class TessTestObject : public BufferObject
{
public:
	TessTestObject();
};

class Perlin2d: public BufferObject
{
public:
	Perlin2d();
};

class MeshBufferObject : public BufferObject
{
public:
	MeshBufferObject(GLuint vertexShader, GLuint fragmentShader);
};

class MeshPerlin2d : public BufferObject
{
public:
	MeshPerlin2d(char *vertexShaderName);
};

#endif //MESHBUFFEROBJECT_H
