//Fragment Shader
uniform sampler2D samp;
uniform mat4 mView;

in vec3 nTransform;
in vec3 Position;
in vec2 texCoord;
out vec4 FragColor;

const vec3 lightPosition = vec3(100.0,100.0,100.0);

void main()
{
	vec4 tex=texture2D(samp,texCoord);
	vec3 A=0.1*tex.rgb;
	vec3 D=tex.rgb;
	vec3 S=vec3(1.0,1.0,0.6);

	vec3 s = normalize( vec3(mView*vec4(lightPosition,1.0)) - Position);
	vec3 n = normalize(nTransform);
	vec3 v = normalize(-Position);
	vec3 r = reflect(-s,n);
	
	float diffuseIntensity=max(dot(s,n),0.0);
	vec3 spec = vec3(0.0);
	if( diffuseIntensity > 0.0 )
		spec = S * pow( max( dot(r,v), 0.0 ), 30.0 );

	vec3 ADS = A + diffuseIntensity*D + spec;

	FragColor = vec4(ADS,1.0);		
}