#version 330 core
struct DirLight {
    vec3 sunDirection;
    vec3 ambient, diffuse, specular;
};

uniform sampler2D grass_top;
uniform sampler2D grass_side;
uniform sampler2D dirt;
uniform DirLight dirLight;
uniform vec3 viewpos;
uniform bool useSpecular, useNormal;

varying vec2 TexCoords;
varying vec3 normal;
varying vec3 pos;
varying float isTop;

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
    vec3 diffuse;
    if(isTop > 0.0) {
        if(normal.y > 0.9) {
            diffuse = (texture2D(grass_top, TexCoords).rgb * diff) * dirLight.diffuse;
        } else {
            diffuse = (texture2D(grass_side, TexCoords).rgb * diff) * dirLight.diffuse;
        }
    } else {
        diffuse = (texture2D(dirt, TexCoords).rgb * diff) * dirLight.diffuse;
    }

    //vec3 specular = (texture2D(texture_specular1, TexCoords).rgb * spec) * dirLight.specular;

/*    if(useSpecular)
        gl_FragColor = vec4(diffuse + specular, 1.0);
    else {*/
        vec3 specular = (vec3(0.2, 0.2, 0.2) * spec) * dirLight.specular;
        gl_FragColor = vec4(diffuse + specular, 1.0);
   // }
    //gl_FragColor = vec4(diffuse, 1.0);
    //gl_FragColor = vec4(specular, 1.0);
   // gl_FragColor = vec4(texture2D(texture_specular1, TexCoords).rgb, 1.0);
    //gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
