//Geometry Shader
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

layout (lines_adjacency) in;
layout (line_strip, max_vertices=200) out;

void main()
{
	int n=101;
	float t=0.0;
	float omt;
	float B0,B1,B2,B3;	
	vec2 P;
	
	for(int i=0;i<n;i++)
	{
		omt=1.0-t;
		B0=omt*omt*omt;
		B1=3.0*omt*omt*t;
		B2=3.0*omt*t*t;
		B3=t*t*t;
		P = B0*gl_in[0].gl_Position.xy + B1*gl_in[1].gl_Position.xy + B2*gl_in[2].gl_Position.xy + B3*gl_in[3].gl_Position.xy;
		gl_Position = mProjection * mView * mModel * vec4(P,-2.0,1.0);		
		EmitVertex();
		t+=0.01;
	}
	  	
    EndPrimitive();
}