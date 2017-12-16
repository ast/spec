#version 120

uniform float   offset;
uniform mat4    ortho;

attribute vec2  vec;

varying vec2    textcoord;
varying float   y;

const vec2 norm = vec2(0.5);

void main()
{
    // smooth top edge
    y = vec.y;
    textcoord = vec * norm + norm + vec2(0, offset);
    gl_Position =  ortho * vec4(vec, 0.0, 1.0);
}
