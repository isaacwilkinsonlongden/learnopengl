#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform Material material;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {
    // ambient
    vec3 ambient = 0.2 * texture(material.diffuse, TexCoord).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * vec3(texture(material.diffuse, TexCoord));

    vec3 result = ambient + diffuse;
    FragColor = vec4(result, 1.0);
}