#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 12) out;

const int BLADE_DISTANCE = 10;

in VS_OUT
{
	vec3 normal;
	vec3 WorldPos;
	vec3 FragPos;
	float randomCurve;
} gs_in[];

uniform mat4 view;
uniform mat4 projection;
uniform float time;

out vec4 fColor;
out vec3 FaceNormal;

mat4 rot(float angle)
{	
	return mat4(
	vec4(cos(angle),0., sin(angle), 0.),
	vec4(0.,1.,0.,0.),
	vec4(-sin(angle), 0., cos(angle), 0.),
	vec4(0., 0., 0., 1.)
);
}

mat4 scaleY(float scale)
{
	return mat4(
	vec4(1.,0., 0., 0.),
	vec4(0.,scale, 0., 0.),
	vec4(0.,0., 1., 0.),
	vec4(0.,0., 0., 1.)
	);
}

void createLine(int index)
{
			mat4 brot = rot(radians(gs_in[index].randomCurve * 100.));

	vec4 pos = vec4(gs_in[index].WorldPos, 1.);

	fColor = vec4(0., .4, 0., 1.);

	float influence = ((sin(time * gs_in[index].randomCurve * .2) + .5)/2) * fract(gs_in[index].randomCurve);
//	float influence = ((sin(gs_in[index].randomCurve * .2) + 1)/2);
//	float grassWidth = gs_in[index].randomCurve * .2;
	float grassWidth = 4.;
	float grassColor = 0.;

	for (float y = 0.1, x = 0.; y >= 0, x <= 10.; y -= 0.02, x += 0.1)
	{
		
		
			mat4 brot = rot(radians(gs_in[index].randomCurve * 100.));

			// translate to origin by subtracting position, apply rotation, then translate back
			vec4 ran = vec4(pos.x - y * grassWidth, pos.y + x * 10., pos.z - (x*x) * gs_in[index].randomCurve * influence, 1.);
			vec4 ran2 = vec4(pos.x + y * grassWidth, pos.y + x * 10., pos.z - (x*x) * gs_in[index].randomCurve * influence, 1.);
			vec4 result1 = ((pos + (brot * (ran - pos))) * scaleY(gs_in[index].randomCurve * 0.1));
			vec4 result2 = (( pos + (brot * (ran2 - pos))) * scaleY(gs_in[index].randomCurve * 0.1));
			gl_Position = (projection * view * result1);
			EmitVertex();

			gl_Position = (projection * view * result2);

			EmitVertex();

			fColor = vec4(0., x + grassColor, 0., 1.);
		
	}
	gl_Position = (projection * view * rot(radians(gs_in[index].randomCurve)) * vec4(pos.x, pos.y + 200000., pos.z + sin(12.), 1.));


	EmitVertex();

}

void createLines()
{

}

void main()
{
	
	createLine(0);

}