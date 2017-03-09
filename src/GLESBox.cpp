#include <iostream>
using namespace std;

#include <string.h>

#include "gbox/Environment.h"
#include "gbox/Application.h"
#include "log/Log.h"

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

int gbox_main(gbox::Environment* env) {

	gbox::CallBackHolder* holder = env->getCallBackHolder();

	holder->configureNotify = &configureNotify;
	holder->buttonPress = &buttonPress;
	holder->buttonRelease = &buttonRelease;
	holder->motionNotify = &motionNotify;
	holder->destroyNotify = &destroyNotify;
	holder->update = &update;
	holder->draw = &draw;

	gbox::Application app(env);

	if(app.init()){
		app.mainLoop();
	}

	LOGI("<---- the end of the main ---->");
	return 0;
}


