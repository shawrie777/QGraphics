#version 330 core

#define MAX_LIGHTS 20

out vec4 FragColor;

struct spotLight {
	vec3 position;
	vec3 direction;
	float angle;
	float outerAngle;
	vec4 colour;
	vec3 attenuation;
	samplerCube depthMap;    
};

struct pointLight {
	vec3 position;
	vec4 colour;
	vec3 attenuation;
	samplerCube depthMap;
};

//struct dirLight {
//	vec3 position;
//	vec4 colour;
//	vec3 direction;
//	vec3 attenuation;
//};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform int spotLightCount;
uniform spotLight SLights[MAX_LIGHTS];

uniform int pointLightCount;
uniform pointLight PLights[MAX_LIGHTS];

//uniform int dirLightCount;
//uniform dirLight DLights[MAX_LIGHTS];

uniform bool useDifTex;
uniform bool useSpecTex;

uniform vec4 DifCol;
uniform vec4 SpecCol;

uniform sampler2D DifTex;
uniform sampler2D SpecTex;

uniform float shininess;

vec4 matDiffuse;
vec4 matSpecular;

uniform vec3 viewPos;

uniform float far_plane;

//vec4 CalcDirLight(dirLight L, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//	vec3 lightDir = normalize(-L.direction);
//	float diff = max(dot(normal, lightDir),0.0);
//	vec3 reflectDir = reflect(-lightDir,normal);
//	float spec = pow(max(dot(viewDir,reflectDir),0.0), shininess);
	
//	vec4 ambient = 0.1 * L.colour * matDiffuse;
//	vec4 diffuse = L.colour * diff * matDiffuse;
//	vec4 specular = L.colour * spec * matSpecular;

//	float distance = length(L.position - fragPos);
//	float attenuation = 1.0 / ((L.attenuation.x * distance * distance) + (L.attenuation.y * distance) + L.attenuation.z);

//	ambient *= attenuation;
//	diffuse *= attenuation;
//	specular *= attenuation;

//	return (ambient + diffuse + specular);
//}

vec4 CalcPointLight(pointLight L, vec3 normal, vec3 viewDir)
{
    vec3 lightColor = vec3(L.colour);
    
    // ambient
    vec3 ambient = 0.3 * lightColor * vec3(matDiffuse);
    // diffuse
    vec3 lightDir = normalize(L.position - FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor * vec3(matDiffuse);
    // specular
    //vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), (128.0 * shininess));
    vec3 specular = spec * lightColor * vec3(matSpecular); 

    float distance = length(L.position - FragPos);
	float attenuation = 1 / ((L.attenuation.x * distance * distance) + (L.attenuation.y * distance) + L.attenuation.z);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

    // calculate shadow

    // get vector between fragment position and light position
    vec3 fragToLight = FragPos - L.position;
    // is the fragment to light vector to sample from the depth map    
    float closestDepth = texture(L.depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;  

    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    return vec4(lighting,1.0);
}


vec4 CalcSpotLight(spotLight L, vec3 normal, vec3 viewDir)
{
    // ambient
    vec4 ambient = 0.3 * L.colour * matDiffuse;
    // diffuse shading
    vec3 lightDir = normalize(L.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec4 diffuse = L.colour * diff * matDiffuse;
    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), (128.0 * shininess));
    vec4 specular = L.colour * spec * matSpecular;

    // attenuation
    float distance = length(L.position - FragPos);
    float attenuation = 1.0 / ((L.attenuation.x * distance * distance) + (L.attenuation.y * distance) + L.attenuation.z);
    // spotlight intensity
    float theta = degrees(acos(dot(lightDir, normalize(-L.direction))));
     
    float epsilon = L.angle/2 - L.outerAngle/2;
    float intensity = 1;
    if (epsilon != 0)
    {
        intensity = clamp((theta - L.outerAngle/2) / epsilon, 0.0, 1.0);
    }
    else
    {
        intensity = L.angle/2  - theta > 0 ? 1.0 : 0.0;
    }
    
    // combine results
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    // calculate shadow

    // get vector between fragment position and light position
    vec3 fragToLight = FragPos - L.position;
    // is the fragment to light vector to sample from the depth map    
    float closestDepth = texture(L.depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;  


    return (ambient + (1.0 - shadow) * (diffuse + specular));
}

//	for (int i=0; i < dirLightCount; i++)
//		result += CalcDirLight(DLights[i], norm, FragPos, viewDir);

void main()
{
    if (useDifTex)
    {
        matDiffuse = texture(DifTex, TexCoords);
    }
    else
    {
        matDiffuse = DifCol;
    }

    if (useSpecTex)
    {
        matSpecular = texture(SpecTex,TexCoords);
    }
    else
    {
        matSpecular = SpecCol;
    }
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec4 result = vec4(0.0,0.0,0.0,0.0);

    for (int i=0; i < pointLightCount; i++)
		result += CalcPointLight(PLights[i], normal, viewDir);
    
    for (int i=0; i < spotLightCount; i++)
        result += CalcSpotLight(SLights[i], normal, viewDir);

    FragColor = result;
}