#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in VS_OUT
{
	vec3 normal;
} gs_in[];

uniform mat4 projection;

void createLine(int index, vec3 offSet)
{

	vec4 pos = gl_in[index].gl_Position;
for (float i = 0.; i < 100.; i++)
{

	gl_Position = (projection * vec4(pos.x - .5, pos.y, pos.z, 1.)) - vec4(offSet + i, 0.);
	EmitVertex();

	gl_Position = (projection * vec4(pos + vec4(gs_in[index].normal, 0.) * 2.)) - vec4(offSet + i, 0.);
	EmitVertex();

	gl_Position = (projection * vec4(vec3(pos.x + 0.5, pos.y, pos.z), 1.)) - vec4(offSet + i, 0.);
	EmitVertex();

	EndPrimitive();
}

}

void createLines()
{

}

void main()
{
		createLine(0, vec3(0., 0., 0.));
}