uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

attribute vec4 vVertex;

void main()
{	
	float x;
	vec4 vPos;

	x=2.0*vVertex.x-1.0;

	vPos.x=x;
	vPos.y=0.25*sin(8.0*x);
	vPos.z=-2.0;

	gl_Position = mProjection * mView * mModel * vPos;
}