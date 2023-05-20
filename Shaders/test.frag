#version 430
out vec4 fragment;
in vec3 vNormal;
uniform float c;
void main()
{
float vn21080 = 4.000000;
float vn9966 = vn21080 + 3.000000;
float vn3857 = 1.500000 + 2.500000;
float vn18033 = 0.100000;
vec3 vn4054 = vec3(vn9966, vn3857, vn18033);
fragment = glm::vec4(vn4054, 1.0);
}
