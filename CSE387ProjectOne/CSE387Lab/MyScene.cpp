#include "MyScene.h"


MyScene::MyScene()
	:sphere(1, 64, 64), earth(0.5), moon(0.25)
{
	cout << "Scene Constructor Called." << endl;
}


MyScene::~MyScene()
{
	cout << "Scene Destructor Called." << endl;

	// Delete shader programs and vertex array object
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void MyScene::initialize()
{
	checkOpenGLErrors("MyScene::initialize0");

	// Initialize OpenGL 
	glEnable(GL_DEPTH_TEST); // Turn depth testing
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set the window clear color

										  // Build shader proram
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "vertexShader.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "fragmentShader.fs.glsl" },
		{ GL_NONE, NULL } // signals that there are no more shaders 
	};

	shaderProgram2 = BuildShaderProgram(shaders);
	checkOpenGLErrors("MyScene::initialize1");

	// Set up the uniform block for this shader
	SharedProjectionAndViewing::setUniformBlockForShader(shaderProgram2);

	// Build shader proram
	ShaderInfo shaders2[] = {
		{ GL_VERTEX_SHADER, "vertexShaderPerPixel.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "fragmentShaderPerPixel.fs.glsl" },
		{ GL_NONE, NULL } // signals that there are no more shaders 
	};

	shaderProgram = BuildShaderProgram(shaders2);
	checkOpenGLErrors("MyScene::initialize1.5");

	// Set up the uniform block for this shader
	SharedProjectionAndViewing::setUniformBlockForShader(shaderProgram);

	cube.setShader(shaderProgram);
	cube.initialize();
	cube.mat.setAmbientAndDiffuseMat(glm::vec4(0.1f, 0.1f, 1.0f, 1.0f));
	cube.setTexture(textureObject);
	cube.mat.setupTexture("BRICK.BMP");

	sphere.setShader(shaderProgram);
	sphere.initialize();
	sphere.mat.setAmbientAndDiffuseMat(glm::vec4(1.0f, 1.0f, 0.1f, 1.0f));
	sphere.setTexture(textureObject);
	sphere.mat.setupTexture("BRICK.BMP");

	earth.setShader(shaderProgram);
	earth.initialize();
	earth.mat.setAmbientAndDiffuseMat(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
	earth.setTexture(textureObject);
	earth.mat.setupTexture("BRICK.BMP");

	moon.setShader(shaderProgram);
	moon.initialize();
	moon.setTexture(textureObject);
	moon.mat.setupTexture("BRICK.BMP");

	checkOpenGLErrors("MyScene::initialize2");

	// Viewing transformation
	glm::mat4  viewingTransformation = glm::lookAt(glm::vec3(0.0f, 35.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f));

	// Set viewing transformation
	SharedProjectionAndViewing::setViewMatrix(viewingTransformation);

	checkOpenGLErrors("MyScene::initialize3");
	// Light 1
	glm::vec4 light1AmbColor(0.15f, 0.15f, 0.15f, 1.0f);
	glm::vec4 light1DifColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 light1SpecColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 light1PositionOfDirection(5.0f, 5.0f, 5.0f, 1.0f);
	glm::vec3 light1SpotDirection(0.0f, -1.0f, 0.0f);
	GLint light1IsSpot = 0;
	GLfloat light1SpotCutOff = cos(glm::radians(10.0f));
	GLfloat light1SpotExponent = 0.9f;
	GLint light1Enabled = 1;
	light1.setAmbientColor(light1AmbColor);
	light1.setDiffuseColor(light1DifColor);
	light1.setSpecularColor(light1SpecColor);
	light1.setPositionOrDirection(light1PositionOfDirection);
	light1.setSpotDirection(light1SpotDirection);
	light1.setIsSpot(light1IsSpot);
	light1.setSpotCutoffCos(light1SpotCutOff);
	light1.setSpotExponent(light1SpotExponent);
	light1.setEnabled(light1Enabled);

	//old light 1 properties
	/*
	GLuint lightt1AmbLocation = glGetUniformLocation(shaderProgram, "light1.ambientColor");
	assert(lightt1AmbLocation != 0xFFFFFFFF);
	glUniform4fv(lightt1AmbLocation, 1, glm::value_ptr(light1AmbColor));

	GLuint lightt1DiffLocation = glGetUniformLocation(shaderProgram, "light1.diffuseColor");
	assert(lightt1DiffLocation != 0xFFFFFFFF);
	glUniform4fv(lightt1DiffLocation, 1, glm::value_ptr(light1DifColor));

	GLuint lightt1SpecLocation = glGetUniformLocation(shaderProgram, "light1.specularColor");
	//	assert(lightt1SpecLocation != 0xFFFFFFFF);
	glUniform4fv(lightt1SpecLocation, 1, glm::value_ptr(light1SpecColor));

	GLuint lightt1DirectLocation = glGetUniformLocation(shaderProgram, "light1.positionOrDirection");
	assert(lightt1DirectLocation != 0xFFFFFFFF);
	glUniform4fv(lightt1DirectLocation, 1, glm::value_ptr(light1PositionOfDirection));

	GLuint lightt1SpotDirectLocation = glGetUniformLocation(shaderProgram, "light1.spotDirection");
	assert(lightt1SpotDirectLocation != 0xFFFFFFFF);
	glUniform3fv(lightt1SpotDirectLocation, 1, glm::value_ptr(light1SpotDirection));

	GLuint lightt1IsSpotLocation = glGetUniformLocation(shaderProgram, "light1.isSpot");
	assert(lightt1IsSpotLocation != 0xFFFFFFFF);
	glUniform1i(lightt1IsSpotLocation, light1IsSpot);

	GLuint lightt1SpotCutOffLocation = glGetUniformLocation(shaderProgram, "light1.spotCutoffCos");
	//	assert(lightt1SpotCutOffLocation != 0xFFFFFFFF);
	glUniform1f(lightt1SpotCutOffLocation, light1SpotCutOff);

	GLuint lightt1SpotExponentLocation = glGetUniformLocation(shaderProgram, "light1.spotExponent");
	//	assert(lightt1SpotExponentLocation != 0xFFFFFFFF);
	glUniform1f(lightt1SpotExponentLocation, light1SpotExponent);

	GLuint lightt1EnabledLocation = glGetUniformLocation(shaderProgram, "light1.enabled");
	assert(lightt1EnabledLocation != 0xFFFFFFFF);
	glUniform1i(lightt1EnabledLocation, light1Enabled);
	checkOpenGLErrors("MyScene::initialize4");
	*/
	// Light 2
	glm::vec4 light2AmbColor(0.15f, 0.15f, 0.15, 1.0f);
	glm::vec4 light2DifColor(0.75f, 0.75f, 0.75f, 1.0f);
	glm::vec4 light2SpecColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 light2PositionOfDirection(1.0f, 1.0f, 1.0f, 0.0f);
	glm::vec3 light2SpotDirection(0.0f, -1.0f, 0.0f);
	GLint light2IsSpot = 0;
	GLfloat light2SpotCutOff = glm::cos(glm::radians(10.0f));
	GLfloat light2SpotExponent = 0.9f;
	GLint light2Enabled = 0;
	light2.setAmbientColor(light2AmbColor);
	light2.setDiffuseColor(light2DifColor);
	light2.setSpecularColor(light2SpecColor);
	light2.setPositionOrDirection(light2PositionOfDirection);
	light2.setSpotDirection(light2SpotDirection);
	light2.setIsSpot(light2IsSpot);
	light2.setSpotCutoffCos(light2SpotCutOff);
	light2.setSpotExponent(light2SpotExponent);
	light2.setEnabled(light2Enabled);

	//old light 2 properties
	/*
	GLuint light2AmbLocation = glGetUniformLocation(shaderProgram, "light2.ambientColor");
	assert(light2AmbLocation != 0xFFFFFFFF);
	glUniform4fv(light2AmbLocation, 1, glm::value_ptr(light2AmbColor));

	GLuint light2DiffLocation = glGetUniformLocation(shaderProgram, "light2.diffuseColor");
	assert(light2DiffLocation != 0xFFFFFFFF);
	glUniform4fv(light2DiffLocation, 1, glm::value_ptr(light2DifColor));

	GLuint light2SpecLocation = glGetUniformLocation(shaderProgram, "light2.specularColor");
	//	assert(light2SpecLocation != 0xFFFFFFFF);
	glUniform4fv(light2SpecLocation, 1, glm::value_ptr(light2SpecColor));

	GLuint light2DirectLocation = glGetUniformLocation(shaderProgram, "light2.positionOrDirection");
	assert(light2DirectLocation != 0xFFFFFFFF);
	glUniform4fv(light2DirectLocation, 1, glm::value_ptr(light2PositionOfDirection));

	GLuint light2SpotDirectLocation = glGetUniformLocation(shaderProgram, "light2.spotDirection");
	assert(light2SpotDirectLocation != 0xFFFFFFFF);
	glUniform3fv(light2SpotDirectLocation, 1, glm::value_ptr(light2SpotDirection));

	GLuint light2IsSpotLocation = glGetUniformLocation(shaderProgram, "light2.isSpot");
	assert(light2IsSpotLocation != 0xFFFFFFFF);
	glUniform1i(light2IsSpotLocation, light2IsSpot);

	GLuint light2SpotCutOffLocation = glGetUniformLocation(shaderProgram, "light2.spotCutoffCos");
	//	assert(light2SpotCutOffLocation != 0xFFFFFFFF);
	glUniform1f(light2SpotCutOffLocation, light2SpotCutOff);

	GLuint light2SpotExponentLocation = glGetUniformLocation(shaderProgram, "light2.spotExponent");
	//	assert(light2SpotExponentLocation != 0xFFFFFFFF);
	glUniform1f(light2SpotExponentLocation, light2SpotExponent);

	GLuint light2EnabledLocation = glGetUniformLocation(shaderProgram, "light2.enabled");
	assert(light2EnabledLocation != 0xFFFFFFFF);
	glUniform1i(light2EnabledLocation, light2Enabled);
	checkOpenGLErrors("MyScene::initialize5");
	*/
	// Light 3
	glm::vec4 light3AmbColor(0.15f, 0.15f, 0.15, 1.0f);
	glm::vec4 light3DifColor(0.9f, 0.9f, 0.9f, 1.0f);
	glm::vec4 light3SpecColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 light3PositionOfDirection(0.0f, 0.0f, 12.0f, 1.0f);
	glm::vec3 light3SpotDirection(0.0f, 0.0f, -1.0f);
	GLint light3IsSpot = 1;
	GLfloat light3SpotCutOff = glm::cos(glm::radians(10.0f));
	GLfloat light3SpotExponent = 0.9f;
	GLint light3Enabled = 1;
	light3.setAmbientColor(light3AmbColor);
	light3.setDiffuseColor(light3DifColor);
	light3.setSpecularColor(light3SpecColor);
	light3.setPositionOrDirection(light3PositionOfDirection);
	light3.setSpotDirection(light3SpotDirection);
	light3.setIsSpot(light3IsSpot);
	light3.setSpotCutoffCos(light3SpotCutOff);
	light3.setSpotExponent(light3SpotExponent);
	light3.setEnabled(light3Enabled);

	//old light 3 properties
	/*
	GLuint light3AmbLocation = glGetUniformLocation(shaderProgram, "light3.ambientColor");
	assert(light3AmbLocation != 0xFFFFFFFF);
	glUniform4fv(light3AmbLocation, 1, glm::value_ptr(light3AmbColor));

	GLuint light3DiffLocation = glGetUniformLocation(shaderProgram, "light3.diffuseColor");
	assert(light3DiffLocation != 0xFFFFFFFF);
	glUniform4fv(light3DiffLocation, 1, glm::value_ptr(light3DifColor));

	GLuint light3SpecLocation = glGetUniformLocation(shaderProgram, "light3.specularColor");
	//	assert(light3SpecLocation != 0xFFFFFFFF);
	glUniform4fv(light3SpecLocation, 1, glm::value_ptr(light3SpecColor));

	GLuint light3DirectLocation = glGetUniformLocation(shaderProgram, "light3.positionOrDirection");
	assert(light3DirectLocation != 0xFFFFFFFF);
	glUniform4fv(light3DirectLocation, 1, glm::value_ptr(light3PositionOfDirection));

	GLuint light3SpotDirectLocation = glGetUniformLocation(shaderProgram, "light3.spotDirection");
	assert(light3SpotDirectLocation != 0xFFFFFFFF);
	glUniform3fv(light3SpotDirectLocation, 1, glm::value_ptr(light3SpotDirection));

	GLuint light3IsSpotLocation = glGetUniformLocation(shaderProgram, "light3.isSpot");
	assert(light3IsSpotLocation != 0xFFFFFFFF);
	glUniform1i(light3IsSpotLocation, light3IsSpot);

	GLuint light3SpotCutOffLocation = glGetUniformLocation(shaderProgram, "light3.spotCutoffCos");
	//	assert(light3SpotCutOffLocation != 0xFFFFFFFF);
	glUniform1f(light3SpotCutOffLocation, light3SpotCutOff);

	GLuint light3SpotExponentLocation = glGetUniformLocation(shaderProgram, "light3.spotExponent");
	//	assert(light3SpotExponentLocation != 0xFFFFFFFF);
	glUniform1f(light3SpotExponentLocation, light3SpotExponent);

	GLuint light3EnabledLocation = glGetUniformLocation(shaderProgram, "light3.enabled");
	assert(light3EnabledLocation != 0xFFFFFFFF);
	glUniform1i(light3EnabledLocation, light3Enabled);

	checkOpenGLErrors("MyScene::initialize6");
	*/

	SharedLightProperties::setUniformBlockForShader(shaderProgram);

	//sets the lightproperties to each light
	SharedLightProperties::setShaderLightProperties(light1, light2, light3);
}

void MyScene::resize(int windowWidth, int windowHeight)
{
	glm::mat4 projectionTransformation = glm::perspective(M_PI / 4.0f, (GLfloat)windowWidth / windowHeight, 1.0f, 100.0f);

	SharedProjectionAndViewing::setProjectionMatrix(projectionTransformation);
}

/*
void MyScene::setTextureMode(int value) {
	cube.mat.setTextureMapped(TextureMode(value));
	sphere.mat.setTextureMapped(TextureMode(value));
	earth.mat.setTextureMapped(TextureMode(value));
	moon.mat.setTextureMapped(TextureMode(value));
}
*/
void MyScene::toggleLight(int value) {
	//toggles the light with modulus in order to make sure it can flip on and off ( switch between 0 and 1)
	if (value == 1) {
		light1.setEnabled((light1.enabled + 1) % 2);
	}
	else if (value == 2) {
		light2.setEnabled((light2.enabled + 1) % 2);
	}
	else if (value == 3) {
		light3.setEnabled((light3.enabled + 1) % 2);
	}
	SharedLightProperties::setShaderLightProperties(light1, light2, light3);
}

void MyScene::setTextureMode() {

	if (textMod == 0){
		cube.mat.setTextureMapped(NO_TEXTURE);
		sphere.mat.setTextureMapped(NO_TEXTURE);
		earth.mat.setTextureMapped(NO_TEXTURE);
		moon.mat.setTextureMapped(NO_TEXTURE);
	}

	else if(textMod == 1) {
		cube.mat.setTextureMapped(DECAL);
		sphere.mat.setTextureMapped(DECAL);
		earth.mat.setTextureMapped(DECAL);
		moon.mat.setTextureMapped(DECAL);
	}

	else if (textMod == 2) {
		cube.mat.setTextureMapped(REPLACE_AMBIENT_DIFFUSE);
		sphere.mat.setTextureMapped(REPLACE_AMBIENT_DIFFUSE);
		earth.mat.setTextureMapped(REPLACE_AMBIENT_DIFFUSE);
		moon.mat.setTextureMapped(REPLACE_AMBIENT_DIFFUSE);
	}
}

void MyScene::setShaderProgram() {

}
void MyScene::draw()
{
	cube.draw();

	earth.draw();

	sphere.draw();

	moon.draw();

	checkOpenGLErrors("MyScene::draw");
}

void MyScene::update(float deltaTime)
{
	
	const float rotationRate = 1.0f;
	static float angle = 0.0f;

	angle += (rotationRate * deltaTime);

	this->sunTrans = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::vec3(10.0f, 0.0f, 0.0f));

	// Set the modeling transformation
	sphere.setModelingTransformation(sunTrans);

	this->earthTrans = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::vec3(10.0f, 0.0f, 0.0f)) *
		glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::vec3(5.0f, 0.0f, 0.0f));

	earth.setModelingTransformation(earthTrans);

	this->moonTrans = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::vec3(10.0f, 0.0f, 0.0f)) *
		glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::vec3(5.0f, 0.0f, 0.0f)) *
		glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::vec3(2.5f, 0.0f, 0.0f));

	moon.setModelingTransformation(moonTrans);
	
}
