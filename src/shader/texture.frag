//Fragment Shader

uniform sampler2D samp;

in vec2 texCoord;
out vec4 FragColor;

void main()
{
	//FragColor = vec4(texCoord,0.0,1.0);
	FragColor = texture2D(samp,texCoord);
}