//Vertex Shader

uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

in float mesh_u;
in float mesh_v;

out vec3 nTransform;
out vec3 Position;

const float pi = 3.14159;

void main()
{	
	float u = 2.0*pi*mesh_u;
	float v = pi*mesh_v;
	vec3 vVertex;	
	vec3 fu,fv;
	vec3 vNormal;	

	vVertex.x = sin(v)*cos(u);
	vVertex.y = sin(v)*sin(u);
	vVertex.z = cos(v);
	
	fu.x=-sin(v)*sin(u);
	fu.y=sin(v)*cos(u);
	fu.z=0.0;

	fv.x=cos(v)*cos(u);
	fv.y=cos(v)*sin(u);
	fv.z=-sin(v);
		
	vNormal.x = sin(v)*cos(u);
	vNormal.y = sin(v)*sin(u);
	vNormal.z = cos(v);

	//vNormal = -cross(fu,fv);

	nTransform = transpose(inverse(mView*mModel))*vec4(vNormal,1.0);	

	Position = mView*mModel*vec4(vVertex,1.0);
				
	gl_Position = mProjection * mView * mModel * vec4(vVertex,1.0);
}