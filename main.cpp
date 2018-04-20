#include "Renderer.h"

int main(){

	if(InitWindow() | InitGlewFailed()){
		return EXIT_WITH_ERROR;
	}

	BeginRenderingLoop();

	return EXIT_WITH_SUCCESS;
}