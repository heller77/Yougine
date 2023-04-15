#version 430
out vec4 fragment;
in vec3 vNormal;
uniform float c;
void main()
{
float vn10610 = 0.000000;
float vn865 = 2.000000;
float vn20010 = 0.500000;
vec3 vn17869 = vec3(vn10610, vn20010, vn865);
fragment = glm::vec4(vn17869, 1.0);
}
