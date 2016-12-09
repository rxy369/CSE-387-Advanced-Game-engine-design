#include "SharedMaterialProperties.h"


static GLuint ambientMatLocation;
static GLuint diffuseMatLocation;
static GLuint specularMatLocation;
static GLuint specularExpLocation;
static GLuint emmissiveMatLocation;
static GLuint textureModeLocation;
static GLuint objectLocation;

static GLuint materialBuffer; // Identifier for the buffer. There would only be one buffer to feed several uniform blocks.
static GLint materialBlockSize = 0; // Size in bytes of both the buffer and the uniform blocks in all the the shaders. 
static GLuint materialBlockIndex; // Identifier for the uniform block.

static bool blockSizeAndOffetsSet = false; // Indicates whether or not the buffer for the blocks has been setup

const static string materialBlockName = "MaterialBlock";


void SharedMaterialProperties::setShaderMaterialProperties(Material material) {

	glBindBuffer(GL_UNIFORM_BUFFER, materialBuffer);

	if (ambientMatLocation != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, ambientMatLocation, sizeof(material.ambientMat), value_ptr(material.ambientMat));
	}
	else {
		cout << "ambient material location not set." << endl;
	}
	if (diffuseMatLocation != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, diffuseMatLocation, sizeof(material.diffuseMat), value_ptr(material.diffuseMat));
	}
	else {
		cout << "ambient material location not set." << endl;
	}
	if (specularMatLocation != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, specularMatLocation, sizeof(material.specularMat), value_ptr(material.specularMat));
	}
	else {
		cout << "ambient material location not set." << endl;
	}
	if (specularExpLocation != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, specularExpLocation, sizeof(material.specularExpMat), &material.specularExpMat);
	}
	else {
		cout << "ambient material location not set." << endl;
	}
	if (emmissiveMatLocation != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, emmissiveMatLocation, sizeof(material.emissiveMat), value_ptr(material.emissiveMat));
	}
	else {
		cout << "ambient material location not set." << endl;
	}
	if (textureModeLocation != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, textureModeLocation, sizeof(material.textureMode), &material.textureMode);
	}
	else {
		cout << "ambient material location not set." << endl;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	if (material.textureMode != NO_TEXTURE) {
		glBindTexture(GL_TEXTURE_2D, material.textureObject);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SharedMaterialProperties::setUniformBlockForShader(GLuint shaderProgram)
{
	// Determine the size of the block and set the binding point for the block(s)
	determineBlockSizeSetBindingPoint(shaderProgram);

	// Has the buffer been creates and have the byte offset been found?
	if (blockSizeAndOffetsSet == false) {

		// Set up the buffers and bind to binding points
		allocateBuffers(shaderProgram);

		// Find the byte offsets of the uniform block variables
		findOffsets(shaderProgram);
	}

	checkOpenGLErrors("setUniformBlockForShader");

} // end setUniformBlockForShader


void SharedMaterialProperties::allocateBuffers(GLuint shaderProgram)
{
	if (materialBlockSize > 0) {

		// Get an identifier for a buffer
		glGenBuffers(1, &materialBuffer);

		// Bind the buffer
		glBindBuffer(GL_UNIFORM_BUFFER, materialBuffer);

		// Allocate the buffer. Does not load data. Note the use of NULL where the data would normally be.
		// Data is not loaded because the above struct will not be byte alined with the uniform block.
		glBufferData(GL_UNIFORM_BUFFER, materialBlockSize, NULL, GL_DYNAMIC_DRAW);

		// Assign the buffer to a binding point to be the same as the uniform in the shader(s). In this case 1.
		glBindBufferBase(GL_UNIFORM_BUFFER, materialBlockBindingPoint, materialBuffer);

		blockSizeAndOffetsSet = true;
	}

	checkOpenGLErrors("findOffets");

} // end allocateBuffers


void SharedMaterialProperties::findOffsets(GLuint shaderProgram)
{
	const int numberOfNames = 6;

	GLuint uniformIndices[numberOfNames] = { 0 };
	GLint uniformOffsets[numberOfNames] = { 0 };

	const GLchar * charStringNames[] = {
		"object.ambientMat",
		"object.diffuseMat",
		"object.specularMat",
		"object.specularExp",
		"object.emmissiveMat",
		"object.textureMode" };

	glGetUniformIndices(shaderProgram, numberOfNames, (const GLchar **)charStringNames, uniformIndices);

	if (uniformIndices[0] != GL_INVALID_INDEX && uniformIndices[1] != GL_INVALID_INDEX) {
		for (int i = 0; i < numberOfNames; i++) {

			checkLocationFound(charStringNames[i], uniformIndices[i]);
		}

		//Get the offsets of the uniforms. The offsets in the buffer will be the same.
		glGetActiveUniformsiv(shaderProgram, numberOfNames, uniformIndices, GL_UNIFORM_OFFSET, uniformOffsets);

		for (int i = 0; i < numberOfNames; i++) {

			cout << '\t' << charStringNames[i] << " offset is " << uniformOffsets[i] << endl;
		}

		ambientMatLocation = uniformOffsets[0];
		diffuseMatLocation = uniformOffsets[1];
		specularMatLocation = uniformOffsets[2];
		specularExpLocation = uniformOffsets[3];
		emmissiveMatLocation = uniformOffsets[4];
		textureModeLocation = uniformOffsets[5];
	}
	else {

		cout << " Did not find names in " << materialBlockName.c_str() << endl;
	}

	checkOpenGLErrors("findOffets");

} // findOffsets


void SharedMaterialProperties::determineBlockSizeSetBindingPoint(GLuint shaderProgram)
{
	// Get the index of the "projectionViewBlock"
	materialBlockIndex = glGetUniformBlockIndex(shaderProgram, materialBlockName.c_str());

	cout << materialBlockName.c_str() << " index is " << materialBlockIndex << endl;

	if (checkLocationFound(materialBlockName.c_str(), materialBlockIndex)) {

		// Determine the size in bytes of the uniform block.
		glGetActiveUniformBlockiv(shaderProgram, materialBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &materialBlockSize);
		cout << materialBlockName.c_str() << " size is " << materialBlockSize << endl;

		// Assign the block to a binding point. In this case 2.
		glUniformBlockBinding(shaderProgram, materialBlockIndex, materialBlockBindingPoint);
	}

	checkOpenGLErrors("findBlockSizeSetBindingPoint");

} // end determineBlockSizeSetBindingPoint

bool SharedMaterialProperties::checkLocationFound(const GLchar* locationName, GLuint indice)
{
	if (indice == GL_INVALID_INDEX) {
		cout << locationName << " not found in shader." << endl;

		return false;
	}
	else {

		//cout << locationName << " index is " <<  indice << endl; 
		return true;
	}

} // end checkLocationFound


