#version 330 core
struct DirLight {
    vec3 sunDirection;
    vec3 ambient, diffuse, specular;
};
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform DirLight dirLight;
uniform vec3 viewpos;
uniform bool useSpecular, useNormal;

varying vec2 TexCoords;
varying vec3 normal;
varying vec3 pos;

void main()
{
    vec3 lightVector = normalize(-dirLight.sunDirection);
    vec3 viewDir = normalize(viewpos - pos);
    vec3 halfwayDir = normalize(lightVector + viewDir);
    //difuse
    float diff = max(dot(normal, lightVector), 0.2);
    //specular phong
    //vec3 reflect = reflect(-lightVector, normal);
    //float spec = pow(max(dot(viewDir, reflect), 0.0), 8);
    //blinn
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 24);
    //diffuse and specular texture Value
    vec3 diffuse = (texture2D(texture_diffuse1, TexCoords).rgb * diff) * dirLight.diffuse;
    vec3 specular = (texture2D(texture_specular1, TexCoords).rgb * spec) * dirLight.specular;

    if(useSpecular)
        gl_FragColor = vec4(diffuse + specular, 1.0);
    else {
        specular = (vec3(0.2, 0.2, 0.2) * spec) * dirLight.specular;
        gl_FragColor = vec4(diffuse + specular, 1.0);
    }
    //gl_FragColor = vec4(diffuse, 1.0);
    //gl_FragColor = vec4(specular, 1.0);
   // gl_FragColor = vec4(texture2D(texture_specular1, TexCoords).rgb, 1.0);
    //gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
