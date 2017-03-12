#include "X11Environment.h"

#include <pthread.h>

int gbox_main(gbox::Environment* env);

int main() {
	gbox::X11Environment env("res");
	if(!env.initX11Context("GBox", 640, 480)){
		return -1;
	}
	gbox_main(&env);

	// Hello to the Nvidia GLES driver!
	pthread_getconcurrency();
}
