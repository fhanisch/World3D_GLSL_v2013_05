//Fragment Shader
uniform vec4 vColor;

in float lightIntensity;
out vec4 FragColor;

void main()
{
	
	FragColor = vec4(lightIntensity*vColor.xyz,1.0);		
}