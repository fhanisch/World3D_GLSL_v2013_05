#include "Renderer.h"

Renderer::Renderer(CAMERA *camera, ORIENTATION *orientation, GLuint font)
{
    startTime=0;
    fpsCount=0;
	loadShader();
	textShaderProgram = Shader::createShaderProgram(textVertexShader, testFragmentShader);
	schrift=font;
    cam=camera;
	ori=orientation;

	apfel = new MeshBufferObject(apfelVertexShader, adsPerFragmentShader);
	plane = new MeshBufferObject(planeVertexShader, adsPerFragmentShader);
	sphere = new MeshBufferObject(sphereVertexShader, adsPerFragmentShader);
	planet = new MeshBufferObject(sphereVertexShader, adsPerFragmentShader);
	ei = new MeshBufferObject(eiVertexShader, adsPerFragmentShader);
	wave = new MeshBufferObject(waveVertexShader, adsPerFragmentShader);
	curve = new Curve();
	bezier = new Bezier();
	gradNoise = new Perlin1d("src\\shader\\gradientnoise.vert", "src\\shader\\gradientnoise.geo");
	perlin1d = new Perlin1d("src\\shader\\perlin1d.vert", "src\\shader\\perlin1d.geo");
	perlin1d->setColor(1.0,0.0,0.0);
	perlinmod1d = new Perlin1d("src\\shader\\perlin1d.vert", "src\\shader\\perlinmod1d.geo");
	perlinmod1d->setColor(0.0,1.0,0.0);
	dreieck = new Dreieck();
	quad = new Rechteck();
	perlin2d = new Perlin2d();
	terrain = new MeshPerlin2d("src\\shader\\mesh_perlin2d.vert");
	teapot = new Teapot();
	bezierCurveTesselator = new BezierCurveTesselator();
	boden = new TessPlane(genericVertexShader, adsPerFragmentShaderTex);
	tessTestObject = new TessTestObject();
	teapotPatches = new TeapotPatches(genericVertexShader);
	tessModel = new TessModel(genericVertexShader, adsPerFragmentShader);
	fighter = new TessModel(genericVertexShader, calcNormalsGeometryShader, adsPerFragmentShader);
	mandelbrot = new TessPlane(genericVertexShader, mandelbrotFragmentShader);

	createMeshGrid(101,101);
	createMeshGridIndices();
	createMeshGridGradients();

	mProjection.setFrustum(0.25*(double)WND_WIDTH/(double)WND_HEIGHT,0.25,0.5,100000.0);
	mView[ori->viewIndex].translate(0.0,-100001.0,0.0);

	apfel->mModel.translate(0.0,100002.0,-10.0);
    plane->setColor(0.0,0.0,1.0);
	plane->mModel.translate(0.0,-5.0,0.0);
	sphere->setColor(1.0,0.0,0.0);
	sphere->mModel.translate(0.0, 100002.0, 10.0);
	sphere->arg1=1.0;
	planet->setColor(0.4f,0.2f,0.0f);
	planet->arg1=100000.0;
	boden->mModel.translate(0.0, 100000.0, 0.0);
	boden->setDepthFunc(GL_ALWAYS);
	ei->setColor(1.0,1.0,0.0);
	ei->mModel.translate(-10.0, 100000.0, 0.0);
	wave->setColor(0.3333f, 0.10196f,  0.5451f);
	wave->mModel.translate(10.0, 100002.0, 0.0);
	terrain->setColor(0.5f,0.5f,0.5f);
	tessTestObject->setColor(0.5,0.5,0.5);
	teapot->mModel.translate(5.0,10.0,0.0);
	teapotPatches->mModel.rotateX(-PI/2);
	teapotPatches->mModel.translate(0.0,100001.0,0.0);

	vessel = new Vessel(fighter, vec3(0.0,105000,0), vec3(0.0,0.0,0.0),ori);
	vessel->startSimulation();

	overallStartTime=clock();
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (ori->viewIndex==0)
    {
        mView[0].rotateX(cam->xAngle);

        mView[0].rotateX(vec3::cross(mView[0].getXAxis(),mView[0].getZAxis())[0]*cam->yAngle);
        mView[0].rotateY(vec3::cross(mView[0].getXAxis(),mView[0].getZAxis())[1]*cam->yAngle);
        mView[0].rotateZ(vec3::cross(mView[0].getXAxis(),mView[0].getZAxis())[2]*cam->yAngle);

        mView[0].translate(cam->yPos, 0.0, cam->xPos);
        mView[0].translate(vec3::cross(mView[0].getXAxis(),mView[0].getZAxis())[0]*cam->zPos,
                        vec3::cross(mView[0].getXAxis(),mView[0].getZAxis())[1]*cam->zPos,
                        vec3::cross(mView[0].getXAxis(),mView[0].getZAxis())[2]*cam->zPos);
    }
    vessel->render(&mProjection,mView);
	tessModel->mModel.setIdentity();
	/*
	tessModel->mModel.rotateX(ori->xAngle);
	tessModel->mModel.rotateY(ori->yAngle);
	*/
	tessModel->mModel.translate(10.0,100005.0,10.0);

	//plane->renderMBO(mProjection,mView);
	planet->renderMBO(mProjection,mView[ori->viewIndex]);
	boden->renderVBO(mProjection, mView[ori->viewIndex]);
	apfel->renderMBO(mProjection,mView[ori->viewIndex]);
	sphere->renderMBO(mProjection,mView[ori->viewIndex]);
	ei->renderMBO(mProjection,mView[ori->viewIndex]);
	wave->renderMBO(mProjection,mView[ori->viewIndex]);
	wave->arg1+=0.01f;
	teapotPatches->renderVBO(mProjection, mView[ori->viewIndex]);
	tessModel->renderVBO(mProjection, mView[ori->viewIndex]);
	//curve->renderVBO(mProjection, Matrix4());
	//bezier->renderVBO(mProjection, Matrix4());
	//gradNoise->renderVBO(mProjection, Matrix4());
	//perlin1d->renderVBO(mProjection, Matrix4());
	//perlinmod1d->renderVBO(mProjection, Matrix4());
	//dreieck->renderVBO(mProjection, Matrix4());
	//quad->renderVBO(mProjection, Matrix4());
	//perlin2d->renderVBOTex(mProjection, mView);
	//terrain->renderMBOGrad(mProjection, mView);
	//teapot->renderTeapotVBO(mProjection,mView);
	//bezierCurveTesselator->renderVBO(mProjection, Matrix4());
	//tessTestObject->renderMBOGrad(mProjection, mView);
	//mandelbrot->renderVBO(mProjection, Matrix4());
	renderText("Time: %.1f s", (double)currentTime/(double)CLOCKS_PER_SEC, 0.0f, 0.0f, vec4(0.0,1.0,0.0),mProjection);
	renderText("Fighter PosX: %.2f m",fighter->mModel[12],0.0f,0.1f,vec4(0.0,1.0,0.0),mProjection);
	renderText("Fighter PosY: %.2f m",fighter->mModel[13],0.0f,0.125f,vec4(0.0,1.0,0.0),mProjection);
	renderText("Fighter PosZ: %.2f m",fighter->mModel[14],0.0f,0.15f,vec4(0.0,1.0,0.0),mProjection);
	renderText("Fighter VelX: %.2f m/s",vessel->velocity[0],0.0f,0.2f,vec4(0.0,1.0,0.0),mProjection);
	renderText("Fighter VelY: %.2f m/s",vessel->velocity[1],0.0f,0.225f,vec4(0.0,1.0,0.0),mProjection);
	renderText("Fighter VelZ: %.2f m/s",vessel->velocity[2],0.0f,0.25f,vec4(0.0,1.0,0.0),mProjection);
    renderText("Fighter R: %.2f m", vessel->R,0.0f,0.3f,vec4(0.0,1.0,0.0),mProjection);
    renderText("Fighter psi: %.2f rad", vessel->psi,0.0f,0.325f,vec4(0.0,1.0,0.0),mProjection);
    renderText("Fighter phi: %.2f rad", vessel->phi,0.0f,0.35f,vec4(0.0,1.0,0.0),mProjection);
    renderText("Fighter rotX: %.2f rad", vessel->rotation[0],0.0f,0.375f,vec4(0.0,1.0,0.0),mProjection);
    renderText("Fighter rotY: %.2f rad", vessel->rotation[1],0.0f,0.4f,vec4(0.0,1.0,0.0),mProjection);

	calcFPS();
	renderText("Framerate: %.0f fps",(double)FPS,1.85f,0.0f,vec4(1.0,0.0,0.0),mProjection);
	fpsCount++;
}

