#version 330 core
uniform mat4 mvp_matrix, transform;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;

varying vec2 TexCoords;
varying vec3 normal;
varying vec3 pos;

void main()
{    
    TexCoords = a_texcoord;
    vec4 posTransform = transform * vec4(a_position, 1.0f);
    normal = normalize(mat3(transpose(inverse(transform))) * a_normal);
    pos = posTransform.xyz;
    gl_Position = mvp_matrix * posTransform;
}
