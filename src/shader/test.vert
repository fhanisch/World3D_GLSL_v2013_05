uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

attribute vec4 vVertex;

void main()
{
	
	gl_Position = mProjection * mView * mModel * vVertex;
}