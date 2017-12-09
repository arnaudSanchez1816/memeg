#version 330 core
uniform samplerCube skybox;

varying vec3 TexCoords;

void main()
{
    gl_FragColor = texture(skybox, TexCoords);
}
