#version 430
in vec4 position;
in vec3 normal;
in vec2 vUV;
uniform mat4 mvp;
out vec3 vNormal;
out vec2 uv;
void main(){
	gl_Position=mvp*position;
	vNormal=normal;
	uv=vUV;
}