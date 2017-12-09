#version 330 core
uniform mat4 mvp_matrix;

attribute vec3 a_position;

varying vec3 TexCoords;

void main()
{    
    vec3 pos = a_position * vec3(1000.0);
    TexCoords = pos;
    gl_Position = mvp_matrix * vec4(pos, 1.0);
}
