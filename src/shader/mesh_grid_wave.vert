//Vertex Shader

uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

uniform float arg1;

attribute float mesh_u;
attribute float mesh_v;

out vec3 nTransform;
out vec3 Position;

const float pi = 3.14159;
const float A=0.1;
const float w=5.0;

void main()
{	
	float u = 4.0*mesh_u-2.0;
	float v = 4.0*mesh_v-2.0;
	vec3 vVertex;	
	vec3 vNormal;

	vVertex.x=u;
	vVertex.y=A*(sin(w*u-arg1)+sin(w*u+w*v+arg1)+sin(w*v-arg1));
	vVertex.z=v;

	vNormal.x = -A*(w*cos(arg1 + u*w + v*w) + w*cos(u*w - arg1));
	vNormal.y = 1.0;
	vNormal.z = -A*(w*cos(arg1 + u*w + v*w) + w*cos(v*w - arg1));

	nTransform = transpose(inverse(mView*mModel))*vec4(vNormal,1.0);	
	Position = mView*mModel*vec4(vVertex,1.0);
	gl_Position = mProjection * mView * mModel * vec4(vVertex,1.0);
}