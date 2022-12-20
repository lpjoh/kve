#include "TileMap.h"
#include <iostream>
#include <filesystem>
#include <rapidxml/rapidxml.hpp>
#include "IO.h"
#include "Assets.h"

using namespace kve;

bool TileSet::LoadTSX(const std::string filePath) {
	// Load file
	std::optional<std::string> tsxTextLoad = IO::LoadFileString(filePath);

	if (tsxTextLoad == std::nullopt) {
		std::cerr << "Failed to load tileset at \"" << filePath << "\"." << std::endl;
		return false;
	}

	std::string tsxText = tsxTextLoad.value();

	// Parse XML
	rapidxml::xml_document<> xmlDocument;
	xmlDocument.parse<0>(tsxText.data());

	rapidxml::xml_node<>* tileSetNode = xmlDocument.first_node("tileset");
	rapidxml::xml_node<>* textureNode = tileSetNode->first_node("image");

	// Get texture path
	std::filesystem::path tileSetFsPath(filePath);
	tileSetFsPath = tileSetFsPath.parent_path();

	std::string textureRelativePath =
		textureNode->first_attribute("source")->value();

	std::string textureAbsolutePath =
		tileSetFsPath.generic_string() + '/' + textureRelativePath;

	// Set texture
	Texture* texture = Assets::LoadTexture(textureAbsolutePath);

	int tileWidth = std::stoi(tileSetNode->first_attribute("tilewidth")->value());
	int tileHeight = std::stoi(tileSetNode->first_attribute("tileheight")->value());

	texture->hFrames = texture->GetWidth() / tileWidth;
	texture->vFrames = texture->GetHeight() / tileHeight;

	// Set sprite properties
	sprite.SetTexture(texture);
	sprite.size = glm::vec2((float)tileWidth, (float)tileHeight);

	return true;
}

TileSet::TileSet(int firstGlobalID) {
	this->firstGlobalID = firstGlobalID;
}

int TileLayer::GetWidth() {
	return size.x;
}

int TileLayer::GetHeight() {
	return size.y;
}

int TileLayer::GetCell(int x, int y) {
	return cells.at(y * size.x + x);
}

TileLayer::TileLayer(glm::ivec2 size, std::string& cellData) {
	this->size = size;

	cells.clear();

	// Read CSV data
	std::string nextCell;

	for (int i = 0; i < cellData.length(); i++) {
		char c = cellData[i];

		if (c == ',') {
			cells.push_back(std::stoi(nextCell));

			nextCell = "";
			continue;
		}

		nextCell += c;
	}

	if (nextCell.length() > 0) {
		cells.push_back(std::stoi(nextCell));
	}
}

bool TileMap::LoadTMX(const std::string filePath) {
	// Reset
	tileSets.clear();
	tileLayers.clear();

	// Load file
	std::optional<std::string> tmxTextLoad = IO::LoadFileString(filePath);

	if (tmxTextLoad == std::nullopt) {
		std::cerr << "Failed to load map at \"" << filePath << "\"." << std::endl;
		return false;
	}

	std::string tmxText = tmxTextLoad.value();
	
	// Parse XML
	rapidxml::xml_document<> xmlDocument;
	xmlDocument.parse<0>(tmxText.data());

	rapidxml::xml_node<>* mapNode = xmlDocument.first_node("map");

	size.x = std::stoi(mapNode->first_attribute("width")->value());
	size.y = std::stoi(mapNode->first_attribute("height")->value());

	tileSize.x = std::stoi(mapNode->first_attribute("tilewidth")->value());
	tileSize.y = std::stoi(mapNode->first_attribute("tileheight")->value());

	// Load tilesets
	const char* tileSetName = "tileset";

	for (
		rapidxml::xml_node<>* tileSetNode = mapNode->first_node(tileSetName);
		tileSetNode != nullptr;
		tileSetNode = tileSetNode->next_sibling(tileSetName)) {

		int firstGlobalID = std::stoi(tileSetNode->first_attribute("firstgid")->value());
		
		tileSets.push_back(TileSet(firstGlobalID));
		TileSet& tileSet = tileSets.back();

		std::filesystem::path tileMapFsPath(filePath);
		tileMapFsPath = tileMapFsPath.parent_path();

		std::string tileSetRelativePath = 
			tileSetNode->first_attribute("source")->value();

		std::string tileSetAbsolutePath = 
			tileMapFsPath.generic_string() + '/' + tileSetRelativePath;

		tileSet.LoadTSX(tileSetAbsolutePath);
	}

	// Load layers
	const char* layerName = "layer";

	for (
		rapidxml::xml_node<>* layerNode = mapNode->first_node(layerName);
		layerNode != nullptr;
		layerNode = layerNode->next_sibling(layerName)) {

		int layerWidth = std::stoi(layerNode->first_attribute("width")->value());
		int layerHeight = std::stoi(layerNode->first_attribute("height")->value());

		rapidxml::xml_node<>* layerDataNode = layerNode->first_node("data");

		const std::string csvName = "csv";

		if (std::string(layerDataNode->first_attribute("encoding")->value()) != csvName) {
			std::cerr << "Map file at \"" + filePath + "\" did not use CSV encoding.";
			return false;
		}

		std::string layerCellData = layerDataNode->value();

		tileLayers.push_back(TileLayer(glm::ivec2(layerWidth, layerHeight), layerCellData));
	}

	return true;
}

void TileMap::Render(SpriteBatch& spriteBatch) {
	for (TileLayer& layer : tileLayers) {
		int width = layer.GetWidth();
		int height = layer.GetHeight();

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				int cell = layer.GetCell(x, y);

				if (cell == 0) {
					continue;
				}

				// Find tileset
				TileSet* tileSet = nullptr;

				for (int i = tileSets.size() - 1; i >= 0; i--) {
					TileSet& testTileSet = tileSets.at(i);

					if (cell >= testTileSet.firstGlobalID) {
						tileSet = &testTileSet;
						break;
					}
				}

				if (tileSet == nullptr) {
					continue;
				}

				// Draw cell
				Sprite& sprite = tileSet->sprite;

				sprite.position = glm::vec2(x, y) * tileSize;
				sprite.SetFrame(cell - tileSet->firstGlobalID);

				sprite.Render(spriteBatch);
			}
		}
	}
}