#apfel#
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;
uniform mat4 mModelView;

in float mesh_u;
in float mesh_v;

out vec3 nTransform;
out vec3 Position;

const float pi = 3.14159;
const float R1 = 5.0;
const float R2 = 4.8;
const float scale = 0.1;

void main()
{
	float u = pi*(2.0*mesh_u-1.0);
	float v = pi*(2.0*mesh_v-1.0);
	vec3 vVertex;
	vec3 vNormal;
	vec3 fu, fv;

	vVertex.x = scale*(cos(u)*(R1+R2*cos(v))+pow(abs(v)/pi,20.0));  // pow(x,y) --> x kann keine negativen Werte annehmen!!!
	vVertex.y = scale*(-2.3*log(1.0-v*0.3157)+6.0*sin(v)+2.0*cos(v));
	vVertex.z = scale*(sin(u)*(R1+R2*cos(v))+0.25*cos(5.0*u));

	fu.x = -scale*sin(u)*(R1 + R2*cos(v));
	fu.y = 0.0;
	fu.z = -scale*((5.0*sin(5.0*u))/4.0 - cos(u)*(R1 + R2*cos(v)));

	fv.x = scale*((20.0*pow(abs(v),19.0)*sign(v))/pow(pi,20.0) - R2*cos(u)*sin(v)); // pow(x,y) --> x kann keine negativen Werte annehmen!!!
	fv.y = -scale*(2.0*sin(v) - 6.0*cos(v) + 72611.0/(100000.0*((3157.0*v)/10000.0 - 1.0)));
	fv.z = -R2*scale*sin(u)*sin(v);

	vNormal = -cross(fu,fv);
	nTransform = transpose(inverse(mModelView))*vec4(vNormal,1.0);
	Position = mModelView*vec4(vVertex,1.0);
	gl_Position = mProjection * mModelView * vec4(vVertex,1.0);
}

#sphere#
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;
uniform mat4 mModelView;
uniform float arg1;

in float mesh_u;
in float mesh_v;

out vec3 nTransform;
out vec3 Position;

const float pi = 3.14159;

void main()
{
	float R=arg1;

	float u = 2.0*pi*mesh_u;
	float v = pi*mesh_v;
	//float u = (0.0-pi/1024.0+2.0*mesh_u*pi/1024.0)+pi/2.0;
	//float v = (1.0-pi/1024.0+2.0*mesh_v*pi/1024.0)+pi/5.5;
	vec3 vVertex;
	vec3 fu,fv;
	vec3 vNormal;

	vVertex.x = R*sin(v)*cos(u);
	vVertex.y = R*sin(v)*sin(u);
	vVertex.z = R*cos(v);

	fu.x=-sin(v)*sin(u);
	fu.y=sin(v)*cos(u);
	fu.z=0.0;

	fv.x=cos(v)*cos(u);
	fv.y=cos(v)*sin(u);
	fv.z=-sin(v);

	vNormal.x = sin(v)*cos(u);
	vNormal.y = sin(v)*sin(u);
	vNormal.z = cos(v);

	//vNormal = -cross(fu,fv);

	nTransform = transpose(inverse(mModelView))*vec4(vNormal,1.0);

	Position = mModelView*vec4(vVertex,1.0);

	gl_Position = mProjection * mModelView * vec4(vVertex,1.0);
}

#ei#
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;
uniform mat4 mModelView;

attribute float mesh_u;
attribute float mesh_v;

out vec3 nTransform;
out vec3 Position;

const float pi = 3.14159;
const float a=3.0;
const float b=4.5;
const float c=0.4;

void main()
{
	float u = a*mesh_u;
	float v = 2.0*pi*mesh_v;

	vec3 vVertex;
	vec3 vNormal;
	vec3 fu, fv;

	vVertex.x=c*sqrt(u*(u-a)*(u-b))*sin(v);
	vVertex.y=u;
	vVertex.z=c*sqrt(u*(u-a)*(u-b))*cos(v);

	fu.x=-(c*sin(v)*(u*(a-u)+u*(b-u)-(a-u)*(b-u)))/(2.0*pow(u*(a-u)*(b-u),1.0/2.0));
	fu.y=1.0;
	fu.z=-(c*cos(v)*(u*(a-u)+u*(b-u)-(a-u)*(b-u)))/(2.0*pow(u*(a-u)*(b-u),1.0/2.0));

	fv.x=c*cos(v)*pow(u*(a-u)*(b-u),1.0/2.0);
	fv.y=0.0;
	fv.z=-c*sin(v)*pow(u*(a-u)*(b-u),1.0/2.0);

	vNormal = -cross(fu,fv);

	nTransform = transpose(inverse(mView*mModel))*vec4(vNormal,1.0);
	Position = mView*mModel*vec4(vVertex,1.0);
	gl_Position = mProjection * mView * mModel * vec4(vVertex,1.0);
}

#wave#
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;
uniform mat4 mModelView;

uniform float arg1;

attribute float mesh_u;
attribute float mesh_v;

out vec3 nTransform;
out vec3 Position;

const float pi = 3.14159;
const float A=0.1;
const float w=5.0;

void main()
{
	float u = 4.0*mesh_u-2.0;
	float v = 4.0*mesh_v-2.0;
	vec3 vVertex;
	vec3 vNormal;

	vVertex.x=u;
	vVertex.y=A*(sin(w*u-arg1)+sin(w*u+w*v+arg1)+sin(w*v-arg1));
	vVertex.z=v;

	vNormal.x = -A*(w*cos(arg1 + u*w + v*w) + w*cos(u*w - arg1));
	vNormal.y = 1.0;
	vNormal.z = -A*(w*cos(arg1 + u*w + v*w) + w*cos(v*w - arg1));

	nTransform = transpose(inverse(mView*mModel))*vec4(vNormal,1.0);
	Position = mView*mModel*vec4(vVertex,1.0);
	gl_Position = mProjection * mView * mModel * vec4(vVertex,1.0);
}

#plane#
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;
uniform mat4 mModelView;

in float mesh_u;
in float mesh_v;

out vec3 nTransform;
out vec3 Position;

void main()
{
	vec3 vVertex;
	vec3 vNormal;

	vVertex.x = 20.0*mesh_u-10.0;
	vVertex.y = 0.0;
	vVertex.z = 20.0*mesh_v-10.0;

	vNormal.x = 0.0;
	vNormal.y = 1.0;
	vNormal.z = 0.0;

	nTransform = transpose(inverse(mView*mModel))*vec4(vNormal,1.0);
	Position = mView*mModel*vec4(vVertex,1.0);
	gl_Position = mProjection * mView * mModel * vec4(vVertex,1.0);
}
