#test#
uniform vec4 vColor;
out vec4 FragColor;

void main()
{
	FragColor = vColor;
}

#simple#
uniform vec4 vColor;

in vec3 nTransform;

void main()
{
	vec4 schattierung;
	vec4 light = vec4(0.3,0.3,1.0,1.0);
	float intensity=dot(nTransform,light.xyz)/(length(nTransform)*length(light.xyz));
	//float intensity=dot(normalize(nTransform),normalize(light.xyz));
	float shine=pow(max(intensity,0.01),90.0); // pow(x,y) --> x kann keine negativen Werte annehmen!!!

	schattierung.r=max(intensity,-0.15)*vColor.r+0.2*vColor.r+shine;
	schattierung.g=max(intensity,-0.15)*vColor.g+0.2*vColor.g+shine;
	schattierung.b=max(intensity,-0.15)*vColor.b+0.2*vColor.b+shine;

	gl_FragColor = schattierung;
}

#ads_per_fragment#
uniform vec4 vColor;
uniform mat4 mView;

in vec3 nTransform;
in vec3 Position;
out vec4 FragColor;

const vec3 lightPosition = vec3(1000000.0,1000000.0,1000000.0);

void main()
{
	vec3 A=0.1*vColor.rgb;
	vec3 D=vColor.rgb;
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

#_ads_per_fragment_tex#
uniform sampler2D samp;
uniform mat4 mView;

in vec3 nTransform;
in vec3 Position;
in vec2 texCoord;
out vec4 FragColor;

const vec3 lightPosition = vec3(1000000.0,1000000.0,1000000.0);

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

#mandelbrot#
in vec2 texCoord;
out vec4 FragColor;

void main()
{
	int iter=25;
	int i;
	vec2 c,z;
	vec3 color;

	c=(texCoord+vec2(-0.75,-0.5))*vec2(2.0,2.0);

	z=c;

	for(i=0; i<iter; i++) {
        float x = (z.x * z.x - z.y * z.y) + c.x;
        float y = (z.y * z.x + z.x * z.y) + c.y;

        if((x * x + y * y) > 4.0) break;
        z.x = x;
        z.y = y;
    }

	color = vec3(float(i)/float(iter),float(i)/float(iter),1.0);
	//color = vec3(1.0,0.0,float(i)/float(iter));
	//if (i>=iter) color=vec3(0.0,0.0,0.0); else color=vec3(1.0,1.0,1.0);
	if (i>=iter) color=vec3(0.0,0.0,0.0);

	FragColor = vec4(color,1.0);
}
