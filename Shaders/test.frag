#version 430
out vec4 fragment
in vec3 vNormal;
uniform float c;
void main() {
fragment = glm::vec4(vNormal, 1.0);
//405
}
