#version 450

layout( location = 0 ) out vec4 fragColor;  

uniform vec3 ambient ;  
uniform vec3 diffuse ;  
uniform vec3 specular ;
uniform vec3 shininess ;      
//________________________________________________________
uniform bool uHasDiffuseMap ;  
layout(binding=1) uniform sampler2D uDiffuseMap ;  
uniform vec3 lightColor;
uniform vec3 objectColor ;
in vec3 FragPos ;
in vec3 LightPos  ; 
in vec3 Normal;
in vec2 TextCoord ;




void main()
{   

vec4 textColor=texture(uDiffuseMap,TextCoord) ;   


//______Ambient__________
vec3 ambient = 0.9 * ambient;
//______Difuse___________  
 vec3 norm=normalize(Normal);  
 vec3 lightDir=normalize(LightPos-FragPos) ;  
 float diff=max(dot(norm,lightDir),0.0);  
 vec3 diffuse=diff*lightDir ; 

//______Sepecular________
float specularStrength=0.5 ;  
vec3 viewDir=normalize(-FragPos) ;  
vec3 reflectDir=reflect(-lightDir,norm) ;   
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = specularStrength * spec * lightColor; 
vec3 result=(ambient+diffuse+specular)*objectColor ;

fragColor = textColor;
}
