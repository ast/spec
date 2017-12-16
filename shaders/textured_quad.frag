#version 120

uniform sampler2D   waterfall;

varying vec2        textcoord;
varying float       y;

void main()
{
    float alpha = 1.0;
    if(y > 0.5) alpha = smoothstep(1,0.5,y);
    vec4 color = texture2D(waterfall, textcoord);
    gl_FragColor = vec4(color.rgb, alpha);
    
    //gl_FragColor = alpha * texture2D(waterfall, textcoord);
}
