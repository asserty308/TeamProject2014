#include "LobbyState.h"

LobbyState::LobbyState(Client* client, int numberOfPlayers){
	this->client = client;
	this->numberOfPlayers = numberOfPlayers;
}

LobbyState::~LobbyState(){

}

void LobbyState::init(){
	
}

void LobbyState::update(){

	//Send Package to signal that we are connected
	char dummyPackage[BUFLEN];
	memset(dummyPackage, '0', BUFLEN);
	client->setPackage(dummyPackage, BUFLEN);

	client->update();

	//Check other players packages. If they contain defaultvalues ("???")
	//those players have not connected yet and the Game won't start!
	char* receivedBuffer[BUFLEN * MAX_PLAYER];
	memcpy(receivedBuffer, client->getReceivedPackage(), BUFLEN * MAX_PLAYER);

	char* defaultCompareString = "???";

	for (int i = 0; i < numberOfPlayers; i++){
		if (memcmp(receivedBuffer + (i * BUFLEN), defaultCompareString, sizeof(char)* 3) == 0){
			return;
		}
	}

	g_pGame->setState(g_pGame->getGameplayState());
	
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