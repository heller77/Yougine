#version 430
out vec4 fragment;
in vec3 vNormal;
uniform float c;
void main()
{
float vn27571 = 5.000000;
vec3 vn27580 = vec3(vn27571, 3.000000, 1.000000);
fragment = glm::vec4(vn27580, 1.0);
}
