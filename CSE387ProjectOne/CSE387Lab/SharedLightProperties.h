#pragma once

#include "BasicIncludesAndDefines.h"

#define lightBlockBindingPoint 16

struct Light
{
	Light()
	{
		setDefaultProperties();
	}

	void setDefaultProperties()
	{
		ambientColor = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
		diffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		specularColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		positionOrDirection = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
		spotDirection = glm::vec3(0.0f, -1.0f, 0.0f);
		isSpot = 0;
		spotCutoffCos = cos(glm::radians(10.0f));
		spotExponent = 0.9f;
		enabled = 1;
	}

	void setAmbientColor(glm::vec4 ambientColor)
	{
		this->ambientColor = ambientColor;
	}

	void setDiffuseColor(glm::vec4 diffuseColor)
	{
		this->diffuseColor = diffuseColor;
	}

	void setSpecularColor(glm::vec4 specularColor)
	{
		this->specularColor = specularColor;
	}
	void setPositionOrDirection(glm::vec4 positionOrDirection)
	{
		this->positionOrDirection = positionOrDirection;
	}
	void setSpotDirection(glm::vec3 spotDirection)
	{
		this->spotDirection = spotDirection;
	}
	void setIsSpot(int isSpot)
	{
		this->isSpot = isSpot;
	}
	void setSpotCutoffCos(float spotCutoffCos)
	{
		this->spotCutoffCos = spotCutoffCos;
	}
	void setSpotExponent(float spotExponent)
	{
		this->spotExponent = spotExponent;
	}
	void setEnabled(int enabled)
	{
		this->enabled = enabled;
	}

	glm::vec4 ambientColor;

	glm::vec4 diffuseColor;

	glm::vec4 specularColor;

	glm::vec4 positionOrDirection;

	glm::vec3 spotDirection;

	int isSpot; // is it a spot light?

	float spotCutoffCos; // if its a spot light where does it cut off at?

	float spotExponent; // the spot light's exponent

	int enabled; // if the light's enabled or not

};



class SharedLightProperties
{
public:

	// Should be called for each shader program that includes the
	// projectionViewBlock and worldEyeBlock uniform blocks.
	static void setUniformBlockForShader(GLuint shaderProgram);

	// Call the set the material properties in the shader before 
	// rendering the object.
	static void setShaderLightProperties(Light light1, Light light2, Light light3);

protected:

	// Finds the byte offsets of the variables in the two uniform 
	// blocks.
	static void findOffsets(GLuint shaderProgram);

	// Creates the buffers and binds them to the binding points.
	static void allocateBuffers(GLuint shaderProgram);

	// Determines the sizes in bytes of the blocks and binds them to the binding points. 
	static void determineBlockSizeSetBindingPoint(GLuint shaderProgram);

	static bool checkLocationFound(const GLchar* locationName, GLuint indice);

};