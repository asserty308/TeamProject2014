#include "LobbyState.h"

LobbyState::LobbyState(){
}

LobbyState::~LobbyState(){
	
}

void LobbyState::init(){
	isWelcomePacketAcknowledged = false;

	client = g_pGame->getClient();
}

void LobbyState::sendWelcomePacketToServer()
{
	if (!client->sendToServer("welcome:" + g_pGame->getName()))
	// send our name to the server
		g_pLogfile->fLog("Failed to send welcome packet to server.");
}

void LobbyState::receivePacket(char* packet)
{
	char *gameInfoString = "gameinfo";
	char *gameStartString = "start";

	if (memcmp(packet, gameInfoString, sizeof(char) * strlen(gameInfoString)) == 0)
	// if we received a gameinfo packet from the server to let us know the welcome string was acknowledged and how many players are connected
	{
		char *tmp = packet + sizeof(char) * (strlen(gameInfoString) + 1);
		int playerCount = atoi(tmp);

		tmp = packet + sizeof(char) * (strlen(gameInfoString) + 3);
		int bestOfX = atoi(tmp);

		tmp = packet + sizeof(char) * (strlen(gameInfoString) + 5);
		int mapID = atoi(tmp);

		//g_pLogfile->fLog("Gameinfo packet received from server, playercount received: %d, best of %d, map id: %d", playerCount, bestOfX, mapID);
		g_pGame->setNumberOfPlayers(playerCount);
		g_pGame->setBestOfX(bestOfX);
		g_pGame->setMapID(mapID);

		isWelcomePacketAcknowledged = true;
	}
	else if (memcmp(packet, gameStartString, sizeof(char) * strlen(gameStartString)) == 0)
	// if we received a start packet from the server to let us know the game is starting
	{
		// parse our player ID

		char *pID = packet + (strlen(gameStartString) + 1);
		int playerID = atoi(pID);
		//g_pLogfile->fLog("Start packet received from server, our player ID: %d", playerID);
		g_pGame->getGameplayState()->playerID = playerID;


		// parse list of player names

		std::string tmp = packet + sizeof(char)* (strlen(gameStartString) + 3);

		std::string playerName;
		std::stringstream ss(tmp);
		char j;
		while (ss >> j)
		{
			playerName.push_back(j);
			
			if (ss.peek() == ':')
			{
				g_pGame->getGameplayState()->addNetplayer(playerName);
				playerName.clear();
				ss.ignore();
			}
		}

		
		// answer with an ack packet

		if (!client->sendToServer("start:ack"))
		// send an ack packet to the server
			g_pLogfile->fLog("Failed to send ack start packet to server.");

		g_pLogfile->fLog("Starting game...");
		g_pGame->setState(g_pGame->getGameplayState());
	}
	else
		g_pLogfile->fLog("Discarded malformed packet: \"%s\".", packet);
}

void LobbyState::update()
{
	if (!isWelcomePacketAcknowledged)
	{
		for (int i = 0; i < 3; ++i)
		// burst fire
			sendWelcomePacketToServer();
	}

	client->update();
}

void LobbyState::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.f, 1.f, 1.f);

	static float time;
	std::string waitingText = "Waiting for players to connect";

	if (sinf(time) > -.5f && sinf(time) <= .0f)
		waitingText += ".";
	else if (sinf(time) > 0.f && sinf(time) <= .5f)
		waitingText += "..";
	if (sinf(time) > .5f)
		waitingText += "...";

	time += 0.025f;

	SDL_Color color = { 255, 127, 0 };

	Vector2 textDimensions = g_pFontRenderer->getTextDimensions("Waiting for players to connect...");
	Vector2 textPos((g_pGame->getWindowWidth() / 2) - (textDimensions.getX() / 2), (g_pGame->getWindowHeight() / 2) - (textDimensions.getY() / 2));
	g_pFontRenderer->drawText(waitingText, textPos, color);
}

void LobbyState::quit(){

}

void LobbyState::inputReceived(SDL_KeyboardEvent *key){

}