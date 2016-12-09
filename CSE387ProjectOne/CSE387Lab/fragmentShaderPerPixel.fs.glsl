// Targeting version 4.2 of GLSL. 
#version 420 core

#pragma optimize(off)
#pragma debug(on)

// Declare default precision - eliminates warnings 
precision mediump float;

out vec4 fragmentColor;

vec4 color0;
in vec2 TexCoord0;

in vec4 vertexWorldPosition;
in vec4 vertexWorldNormal;

// Create a to sampler
uniform sampler2D gSampler;
//uniform int textureMode;

layout (shared) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

struct Material
{
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	vec4 emmissiveMat;
	float specularExp;
	int textureMode;
};

layout (shared) uniform MaterialBlock
{
	Material object;
};

//uniform Material object;

struct Light {

	vec4 ambientColor; // ambient color of the light 
	vec4 diffuseColor; // diffuse color of the light 
	vec4 specularColor; // specular color of the light
	vec4 positionOrDirection;
	
	// spotlight attributes 
	// the direction the cone of light is shinning 
	vec3 spotDirection; 

	// 1 if the light is a spotlight 
	int isSpot; 
	 
	// Cosine of the spot cutoff angle float spotExponent;
	float spotCutoffCos; 
	
	float spotExponent; // For gradual falloff near cone edge 

	int enabled; // 1 if light is "on"  
};

/*
uniform Light light1; 
uniform Light light2;
uniform Light light3;
*/

layout (shared) uniform LightBlock { 
	Light light1; 
	Light light2; 
	Light light3; 
};

vec3 shadingCalculation(Light light, Material object )
{
	vec3 totalFromThisLight = vec3(0.0, 0.0, 0.0);

	if (light.enabled == 1) {

		// Calculate a bunch of vectors
		vec3 lightVector;
		if (light.positionOrDirection.w < 1) {
			// Directional
			lightVector = normalize(light.positionOrDirection.xyz);
		}
		else {
			// Positional
			lightVector = normalize(light.positionOrDirection.xyz - 
				vertexWorldPosition.xyz );
		}

		vec3 reflection = normalize( reflect(-lightVector, vertexWorldNormal.xyz) );
		vec3 eyeVector = normalize(worldEyePosition - vertexWorldPosition.xyz);

		float spotCosFactor = 0; 
		if (light.isSpot == 1) {
			spotCosFactor = dot (-lightVector, normalize(light.spotDirection));
		}	

		// Is it a spot light and are we in the cone?
		if( light.isSpot < 1 ||  (light.isSpot == 1 && spotCosFactor >= light.spotCutoffCos)) {
			// Ambient Reflection
			totalFromThisLight += object.ambientMat.xyz * light.ambientColor.xyz;

			// Diffuse Reflection
			totalFromThisLight += max(dot(vertexWorldNormal.xyz, lightVector ), 0) *
				object.diffuseMat.xyz * light.diffuseColor.xyz;
            
            // Specular Reflection
			totalFromThisLight += pow( max( dot( reflection, eyeVector ), 0), object.specularExp) *
			object.specularMat.xyz * light.specularColor.xyz;
		}
	}

	return totalFromThisLight;
	//return vec3(0.0,1.0,0.0);

} // end shadingCalculation

void main()
{
	
	if(object.textureMode == 0){
		color0 = object.emmissiveMat +
			  vec4(shadingCalculation(light1, object),1.0) + 
			  vec4(shadingCalculation(light2, object),1.0) + 
			  vec4(shadingCalculation(light3, object),1.0);

		fragmentColor = color0;
	}
	else if (object.textureMode == 1){
		fragmentColor = texture2D(gSampler, TexCoord0.st);
	}
	else{
		
		Material myObject = object;

		myObject.ambientMat = texture2D(gSampler, TexCoord0.st);
		myObject.diffuseMat = texture2D(gSampler, TexCoord0.st);

		color0 = object.emmissiveMat +
			  vec4(shadingCalculation(light1, myObject),1.0) + 
			  vec4(shadingCalculation(light2, myObject),1.0) + 
			  vec4(shadingCalculation(light3, myObject),1.0);

		fragmentColor = color0;
	}

}