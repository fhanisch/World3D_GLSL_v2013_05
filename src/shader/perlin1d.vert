//Vertex Shader
attribute vec4 vVertex;

void main()
{			
	vec2 grad;

	grad.x=vVertex.x;
	//grad.y=noise1(vVertex.x);	
	grad.y=vVertex.y;

	gl_Position = vec4(grad,-2.0,1.0);
}