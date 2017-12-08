#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix, transform;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;

varying vec2 TexCoords;

void main()
{    
    TexCoords = a_texcoord;
    //apply transform
    vec4 posTransform = transform * vec4(a_position, 1.0f);
    gl_Position = mvp_matrix * posTransform;
}
