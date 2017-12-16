#version 120

attribute float pow;
attribute float bin;

uniform float line;

uniform mat4 ortho;

varying float norm_pow;

float log10(float x) {
    const float rln10 = 0.4342944819;
    return rln10 * log(x);
}

void main()
{
    norm_pow = smoothstep(-100., 0., 10.*log10(pow)-10.0);
    //norm_pow = smoothstep(-100., 0., pow);
    gl_Position = ortho * vec4(bin, line, 0, 1.0);
    gl_PointSize = 1.0;
}
