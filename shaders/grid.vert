#version 120

attribute vec2 vec;
uniform mat4 proj;

void main()
{
   gl_Position = proj * vec4(vec, 0.0, 1.0);
}
