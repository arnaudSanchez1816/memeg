#version 330 core
uniform mat4 mvp_matrix, transform;
uniform mat3 normal_mat;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;
attribute int a_isTop;

varying vec2 TexCoords;
varying vec3 normal;
varying vec3 pos;
varying float isTop;

void main()
{    
    TexCoords = a_texcoord;
    vec4 posTransform = transform * vec4(a_position, 1.0f);
    normal = normalize(normal_mat * a_normal);
    pos = posTransform.xyz;
    isTop = a_isTop;
    gl_Position = mvp_matrix * posTransform;
}
