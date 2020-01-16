// include declarations
#include <SDL.h>
#include <iostream>
#include <string>

// screen constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

// rectangle info
int rectWidth = 100;
int rectHeight = 100;

// the window
SDL_Window* gWindow;

// the renderer
SDL_Renderer* gRenderer;

// the initialization method
void init() {
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("rectangle differing size", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

// the load media method
void loadMedia() {
	// nothing to load
}

// the clean up method
void cleanUp() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

// the draw rectangle method
void drawRectangle(int x, int y, int width, int height) {
	SDL_Rect drawRect = {x, y, width, height};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &drawRect);
}

// the key state method
void checkKeyStates() {
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		rectHeight = rectHeight + 10;
		rectWidth = rectWidth + 10;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		if (rectHeight > 0 && rectWidth > 0) {
			rectHeight = rectHeight - 10;
			rectWidth = rectWidth - 10;
		}

	}
}

// the main method
int main(int argc, char* args[]) {
	init();
	loadMedia();
	SDL_Event e;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}
		
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		
		checkKeyStates();
		
		drawRectangle(SCREEN_WIDTH/2 - rectWidth/2, SCREEN_HEIGHT/2 - rectHeight/2, rectWidth, rectHeight);
		
		SDL_RenderPresent(gRenderer);
	}
	cleanUp();
}