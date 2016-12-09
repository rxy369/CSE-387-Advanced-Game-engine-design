#include "SharedLightProperties.h"

//property location for the first light
static GLuint ambientColorLocation1;
static GLuint diffuseColorLocation1;
static GLuint specularColorLocation1;
static GLuint positionOrDirectionLocation1;
static GLuint spotDirectionLocation1;
static GLuint isSpotLocation1;
static GLuint spotCutoffCosLocation1;
static GLuint spotExponentLocation1;
static GLuint enabledLocation1;

//property location for the second light
static GLuint ambientColorLocation2;
static GLuint diffuseColorLocation2;
static GLuint specularColorLocation2;
static GLuint positionOrDirectionLocation2;
static GLuint spotDirectionLocation2;
static GLuint isSpotLocation2;
static GLuint spotCutoffCosLocation2;
static GLuint spotExponentLocation2;
static GLuint enabledLocation2;

//property location for the third light
static GLuint ambientColorLocation3;
static GLuint diffuseColorLocation3;
static GLuint specularColorLocation3;
static GLuint positionOrDirectionLocation3;
static GLuint spotDirectionLocation3;
static GLuint isSpotLocation3;
static GLuint spotCutoffCosLocation3;
static GLuint spotExponentLocation3;
static GLuint enabledLocation3;

// identifies the buffer, used for multiple uniform blocks
static GLuint lightBuffer; 
//the size of both the buffer and uniformblocks for all the shaders. In bytes. 
static GLint lightBlockSize = 0; 
// Identifier for the uniform block.
static GLuint lightBlockIndex; 

static bool blockSizeAndOffetsSet = false; //Whetehr or not the buffer for the blocks have been set up

const static string lightBlockName = "LightBlock";


