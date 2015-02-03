#include "MainMenuState.h"

void MainMenuState::init()
{
	prompt = PROMPTING_NAME;
}

void MainMenuState::inputReceived(SDL_KeyboardEvent *key)
{
	if (key->type == SDL_KEYUP)
	{
		switch (prompt)
		{
			case PROMPTING_NAME:
				if (key->keysym.sym == SDLK_KP_ENTER || key->keysym.sym == SDLK_RETURN)
				{
					prompt = PROMPTING_IP;
					break;
				}
				else
					appendSDLKey(key, &name);
				break;
			case PROMPTING_IP:
				if (key->keysym.sym == SDLK_KP_ENTER || key->keysym.sym == SDLK_RETURN)
				{
					prompt = PROMPTING_PORT;
					break;
				}
				else
					appendSDLKey(key, &ip);
				break;
			case PROMPTING_PORT:
				if (key->keysym.sym == SDLK_KP_ENTER || key->keysym.sym == SDLK_RETURN)
				{
					prompt = PROMPTING_CL_PORT;
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
	char k = key->keysym.sym;
	str->push_back(k);
}

void MainMenuState::update()
{

}

void MainMenuState::render()
{
	std::stringstream stream;
	stream << "Name: " + name;

	SDL_Color col = { 255, 127, 0 };

	g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 10.f), col);

	stream.str("");
	stream << "Server IP: " + ip;
	g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 50.f), col);

	stream.str("");
	stream << "Server Port: " + port;
	g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 90.f), col);

	stream.str("");
	stream << "Client Port: " + clPort;
	g_pFontRenderer->drawText(stream.str(), Vector2(10.f, 130.f), col);
}

void MainMenuState::quit()
{

}