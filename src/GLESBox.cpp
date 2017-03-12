#include <iostream>
using namespace std;

#include <string.h>
#include <memory>
#include <assert.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "log/Log.h"
#include "log/Printer.h"

#include "gbox/Environment.h"
#include "gbox/Application.h"
#include "gbox/utils/glutils.h"

#include "core/utils/files.h"

static gbox::Environment* gboxEnv = nullptr;
int screenWidth, screenHeight;

const GLfloat COORD = 1.0f;

const GLfloat gSpriteVertices[] = {
		-COORD, COORD,
		-COORD, -COORD,
		COORD, -COORD,

		-COORD, COORD,
		COORD, -COORD,
		COORD, COORD,
};

//const GLfloat gSpriteColors[] = {
//		1.0f, 0.0f, 0.0f,
//		0.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 1.0f,
//
//		1.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f,
//		0.0f, 1.0f, 0.0f,
//};

GLint createShader(GLenum type, const char* file) {
	std::unique_ptr<core::InputFile> shaderFile(gboxEnv->openFile(file));
	assert(shaderFile.get());

	core::AutoArray<char> shaderSource(core::loadFileCString(shaderFile.get()));
	assert(*shaderSource);

	GLint shader = gbox::glutils::loadShader(type, *shaderSource);
	return shader;
}

GLint locUniTime;
GLfloat uniTime;

void onContextCreate() {
	LOGI("onContextCreate()");
	assert(gboxEnv);

	GLint shaderVertex = createShader(GL_VERTEX_SHADER, "simple.vert");
	assert(shaderVertex);

	GLint shaderFragment = createShader(GL_FRAGMENT_SHADER, "simple.frag");
	assert(shaderFragment);

	GLint program = gbox::glutils::createProgram(shaderVertex, shaderFragment);
	assert(program);

	gbox::glutils::infoProgram(program);

	GL_CHECK(glUseProgram(program));

	locUniTime = GL_CHECK(glGetUniformLocation(program, "uTime"));
	assert(locUniTime >= 0);

	GLint locAttrPosition = GL_CHECK(glGetAttribLocation(program, "aPosition"));
	assert(program >= 0);

	GL_CHECK(glVertexAttribPointer(locAttrPosition, 2, GL_FLOAT, GL_FALSE, 0, gSpriteVertices));
	GL_CHECK(glEnableVertexAttribArray(locAttrPosition));
}

void onContextDestroy() {
	LOGI("onContextDestroy()");
}

void onContextConfigure(int width, int height) {
	LOGI("onContextConfigure(%d:%d)", width, height);
	GL_CHECK(glViewport(0,0, width, height));
	screenWidth = width;
	screenHeight = height;
}

int lastX;
bool isCatch = false;
float direction = 1.0f;

void onButtonPress(unsigned button, int x, int y) {
	LOGI("onButtonPress(%u, %d, %d)", button, x, y);
	lastX = x;
	isCatch = true;
}

void onButtonRelease(unsigned button, int x, int y) {
	LOGI("onButtonRelease(%u, %d, %d)", button, x, y);
	isCatch = false;
}

void onPointerMotion(int x, int y) {
	LOGI("onPointerMotion(%d:%d)", x, y);
	float diff = lastX - x;
	diff = (diff / screenWidth) * -5.0f;
	LOGI("%f", diff);
	uniTime += diff;
	lastX = x;
	if(diff < 0.0){
		direction = -1.0f;
	} else {
		direction = 1.0f;
	}
}

void onUpdate(float deltaTime) {
	if(!isCatch){
		uniTime += direction * deltaTime;
	}
}


void onDraw() {
	GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));
	GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUniform1f(locUniTime, uniTime));
	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
}

int gbox_main(gbox::Environment* env) {

	gbox::CallBackHolder* holder = env->getCallBackHolder();

	holder->onContextCreate = &onContextCreate;
	holder->onContextDestroy = &onContextDestroy;
	holder->onContextConfigure = &onContextConfigure;
	holder->onButtonPress = &onButtonPress;
	holder->onButtonRelease = &onButtonRelease;
	holder->onPointerMotion = &onPointerMotion;
	holder->onUpdate = &onUpdate;
	holder->onDraw = &onDraw;

	gboxEnv = env;

	gbox::Application app(env);

	if (app.createContext()) {
		app.mainLoop();
		app.destroyContext();
	}

	LOGI("<---- the end of the main ---->");
	return 0;
}

