#include "TeapotPatches.h"

TeapotPatches::TeapotPatches(GLuint vertexShader)
{
	setVertices(teapotPatchVertices);
	verticesLength=sizeof(teapotPatchVertices)/sizeof(GLfloat);

	setIndices(teapotPatchIndices);
	indicesLength = sizeof(teapotPatchIndices)/sizeof(GLuint);

	color[0]=1.0f;color[1]=0.0f;color[2]=0.0f;color[3]=1.0f;

	createVBO();
	createIBO();

	maxPatchVertices=16;
	renderMode = GL_PATCHES;

	tesselationControlShader = Shader::createShader(GL_TESS_CONTROL_SHADER,"src\\shader\\teapot.tcs");
	tesselationEvaluationShader = Shader::createShader(GL_TESS_EVALUATION_SHADER,"src\\shader\\teapot.tes");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\ads_per_fragment.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader,tesselationControlShader,tesselationEvaluationShader,fragmentShader);
}
