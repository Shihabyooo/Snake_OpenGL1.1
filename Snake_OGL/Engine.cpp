#include "Engine.h"

Engine::Engine()
{
	snake = new Snake();
}

Engine::~Engine()
{

}

void Engine::DrawFrame()
{
#pragma region background and view
	glViewport(0, 0, g.width, g.height);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.1 + (float)g.width / 100.0, -0.1 - (float)g.width / 100.0, -0.1 - (float)g.height / 100.0, 0.1 + (float)g.height / 100.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, -10,
		0, 0, 0,
		0, 1, 0);

	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#pragma endregion


	//FBlock(xold, yold);
#pragma region borders
	GLUquadric* circle;
	circle = gluNewQuadric();
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(45.0, 0, 0, 1);
	gluDisk(circle, 7.0710678118654752440084436210485, 7.5, 4, 1);
	glPopMatrix();
#pragma endregion
	//SwapBuffers(g.hdc);
}

void Engine::UpdateGame()
{
	DrawFrame(); //background and borders
			//TODO research a way to output score in the whitespace above



	UpdateBlock(xta, yta);

	//TODO, if this doesn't work well after chaning FRandom ->IRandom, try making the check in ratios xcoord/xta < a*step
	if (CheckCollision())
	{
		snake->SAddBlock();
		growth_flag = true;
		Target();
	}

	if (snake->SCheckSelfCollision() || snake->SCheckWallCollision())
	{
		//game end here;
		//TODO check a method of posting custom message using PostMessage()
		//add appropriate game end handling in WinMain

		PostMessage(g.hwnd, WM_USER, WM_END_GAME, 0);

		//test
		//u = 0;
		//v = 0;
		//MessageBox(0, _T("GAME OVER"), _T("GAME OVER"), 0);
		//end test
	}

	for (int i = 0; i <= snake->SGetLength(); i++)
	{
		if (i == snake->SGetLength() && growth_flag)
		{
			growth_flag = false;
			break;
		}

		if (i == 0)
		{
			float xt = snake->SGetBlock(i).xcoord + u;
			float yt = snake->SGetBlock(i).ycoord + v;
			snake->SUpdateHead(xt, yt);
			UpdateHead(xt, yt);
		}
		else
		{
			snake->SUpdateTail(i);
			float xt = snake->SGetBlock(i).xcoord;
			float yt = snake->SGetBlock(i).ycoord;
			UpdateBlock(xt, yt);
		}
	}


	UpdateScore(); //test
	SwapBuffers(g.hdc);


	sleep(); //TODO replace sleep with chrono implementation
}

void Engine::ResetGame()
{
	SetDirection(0, 0);
	isGameRunning = false;
	snake->SReset();
}

void Engine::SetDirection(int vertical, int horizontal)
{
	if (!isGameRunning)
		return;

	u = horizontal * g.step;
	v = vertical * g.step;
}

void Engine::IncrementSpeed(int increment) //2020 negative value mean decrements
{
	if (naptime + increment <= MAX_NAPTIME && naptime + increment >= MIN_NAPTIME) //2020 A two-in-one test
	{
		naptime += increment;
	}
}

