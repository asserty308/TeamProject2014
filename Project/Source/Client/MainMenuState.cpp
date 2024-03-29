#include "MainMenuState.h"
#include "SpriteRenderer.hpp"

void MainMenuState::init()
{
	currentState = SPLASH_SCREEN;

	name = "Unknown Player";
	ip = "127.0.0.1";
	port = "8888";
	clPort = "54290";

	glEnable(GL_TEXTURE_2D);

	//create sprite
	backgroundSprite = new Sprite("Sprites\\menu_background.png", Vector2(g_pGame->getWindowWidth() / 2.f, g_pGame->getWindowHeight() / 2.f), Vector2(1280.f, 720.f), 1);
}

void MainMenuState::receivePacket(char* data)
{

}

void MainMenuState::inputReceived(SDL_KeyboardEvent *key)
{
	if (key->type == SDL_KEYUP)
	{
		switch (currentState)
		{
			case SPLASH_SCREEN:
				currentState = PROMPTING_NAME;
				break;
			case PROMPTING_NAME:
				if (key->keysym.sym == SDLK_KP_ENTER || key->keysym.sym == SDLK_RETURN)
				{
					currentState = PROMPTING_IP;
					break;
				}
				else
					appendSDLKey(key, &name);
				break;
			case PROMPTING_IP:
				if (key->keysym.sym == SDLK_KP_ENTER || key->keysym.sym == SDLK_RETURN)
				{
					currentState = PROMPTING_PORT;
					break;
				}
				else
					appendSDLKey(key, &ip);
				break;
			case PROMPTING_PORT:
				if (key->keysym.sym == SDLK_KP_ENTER || key->keysym.sym == SDLK_RETURN)
				{
					currentState = PROMPTING_CL_PORT;
				}
				else
					appendSDLKey(key, &port);
				break;
			case PROMPTING_CL_PORT:
				if (key->keysym.sym == SDLK_KP_ENTER || key->keysym.sym == SDLK_RETURN)
				{
					g_pGame->setName(name);
					g_pGame->setServerIP(ip);
					g_pGame->setServerPort(atoi(port.c_str()));
					g_pGame->setClientPort(atoi(clPort.c_str()));
					g_pGame->setClient(new Client());
					g_pGame->setState(g_pGame->getLobbyState());
				}
				else
					appendSDLKey(key, &clPort);
				break;
		}
	}
}

void MainMenuState::appendSDLKey(SDL_KeyboardEvent *key, std::string *str)
{
	SDL_Keycode code = key->keysym.sym;
	if (code == SDLK_BACKSPACE)
	{
		if (str->length() > 0)
			str->pop_back();
		else
			switchPromptUp();
		return;
	}
	else if (code == SDLK_UP)
	{
		switchPromptUp();
		return;
	}
	else if (code == SDLK_DOWN)
	{
		switchPromptDown();
		return;
	}

	if (key->keysym.mod == KMOD_LSHIFT)
	{
		str->push_back(code - 32);
		return;
	}

	if (code != SDLK_LSHIFT)
		str->push_back(code);
}

void MainMenuState::switchPromptUp()
{
	switch (currentState)
	{
		case PROMPTING_NAME:
			currentState = PROMPTING_CL_PORT;
			break;
		case PROMPTING_IP:
			currentState = PROMPTING_NAME;
			break;
		case PROMPTING_PORT:
			currentState = PROMPTING_IP;
			break;
		case PROMPTING_CL_PORT:
			currentState = PROMPTING_PORT;
			break;
	}
}

void MainMenuState::switchPromptDown()
{
	switch (currentState)
	{
		case PROMPTING_NAME:
			currentState = PROMPTING_IP;
			break;
		case PROMPTING_IP:
			currentState = PROMPTING_PORT;
			break;
		case PROMPTING_PORT:
			currentState = PROMPTING_CL_PORT;
			break;
		case PROMPTING_CL_PORT:
			currentState = PROMPTING_NAME;
			break;
	}
}

void MainMenuState::update()
{

}

void MainMenuState::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_pSpriteRenderer->renderScene();

	glColor3f(1.f, 1.f, 1.f);
	SDL_Color col = { 255, 127, 0 };
	Vector2 dim = Vector2(0.f, 0.f);

	if (currentState == SPLASH_SCREEN)
	{
		stream.str("");
		stream << "ALPHA STRIKE";
		dim = g_pFontRenderer->getTextDimensions(stream.str());
		g_pFontRenderer->drawText(stream.str(), Vector2(400.f - dim.getX() / 2, 230.f - dim.getY() / 2), col);

		static float time;
		std::string waitingText = "Press any key to continue";

		if (sinf(time) > -.5f && sinf(time) <= .0f)
			waitingText += ".";
		else if (sinf(time) > 0.f && sinf(time) <= .5f)
			waitingText += "..";
		if (sinf(time) > .5f)
			waitingText += "...";

		time += 0.025f;

		dim = g_pFontRenderer->getTextDimensions("Press any key to continue...");
		g_pFontRenderer->drawText(waitingText, Vector2(400.f - dim.getX() / 2, 300.f - dim.getY() / 2), col);
	}
	else
	{
		static float time;

		stream.str("");
		stream << "Name: " << name << (currentState == PROMPTING_NAME && sinf(time) < 0.f ? "_" : "");
		g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 10.f), col);

		stream.str("");
		stream << "Server IP: " << ip << (currentState == PROMPTING_IP && sinf(time) < 0.f ? "_" : "");
		g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 80.f), col);

		stream.str("");
		stream << "Server Port: " << port << (currentState == PROMPTING_PORT && sinf(time) < 0.f ? "_" : "");
		g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 150.f), col);

		stream.str("");
		stream << "Client Port: " << clPort << (currentState == PROMPTING_CL_PORT && sinf(time) < 0.f ? "_" : "");
		g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 220.f), col);

		float y = 10.f;

		if (currentState == PROMPTING_IP)
			y = 80.f;
		else if (currentState == PROMPTING_PORT)
			y = 150.f;
		else if (currentState == PROMPTING_CL_PORT)
			y = 220.f;

		
		glColor3f(1.f, 0.5f + sinf(time) / 2.f, 0.f);
		time += 0.05f;

		glLineWidth(3.f);
		glBegin(GL_LINE_STRIP);

		glVertex2f(5.f, y);
		glVertex2f(g_pGame->getWindowWidth() - 5.f, y);
		glVertex2f(g_pGame->getWindowWidth() - 5.f, y + 55.f);
		glVertex2f(5.f, y + 55.f);
		glVertex2f(5.f, y);

		glEnd();
	}
}

void MainMenuState::quit()
{
	delete backgroundSprite;
}