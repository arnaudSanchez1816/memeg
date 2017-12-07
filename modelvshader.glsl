#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;

varying vec2 TexCoords;

//! [0]
void main()
{    
    TexCoords = a_texcoord;
    gl_Position = mvp_matrix * vec4(a_position, 1.0f);
}
//! [0]
