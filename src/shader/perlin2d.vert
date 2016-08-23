//Vertex Shader

in vec4 vVertex;
in vec2 vTexCoord;
out vec2 gradient;

void main()
{			
	gl_Position = vVertex;
	gradient=vTexCoord;	
}