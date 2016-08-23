#include "Teapot.h"

Teapot::Teapot()
{
	setVertices(teapotVertices);
	verticesLength=sizeof(teapotVertices)/sizeof(GLfloat);

	setNormals(teapotNormals);
	normalsLength = sizeof(teapotNormals)/sizeof(GLfloat);

	setIndices(teapotIndices);
	indicesLength = sizeof(teapotIndices)/sizeof(GLuint);

	color[0]=1.0f;color[1]=0.0f;color[2]=0.0f;color[3]=1.0f;

	createVBO();
	createNBO();
	createIBO();

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\teapot.vert");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\ads_per_fragment.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader, fragmentShader);
}

void Teapot::renderTeapotVBO(mat4 mProjection, mat4 mView)
{
	glUseProgram(shaderProgram);

	mProjectionHandle = glGetUniformLocation(shaderProgram,"mProjection");
	glUniformMatrix4dv(mProjectionHandle,1,false,mProjection.get());

	mViewHandle = glGetUniformLocation(shaderProgram,"mView");
	glUniformMatrix4dv(mViewHandle,1,false,mView.get());

	mModelHandle = glGetUniformLocation(shaderProgram,"mModel");
	glUniformMatrix4dv(mModelHandle,1,false,mModel.get());

	vColorHandle = glGetUniformLocation(shaderProgram,"vColor");
	glUniform4fv(vColorHandle,1,color);

	vVertexHandle = glGetAttribLocation(shaderProgram,"vVertex");
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glVertexAttribPointer(vVertexHandle, 3, GL_FLOAT, false, 0, 0);

	vNormalHandle = glGetAttribLocation(shaderProgram,"vNormal");
	glBindBuffer(GL_ARRAY_BUFFER,nboID);
	glVertexAttribPointer(vNormalHandle, 3, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	//glIndexPointer(GL_UNSIGNED_INT,0,0); // scheinbar nicht notwendig (nicht mehr im OpenGL Core Profile)

	glEnableVertexAttribArray(vVertexHandle);
	glEnableVertexAttribArray(vNormalHandle);

	glDrawElements(GL_TRIANGLE_STRIP, 12, GL_UNSIGNED_INT, (GLuint*)0+0);
	glDrawElements(GL_TRIANGLE_STRIP, 78, GL_UNSIGNED_INT, (GLuint*)0+12);
	glDrawElements(GL_TRIANGLE_STRIP, 35, GL_UNSIGNED_INT, (GLuint*)0+90);
	glDrawElements(GL_TRIANGLE_STRIP, 70, GL_UNSIGNED_INT, (GLuint*)0+125);
	glDrawElements(GL_TRIANGLE_STRIP, 65, GL_UNSIGNED_INT, (GLuint*)0+195);
	glDrawElements(GL_TRIANGLE_STRIP, 37, GL_UNSIGNED_INT, (GLuint*)0+260);
	glDrawElements(GL_TRIANGLE_STRIP, 35, GL_UNSIGNED_INT, (GLuint*)0+297);
	glDrawElements(GL_TRIANGLE_STRIP, 32, GL_UNSIGNED_INT, (GLuint*)0+332);
	glDrawElements(GL_TRIANGLE_STRIP, 56, GL_UNSIGNED_INT, (GLuint*)0+364);
	glDrawElements(GL_TRIANGLE_STRIP, 45, GL_UNSIGNED_INT, (GLuint*)0+420);
	glDrawElements(GL_TRIANGLE_STRIP, 41, GL_UNSIGNED_INT, (GLuint*)0+465);
	glDrawElements(GL_TRIANGLE_STRIP, 37, GL_UNSIGNED_INT, (GLuint*)0+506);
	glDrawElements(GL_TRIANGLE_STRIP, 33, GL_UNSIGNED_INT, (GLuint*)0+543);
	glDrawElements(GL_TRIANGLE_STRIP, 29, GL_UNSIGNED_INT, (GLuint*)0+576);
	glDrawElements(GL_TRIANGLE_STRIP, 25, GL_UNSIGNED_INT, (GLuint*)0+605);
	glDrawElements(GL_TRIANGLE_STRIP, 21, GL_UNSIGNED_INT, (GLuint*)0+630);
	glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_INT, (GLuint*)0+651);
	glDrawElements(GL_TRIANGLE_STRIP, 13, GL_UNSIGNED_INT, (GLuint*)0+668);
	glDrawElements(GL_TRIANGLE_STRIP, 9, GL_UNSIGNED_INT, (GLuint*)0+681);
	glDrawElements(GL_TRIANGLE_STRIP, 27, GL_UNSIGNED_INT, (GLuint*)0+690);
	glDrawElements(GL_TRIANGLE_STRIP, 16, GL_UNSIGNED_INT, (GLuint*)0+717);
	glDrawElements(GL_TRIANGLE_STRIP, 22, GL_UNSIGNED_INT, (GLuint*)0+733);
	glDrawElements(GL_TRIANGLE_STRIP, 50, GL_UNSIGNED_INT, (GLuint*)0+755);
	glDrawElements(GL_TRIANGLE_STRIP, 42, GL_UNSIGNED_INT, (GLuint*)0+805);
	glDrawElements(GL_TRIANGLE_STRIP, 43, GL_UNSIGNED_INT, (GLuint*)0+847);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (GLuint*)0+890);
	glDrawElements(GL_TRIANGLE_STRIP, 143, GL_UNSIGNED_INT, (GLuint*)0+894);
	glDrawElements(GL_TRIANGLE_STRIP, 234, GL_UNSIGNED_INT, (GLuint*)0+1037);
	glDrawElements(GL_TRIANGLE_STRIP, 224, GL_UNSIGNED_INT, (GLuint*)0+1271);
	glDrawElements(GL_TRIANGLE_STRIP, 71, GL_UNSIGNED_INT, (GLuint*)0+1495);
	glDrawElements(GL_TRIANGLE_STRIP, 69, GL_UNSIGNED_INT, (GLuint*)0+1566);
	glDrawElements(GL_TRIANGLE_STRIP, 67, GL_UNSIGNED_INT, (GLuint*)0+1635);
	glDrawElements(GL_TRIANGLE_STRIP, 65, GL_UNSIGNED_INT, (GLuint*)0+1702);
	glDrawElements(GL_TRIANGLE_STRIP, 63, GL_UNSIGNED_INT, (GLuint*)0+1767);
	glDrawElements(GL_TRIANGLE_STRIP, 61, GL_UNSIGNED_INT, (GLuint*)0+1830);
	glDrawElements(GL_TRIANGLE_STRIP, 59, GL_UNSIGNED_INT, (GLuint*)0+1891);
	glDrawElements(GL_TRIANGLE_STRIP, 57, GL_UNSIGNED_INT, (GLuint*)0+1950);
	glDrawElements(GL_TRIANGLE_STRIP, 55, GL_UNSIGNED_INT, (GLuint*)0+2007);
	glDrawElements(GL_TRIANGLE_STRIP, 53, GL_UNSIGNED_INT, (GLuint*)0+2062);
	glDrawElements(GL_TRIANGLE_STRIP, 51, GL_UNSIGNED_INT, (GLuint*)0+2115);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+2166);
	glDrawElements(GL_TRIANGLE_STRIP, 50, GL_UNSIGNED_INT, (GLuint*)0+2169);
	glDrawElements(GL_TRIANGLE_STRIP, 48, GL_UNSIGNED_INT, (GLuint*)0+2219);
	glDrawElements(GL_TRIANGLE_STRIP, 46, GL_UNSIGNED_INT, (GLuint*)0+2267);
	glDrawElements(GL_TRIANGLE_STRIP, 44, GL_UNSIGNED_INT, (GLuint*)0+2313);
	glDrawElements(GL_TRIANGLE_STRIP, 42, GL_UNSIGNED_INT, (GLuint*)0+2357);
	glDrawElements(GL_TRIANGLE_STRIP, 40, GL_UNSIGNED_INT, (GLuint*)0+2399);
	glDrawElements(GL_TRIANGLE_STRIP, 38, GL_UNSIGNED_INT, (GLuint*)0+2439);
	glDrawElements(GL_TRIANGLE_STRIP, 36, GL_UNSIGNED_INT, (GLuint*)0+2477);
	glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_INT, (GLuint*)0+2513);
	glDrawElements(GL_TRIANGLE_STRIP, 32, GL_UNSIGNED_INT, (GLuint*)0+2547);
	glDrawElements(GL_TRIANGLE_STRIP, 30, GL_UNSIGNED_INT, (GLuint*)0+2579);
	glDrawElements(GL_TRIANGLE_STRIP, 28, GL_UNSIGNED_INT, (GLuint*)0+2609);
	glDrawElements(GL_TRIANGLE_STRIP, 26, GL_UNSIGNED_INT, (GLuint*)0+2637);
	glDrawElements(GL_TRIANGLE_STRIP, 24, GL_UNSIGNED_INT, (GLuint*)0+2663);
	glDrawElements(GL_TRIANGLE_STRIP, 22, GL_UNSIGNED_INT, (GLuint*)0+2687);
	glDrawElements(GL_TRIANGLE_STRIP, 20, GL_UNSIGNED_INT, (GLuint*)0+2709);
	glDrawElements(GL_TRIANGLE_STRIP, 18, GL_UNSIGNED_INT, (GLuint*)0+2729);
	glDrawElements(GL_TRIANGLE_STRIP, 16, GL_UNSIGNED_INT, (GLuint*)0+2747);
	glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, (GLuint*)0+2763);
	glDrawElements(GL_TRIANGLE_STRIP, 12, GL_UNSIGNED_INT, (GLuint*)0+2777);
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (GLuint*)0+2789);
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_INT, (GLuint*)0+2799);
	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (GLuint*)0+2807);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+2813);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+2816);
	glDrawElements(GL_TRIANGLE_STRIP, 200, GL_UNSIGNED_INT, (GLuint*)0+2819);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3019);
	glDrawElements(GL_TRIANGLE_STRIP, 66, GL_UNSIGNED_INT, (GLuint*)0+3022);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3088);
	glDrawElements(GL_TRIANGLE_STRIP, 209, GL_UNSIGNED_INT, (GLuint*)0+3091);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3300);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3303);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3306);
	glDrawElements(GL_TRIANGLE_STRIP, 38, GL_UNSIGNED_INT, (GLuint*)0+3309);
	glDrawElements(GL_TRIANGLE_STRIP, 15, GL_UNSIGNED_INT, (GLuint*)0+3347);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3362);
	glDrawElements(GL_TRIANGLE_STRIP, 26, GL_UNSIGNED_INT, (GLuint*)0+3365);
	glDrawElements(GL_TRIANGLE_STRIP, 9, GL_UNSIGNED_INT, (GLuint*)0+3391);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3400);
	glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, (GLuint*)0+3403);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3417);
	glDrawElements(GL_TRIANGLE_STRIP, 115, GL_UNSIGNED_INT, (GLuint*)0+3420);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3535);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3538);
	glDrawElements(GL_TRIANGLE_STRIP, 39, GL_UNSIGNED_INT, (GLuint*)0+3541);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3580);
	glDrawElements(GL_TRIANGLE_STRIP, 91, GL_UNSIGNED_INT, (GLuint*)0+3583);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3674);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3677);
	glDrawElements(GL_TRIANGLE_STRIP, 31, GL_UNSIGNED_INT, (GLuint*)0+3680);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3711);
	glDrawElements(GL_TRIANGLE_STRIP, 67, GL_UNSIGNED_INT, (GLuint*)0+3714);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3781);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3784);
	glDrawElements(GL_TRIANGLE_STRIP, 23, GL_UNSIGNED_INT, (GLuint*)0+3787);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3810);
	glDrawElements(GL_TRIANGLE_STRIP, 45, GL_UNSIGNED_INT, (GLuint*)0+3813);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3858);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3861);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3864);
	glDrawElements(GL_TRIANGLE_STRIP, 32, GL_UNSIGNED_INT, (GLuint*)0+3867);
	glDrawElements(GL_TRIANGLE_STRIP, 38, GL_UNSIGNED_INT, (GLuint*)0+3899);
	glDrawElements(GL_TRIANGLE_STRIP, 15, GL_UNSIGNED_INT, (GLuint*)0+3937);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3952);
	glDrawElements(GL_TRIANGLE_STRIP, 26, GL_UNSIGNED_INT, (GLuint*)0+3955);
	glDrawElements(GL_TRIANGLE_STRIP, 9, GL_UNSIGNED_INT, (GLuint*)0+3981);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3990);
	glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, (GLuint*)0+3993);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+4007);
	glDrawElements(GL_TRIANGLE_STRIP, 135, GL_UNSIGNED_INT, (GLuint*)0+4010);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+4145);
	glDrawElements(GL_TRIANGLE_STRIP, 76, GL_UNSIGNED_INT, (GLuint*)0+4148);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+4224);
	glDrawElements(GL_TRIANGLE_STRIP, 60, GL_UNSIGNED_INT, (GLuint*)0+4227);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+4287);
	glDrawElements(GL_TRIANGLE_STRIP, 23, GL_UNSIGNED_INT, (GLuint*)0+4290);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+4313);
	glDrawElements(GL_TRIANGLE_STRIP, 26, GL_UNSIGNED_INT, (GLuint*)0+4316);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+4342);
	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (GLuint*)0+4345);
	glDrawElements(GL_TRIANGLE_STRIP, 947, GL_UNSIGNED_INT, (GLuint*)0+4351);
	glDrawElements(GL_TRIANGLE_STRIP, 35, GL_UNSIGNED_INT, (GLuint*)0+5298);
	glDrawElements(GL_TRIANGLE_STRIP, 31, GL_UNSIGNED_INT, (GLuint*)0+5333);
	glDrawElements(GL_TRIANGLE_STRIP, 27, GL_UNSIGNED_INT, (GLuint*)0+5364);
	glDrawElements(GL_TRIANGLE_STRIP, 23, GL_UNSIGNED_INT, (GLuint*)0+5391);
	glDrawElements(GL_TRIANGLE_STRIP, 20, GL_UNSIGNED_INT, (GLuint*)0+5414);
	glDrawElements(GL_TRIANGLE_STRIP, 24, GL_UNSIGNED_INT, (GLuint*)0+5434);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5458);
	glDrawElements(GL_TRIANGLE_STRIP, 28, GL_UNSIGNED_INT, (GLuint*)0+5461);
	glDrawElements(GL_TRIANGLE_STRIP, 32, GL_UNSIGNED_INT, (GLuint*)0+5489);
	glDrawElements(GL_TRIANGLE_STRIP, 36, GL_UNSIGNED_INT, (GLuint*)0+5521);
	glDrawElements(GL_TRIANGLE_STRIP, 76, GL_UNSIGNED_INT, (GLuint*)0+5557);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5633);
	glDrawElements(GL_TRIANGLE_STRIP, 67, GL_UNSIGNED_INT, (GLuint*)0+5636);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5703);
	glDrawElements(GL_TRIANGLE_STRIP, 59, GL_UNSIGNED_INT, (GLuint*)0+5706);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5765);
	glDrawElements(GL_TRIANGLE_STRIP, 51, GL_UNSIGNED_INT, (GLuint*)0+5768);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5819);
	glDrawElements(GL_TRIANGLE_STRIP, 43, GL_UNSIGNED_INT, (GLuint*)0+5822);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5865);
	glDrawElements(GL_TRIANGLE_STRIP, 35, GL_UNSIGNED_INT, (GLuint*)0+5868);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5903);
	glDrawElements(GL_TRIANGLE_STRIP, 27, GL_UNSIGNED_INT, (GLuint*)0+5906);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5933);
	glDrawElements(GL_TRIANGLE_STRIP, 19, GL_UNSIGNED_INT, (GLuint*)0+5936);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5955);
	glDrawElements(GL_TRIANGLE_STRIP, 11, GL_UNSIGNED_INT, (GLuint*)0+5958);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+5969);
	glDrawElements(GL_TRIANGLE_STRIP, 30, GL_UNSIGNED_INT, (GLuint*)0+5972);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+6002);
	glDrawElements(GL_TRIANGLE_STRIP, 11, GL_UNSIGNED_INT, (GLuint*)0+6005);
	glDrawElements(GL_TRIANGLE_STRIP, 18, GL_UNSIGNED_INT, (GLuint*)0+6016);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+6034);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+6037);
	glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (GLuint*)0+6040);
	glDrawElements(GL_TRIANGLE_STRIP, 122, GL_UNSIGNED_INT, (GLuint*)0+6045);
	glDrawElements(GL_TRIANGLE_STRIP, 75, GL_UNSIGNED_INT, (GLuint*)0+6167);
	glDrawElements(GL_TRIANGLE_STRIP, 71, GL_UNSIGNED_INT, (GLuint*)0+6242);
	glDrawElements(GL_TRIANGLE_STRIP, 67, GL_UNSIGNED_INT, (GLuint*)0+6313);
	glDrawElements(GL_TRIANGLE_STRIP, 63, GL_UNSIGNED_INT, (GLuint*)0+6380);
	glDrawElements(GL_TRIANGLE_STRIP, 59, GL_UNSIGNED_INT, (GLuint*)0+6443);
	glDrawElements(GL_TRIANGLE_STRIP, 55, GL_UNSIGNED_INT, (GLuint*)0+6502);
	glDrawElements(GL_TRIANGLE_STRIP, 51, GL_UNSIGNED_INT, (GLuint*)0+6557);
	glDrawElements(GL_TRIANGLE_STRIP, 47, GL_UNSIGNED_INT, (GLuint*)0+6608);
	glDrawElements(GL_TRIANGLE_STRIP, 43, GL_UNSIGNED_INT, (GLuint*)0+6655);
	glDrawElements(GL_TRIANGLE_STRIP, 39, GL_UNSIGNED_INT, (GLuint*)0+6698);
	glDrawElements(GL_TRIANGLE_STRIP, 35, GL_UNSIGNED_INT, (GLuint*)0+6737);
	glDrawElements(GL_TRIANGLE_STRIP, 31, GL_UNSIGNED_INT, (GLuint*)0+6772);
	glDrawElements(GL_TRIANGLE_STRIP, 27, GL_UNSIGNED_INT, (GLuint*)0+6803);
	glDrawElements(GL_TRIANGLE_STRIP, 23, GL_UNSIGNED_INT, (GLuint*)0+6830);
	glDrawElements(GL_TRIANGLE_STRIP, 19, GL_UNSIGNED_INT, (GLuint*)0+6853);
	glDrawElements(GL_TRIANGLE_STRIP, 15, GL_UNSIGNED_INT, (GLuint*)0+6872);
	glDrawElements(GL_TRIANGLE_STRIP, 11, GL_UNSIGNED_INT, (GLuint*)0+6887);
	glDrawElements(GL_TRIANGLE_STRIP, 7, GL_UNSIGNED_INT, (GLuint*)0+6898);

	glDisableVertexAttribArray(vNormalHandle);
	glDisableVertexAttribArray(vVertexHandle);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
