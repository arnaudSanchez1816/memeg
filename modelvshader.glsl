#version 330 core
uniform mat4 mvp_matrix, transform;
uniform vec3 viewpos;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;

varying vec2 TexCoords;
varying vec3 normal;
varying vec3 lightVector;
varying vec3 viewDir;

const vec3 sun = vec3(0.0, 20.0, 50.0);

void main()
{    
    TexCoords = a_texcoord;
    vec4 posTransform = transform * vec4(a_position, 1.0f);
    normal = normalize(mat3(transpose(inverse(transform))) * a_normal);
    //normal = normalize(transform * vec4(a_normal, 1.0)).xyz;
    lightVector = normalize(sun - posTransform.xyz);
    viewDir = normalize(viewpos - posTransform.xyz);

    gl_Position = mvp_matrix * posTransform;
}
