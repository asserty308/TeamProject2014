#include "MainMenuState.h"

void MainMenuState::init()
{
	currentState = SPLASH_SCREEN;
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
	if (key->keysym.sym == SDLK_BACKSPACE && str->length() > 0){
		str->pop_back();
		return;
	}

	char k = key->keysym.sym;
	str->push_back(k);
}

void MainMenuState::update()
{

}

void MainMenuState::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_Color col = { 255, 127, 0 };
	Vector2 dim = Vector2(0.f, 0.f);

	if (currentState == SPLASH_SCREEN)
	{
		stream.str("");
		stream << "ALPHA STRIKE";
		dim = g_pFontRenderer->getTextDimensions(stream.str());
		g_pFontRenderer->drawText(stream.str(), Vector2(400.f - dim.getX() / 2, 230.f - dim.getY() / 2), col);

		stream.str("");
		stream << "press any key to continue";
		dim = g_pFontRenderer->getTextDimensions(stream.str());
		g_pFontRenderer->drawText(stream.str(), Vector2(400.f - dim.getX() / 2, 300.f - dim.getY() / 2), col);
	}
	else
	{
		stream.str("");
		stream << "Name: " + name;
		g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 10.f), col);

		stream.str("");
		stream << "Server IP: " + ip;
		g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 80.f), col);

		stream.str("");
		stream << "Server Port: " + port;
		g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 150.f), col);

		stream.str("");
		stream << "Client Port: " + clPort;
		g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 220.f), col);
	}
}

void MainMenuState::quit()
{

}