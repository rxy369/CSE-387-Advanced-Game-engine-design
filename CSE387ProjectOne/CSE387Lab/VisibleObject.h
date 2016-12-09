#pragma once

#include "BasicIncludesAndDefines.h"

class VisibleObject
{

public:

	VisibleObject() :numberOfIndices(0) {};
	~VisibleObject() {};

	// Set the shader program for this object
	void setShader(GLuint shaderProgram) { this->shaderProgram = shaderProgram; }

	void setTexture(GLuint texture) { this->textureObject = texture; }

	// Set the modeling transformation that will be used when this object is rendered
	void setModelingTransformation(glm::mat4 modelingTransformation)
	{
		this->modelingTransformation = modelingTransformation;
	}

	// Initializes this object
	virtual void initialize() = 0;

	// "Renders" this object
	virtual void draw() = 0;

	void update(float deltaTime) {}

	// Material properties of the object (public so that is can be adjusted
	// outside the class)
	SharedMaterialProperties material;
	Material mat;

	GLuint shaderProgram, shaderProgram2;

protected:


	GLuint vertexArrayObject;

	GLuint textureObject;

	int numberOfIndices;

	glm::mat4 modelingTransformation;

	GLuint modelLocation;

};