//holds the location of all the light properties
void SharedLightProperties::setShaderLightProperties(Light light1, Light light2, Light light3) {

	glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);

	if (ambientColorLocation1 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, ambientColorLocation1, sizeof(light1.ambientColor), value_ptr(light1.ambientColor));
	}
	else {
		cout << "the location for ambient material is not set." << endl;
	}
	if (diffuseColorLocation1 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, diffuseColorLocation1, sizeof(light1.diffuseColor), value_ptr(light1.diffuseColor));
	}
	else {
		cout << "the location for diffuse material is not set." << endl;
	}
	if (specularColorLocation1 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, specularColorLocation1, sizeof(light1.specularColor), value_ptr(light1.specularColor));
	}
	else {
		cout << "the location for specular material is not set." << endl;
	}
	if (positionOrDirectionLocation1 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, positionOrDirectionLocation1, sizeof(light1.positionOrDirection), value_ptr(light1.positionOrDirection));
	}
	else {
		cout << "the location for position or direction is not set." << endl;
	}
	if (spotDirectionLocation1 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, spotDirectionLocation1, sizeof(light1.spotDirection), value_ptr(light1.spotDirection));
	}
	else {
		cout << "the location for spotDirection is not set." << endl;
	}
	if (isSpotLocation1 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, isSpotLocation1, sizeof(light1.isSpot), &light1.isSpot);
	}
	else {
		cout << "the location for isSpotLocation is not set." << endl;
	}
	if (spotCutoffCosLocation1 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, spotCutoffCosLocation1, sizeof(light1.spotCutoffCos), &light1.spotCutoffCos);
	}
	else {
		cout << "the location for spotCutoffLocation is not set." << endl;
	}
	if (spotExponentLocation1 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, spotExponentLocation1, sizeof(light1.spotExponent), &light1.spotExponent);
	}
	else {
		cout << "the location for spotExponential is not set." << endl;
	}
	if (enabledLocation1 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, enabledLocation1, sizeof(light1.enabled), &light1.enabled);
	}
	else {
		cout << "the location for enabledLocation1 is not set." << endl;
	}
	if (ambientColorLocation2 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, ambientColorLocation2, sizeof(light2.ambientColor), value_ptr(light2.ambientColor));
	}
	else {
		cout << "the location for ambient color 2 is not set." << endl;
	}
	if (diffuseColorLocation2 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, diffuseColorLocation2, sizeof(light2.diffuseColor), value_ptr(light2.diffuseColor));
	}
	else {
		cout << "the location for diffuse color 2 is not set." << endl;
	}
	if (specularColorLocation2 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, specularColorLocation2, sizeof(light2.specularColor), value_ptr(light2.specularColor));
	}
	else {
		cout << "the location for specular color 2 is not set." << endl;
	}
	if (positionOrDirectionLocation2 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, positionOrDirectionLocation2, sizeof(light2.positionOrDirection), value_ptr(light2.positionOrDirection));
	}
	else {
		cout << "the location for position or direction is not set." << endl;
	}
	if (spotDirectionLocation2 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, spotDirectionLocation2, sizeof(light2.spotDirection), value_ptr(light2.spotDirection));
	}
	else {
		cout << "the location for spot direction 2 is not set." << endl;
	}
	if (isSpotLocation2 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, isSpotLocation2, sizeof(light2.isSpot), &light2.isSpot);
	}
	else {
		cout << "the location for is spot 2 is not set." << endl;
	}
	if (spotCutoffCosLocation2 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, spotCutoffCosLocation2, sizeof(light2.spotCutoffCos), &light2.spotCutoffCos);
	}
	else {
		cout << "the location for spot cutoff cos 2 is not set." << endl;
	}
	if (spotExponentLocation2 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, spotExponentLocation2, sizeof(light2.spotExponent), &light2.spotExponent);
	}
	else {
		cout << "the location for spot eponent 2 is not set." << endl;
	}
	if (enabledLocation2 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, enabledLocation2, sizeof(light2.enabled), &light2.enabled);
	}
	else {
		cout << "the location for enabled 2 is not set." << endl;
	}
	if (ambientColorLocation3 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, ambientColorLocation3, sizeof(light3.ambientColor), value_ptr(light3.ambientColor));
	}
	else {
		cout << "the location for ambient color 3 is not set." << endl;
	}
	if (diffuseColorLocation3 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, diffuseColorLocation3, sizeof(light3.diffuseColor), value_ptr(light3.diffuseColor));
	}
	else {
		cout << "the location for diffuse color 3 is not set." << endl;
	}
	if (specularColorLocation3 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, specularColorLocation3, sizeof(light3.specularColor), value_ptr(light3.specularColor));
	}
	else {
		cout << "the location for specular color 3 is not set." << endl;
	}
	if (positionOrDirectionLocation3 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, positionOrDirectionLocation3, sizeof(light3.positionOrDirection), value_ptr(light3.positionOrDirection));
	}
	else {
		cout << "the location for position or direction 3 is not set." << endl;
	}
	if (spotDirectionLocation3 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, spotDirectionLocation3, sizeof(light3.spotDirection), value_ptr(light3.spotDirection));
	}
	else {
		cout << "the location for spot Direction 3 is not set." << endl;
	}
	if (isSpotLocation3 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, isSpotLocation3, sizeof(light3.isSpot), &light3.isSpot);
	}
	else {
		cout << "the location for is spot location 3 is not set." << endl;
	}
	if (spotCutoffCosLocation3 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, spotCutoffCosLocation3, sizeof(light3.spotCutoffCos), &light3.spotCutoffCos);
	}
	else {
		cout << "the location for spot cut off 3 is not set." << endl;
	}
	if (spotExponentLocation3 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, spotExponentLocation3, sizeof(light3.spotExponent), &light3.spotExponent);
	}
	else {
		cout << "the location for spot exponent 3 is not set." << endl;
	}
	if (enabledLocation3 != 0xFFFFFFFF) {
		glBufferSubData(GL_UNIFORM_BUFFER, enabledLocation3, sizeof(light3.enabled), &light3.enabled);
	}
	else {
		cout << "the location for enabled is not set." << endl;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void SharedLightProperties::setUniformBlockForShader(GLuint shaderProgram)
{
	// Sets the binding point for the blocks and find the size of the block
	determineBlockSizeSetBindingPoint(shaderProgram);

	//checks if the buffer has been created and if the byte offset has been found
	if (blockSizeAndOffetsSet == false) {

		// Set up the buffers and bind to binding points
		allocateBuffers(shaderProgram);

		// Find the byte offsets of the uniform block variables
		findOffsets(shaderProgram);
	}

	checkOpenGLErrors("setUniformBlockForShader");

} // end setUniformBlockForShader


void SharedLightProperties::allocateBuffers(GLuint shaderProgram)
{
	if (lightBlockSize > 0) {

		// Get an identifier for a buffer
		glGenBuffers(1, &lightBuffer);

		// Bind the buffer
		glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);

		// Allocate the buffer. Does not load data. Note the use of NULL where the data would normally be.
		// Data is not loaded because the above struct will not be byte alined with the uniform block.
		glBufferData(GL_UNIFORM_BUFFER, lightBlockSize, NULL, GL_DYNAMIC_DRAW);

		// Assign the buffer to a binding point to be the same as the uniform in the shader(s). In this case 1.
		glBindBufferBase(GL_UNIFORM_BUFFER, lightBlockBindingPoint, lightBuffer);

		blockSizeAndOffetsSet = true;
	}

	checkOpenGLErrors("findOffets");

} // end allocateBuffers


