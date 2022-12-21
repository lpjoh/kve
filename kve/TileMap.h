#pragma once
#include <vector>
#include "Sprite.h"

namespace kve {
	class TileSet {
	public:
		int firstGlobalID;
		Sprite sprite;

		bool LoadTSX(const std::string filePath);
		
		TileSet(int firstGlobalID);
	};

	class TileLayer {
	private:
		glm::ivec2 size;
		std::vector<int> cells;

	public:
		glm::ivec2 GetSize();

		int GetCell(int x, int y);

		TileLayer(glm::ivec2 size, std::string& cellData);
	};

	class TileMap {
	private:
		glm::ivec2 size;
		glm::vec2 tileSize;

		std::vector<TileSet> tileSets;
		std::vector<TileLayer> tileLayers;
	
	public:
		bool LoadTMX(const std::string filePath);
		
		void Render(SpriteBatch& spriteBatch);
	};
}