//Vertex Shader

uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

in vec4 vVertex;
in vec4 vNormal;
out vec3 nTransform;

void main()
{		
	nTransform = transpose(inverse(mModel))*vNormal;	
	gl_Position = mProjection * mView * mModel * vVertex;	
}