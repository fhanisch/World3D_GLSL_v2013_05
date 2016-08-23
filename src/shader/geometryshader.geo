#generic#
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

layout (triangles) in;
layout (triangle_strip) out;

void main()
{
	//Vertices werden transformiert und direkt weitergeleitet
	for(int i=0;i<3;i++)
	{
		gl_Position = mProjection * mView * mModel * gl_in[i].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}

#calc_normals#
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;
uniform mat4 mModelView;

layout (triangles) in;
layout (triangle_strip) out;

out vec3 nTransform;
out vec3 Position;

void main()
{
	vec3 v1	 = gl_in[1].gl_Position.xyz;
	vec3 v10 = gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz;
	vec3 v12= gl_in[2].gl_Position.xyz - gl_in[1].gl_Position.xyz;

	vec3 vNormal = -cross(v10,v12);

	for(int i=0;i<3;i++)
	{
		nTransform = transpose(inverse(mModelView))*vec4(vNormal,1.0);
		Position = mModelView * gl_in[i].gl_Position;
		gl_Position = mProjection * mModelView * gl_in[i].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}