void Renderer::loadShader()
{
	genericVertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\vertexshader.vert","generic");
	textVertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\vertexshader.vert","text");
	apfelVertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\parametric_functions.vert","apfel");
	sphereVertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\parametric_functions.vert","sphere");
	eiVertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\parametric_functions.vert","ei");
	waveVertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\parametric_functions.vert","wave");
	planeVertexShader = Shader::createShader(GL_VERTEX_SHADER,"src\\shader\\parametric_functions.vert","plane");
	adsPerFragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\fragmentshader.frag","ads_per_fragment");
	adsPerFragmentShaderTex = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\fragmentshader.frag","_ads_per_fragment_tex");
	testFragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\fragmentshader.frag","test");
	genericGeometryShader = Shader::createShader(GL_GEOMETRY_SHADER,"src\\shader\\geometryshader.geo","generic");
	calcNormalsGeometryShader = Shader::createShader(GL_GEOMETRY_SHADER,"src\\shader\\geometryshader.geo","calc_normals");
	mandelbrotFragmentShader = Shader::createShader(GL_FRAGMENT_SHADER,"src\\shader\\fragmentshader.frag","mandelbrot");
}

void Renderer::renderText(char *text, double value, GLfloat posX, GLfloat posY, vec4 color, mat4 mProjection)
{
	glRasterPos2f(-1.0f+posX,0.98f-posY);

    glUseProgram(textShaderProgram);

	GLuint mProjectionHandle = glGetUniformLocation(textShaderProgram,"mProjection");
	glUniformMatrix4dv(mProjectionHandle,1,false,mProjection.get());

	GLuint vColorHandle = glGetUniformLocation(textShaderProgram,"vColor");
	glUniform4dv(vColorHandle,1,color.get());

    char str[256];
    sprintf_s(str,256,text,value);
    glPushAttrib(GL_LIST_BIT); 		// Pushes The Display List Bits ( NEW )
	glListBase(schrift - 32); 			// Sets The Base Character to 32 ( NEW )
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); // Draws The Display List    Text ( NEW )
	glPopAttrib(); // Pops The Display List Bits ( NEW )
}

void Renderer::calcFPS()
{
    currentTime=clock()-overallStartTime;
	if((currentTime-startTime)/CLOCKS_PER_SEC>=1)
	{
		FPS=fpsCount;
		startTime=currentTime;
		fpsCount=0;
	}
}
