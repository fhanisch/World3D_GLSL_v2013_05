//Geometry Shader
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

layout (lines) in;
layout (line_strip, max_vertices=200) out;

void main()
{
	
	int n=101;
	float x,F;
	float t=0.0;

	float a1=gl_in[0].gl_Position.y;
	float a2=-2.0*gl_in[0].gl_Position.y-gl_in[1].gl_Position.y;
	float a3=gl_in[0].gl_Position.y+gl_in[1].gl_Position.y;
	
	for(int i=0;i<n;i++)
	{
		x=(gl_in[0].gl_Position.x + t)*0.2-1.0;
		F = a3*t*t*t + a2*t*t + a1*t;
		gl_Position = mProjection * mView * mModel * vec4(x,F,-2.0,1.0);		
		EmitVertex();
		t+=0.01;
	}
	
	EndPrimitive();
}