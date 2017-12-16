#version 120

const vec3 color0 = vec3(0.0,0.0,0.0);
const vec3 color1 = vec3(1.0,0.0,0.0);

varying float norm_pow;

void main()
{
    vec3 color = mix(color0, color1, vec3(norm_pow));
    gl_FragColor = vec4(color, 1.0);
}
