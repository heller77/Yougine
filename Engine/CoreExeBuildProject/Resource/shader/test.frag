#version 430
out vec4 fragment;
in vec3 vNormal;
in vec2 uv;
uniform float c;
uniform vec3 color_vec3;
uniform sampler2D textureSampler;
void main() {
	float diffuse=dot(vNormal,vec3(1,1,1));
	fragment = vec4(color_vec3*diffuse, 1.0); 
	fragment = texture2D(textureSampler,uv); 
}