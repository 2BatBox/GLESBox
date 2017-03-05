#include <iostream>
using namespace std;

#include <string.h>

#include "log/Log.h"
#include "core/memory.h"

#include "Application.h"


void configureNotify(int width, int height){
	LOGI("configureNotify(%d:%d)", width, height);
}

void buttonPress(unsigned button, int x, int y){
	LOGI("buttonPress(%u, %d, %d)", button, x, y);
}

void buttonRelease(unsigned button, int x, int y){
	LOGI("buttonRelease(%u, %d, %d)", button, x, y);
}

void motionNotify(int x, int y){
	LOGI("motionNotify(%d:%d)", x, y);
}

void destroyNotify(){
	LOGI("destroyNotify()");
}

void update(float deltaTime){
}

void draw(){
}

int main() {

	Application app;
	Application::CallBackHolder& env = app.getCallBackHolder();

	env.configureNotify = &configureNotify;
	env.buttonPress = &buttonPress;
	env.buttonRelease = &buttonRelease;
	env.motionNotify = &motionNotify;
	env.destroyNotify = &destroyNotify;
	env.update = &update;
	env.draw = &draw;

	if(app.init("GLESBox", 640, 480)){
		app.mainLoop();
	}

	LOGI("<---- the end of the main ---->");
	return 0;
}


