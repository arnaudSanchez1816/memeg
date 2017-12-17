#version 330 core
uniform mat4 mvp_matrix, transform;
uniform sampler2D height_map;
uniform float sizeV;
uniform float iTime;

attribute vec3 a_position;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;
varying vec3 pos;
varying vec3 normal;
varying vec3 lightVector;

void main()
{
    vec4 a_posTransfom = transform * vec4(a_position, 1.0);
    vec4 a_height = vec4(a_posTransfom.x, (texture2D(height_map, a_texcoord).r) * (sizeV / 30.0), a_posTransfom.z, 1.0);
    //calcul normal
    float up = texture2D(height_map, a_texcoord - vec2(0.0, 1.0 / sizeV)).r * (sizeV / 50.0);
    float down = texture2D(height_map, a_texcoord + vec2(0.0, 1.0 / sizeV)).r * (sizeV / 50.0);
    float left = texture2D(height_map, a_texcoord - vec2(1.0 / sizeV, 0.0)).r * (sizeV / 50.0);
    float right = texture2D(height_map, a_texcoord + vec2(1.0 / sizeV, 0.0)).r * (sizeV / 50.0);
    normal.x = left - right;
    normal.y = 2.0;
    normal.z = down - up;
    normal = normalize(normal);
    v_texcoord = a_texcoord;
    pos = a_height.xyz;

    gl_Position = mvp_matrix * a_height;
}
