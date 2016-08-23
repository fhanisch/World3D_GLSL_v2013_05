#include "MeshBufferObject.h"


void createMeshGrid(int m, int n)
{
	v_max=m;
	u_max=n;

	u=new GLfloat[m*n];
	v=new GLfloat[m*n];
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
		{
			u[i*n+j]=(float)j/((float)n-1);
			v[j*m+i]=(float)j/((float)m-1);
		}

	createMBO();
}

void createMeshGridIndices()
{
	indicesMeshLength=3*2*(v_max-1)*(u_max-1);
	indices = new GLuint[indicesMeshLength];
	for(unsigned int i=0;i<v_max-1;i++)
		for(unsigned int j=0;j<u_max-1;j++)
		{
			indices[6*(i*(u_max-1)+j)+0]=i*u_max+j;
			indices[6*(i*(u_max-1)+j)+1]=i*u_max+j+1;
			indices[6*(i*(u_max-1)+j)+2]=(i+1)*u_max+j;

			indices[6*(i*(u_max-1)+j)+3]=i*u_max+j+1;
			indices[6*(i*(u_max-1)+j)+4]=(i+1)*u_max+j;
			indices[6*(i*(u_max-1)+j)+5]=(i+1)*u_max+j+1;
		}
	createMeshGridIBO();
}

void createMeshGridGradients()
{
	gradientsLength=2*v_max*u_max;
	gradients = new GLfloat[gradientsLength];
	for(unsigned int i=0;i<gradientsLength;i++) gradients[i]=2.0f*(float)(rand()%1000)/1000.0f-1.0f;
	createGBO();
}

void createMBO() // Mesh Grid Buffer Object
{
	glGenBuffers(2,mboID);

	glBindBuffer(GL_ARRAY_BUFFER,mboID[0]);
	glBufferData(GL_ARRAY_BUFFER,u_max*v_max*sizeof(GLfloat),u,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,mboID[1]);
	glBufferData(GL_ARRAY_BUFFER,v_max*u_max*sizeof(GLfloat),v,GL_STATIC_DRAW);
}

void createMeshGridIBO() // Index Buffer Object
{
	glGenBuffers(1,&iboMeshID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboMeshID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesMeshLength*sizeof(GLuint), indices, GL_STATIC_DRAW);
}

void createGBO() // Gradients Buffer Object
{
	glGenBuffers(1,&gboID);

	glBindBuffer(GL_ARRAY_BUFFER, gboID);
	glBufferData(GL_ARRAY_BUFFER, gradientsLength*sizeof(GLfloat), gradients, GL_STATIC_DRAW);
}

void setVertices(GLfloat *ptr)
{
	vertices=ptr;
}

void setNormals(GLfloat *ptr)
{
	normals=ptr;
}

void setIndices(GLuint *ptr)
{
	indices=ptr;
}

BufferObject::BufferObject()
{
	arg1=0;
	maxPatchVertices=4;
	texID=0;
	depthFunc=GL_LESS;
}

void BufferObject::createVBO() // Vertex Buffer Object
{
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER, verticesLength*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
}

void BufferObject::createNBO() // Normal Buffer Object
{
	glGenBuffers(1,&nboID);
	glBindBuffer(GL_ARRAY_BUFFER, nboID);
	glBufferData(GL_ARRAY_BUFFER, normalsLength*sizeof(GLfloat), normals, GL_STATIC_DRAW);
}

void BufferObject::createIBO() // Index Buffer Object
{
	glGenBuffers(1,&iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength*sizeof(GLuint), indices, GL_STATIC_DRAW);
}

void BufferObject::createTCO() // TexCoord Buffer Object
{
	glGenBuffers(1,&tcoID);
	glBindBuffer(GL_ARRAY_BUFFER, tcoID);
	glBufferData(GL_ARRAY_BUFFER, texCoordsLength*sizeof(GLfloat), texCoords, GL_STATIC_DRAW);
}

