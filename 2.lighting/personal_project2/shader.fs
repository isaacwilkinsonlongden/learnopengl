#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess; 
};

// a single point light. ambient is deliberately NOT part of this struct: it is
// a scene-wide term (see the `ambient` uniform below), so summing it once per
// light would scale it with the light count and make it attenuate with
// distance, which is the opposite of what an ambient term is for.
struct Light {
    vec3 position;

    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// must match NR_POINT_LIGHTS in main.cpp
#define NR_POINT_LIGHTS 3

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 texColor, vec3 specColor);

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform Material material;
uniform Light light[NR_POINT_LIGHTS];
uniform vec3 ambient;
uniform vec3 viewPos;

void main() {
    // properties 
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // the material maps don't vary per light, so sample them once here rather
    // than once per iteration of the loop below
    vec3 texColor  = texture(material.diffuse, TexCoord).rgb;
    vec3 specColor = texture(material.specular, TexCoord).rgb;

    // ambient: constant low-level light so surfaces facing away from the lights
    // aren't pure black. Applied once for the whole scene, unattenuated.
    vec3 result = ambient * texColor;

    // point lights: diffuse and specular do accumulate, since each light is a
    // real source producing its own shading and highlight
    for (int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(light[i], norm, FragPos, viewDir, texColor, specColor);

    FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 texColor, vec3 specColor) {
    // the vector to the light is needed both normalized (for shading) and as a
    // length (for attenuation), so compute the difference once
    vec3 lightVec = light.position - fragPos;
    float distance = length(lightVec);
    vec3 lightDir = lightVec / distance;

    // diffuse shading: brighter the more directly the surface faces the light
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading: highlight where the reflected light lines up with the view direction
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation: lighting decreases over distance from the point light
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results 
    vec3 diffuse  = light.diffuse * diff * texColor;
    vec3 specular = light.specular * spec * specColor;
    return (diffuse + specular) * attenuation;
}
