//Vertex Shader

uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

attribute float mesh_u;
attribute float mesh_v;

out vec3 nTransform;
out vec3 Position;

const float pi = 3.14159;
const float a=3.0;
const float b=4.5;
const float c=0.4;

void main()
{	
	float u = a*mesh_u;
	float v = 2.0*pi*mesh_v;

	vec3 vVertex;	
	vec3 vNormal;
	vec3 fu, fv;
	
	vVertex.x=c*sqrt(u*(u-a)*(u-b))*sin(v);
	vVertex.y=u;
	vVertex.z=c*sqrt(u*(u-a)*(u-b))*cos(v);
	
	fu.x=-(c*sin(v)*(u*(a-u)+u*(b-u)-(a-u)*(b-u)))/(2.0*pow(u*(a-u)*(b-u),1.0/2.0));
	fu.y=1.0;
	fu.z=-(c*cos(v)*(u*(a-u)+u*(b-u)-(a-u)*(b-u)))/(2.0*pow(u*(a-u)*(b-u),1.0/2.0));

	fv.x=c*cos(v)*pow(u*(a-u)*(b-u),1.0/2.0);
	fv.y=0.0;
	fv.z=-c*sin(v)*pow(u*(a-u)*(b-u),1.0/2.0);
	
	vNormal = -cross(fu,fv);

	nTransform = transpose(inverse(mView*mModel))*vec4(vNormal,1.0);	
	Position = mView*mModel*vec4(vVertex,1.0);
	gl_Position = mProjection * mView * mModel * vec4(vVertex,1.0);
}