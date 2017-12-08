#version 330 core
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

varying vec2 TexCoords;
varying vec3 normal;
varying vec3 lightVector;
varying vec3 viewDir;

void main()
{
    //difuse
    float diff = max(dot(normal, lightVector), 0.1);
    //specular
    vec3 reflect = reflect(-lightVector, normal);
    float spec = pow(max(dot(viewDir, reflect), 0.0), 8);
    //diffuse and specular texture Value
    vec3 diffuse = texture2D(texture_diffuse1, TexCoords).rgb * diff;
    vec3 specular = texture2D(texture_specular1, TexCoords).rgb * spec;

    gl_FragColor = vec4(diffuse + specular, 1.0);
    //gl_FragColor = vec4(diffuse, 1.0);
    //gl_FragColor = vec4(specular, 1.0);
}
