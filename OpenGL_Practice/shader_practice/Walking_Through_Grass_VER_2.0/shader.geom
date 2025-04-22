#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in VS_OUT
{
	vec3 normal;
//	float magnitude;
} gs_in[];

uniform mat4 projection;
uniform float time;

out vec4 fColor;
out vec3 FaceNormal;

void createLine(int index)
{

	vec4 pos = gl_in[index].gl_Position;

    vec3 v0 = vec3(pos.x - 0.03, pos.y, pos.z - 0.03);
    vec3 v1 = vec3(pos.x + (sin(time + sin(pos.x) + fract(sin(pos.x * pos.z) * sin(9382.) * 2918.)) + 2.0 / 2.0) * 0.2, pos.y, pos.z) + gs_in[index].normal;
    vec3 v2 = vec3(pos.x + 0.02, pos.y, pos.z + 0.02);

    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;
    vec3 faceNormal = normalize(cross(edge1, edge2));

	fColor = vec4(0., 1., 0., 1.);

	FaceNormal = faceNormal;

	gl_Position = (projection * vec4(pos.x - .03, pos.y, pos.z -.03, 1.));
	EmitVertex();


	gl_Position = (projection * vec4(vec4(pos.x + (sin(time + sin(pos.x) + fract(sin(pos.x * pos.z) * sin(9382.) * 2918.)) + 2. / 2.) * .2, pos.y, pos.z, 1.) + vec4(vec3(gs_in[index].normal), 0.)));
	EmitVertex();

	gl_Position = (projection * vec4(vec3(pos.x + 0.03, pos.y, pos.z + .03), 1.));

	fColor = vec4(0., .3, 0., 1.);

	EmitVertex();

	EndPrimitive();

}

void createLines()
{

}

void main()
{
	
	createLine(0);

}