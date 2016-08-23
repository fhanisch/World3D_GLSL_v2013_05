//Geometry Shader
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

layout (lines) in;
layout (line_strip, max_vertices=200) out;

float perlininterp(float x, float g0, float g1)
{
	float h0=g0*x;
	float h1=g1*(x-1.0);
	float s=3.0*x*x-2.0*x*x*x;
	return (1.0-s)*h0+s*h1;
}

void main()
{	
	int n=101;
	float x,F;
	float t=0.0;
		
	for(int i=0;i<n;i++)
	{
		x=(gl_in[0].gl_Position.x + t)*0.2-1.0;
		F = perlininterp(t,gl_in[0].gl_Position.y,gl_in[1].gl_Position.y);
		gl_Position = mProjection * mView * mModel * vec4(x,F,-2.0,1.0);		
		EmitVertex();
		t+=0.01;
	}
	
	EndPrimitive();
}