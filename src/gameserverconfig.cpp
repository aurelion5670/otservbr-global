// Original idea and template by Milice, continued and completed by Aurelion5670

#include "otpch.h"
#include "tools.h"
#include "gameserverconfig.h"
#include "pugicast.h"

GameserverConfig::GameserverConfig()
{	
	loaded = false;
}

bool GameserverConfig::load()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/gameservers.xml");
	if (!result) {
		printXMLError("Error - GameserverConfig::load", "gameservers.xml", result);
		return false;
	}
	
	gameservers.clear();

	for (auto catNode : doc.child("worlds").children()) {
		GameServer gs;
		
		// Normal handling values
		gs.name = catNode.attribute("name").as_string();
		gs.ip = catNode.attribute("ip").as_string();
		gs.port = pugi::cast<uint16_t>(catNode.attribute("port").value());
		gs.worldid = pugi::cast<uint16_t>(catNode.attribute("id").value());
		
		// Stored values to use later
		std::string oldIp = gs.ip;
		const char * worldIp = oldIp.c_str();
		serverIp[gs.worldid] = worldIp;
		serverPort[gs.worldid] = gs.port;
		serverName[gs.worldid] = gs.name;
		
		gameservers.push_back(gs);
	}
	
	loaded = true;
	return true;
}

const char* GameserverConfig::getWorldIp(uint16_t id)
{
	return serverIp[id];
}

uint16_t GameserverConfig::getWorldPort(uint16_t id)
{
	return serverPort[id];
}

std::string GameserverConfig::getWorldName(uint16_t id)
{
	return serverName[id];
}

void GameserverConfig::setWorldId(uint16_t id)
{
	worldId = id;
}

uint16_t GameserverConfig::getWorldId()
{
	return worldId;
}

bool GameserverConfig::reload()
{
	bool result = load();
	return result;
}