#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{

}

Game::~Game() {}

//Cubes Points 
// FACE 
// A : -1, 1 -5
// B : 1, 1, -5 
// C : 1, -1, -5
// D : -1, -1, -5
//BACK 
// E : -1, 1, -7
// F : 1, 1, -7
// G : 1, -1, -7
// H : -1, -1, -7

// Vertices
float vertices[] = { 1.0f, 1.0f, -7.0f, //T1 EFG
					-1.0f, 1.0f, -7.0f,
					-1.0f, -1.0f, -7.0f,
					 1.0f, 1.0f, -7.0f, //T2 FGH
					 1.0f, -1.0f, -7.0f,
					-1.0f, -1.0f, -7.0f,
					 1.0f, -1.0f, -5.0f, //T3 CDG
					-1.0f, -1.0f, -5.0f,
					 1.0f, -1.0f, -7.0f,
					-1.0f, -1.0f, -5.0f, //T4 DGH
					 1.0f, -1.0f, -7.0f,
					-1.0f, -1.0f, -7.0f,
					-1.0f, -1.0f, -5.0f, //T5 DEH
					-1.0f, 1.0f, -7.0f,
					-1.0f, -1.0f, -7.0f,
					-1.0f, 1.0f, -5.0f, //T6 ADE
					-1.0f, -1.0f, -5.0f,
					-1.0f, 1.0f, -7.0f,
					 1.0f, 1.0f, -5.0f, //T7 ABC
					-1.0f, 1.0f, -5.0f,
					-1.0f, -1.0f, -5.0f,
					 1.0f, 1.0f, -5.0f, //T8 BCD
					 1.0f, -1.0f, -5.0f,
					-1.0f, -1.0f, -5.0f 
};

// Colors
float colors[] = {  0.0f, 0.0f, 0.8f, //T1 
					0.0f, 0.0f, 1.0f,
					0.0f, 0.0f, 0.8f,
					0.0f, 0.0f, 0.6f, //T2
					0.0f, 0.0f, 0.3f,
					0.0f, 0.0f, 0.6f,
					0.0f, 1.0f, 0.0f, //T3 
					0.0f, 0.8f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.6f, 0.0f, //T4
					0.0f, 0.3f, 0.0f,
					0.0f, 0.6f, 0.0f,
					0.8f, 0.8f, 0.0f, //T5 
					1.0f, 1.0f, 0.0f,
					0.8f, 0.8f, 0.0f,
					0.6f, 0.6f, 0.0f, //T6
					0.3f, 0.3f, 0.0f,
					0.6f, 0.6f, 0.0f,
					0.8f, 0.0f, 0.0f, //T7 
					1.0f, 0.0f, 0.0f,
					0.8f, 0.0f, 0.0f,
					0.6f, 0.0f, 0.0f, //T8
					0.3f, 0.0f, 0.0f,
					0.6f, 0.0f, 0.0f,
};

// Index to be drawn
unsigned int vertex_index[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

