//Geometry Shader
//Erzeugung neuer Vertices durch Subdivision
//Perlininterpolation für y-Wert

uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

layout (triangles_adjacency) in;
layout (triangle_strip, max_vertices=400) out;

in vec2 gradient[];
in vec3 normal[];
out vec3 nTransform;

float ramp;

vec3 bilininterp3(float x, float y, vec3 f00, vec3 f10, vec3 f01, vec3 f11)
{
	return f00*(1.0-x)*(1.0-y)+f10*x*(1.0-y)+f01*(1.0-x)*y+f11*x*y;
}

float bilininterp(float x, float y, float f00, float f10, float f01, float f11)
{
	return f00*(1.0-x)*(1.0-y)+f10*x*(1.0-y)+f01*(1.0-x)*y+f11*x*y;
}

float calc_h(float x, float y, vec2 g, vec2 p)
{
	return g.x*(x-p.x) + g.y*(y-p.y);
}

float perlininterp(out vec4 vNormal ,float x, float y, vec2 g00, vec2 g10, vec2 g01, vec2 g11)
{	
	float sx=x*x*x*(x*(x*6.0-15.0)+10.0);
	float derx_sx=x*x*(x*(x*30.0-60.0)+30.0);
	float dery_sx=0.0;

	float sy=y*y*y*(y*(y*6.0-15.0)+10.0);
	float derx_sy=0.0;
	float dery_sy=y*y*(y*(y*30.0-60.0)+30.0);

	float w00 = calc_h(x,y,g00,vec2(0.0,0.0));
	float w10 = calc_h(x,y,g10,vec2(1.0,0.0));
	float w01 = calc_h(x,y,g01,vec2(0.0,1.0));
	float w11 = calc_h(x,y,g11,vec2(1.0,1.0));

	float w0=(1.0-sx)*w00+sx*w10;
	float derx_w0=(1.0-sx)*g00.x+(0.0-derx_sx)*w00+sx*g10.x+derx_sx*w10;
	float dery_w0=(1.0-sx)*g00.y+(0.0-dery_sx)*w00+sx*g10.y+dery_sx*w10;

	float w1=(1.0-sx)*w01+sx*w11;
	float derx_w1=(1.0-sx)*g01.x+(0.0-derx_sx)*w01+sx*g11.x+derx_sx*w11;
	float dery_w1=(1.0-sx)*g01.y+(0.0-dery_sx)*w01+sx*g11.y+dery_sx*w11;

	float w=(1.0-sy)*w0+sy*w1;
	float derx_w=(1.0-sy)*derx_w0+(0.0-derx_sy)*w0+sy*derx_w1+derx_sy*w1;
	float dery_w=(1.0-sy)*dery_w0+(0.0-dery_sy)*w0+sy*dery_w1+dery_sy*w1;
	
	vNormal.xyz = normalize(-cross(vec3(1.0,4.0*derx_w,0.0),vec3(0.0,4.0*dery_w,1.0)));
		
	return w;
}

void createVertex(vec2 v0, vec2 v01, vec2 v02, float s, float t)
{
	vec4 vNormal;
	vec4 n;

	vec2 vertex = v0 + s*v01 + t*v02;

	float F1 = perlininterp(vNormal ,s, t, gradient[0], gradient[1], gradient[2], gradient[5]);
	
	float F2 = bilininterp(s, t, gl_in[0].gl_Position.y, gl_in[1].gl_Position.y, gl_in[2].gl_Position.y, gl_in[5].gl_Position.y);

	n.xyz = bilininterp3(s, t, normal[0], normal[1], normal[2], normal[5]);

	nTransform = transpose(inverse(mModel))*(vNormal*ramp+n);

	gl_Position = mProjection * mView * mModel * vec4(vertex.x,4.0*F1+F2,vertex.y,1.0);
	EmitVertex();
}

void main()
{
	vec2 v0 = gl_in[0].gl_Position.xz;
	vec2 v01= gl_in[1].gl_Position.xz - gl_in[0].gl_Position.xz;
	vec2 v02= gl_in[2].gl_Position.xz - gl_in[0].gl_Position.xz;
	
	int n;
	float ds;
	float dt;

	mat4 rot = mView;
	rot[3].x=0.0;
	rot[3].y=0.0;
	rot[3].z=0.0;
	mat4 pos=-inverse(rot)*mView;
	
	if (length(vec2(pos[3].x-gl_in[0].gl_Position.x,pos[3].z-gl_in[0].gl_Position.z)) < 40.0)
	{
		n	= 5;
		ds	= 0.2;
		dt	= 0.2;
		ramp= 1.0;
	} 
	else 
	{
		n	= 1;
		ds	= 1.0;
		dt	= 1.0;
		ramp= 0.0;
	}

	float t=0.0;

	for(int i=0;i<n;i++)
	{
		float s=0.0;
		for(int j=0;j<n+1;j++)
		{
			createVertex(v0,v01,v02,s,t);		
			createVertex(v0,v01,v02,s,t+dt);		
			s+=ds;
		}			
		t+=dt;
		EndPrimitive();
	}			
}