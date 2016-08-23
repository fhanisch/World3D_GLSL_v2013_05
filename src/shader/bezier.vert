//Vertex Shader
in vec3 vVertex;

void main()
{			
	gl_Position = vec4(vVertex,1.0);
}