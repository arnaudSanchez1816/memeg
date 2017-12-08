#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D sand, winter_sand;
uniform sampler2D rock, winter_rock;
uniform int winter;

varying vec2 v_texcoord;
varying float h;
varying vec3 normal;
varying vec3 lightVector;

//! [0]
void main()
{
    sampler2D tSand = winter > 0 ? winter_sand : sand;
    sampler2D tRock = winter > 0 ? winter_rock : rock;
    float rockH = 1.0f;
    float sandH = 0.8f;
    // Set fragment color from texture
    float diffuse = max(dot(normal, lightVector), 0.1);
    vec3 color;
    if(h > rockH) {
        color = texture2D(tRock, v_texcoord * 5).rgb * diffuse;
    } else if (h > sandH && h < rockH ){
        color = mix(texture2D(tSand, v_texcoord * 5),texture2D(tRock, v_texcoord * 5), (h - sandH) / (rockH - sandH)).rgb * diffuse;
    } else {
        color = texture2D(tSand, v_texcoord * 5).rgb * diffuse;
    }
    gl_FragColor = vec4(color, 1.0);
    //debug normal
    //gl_FragColor = vec4(normal, 1.0);
    //gl_FragColor = vec4(diffuse);
    //gl_FragColor = vec4(1, 1, 1, 1);
}
//! [0]
