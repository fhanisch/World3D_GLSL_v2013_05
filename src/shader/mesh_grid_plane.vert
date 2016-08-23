//Vertex Shader
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

in float mesh_u;
in float mesh_v;

out vec3 nTransform;

void main()
{
	vec4 vVertex;
	vec4 vNormal;

	vVertex.x = 20.0*mesh_u-10.0;
	vVertex.y = 0.0;
	vVertex.z = 20.0*mesh_v-10.0;

	vNormal.x = 0.0;
	vNormal.y = 1.0;
	vNormal.z = 0.0;
	
	nTransform = transpose(inverse(mModel))*vNormal;	

	gl_Position = mProjection * mView * mModel * vVertex;
}