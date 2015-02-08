#include "LobbyState.h"

LobbyState::LobbyState(){
}

LobbyState::~LobbyState(){
	delete[] receivedBuffer;
}

void LobbyState::init(){
	this->numberOfPlayers = g_pGame->getNumberOfPlayers() - 1;
	receivedBuffer = new char[BUFLEN * numberOfPlayers];

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
	char *cmpString = "welcome:ack";

	if (memcmp(packet, cmpString, sizeof(char) * strlen(cmpString)) == 0)
	// if we received a start packet from the server to let us know the welcome string was acknowledged
	{
		g_pLogfile->fLog("Welcome packet acknowledged from server.");
		isWelcomePacketAcknowledged = true;
	}
	//else
		//g_pLogfile->fLog("Invalid packet \"%s\" received and discarded.", packet);

	cmpString = "start";

	if (memcmp(packet, cmpString, sizeof(char)* strlen(cmpString)) == 0)
	// if we received a start packet from the server to let us know the game is starting
	{
		std::string tmp = packet + sizeof(char) * (strlen(cmpString) + 1);
		int spawnIndex = atoi(tmp.c_str());

		g_pGame->getGameplayState()->spawnPoint = spawnIndex;

		if (!client->sendToServer("start:ack"))
		// send an ack packet to the server
			g_pLogfile->fLog("Failed to send ack start packet to server.");

		g_pLogfile->fLog("Starting game (spawn point %d).", spawnIndex);
		g_pGame->setState(g_pGame->getGameplayState());
	}
	//else
		//g_pLogfile->fLog("Invalid packet \"%s\" received and discarded.", packet);
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