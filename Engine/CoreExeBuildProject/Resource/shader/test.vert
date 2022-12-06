#version 430
in vec4 position;
in vec3 normal;
uniform mat4 mvp;
out vec3 vNormal;

void main(){
	gl_Position=mvp*position;
	vNormal=normal;
}