#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif
struct DirLight {
    vec3 sunDirection;
    vec3 ambient, diffuse, specular;
};
uniform sampler2D sand, winter_sand;
uniform sampler2D rock, winter_rock;
uniform DirLight dirLight;
uniform vec3 viewpos;
uniform int winter;

varying vec2 v_texcoord;
varying vec3 normal;
varying vec3 pos;

//! [0]
void main()
{
    vec3 lightVector = normalize(-dirLight.sunDirection);
    vec3 viewDir = normalize(viewpos - pos);
    vec3 reflect = reflect(-lightVector, normal);
    sampler2D tSand = winter > 0 ? winter_sand : sand;
    sampler2D tRock = winter > 0 ? winter_rock : rock;
    float rockH = 1.0f;
    float sandH = 0.8f;
    // Set fragment color from texture
    float diff = max(dot(normal, lightVector), 0.1);
    float spec = pow(max(dot(viewDir, reflect), 0.0), 32);
    vec3 diffuse, specular;
    if(pos.y > rockH) {
        diffuse = (texture2D(tRock, v_texcoord * 5).rgb * diff) * dirLight.diffuse;
    } else if (pos.y > sandH && pos.y < rockH ){
        diffuse = (mix(texture2D(tSand, v_texcoord * 5),texture2D(tRock, v_texcoord * 5), (pos.y - sandH) / (rockH - sandH)).rgb * diff) * dirLight.diffuse;
    } else {
        diffuse = (texture2D(tSand, v_texcoord * 5).rgb * diff) * dirLight.diffuse;
    }
    specular = (spec * 0.5) * dirLight.specular;
    gl_FragColor = vec4(diffuse + specular, 1.0);
    //debug normal
    //gl_FragColor = vec4(lightVector, 1.0);
    //gl_FragColor = vec4(normal, 1.0);
    //gl_FragColor = vec4(diffuse);
    //gl_FragColor = vec4(1, 1, 1, 1);
    //gl_FragColor = vec4(specular, 1.0);
}
//! [0]
