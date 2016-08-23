#include "main.h"
#include "MeshBufferObject.h"
#include "Teapot.h"
#include "TeapotPatches.h"
#include "Vessel.h"

class Renderer
{
private:
	MeshBufferObject *apfel;
	MeshBufferObject *plane;
	MeshBufferObject *sphere;
	MeshBufferObject *planet;
	MeshBufferObject *ei;
	MeshBufferObject *wave;
	Curve *curve;
	Bezier *bezier;
	Perlin1d *gradNoise, *perlin1d, *perlinmod1d;
	Dreieck *dreieck;
	Rechteck *quad;
	Perlin2d *perlin2d;
	MeshPerlin2d *terrain;
	Teapot *teapot;
	BezierCurveTesselator *bezierCurveTesselator;
	TessPlane *boden;
	TessTestObject *tessTestObject;
	TeapotPatches *teapotPatches;
	TessModel *tessModel;
	TessModel *fighter;
	TessPlane *mandelbrot;
	Vessel *vessel;

	clock_t	currentTime;
    clock_t	startTime;
    clock_t overallStartTime;
    int FPS;
	short fpsCount;

	mat4 mProjection;
	mat4 mView[3];
	CAMERA *cam;
	ORIENTATION *ori;
	GLuint schrift;

	//Shader
	GLuint genericVertexShader, apfelVertexShader, sphereVertexShader, eiVertexShader,
			waveVertexShader, planeVertexShader, textVertexShader;

	GLuint adsPerFragmentShader, testFragmentShader, adsPerFragmentShaderTex,
				mandelbrotFragmentShader;

	GLuint genericGeometryShader, calcNormalsGeometryShader;

	GLuint textShaderProgram;

	void loadShader();
	void renderText(char *text,double value, GLfloat posX, GLfloat posY, vec4 color, mat4 mProjection);
	void calcFPS();

public:
	Renderer(CAMERA *camera, ORIENTATION *orientation, GLuint font);
	void render();
};
