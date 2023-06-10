#pragma once

#include <vector>
#include "Tile.h"

class Pathfinder
{
public:
	using TileContainer = std::vector<std::vector<Tile*>>;

	Pathfinder() = default;

	bool Init();
};