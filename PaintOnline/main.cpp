
#include <iostream>
#include <SDL.h>

#include "Server.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

class myServer :Server {
public:
	myServer(unsigned short PORT):Server(PORT) {

	}
	void tick(double dT) {
		
	}
	int receive(char* data) {
		cout << "RECV:" << data << endl;
		return 0;
	}
};

int main(int args, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"PaintOnline",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280, 720, SDL_WINDOW_RESIZABLE
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	int type = -1;
	cin >> type;
	if (type == 0) {
		cout << "[Server]" << endl;
		myServer myserver(8990);
		while (true) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			SDL_Rect rect{ 10, 10, 10, 10 };
			SDL_RenderDrawRect(renderer, &rect);
			SDL_RenderPresent(renderer);
			SDL_Event e;
			while (SDL_PollEvent(&e)) {

			}
			Sleep(10);
		}
	}

	return 0;
}