int BufferObject::loadTexture(char *filename)
{
	FILE *file;
	char signature[2];
	long farbtiefe;
	unsigned int offset, buf_ptr=0;

	if (fopen_s(&file,filename,"rb") != 0) return 1;
	fseek(file,0,SEEK_SET);
	fread(signature,2,1,file);
	if( signature[0] != 'B' || signature[1] != 'M' ) return 1;
	fseek(file,28,SEEK_SET);
	fread(&farbtiefe,2,1,file);
	fseek(file,18,SEEK_SET);
	fread(&tex_x_size,4,1,file);
	fread(&tex_y_size,4,1,file);
	texture = new GLubyte[tex_x_size*tex_y_size*4];
	fseek(file,10,SEEK_SET);
	fread(&offset,4,1,file);
	fseek(file,offset,SEEK_SET);
	for( long y=0 ; y<tex_y_size ; y++ )
	{
		for( long x=0 ; x<tex_x_size ; x++ )
		{
			fread(texture+buf_ptr+2,1,1,file);
			fread(texture+buf_ptr+1,1,1,file);
			fread(texture+buf_ptr,1,1,file);
			texture[buf_ptr+3]=0xff;
			buf_ptr+=4;
		}
		fseek(file,tex_x_size%4,SEEK_CUR);
	}

	fclose(file);
	return 0;
}

void BufferObject::bindTexture()
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, tex_x_size, tex_y_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
}

