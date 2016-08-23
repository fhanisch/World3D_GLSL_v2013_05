//Vertex Shader

in float mesh_u;
in float mesh_v;
in vec2 vGradient;
out vec2 gradient;
out vec3 normal;

float calc_h(float x, float y, vec2 g, vec2 p)
{
	return g.x*(x-p.x) + g.y*(y-p.y);
}

float perlininterp(float x, float y, vec2 g00, vec2 g10, vec2 g01, vec2 g11)
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
	
	normal = normalize(-cross(vec3(200.0,100.0*derx_w,0.0),vec3(0.0,100.0*dery_w,200.0)));
	
	return w;
}

void main()
{			
	vec4 vVertex;	

	vVertex.x = 200.0*mesh_u-100.0;	
	vVertex.y = 100.0*perlininterp(mesh_u, mesh_v, vec2(0.2893,-0.7632), vec2(-0.842,-0.1242), vec2(0.3844,-0.1332), vec2(0.9843,-0.1835));
	vVertex.z = 200.0*mesh_v-100.0;

	gl_Position = vVertex;

	gradient=vGradient;	
}