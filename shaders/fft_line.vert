#version 120

attribute float  pow;
attribute float  bin;

uniform mat4    ortho;

float log10(float x) {
    const float rln10 = 0.4342944819;
    return rln10 * log(x);
}

void main()
{
    gl_Position = ortho * vec4(bin, 10.0*log10(pow) - 10.0, 0.0, 1.0);
}
