#include "LobbyState.h"

LobbyState::LobbyState(){
}

LobbyState::~LobbyState(){
	delete[] receivedBuffer;
}

void LobbyState::init(){
	this->numberOfPlayers = g_pGame->getNumberOfPlayers() - 1;
	receivedBuffer = new char[BUFLEN * numberOfPlayers];

	client = g_pGame->getClient();
}

void LobbyState::receivePacket(std::string packet)
{
	if (packet.substr(0, 5).compare("start") == 0)
	// if we received a start packet from the server to let us know the game is starting
	{
		std::string tmp = packet.substr(6);
		int spawnIndex = atoi(tmp.c_str());

		g_pGame->getGameplayState()->spawnPoint = spawnIndex;

		g_pLogfile->fLog("Starting game (spawn point %d).", spawnIndex);
		g_pGame->setState(g_pGame->getGameplayState());
	}
	else
		g_pLogfile->fLog("Invalid packet \"%s\" received and discarded.", packet);
}

void LobbyState::update()
{
	client->update();
}

void LobbyState::render(){

	std::string waitingText = "Waiting for players to connect...";
	SDL_Color color = { 255, 127, 0 };

	Vector2 textDimensions = g_pFontRenderer->getTextDimensions(waitingText);
	Vector2 textPos((g_pGame->getWindowWidth() / 2) - (textDimensions.getX() / 2), (g_pGame->getWindowHeight() / 2) - (textDimensions.getY() / 2));
	g_pFontRenderer->drawText(waitingText, textPos, color);
}

void LobbyState::quit(){

}

void LobbyState::inputReceived(SDL_KeyboardEvent *key){

}