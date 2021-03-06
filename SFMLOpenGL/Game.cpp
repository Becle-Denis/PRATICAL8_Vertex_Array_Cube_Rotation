#include <Game.h>

bool flip = false;
int current = 1;
int triangleNumber = 36;

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
					-1.0f, 1.0f, -5.0f,  //T6 ADE
					-1.0f, -1.0f, -5.0f,
					-1.0f, 1.0f, -7.0f,
					 1.0f, 1.0f, -5.0f,  //T7 BCG
					 1.0f, -1.0f, -5.0f,
					 1.0f, -1.0f, -7.0f,
					 1.0f, 1.0f, -5.0f,  //T8 BFG
					 1.0f, 1.0f, -7.0f,
					 1.0f, -1.0f, -7.0f,
					-1.0f, 1.0f, -5.0f,  //T9 ABE
					 1.0f, 1.0f, -5.0f,
					-1.0f, 1.0f, -7.0f,
					 1.0f, 1.0f, -5.0f,  //T10 BEF
					-1.0f, 1.0f, -7.0f,
					 1.0f, 1.0f, -7.0f,
					 1.0f, 1.0f, -5.0f,  //T11 ABC
					-1.0f, 1.0f, -5.0f,
					-1.0f, -1.0f, -5.0f,
					 1.0f, 1.0f, -5.0f,  //T12 BCD
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
					1.0f, 0.0f, 1.0f, //T7 
					0.8f, 0.0f, 0.8f,
					1.0f, 0.0f, 1.0f,
					0.6f, 0.0f, 0.6f, //T8
					0.3f, 0.0f, 0.3f,
					0.6f, 0.0f, 0.6f,
					0.0f, 0.8f, 0.8f, //T9 
					0.0f, 1.0f, 1.0f,
					0.0f, 0.8f, 0.8f,
					0.0f, 0.3f, 0.3f, //T10
					0.0f, 0.6f, 0.6f,
					0.0f, 0.3f, 0.3f,
					0.8f, 0.0f, 0.0f, //T11 
					1.0f, 0.0f, 0.0f,
					0.8f, 0.0f, 0.0f,
					0.6f, 0.0f, 0.0f, //T12
					0.3f, 0.0f, 0.0f,
					0.6f, 0.0f, 0.0f
};

// Index to be drawn
unsigned int vertex_index[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35 };

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

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	cout << "Update up" << endl;
	
	//Allowed movement
	if (movementCLock.getElapsedTime() > sf::milliseconds(30))
	{
		movementCLock.restart();

		//center calculation 
		float sumX = 0;
		float sumY = 0;
		float sumZ = 0;
		for (int i = 0; i < 108; i += 3)
		{
			sumX += vertices[i];
			sumY += vertices[i + 1];
			sumZ += vertices[i + 2];
		}
		db::Vector3 center(sumX / 36, sumY / 36, sumZ / 36);

		// rotation X 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			for (int i = 0; i < 108; i += 3)
			{
				//adapting to vector
				db::Vector3 v(vertices[i], vertices[i + 1], vertices[i + 2]);

				//rotating
				v = v - center;
				v = v * db::Matrix3::rotationX(1);
				v = v + center;

				//reassigning value 
				vertices[i] = v.x;
				vertices[i + 1] = v.y;
				vertices[i + 2] = v.z;
			}
		}


		// rotation Y
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			for (int i = 0; i < 108; i += 3)
			{
				//adapting to vector
				db::Vector3 v(vertices[i], vertices[i + 1], vertices[i + 2]);

				//rotating
				v = v - center;
				v = v * db::Matrix3::rotationY(1);
				v = v + center;

				//reassigning value 
				vertices[i] = v.x;
				vertices[i + 1] = v.y;
				vertices[i + 2] = v.z;
			}
		}

		// rotation Z 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			for (int i = 0; i < 108; i += 3)
			{
				//adapting to vector
				db::Vector3 v(vertices[i], vertices[i + 1], vertices[i + 2]);

				//rotating
				v = v - center;
				v = v * db::Matrix3::rotationZ(1);
				v = v + center;

				//reassigning value 
				vertices[i] = v.x;
				vertices[i + 1] = v.y;
				vertices[i + 2] = v.z;
			}
		}

		// Translating right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			for (int i = 0; i < 108; i += 3)
			{
				//adapting to vector
				db::Vector3 v(vertices[i], vertices[i + 1], 1);

				//translating
				v = v * db::Matrix3::translate(1, 0);

				//reassigning value
				vertices[i] = v.x;
				vertices[i + 1] = v.y;
			}
		}

		// Translating left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			for (int i = 0; i < 108; i += 3)
			{
				//adapting to vector
				db::Vector3 v(vertices[i], vertices[i + 1], 1);

				//translating
				v = v * db::Matrix3::translate(-1, 0);

				//reassigning value
				vertices[i] = v.x;
				vertices[i + 1] = v.y;
			}
		}


		// Translating up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			for (int i = 0; i < 108; i += 3)
			{
				//adapting to vector
				db::Vector3 v(vertices[i], vertices[i + 1], 1);

				//translating
				v = v * db::Matrix3::translate(0, 1);

				//reassigning value
				vertices[i] = v.x;
				vertices[i + 1] = v.y;
			}
		}

		// Translating down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			for (int i = 0; i < 108; i += 3)
			{
				//adapting to vector
				db::Vector3 v(vertices[i], vertices[i + 1], 1);

				//translating
				v = v * db::Matrix3::translate(0, -1);

				//reassigning value
				vertices[i] = v.x;
				vertices[i + 1] = v.y;
			}
		}

		// Scalling up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			for (int i = 0; i < 108; i += 3)
			{
				//adapting to vector
				db::Vector3 v(vertices[i], vertices[i + 1], vertices[i + 2]);

				//scalling
				v = v - center;
				v = v * db::Matrix3::scale3D(101);
				v = v + center;

				//reassigning value
				vertices[i] = v.x;
				vertices[i + 1] = v.y;
				vertices[i + 2] = v.z;
			}
		}

		// Scalling Down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			for (int i = 0; i < 108; i += 3)
			{
				//adapting to vector
				db::Vector3 v(vertices[i], vertices[i + 1], vertices[i + 2]);

				//scalling
				v = v - center;
				v = v * db::Matrix3::scale3D(99);
				v = v + center;

				//reassigning value
				vertices[i] = v.x;
				vertices[i + 1] = v.y;
				vertices[i + 2] = v.z;
			}
		}
	}
	

}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

