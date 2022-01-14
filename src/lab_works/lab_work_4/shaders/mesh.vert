#version 450

layout( location = 0 ) in vec3 aVertexPosition;
layout( location = 1 ) in vec3 aVertexNormal;
layout( location = 2 ) in vec2 aVertexTexCoords;
layout( location = 3 ) in vec3 aVertexTangent;
layout( location = 4 ) in vec3 aVertexBitagent;
out vec3 FragPos ;  
out vec3 LightPos;
out vec3 Normal ; 

uniform mat4 uMVPMatrix; // Projection * View * Model   
uniform mat4 uModelMatrix ; 
uniform mat4 uViewMatrix ;
uniform mat4 uProjectionMatrix ;
uniform mat3 uNormalMatrix;
uniform vec3 lightPos    ; //We now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. LightPos is currently in World Space


void main()
{
    Normal=uNormalMatrix*aVertexNormal;
    LightPos=vec3(uViewMatrix*vec4(lightPos,1.0) ); //Transform world_space light position to view-space light position 
	gl_Position =uMVPMatrix* vec4( aVertexPosition, 1.f );        //View Space   
    FragPos=vec3(uViewMatrix*uModelMatrix*vec4(aVertexPosition, 1.f) );

}
