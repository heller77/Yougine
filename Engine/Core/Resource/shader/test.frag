#version 430
out vec4 fragment;
uniform float c;
void main() { fragment = vec4(c, c, c, 1.0); }