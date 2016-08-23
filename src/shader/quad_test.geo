//Geometry Shader
//Erzeugung neuer Vertices durch Subdivision

uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

layout (triangles_adjacency) in;
layout (triangle_strip, max_vertices=400) out;

void createVertex(vec2 v0, vec2 v01, vec2 v02, float s, float t)
{
	vec2 vertex = v0 + s*v01 + t*v02;
	gl_Position = mProjection * mView * mModel * vec4(vertex,-2.0,1.0);
	EmitVertex();
}

void main()
{	
	vec2 v0 = gl_in[0].gl_Position.xy;
	vec2 v01= gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy;
	vec2 v02= gl_in[2].gl_Position.xy - gl_in[0].gl_Position.xy;

	float ds = 0.1;
	float dt = 0.1;

	float t=0.0;

	for(int i=0;i<10;i++)
	{
		float s=0.0;
		for(int j=0;j<11;j++)
		{
			createVertex(v0,v01,v02,s,t);		
			createVertex(v0,v01,v02,s,t+dt);		
			s+=ds;
		}		
		t+=dt;
		EndPrimitive();
	}		
}