void SharedLightProperties::findOffsets(GLuint shaderProgram)
{
	const int numberOfNames = 27;

	GLuint uniformIndices[numberOfNames] = { 0 };
	GLint uniformOffsets[numberOfNames] = { 0 };

	const GLchar * charStringNames[] = {
		"light1.ambientColor",
		"light1.diffuseColor",
		"light1.specularColor",
		"light1.positionOrDirection",
		"light1.spotDirection",
		"light1.isSpot",
		"light1.spotCutoffCos",
		"light1.spotExponent",
		"light1.enabled",
		"light2.ambientColor",
		"light2.diffuseColor",
		"light2.specularColor",
		"light2.positionOrDirection",
		"light2.spotDirection",
		"light2.isSpot",
		"light2.spotCutoffCos",
		"light2.spotExponent",
		"light2.enabled",
		"light3.ambientColor",
		"light3.diffuseColor",
		"light3.specularColor",
		"light3.positionOrDirection",
		"light3.spotDirection",
		"light3.isSpot",
		"light3.spotCutoffCos",
		"light3.spotExponent",
		"light3.enabled" };

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

		ambientColorLocation1 = uniformOffsets[0];
		diffuseColorLocation1 = uniformOffsets[1];
		specularColorLocation1 = uniformOffsets[2];
		positionOrDirectionLocation1 = uniformOffsets[3];
		spotDirectionLocation1 = uniformOffsets[4];
		isSpotLocation1 = uniformOffsets[5];
		spotCutoffCosLocation1 = uniformOffsets[6];
		spotExponentLocation1 = uniformOffsets[7];
		enabledLocation1 = uniformOffsets[8];
		ambientColorLocation2 = uniformOffsets[9];
		diffuseColorLocation2 = uniformOffsets[10];
		specularColorLocation2 = uniformOffsets[11];
		positionOrDirectionLocation2 = uniformOffsets[12];
		spotDirectionLocation2 = uniformOffsets[13];
		isSpotLocation2 = uniformOffsets[14];
		spotCutoffCosLocation2 = uniformOffsets[15];
		spotExponentLocation2 = uniformOffsets[16];
		enabledLocation2 = uniformOffsets[17];
		ambientColorLocation3 = uniformOffsets[18];
		diffuseColorLocation3 = uniformOffsets[19];
		specularColorLocation3 = uniformOffsets[20];
		positionOrDirectionLocation3 = uniformOffsets[21];
		spotDirectionLocation3 = uniformOffsets[22];
		isSpotLocation3 = uniformOffsets[23];
		spotCutoffCosLocation3 = uniformOffsets[24];
		spotExponentLocation3 = uniformOffsets[25];
		enabledLocation3 = uniformOffsets[26];
	}
	else {

		cout << " Did not find names in " << lightBlockName.c_str() << endl;
	}

	checkOpenGLErrors("findOffets");

} // findOffsets


void SharedLightProperties::determineBlockSizeSetBindingPoint(GLuint shaderProgram)
{
	// Get the index of the "projectionViewBlock"
	lightBlockIndex = glGetUniformBlockIndex(shaderProgram, lightBlockName.c_str());

	cout << lightBlockName.c_str() << " index is " << lightBlockIndex << endl;

	if (checkLocationFound(lightBlockName.c_str(), lightBlockIndex)) {

		// Determine the size in bytes of the uniform block.
		glGetActiveUniformBlockiv(shaderProgram, lightBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &lightBlockSize);
		cout << lightBlockName.c_str() << " size is " << lightBlockSize << endl;

		// Assign the block to a binding point. In this case 2.
		glUniformBlockBinding(shaderProgram, lightBlockIndex, lightBlockBindingPoint);
	}

	checkOpenGLErrors("findBlockSizeSetBindingPoint");

} // end determineBlockSizeSetBindingPoint

bool SharedLightProperties::checkLocationFound(const GLchar* locationName, GLuint indice)
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