void Engine::UpdateBlock(float xb, float yb)
{
	static GLfloat verts[] =
	{
		0, 0,
		0, g.step,
		g.step, g.step,
		g.step, 0
	};
	static GLfloat vertcol[] =
	{
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verts);
	glColorPointer(3, GL_FLOAT, 0, vertcol);
	glPushMatrix();
	glTranslatef(xb, yb, 0);
	glDrawArrays(GL_POLYGON, 0, 4);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void Engine::UpdateHead(float xh, float yh)
{
	static GLfloat verts[] =
	{
		0, 0,
		0, g.step,
		g.step, g.step,
		g.step, 0
	};
	static GLfloat vertcol[] =
	{
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verts);
	glColorPointer(3, GL_FLOAT, 0, vertcol);
	glPushMatrix();
	glTranslatef(xh, yh, 0);
	glDrawArrays(GL_POLYGON, 0, 4);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void Engine::UpdateScore()
{
	//scalar multiplication	
	/*GLfloat * numberarray = new GLfloat[sizes[5]*2];
	for (int i = 0; i < (sizes[5]+1)*2; i++)
	{
		numberarray[i] = step* six[i];
		i = i; //test
	}*/

	//FDrawScore(numberarray, sizes[5], 2); //test
	int tempscore = snake->SGetLength();
	int tempdigit;


	//GLfloat * numberarray;
	static GLfloat numberarray[60]; //because dynamic method doesn't work
							//the function only uses element locations up to max
							//given by digit vertex array (largest one is 30x2)
							//also, without being static, the program crashes after the first score
							//dunno why, yet.
	for (int i = 0; i < 4; i++)
	{
		tempdigit = tempscore / pow(10, i);
		tempdigit = tempdigit % 10;


		//numberarray = new GLfloat[sizes[tempdigit] * 2];

		for (int i = 0; i < (sizes[tempdigit] + 1) * 2; i++)
		{
			switch (tempdigit)
			{
			case 0:
				numberarray[i] = scstep * zero[i];
				break;
			case 1:
				numberarray[i] = scstep * one[i];
				break;
			case 2:
				numberarray[i] = scstep * two[i];
				break;
			case 3:
				numberarray[i] = scstep * three[i];
				break;
			case 4:
				numberarray[i] = scstep * four[i];
				break;
			case 5:
				numberarray[i] = scstep * five[i];
				break;
			case 6:
				numberarray[i] = scstep * six[i];
				break;
			case 7:
				numberarray[i] = scstep * seven[i];
				break;
			case 8:
				numberarray[i] = scstep * eight[i];
				break;
			case 9:
				numberarray[i] = scstep * nine[i];
				break;
			}

		}

		//MessageBox(NULL, _T("check"), _T(""), NULL);
		DrawScore(numberarray, sizes[tempdigit], i);
		//MessageBox(NULL, _T("check"), _T(""), NULL);
		//delete [] numberarray;
		//MessageBox(NULL, _T("check"), _T(""), NULL);
	}
}

void Engine::DrawScore(GLfloat * digit, int digitverts, int digitorder)
{

	float digittranslate = (4 - (float)digitorder) * scstep * 3 - 8 * scstep;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, digit);
	glColorPointer(3, GL_FLOAT, 0, DigitCol);
	glPushMatrix();
	glTranslatef(digittranslate, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, digitverts);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

bool Engine::CheckCollision()
{
	float xtm = snake->SGetBlock(0).xcoord;
	float ytm = snake->SGetBlock(0).ycoord;

	if (abs(xtm - xta) < 0.1*g.step && abs(ytm - yta) < 0.1*g.step)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Engine::Target()
{
	while (1)
	{
		xta = 0.2 * (float)IRandom(-(float)g.width / (100.0*g.step), (float)g.width / (100.0*g.step));
		yta = 0.2 * (float)IRandom(-(float)g.height / (100.0*g.step), (float)g.height / (100.0*g.step));

		//hack
		if (xta < 0) { xta + g.step; }
		else if (xta > 0) { xta - g.step; }
		if (yta < 0) { yta + g.step; }
		else if (yta > 0) { yta - g.step; }

		if (!snake->SCheckIntersection(xta, yta)) { break; }
	}
}

int Engine::GetScore()
{
	return snake->SGetLength();
}

void Engine::StartGame()
{
	if (isGameRunning)
		return;

	SetDirection(1, 0);
	isGameRunning = true;
}

void Engine::EndAnimation()
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.85, 0.05, 0.05, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SwapBuffers(g.hdc);
	for (int i = 0; i < 5; i++)
	{
		Sleep(500);
		SwapBuffers(g.hdc);
	}
}

void Engine::sleep()
{
	Sleep(naptime);
}

int Engine::IRandom(int lower, int upper)
{
	int result;
	std::random_device seed;
	std::mt19937_64 engine(seed());
	std::uniform_int_distribution <> range(lower, upper);
	result = range(engine);
	return result;
}
