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
uniform sampler2D sand_n, winter_sand_n;
uniform sampler2D rock, winter_rock;
uniform sampler2D rock_n, winter_rock_n;
uniform DirLight dirLight;
uniform vec3 viewpos;
uniform int winter;

varying vec2 v_texcoord;
varying vec3 normal;
varying vec3 pos;

const float texMultiplier = 7.0;

struct texs {
    sampler2D tSand, tRock;
    sampler2D tSandN, tRockN;
};
void setTextures(inout texs t) {
    t.tSand = winter > 0 ? winter_sand : sand;
    t.tRock = winter > 0 ? winter_rock : rock;
    t.tSandN = winter > 0 ? winter_sand_n : sand_n;
    t.tRockN = winter > 0 ? winter_rock_n : rock_n;
}

//! [0]
void main()
{
    texs t;
    vec3 lightVector = normalize(-dirLight.sunDirection);
    vec3 viewDir = normalize(viewpos - pos);
    setTextures(t);
    float rockH = 2.0f;
    float sandH = 0.8f;
    // Set fragment color from texture
    vec3 diffuse, specular, nm;
    if(pos.y > rockH) {
        diffuse = vec3(texture2D(t.tRock, v_texcoord * texMultiplier).rgb * dirLight.diffuse);
        nm = texture2D(t.tRockN, v_texcoord * texMultiplier).rgb;
    } else if (pos.y > sandH && pos.y < rockH ){
        diffuse = mix(texture2D(t.tSand, v_texcoord * texMultiplier),texture2D(t.tRock, v_texcoord * texMultiplier), (pos.y - sandH) / (rockH - sandH)).rgb * dirLight.diffuse;
        nm = mix(texture2D(t.tSandN, v_texcoord * texMultiplier), texture2D(t.tRockN, v_texcoord * texMultiplier), (pos.y - sandH) / (rockH - sandH)).rgb;
    } else {
        diffuse = texture2D(t.tSand, v_texcoord * texMultiplier).rgb * dirLight.diffuse;
        nm = texture2D(t.tSandN, v_texcoord * texMultiplier).rgb;
    }
    nm = normalize(nm * 2.0 - 1.0);
    nm = normalize(normal + nm);
    vec3 reflect = reflect(-lightVector, nm);
    float diff = max(dot(nm, lightVector), 0.1);
    float spec = pow(max(dot(viewDir, reflect), 0.0), 32);
    specular = (spec * 0.5) * dirLight.specular;
    gl_FragColor = vec4((diffuse * diff) + specular, 1.0);
    //debug normal
    //gl_FragColor = vec4(lightVector, 1.0);
    //gl_FragColor = vec4(normal, 1.0);
    //gl_FragColor = vec4(diffuse);
    //gl_FragColor = vec4(1, 1, 1, 1);
    //gl_FragColor = vec4(specular, 1.0);
    //gl_FragColor = vec4(texture2D(t.tRockN, v_texcoord * 5).rgb, 1.0);
}
//! [0]
