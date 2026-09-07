#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

in vec2 TexCoord;

uniform Material material;

void main() {
    // ambient
    vec3 ambient = 0.1 * texture(material.diffuse, TexCoord).rgb;

    FragColor = vec4(ambient, 1.0);
}