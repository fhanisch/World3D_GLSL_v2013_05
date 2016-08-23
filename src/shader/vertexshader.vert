#generic#
in vec3 vVertex;

void main()
{
	gl_Position = vec4(vVertex,1.0);
}

#text#
uniform mat4 mProjection;

void main()
{
	gl_Position = mProjection * gl_Vertex;
}