void BufferObject::renderVBO(mat4 mProjection, mat4 mView)
{
	glPatchParameteri(GL_PATCH_VERTICES,maxPatchVertices);

	glUseProgram(shaderProgram);

	glDepthFunc(depthFunc);

	glBindTexture(GL_TEXTURE_2D,texID);

	mProjectionHandle = glGetUniformLocation(shaderProgram,"mProjection");
	glUniformMatrix4dv(mProjectionHandle,1,false,mProjection.get());

	mViewHandle = glGetUniformLocation(shaderProgram,"mView");
	glUniformMatrix4dv(mViewHandle,1,false,mView.get());

	mModelHandle = glGetUniformLocation(shaderProgram,"mModel");
	glUniformMatrix4dv(mModelHandle,1,false,mModel.get());

	mModelViewHandle = glGetUniformLocation(shaderProgram,"mModelView");
	glUniformMatrix4dv(mModelViewHandle,1,false,(mView*mModel).get());

	vColorHandle = glGetUniformLocation(shaderProgram,"vColor");
	glUniform4fv(vColorHandle,1,color);

	textureHandle = glGetUniformLocation(shaderProgram,"samp");
	glUniform1i(textureHandle,0);

	vVertexHandle = glGetAttribLocation(shaderProgram,"vVertex");
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glVertexAttribPointer(vVertexHandle, 3, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	//glIndexPointer(GL_UNSIGNED_INT,0,0); // scheinbar nicht notwendig (nicht mehr im OpenGL Core Profile)

	glEnableVertexAttribArray(vVertexHandle);

	glDrawElements(renderMode, indicesLength, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(vVertexHandle);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glBindTexture(GL_TEXTURE_2D,0);
}

void BufferObject::renderVBOTex(mat4 mProjection, mat4 mView)
{
	glUseProgram(shaderProgram);

    glDepthFunc(depthFunc);

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

	vTexCoordHandle = glGetAttribLocation(shaderProgram,"vTexCoord");
	glBindBuffer(GL_ARRAY_BUFFER, tcoID);
	glVertexAttribPointer(vTexCoordHandle, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	//glIndexPointer(GL_UNSIGNED_INT,0,0); // scheinbar nicht notwendig (nicht mehr im OpenGL Core Profile)

	glEnableVertexAttribArray(vVertexHandle);
	glEnableVertexAttribArray(vTexCoordHandle);

	glDrawElements(renderMode, indicesLength, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(vTexCoordHandle);
	glDisableVertexAttribArray(vVertexHandle);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void BufferObject::renderMBO(mat4 mProjection, mat4 mView)
{
	glUseProgram(shaderProgram);

	glDepthFunc(depthFunc);

	mProjectionHandle = glGetUniformLocation(shaderProgram,"mProjection");
	glUniformMatrix4dv(mProjectionHandle,1,false,mProjection.get());

	mViewHandle = glGetUniformLocation(shaderProgram,"mView");
	glUniformMatrix4dv(mViewHandle,1,false,mView.get());

	mModelHandle = glGetUniformLocation(shaderProgram,"mModel");
	glUniformMatrix4dv(mModelHandle,1,false,mModel.get());

	mModelViewHandle = glGetUniformLocation(shaderProgram,"mModelView");
	glUniformMatrix4dv(mModelViewHandle,1,false,(mView*mModel).get());

	vColorHandle = glGetUniformLocation(shaderProgram,"vColor");
	glUniform4fv(vColorHandle,1,color);

	fArg1Handle = glGetUniformLocation(shaderProgram,"arg1");
	glUniform1f(fArg1Handle, arg1);

	fMeshHandleU = glGetAttribLocation(shaderProgram,"mesh_u");
	glBindBuffer(GL_ARRAY_BUFFER,mboID[0]);
	glVertexAttribPointer(fMeshHandleU, 1, GL_FLOAT, false, 0, 0);

	fMeshHandleV = glGetAttribLocation(shaderProgram,"mesh_v");
	glBindBuffer(GL_ARRAY_BUFFER,mboID[1]);
	glVertexAttribPointer(fMeshHandleV, 1, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboMeshID);
	//glIndexPointer(GL_UNSIGNED_INT,0,0); // scheinbar nicht notwendig (nicht mehr im OpenGL Core Profile)

	glEnableVertexAttribArray(fMeshHandleU);
	glEnableVertexAttribArray(fMeshHandleV);

	glDrawElements(renderMode, indicesMeshLength, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(fMeshHandleV);
	glDisableVertexAttribArray(fMeshHandleU);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void BufferObject::renderMBOGrad(mat4 mProjection, mat4 mView)
{
	glPatchParameteri(GL_PATCH_VERTICES,maxPatchVertices);

	glUseProgram(shaderProgram);

    glDepthFunc(depthFunc);

	mProjectionHandle = glGetUniformLocation(shaderProgram,"mProjection");
	glUniformMatrix4dv(mProjectionHandle,1,false,mProjection.get());

	mViewHandle = glGetUniformLocation(shaderProgram,"mView");
	glUniformMatrix4dv(mViewHandle,1,false,mView.get());

	mModelHandle = glGetUniformLocation(shaderProgram,"mModel");
	glUniformMatrix4dv(mModelHandle,1,false,mModel.get());

	vColorHandle = glGetUniformLocation(shaderProgram,"vColor");
	glUniform4fv(vColorHandle,1,color);

	fArg1Handle = glGetUniformLocation(shaderProgram,"arg1");
	glUniform1f(fArg1Handle, arg1);

	fMeshHandleU = glGetAttribLocation(shaderProgram,"mesh_u");
	glBindBuffer(GL_ARRAY_BUFFER,mboID[0]);
	glVertexAttribPointer(fMeshHandleU, 1, GL_FLOAT, false, 0, 0);

	fMeshHandleV = glGetAttribLocation(shaderProgram,"mesh_v");
	glBindBuffer(GL_ARRAY_BUFFER,mboID[1]);
	glVertexAttribPointer(fMeshHandleV, 1, GL_FLOAT, false, 0, 0);

	vGradientHandle = glGetAttribLocation(shaderProgram,"vGradient");
	glBindBuffer(GL_ARRAY_BUFFER, gboID);
	glVertexAttribPointer(vGradientHandle, 2, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboMeshID);
	//glIndexPointer(GL_UNSIGNED_INT,0,0); // scheinbar nicht notwendig (nicht mehr im OpenGL Core Profile)

	glEnableVertexAttribArray(fMeshHandleU);
	glEnableVertexAttribArray(fMeshHandleV);
	glEnableVertexAttribArray(vGradientHandle);

	glDrawElements(renderMode, indicesMeshLength, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(vGradientHandle);
	glDisableVertexAttribArray(fMeshHandleV);
	glDisableVertexAttribArray(fMeshHandleU);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

Curve::Curve()
{
	int n=201;

	vertices = new GLfloat[3*n];
	verticesLength = 3*n;
	for(int i=0;i<n;i++) vertices[3*i]=(float)i/((float)n-1);

	indices = new GLuint[n];
	indicesLength=n;
	for(int i=0;i<n;i++) indices[i]=i;

	color[0]=1.0f;color[1]=0.0f;color[2]=0.0f;color[3]=1.0f;

	createVBO();
	createIBO();

	renderMode = GL_LINE_STRIP;

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\curve.vert");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\test.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader, fragmentShader);
}

Bezier::Bezier()
{
	GLfloat verts[]={ 0.5f,-0.5f,-2.0f,
					 -0.5f,-0.5f,-2.0f,
					 -0.5f, 0.5f,-2.0f,
					  0.5f, 0.5f,-2.0f};

	vertices=verts;
	verticesLength = 12;

	GLuint inds[]={0,1,2,3};
	indices=inds;
	indicesLength=4;

	color[0]=0.0f;color[1]=1.0f;color[2]=0.0f;color[3]=1.0f;

	createVBO();
	createIBO();

	renderMode = GL_LINE_STRIP_ADJACENCY;

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\bezier.vert");
	geometryShader = Shader::createShader(GL_GEOMETRY_SHADER,"src\\shader\\bezier.geo");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\test.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader,geometryShader, fragmentShader);
}

BezierCurveTesselator::BezierCurveTesselator()
{
	GLfloat verts[]={ 0.5f,-0.5f,-2.0f,
					 -0.5f,-0.5f,-2.0f,
					 -0.5f, 0.5f,-2.0f,
					  0.5f, 0.5f,-2.0f};

	vertices=verts;
	verticesLength = 12;

	GLuint inds[]={0,1,2,3};
	indices=inds;
	indicesLength=4;

	color[0]=0.0f;color[1]=1.0f;color[2]=1.0f;color[3]=1.0f;

	createVBO();
	createIBO();

	maxPatchVertices=4;
	renderMode = GL_PATCHES;

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\bezier.vert");
	tesselationControlShader = Shader::createShader(GL_TESS_CONTROL_SHADER,"src\\shader\\bezier.tcs");
	tesselationEvaluationShader = Shader::createShader(GL_TESS_EVALUATION_SHADER,"src\\shader\\bezier.tes");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\test.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader,tesselationControlShader,tesselationEvaluationShader,fragmentShader);
}

Perlin1d::Perlin1d(char *vertexShaderName, char *geometryShaderName)
{
	int n=11;
	vertices = new GLfloat[3*n];
	verticesLength=3*n;
	indices = new GLuint[n];
	indicesLength=n;

	GLfloat g[]={-0.9076f,	-0.8057f,	0.6469f,	0.3896f,	-0.3658f,	0.9004f,	-0.9311f,
		-0.1225f,	-0.2368f,	0.5310f,	0.5904f};

	for(int i=0;i<n;i++)
	{
		vertices[3*i]=(float)i;
		vertices[3*i+1]=g[i];
	}
	for(int i=0;i<n;i++) indices[i]=i;

	color[0]=1.0f;color[1]=1.0f;color[2]=0.0f;color[3]=1.0f;

	createVBO();
	createIBO();

	renderMode = GL_LINE_STRIP;

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,vertexShaderName);
	geometryShader = Shader::createShader(GL_GEOMETRY_SHADER,geometryShaderName);
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\test.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader,geometryShader, fragmentShader);
}

Dreieck::Dreieck()
{
	GLfloat verts[] = {-0.5f,-0.5f,-2.0f,0.5f,-0.5f,-2.0f,-0.5f,0.5f,-2.0f};
	vertices = verts;
	verticesLength=9;
	GLuint inds[] = {0,1,2};
	indices=inds;
	indicesLength=3;

	color[0]=1.0f;color[1]=1.0f;color[2]=0.0f;color[3]=1.0f;

	createVBO();
	createIBO();

	renderMode = GL_TRIANGLES;

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\subdivision.vert");
	geometryShader = Shader::createShader(GL_GEOMETRY_SHADER,"src\\shader\\subdivision.geo");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\test.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader,geometryShader, fragmentShader);
}

Rechteck::Rechteck()
{
	GLfloat verts[] = {-0.5f,-0.5f,-2.0f, 0.5f,-0.5f,-2.0f, -0.5f,0.5f,-2.0f, 0.5f,0.5f,-2.0f};
	vertices = verts;
	verticesLength=12;

	GLuint inds[] = {0,1,2, 0,0,0};
	indices=inds;
	indicesLength=6;

	color[0]=1.0f;color[1]=0.0f;color[2]=0.0f;color[3]=1.0f;

	renderMode = GL_TRIANGLES_ADJACENCY;

	createVBO();
	createIBO();

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\subdivision.vert");
	geometryShader = Shader::createShader(GL_GEOMETRY_SHADER,"src\\shader\\quad_test.geo");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\test.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader,geometryShader, fragmentShader);
}

TessPlane::TessPlane(GLuint vertexShader, GLuint fragmentShader)
{
	GLfloat verts[]={ -20.0f,0.0,-20.0f,
					   20.0f,0.0,-20.0f,
					  -20.0f,0.0, 20.0f,
					   20.0f,0.0, 20.0f};

	/*GLfloat verts[]={ -1.0f,-1.0,-2.0f,
					   1.0f,-1.0,-2.0f,
					  -1.0f,1.0,-2.0f,
					   1.0f,1.0,-2.0f};*/

	vertices=verts;
	verticesLength = 12;

	GLuint inds[]={0,1,2,3};
	indices=inds;
	indicesLength=4;

	loadTexture("src\\res\\boden.bmp");
	bindTexture();

	color[0]=1.0f;color[1]=1.0f;color[2]=1.0f;color[3]=1.0f;

	createVBO();
	createIBO();

	maxPatchVertices=4;
	renderMode = GL_PATCHES;

	tesselationControlShader = Shader::createShader(GL_TESS_CONTROL_SHADER,"src\\shader\\rechteck.tcs");
	tesselationEvaluationShader = Shader::createShader(GL_TESS_EVALUATION_SHADER,"src\\shader\\rechteck.tes");

	shaderProgram = Shader::createShaderProgram(vertexShader,tesselationControlShader,tesselationEvaluationShader,fragmentShader);
}

TessModel::TessModel(GLuint vertexShader, GLuint fragmentShader)
{
	MODELDATA md;
	loadModel(&md, "src\\res\\suzanne.x");

	verticesLength=md.verticesLength;
	vertices=md.vertices;
	indicesLength=md.indicesLength;
	indices=md.indices;

	loadTexture("src\\res\\boden.bmp");
	bindTexture();

	color[0]=0.0f;color[1]=1.0f;color[2]=0.0f;color[3]=1.0f;

	createVBO();
	createIBO();

	maxPatchVertices=4;
	renderMode = GL_PATCHES;

	tesselationControlShader = Shader::createShader(GL_TESS_CONTROL_SHADER,"src\\shader\\rechteck.tcs");
	tesselationEvaluationShader = Shader::createShader(GL_TESS_EVALUATION_SHADER,"src\\shader\\xmodel.tes");
	shaderProgram = Shader::createShaderProgram(vertexShader,tesselationControlShader,tesselationEvaluationShader,fragmentShader);
}

TessModel::TessModel(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
{
	MODELDATA md;
	loadModel(&md, "src\\res\\fighter.x");

	verticesLength=md.verticesLength;
	vertices=md.vertices;
	indicesLength=md.indicesLength;
	indices=md.indices;

	loadTexture("src\\res\\boden.bmp");
	bindTexture();

	color[0]=0.2f;color[1]=0.2f;color[2]=0.2f;color[3]=1.0f;

	createVBO();
	createIBO();

	renderMode = GL_TRIANGLES;

	shaderProgram = Shader::createShaderProgram(vertexShader, geometryShader, fragmentShader);
}

Perlin2d::Perlin2d()
{
	int n=3;
	int m=3;
	GLfloat verts[] = {	0.0f,0.0f,0.0f, 1.0f,0.0f,0.0f, 2.0f,0.0f,0.0f,
						0.0f,0.0f,1.0f, 1.0f,0.0f,1.0f, 2.0f,0.0f,1.0f,
						0.0f,0.0f,2.0f, 1.0f,0.0f,2.0f, 2.0f,0.0f,2.0f
					  };
	vertices = verts;
	verticesLength=3*n*m;

	texCoords=new GLfloat[2*n*m];
	for(int i=0;i<2*n*m;i++) texCoords[i]=2.0f*(float)(rand()%1000)/1000.0f-1.0f;
	texCoordsLength=2*n*m;

	GLuint inds[] = {0,1,3, 0,0,4, 1,2,4, 0,0,5, 3,4,6, 0,0,7, 4,5,7, 0,0,8};
	indices=inds;
	indicesLength=(n-1)*(m-1)*6;

	color[0]=1.0f;color[1]=0.0f;color[2]=0.0f;color[3]=1.0f;

	renderMode = GL_TRIANGLES_ADJACENCY;

	createVBO();
	createIBO();
	createTCO();

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\perlin2d.vert");
	geometryShader = Shader::createShader(GL_GEOMETRY_SHADER,"src\\shader\\perlinmod2d.geo");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\ads_per_fragment.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader,geometryShader, fragmentShader);

}

MeshBufferObject::MeshBufferObject(GLuint vertexShader, GLuint fragmentShader)
{
	color[0]=0.0f;color[1]=1.0f;color[2]=0.0f;color[3]=1.0f;

	renderMode = GL_TRIANGLES;

	shaderProgram = Shader::createShaderProgram(vertexShader, fragmentShader);
}

MeshPerlin2d::MeshPerlin2d(char *vertexShaderName)
{
	color[0]=0.0f;color[1]=1.0f;color[2]=0.0f;color[3]=1.0f;

	renderMode = GL_TRIANGLES_ADJACENCY;

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,vertexShaderName);
	geometryShader = Shader::createShader(GL_GEOMETRY_SHADER,"src\\shader\\perlinmod2d.geo");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\ads_per_fragment.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader,geometryShader, fragmentShader);
}

TessTestObject::TessTestObject()
{
	GLfloat verts[]={ -0.5f,-0.5f,-2.0f,
					   0.5f,-0.5f,-2.0f,
					  -0.5f, 0.5f,-2.0f,
					   0.5f, 0.5f,-2.0f,
					   0.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 0.0f
					 };

	vertices=verts;
	verticesLength = 18;

	GLuint inds[]={0,1,2,3,4,5};
	indices=inds;
	indicesLength=6;

	color[0]=1.0f;color[1]=1.0f;color[2]=1.0f;color[3]=1.0f;

	createVBO();
	createIBO();

	maxPatchVertices=6;
	renderMode = GL_PATCHES;

	vertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\tess_test.vert");
	tesselationControlShader = Shader::createShader(GL_TESS_CONTROL_SHADER,"src\\shader\\tess_test.tcs");
	tesselationEvaluationShader = Shader::createShader(GL_TESS_EVALUATION_SHADER,"src\\shader\\tess_test.tes");
	fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\ads_per_fragment.frag");
	shaderProgram = Shader::createShaderProgram(vertexShader,tesselationControlShader,tesselationEvaluationShader,fragmentShader);
}

void BufferObject::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	color[0]=r; color[1]=g; color[2]=b;
}

void BufferObject::setDepthFunc(GLenum func)
{
    depthFunc=func;
}

