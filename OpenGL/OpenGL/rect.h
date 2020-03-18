#pragma once
#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <box2d.h>
#include <math.h>
#include <SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;
const float M2P = 20;
const float P2M = 1 / M2P;
b2World* world;

class Rect {

public:
	b2Body* addRect(int x, int y, int w, int h, bool dyn=true)
	{
		b2BodyDef bodydef;
		bodydef.position.Set(x*P2M, y*P2M);
		if (dyn) {
			bodydef.type = b2_dynamicBody;
		}
		b2Body* body = world->CreateBody(&bodydef);

		b2PolygonShape shape;
		shape.SetAsBox(P2M*w/2, P2M*h/2);

		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.0;
		fixture.friction = 0.9;
		body->CreateFixture(&fixture);

		return body;
	}

	void drawRect(b2Vec2* points, b2Vec2 center, float angle)
	{
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(center.x * M2P, center.y * M2P, 0);
		glRotatef(angle * 180.0 / M_PI, 0, 0, 1);
		glBegin(GL_QUADS);
		for (int i = 0; i < 4; i++) {
			glVertex2f(points[i].x * M2P, points[i].y * M2P);
		}
		glEnd();
		glPopMatrix();
	}

	void init()
	{
		glMatrixMode(GL_PROJECTION);
		glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0, 0, 0, 1);
		world = new b2World(b2Vec2(0.0, 9.81));
		addRect(WIDTH / 2, HEIGHT - 50, WIDTH, 30, false);
	}

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		b2Body* tmp = world->GetBodyList();
		b2Vec2 points[4];
		while (tmp)
		{
			for (int i = 0; i < 4; i++)
			{
				points[i] = ((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i);
			}
			drawRect(points, tmp->GetWorldCenter(), tmp->GetAngle());
			tmp = tmp->GetNext();
		}
	}

	void run()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		Uint32 start;
		SDL_Event event;
		bool running = true;
		init();
			while (running)
			{
				start = SDL_GetTicks();
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_QUIT:
						running = false;
						break;
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{
						case SDLK_ESCAPE:
							running = false;
							break;
						}
						break;
					case SDL_MOUSEBUTTONDOWN:
						addRect(event.button.x, event.button.y, 20, 20, true);
						break;

					}
				}
				display();
				world->Step(1.0 / 30.0, 8, 3);
				if (1000.0 / 30 > SDL_GetTicks() - start)
				{
					SDL_Delay(1000.0 / 30 - (SDL_GetTicks() - start));
				}
			}
		SDL_Quit();
	}
};