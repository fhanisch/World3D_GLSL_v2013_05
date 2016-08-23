//Fragment Shader
uniform vec4 vColor;

in vec3 nTransform;
in vec3 Position;
out vec4 FragColor;

const vec3 lightPosition = vec3(100.0,100.0,100.0);

void main()
{
	vec3 s = normalize(lightPosition - Position);
	vec3 n = normalize(nTransform);
	
	float lightIntensity=max(dot(s,n),0.0);

	FragColor = vec4(lightIntensity*vColor.xyz,1.0);		
}