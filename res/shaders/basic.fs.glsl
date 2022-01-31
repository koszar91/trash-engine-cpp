#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    
    bool useDiffuseMap, useSpecularMap;
    sampler2D diffuseMap;
    sampler2D specularMap;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float c, l, q;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};



in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


uniform vec3 viewPos;
uniform DirLight dirLight;
uniform Material material;


out vec4 FragColor;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 getBaseSpecular(Material material, vec2 texCoords);
vec3 getBaseDiffuse(Material material, vec2 texCoords);


void main()
{    
    vec3 result = vec3(0, 0, 0);

    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // directional lights
    result += CalcDirLight(dirLight, norm, viewDir);

    // point lights
    // ...

    FragColor = vec4(result, 1.0);
}


vec3 getBaseSpecular(Material material, vec2 texCoords) {
    if (material.useSpecularMap) {
        return texture(material.specularMap, texCoords).rgb;
    }
    return material.specular;
}
vec3 getBaseDiffuse(Material material, vec2 texCoords) {
    if (material.useDiffuseMap) {
        return texture(material.diffuseMap, texCoords).rgb * material.diffuse;
    }
    return material.diffuse;
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results

    vec3 ambient = light.ambient * getBaseDiffuse(material, TexCoords);
    vec3 diffuse = light.diffuse * diff * getBaseDiffuse(material, TexCoords);
    vec3 specular = light.specular * spec * getBaseSpecular(material, TexCoords);
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float d = length(light.position - fragPos);
    float attenuation = light.c + light.l * d + light.q * (d * d);    
    // combine results
    vec3 ambient = light.ambient * getBaseDiffuse(material, TexCoords);
    vec3 diffuse = light.diffuse * diff * getBaseDiffuse(material, TexCoords);
    vec3 specular = light.specular * spec * getBaseSpecular(material, TexCoords);
    return (ambient + diffuse + specular) / attenuation;
}
