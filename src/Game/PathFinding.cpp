#include "Pathfinding.h"

#include <memory>

Pathfinder::Pathfinder(Maze* maze)
    : m_dimensions(Vec2(maze->GetWidth(), maze->GetHeight()))
    , m_maze(maze)
{
}

void Pathfinder::reset()
{
    m_pathList.clear();
    m_closedList.clear();
}

std::vector<Vec2> Pathfinder::invoke(const Vec2& start, const Vec2& goal, const HeuristicFn& heuristic)
{
    static Vec2 neighbors[] = {
        Vec2{ 0, -1}, // NORTH
        Vec2{ 1,  0}, // EAST
        Vec2{ 0,  1}, // SOUTH
        Vec2{-1,  0}, // WEST
    };

    size_t sz = m_dimensions.x * m_dimensions.y;
    reset();
    m_pathList.resize(sz);
    m_closedList.resize(sz, false);
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList; // ...

    m_pathList[toIndex1D(start)].parent = start; // assign start parent to start so we could recreate the path
    openList.push(Node{ .pos = start }); // just assign pos, everything else is zero-initialized
    Vec2 currentPos;

    while (!openList.empty())
    {
        currentPos = openList.top().pos; // get node with least f value (g + h, to be exact)
        if (currentPos == goal)
        {
            break;
        }

        // Mark node as closed one (as we just traversed it)
        openList.pop();
        m_closedList[toIndex1D(currentPos)] = true;

        for (const Vec2& v : neighbors)
        {
            Vec2 neighborPos = Vec2(currentPos.x + v.x, currentPos.y + v.y);
            size_t index = toIndex1D(neighborPos);

            if (!isValid(neighborPos) || isWall((Vec2)neighborPos) || m_closedList[index])
                continue;

            // we count new f, g and h
            uint32_t g = m_pathList[toIndex1D(currentPos)].g + 1;
            uint32_t h = heuristic(neighborPos, goal);
            uint32_t f = g + h;

            // if neighbors f == 0 (means we didn't traverse it yet) or is less than our current f
            // then we assign our f to the node and push it into openList
            uint32_t neighborF = m_pathList[index].g + m_pathList[index].h;
            if (neighborF == 0 || f < neighborF)
            {
                Node n = { neighborPos, currentPos, g, h };
                openList.push(n);
                m_pathList[index] = n;
            }
        }
    }

    return recreatePath(goal);
}

std::vector<Vec2> Pathfinder::recreatePath(const Vec2& goal) const
{
    std::vector<Vec2> path;

    Vec2 current = goal;
    size_t index = toIndex1D(current);

    while (m_pathList[index].parent != current)
    {
        path.push_back(current);
        current = m_pathList[index].parent;
        index = toIndex1D(current);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

bool Pathfinder::isWall(const Vec2& neighbor) const
{
    return m_maze->GetTile(neighbor.x, neighbor.y)->IsCollider();
}
    