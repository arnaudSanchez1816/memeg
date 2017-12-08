#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture_diffuse1;

varying vec2 TexCoords;

//! [0]
void main()
{
    gl_FragColor = vec4(texture2D(texture_diffuse1, TexCoords).rgb, 1.0);
}
//! [0]
