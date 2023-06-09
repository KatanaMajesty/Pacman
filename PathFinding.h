#pragma once

#include <cstdint>
#include <queue>
#include <vector>
#include <functional>
#include <utility>
#include <memory>
#include "../Pacman/src/Utility/Math.h"
#include "../Pacman/src/Game/Maze.h"

    struct Node
    {
        Vec2 pos = Vec2(0,0);
        Vec2 parent = Vec2(0,0); // from which node this one was created
        uint32_t g = 0; // distance from starting node to current
        uint32_t h = 0; // heuristic distance to the goal

        inline bool operator>(const Node& rhs) const { return (g + h) > (rhs.g + rhs.h); }
    };

    /**
     * @brief Pathfinder object implementation based on A* algorithm
     *
     * TODO: 17.11.22 - this class should be fully rewritten
     */
    class Pathfinder
    {
    public:
        using HeuristicFn = std::function<uint32_t(const Vec2&, const Vec2&)>;

    public:
        Pathfinder(Maze* maze);
        ~Pathfinder() = default;

        void reset();

        std::vector<Vec2> invoke(const Vec2& start, const Vec2& goal, const HeuristicFn& heuristic);
    private:
        std::vector<Vec2> recreatePath(const Vec2& goal) const;
        inline constexpr bool isValid(const Vec2& v) const { return v.x < m_dimensions.x && v.y < m_dimensions.y; }

        /**
         * @param parent a node's position, from which we will be checking the wall
         * @param neighbor is a move-to node's position,
         *
         * undefined behavior if length(neighbor - delta) != 1
         *
         * @return true if it is possible to move from parent to neigbor
         * @return false if there is no way to move from parent to neighbor
         */
        bool isWall(const Vec2& parent, const Vec2& neighbor) const;
        inline constexpr size_t toIndex1D(const Vec2& v) const { return static_cast<size_t>((v.y * m_dimensions.x) + v.x); };

    private:
        std::vector<Node> m_pathList;
        std::vector<bool> m_closedList;
        Vec2 m_dimensions;
        Maze* m_maze = nullptr;
    };

