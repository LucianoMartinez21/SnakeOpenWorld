/*#include "player.h"
#include "raylib.h"
#include "tile.h"
#include "unordered_map"
#include <cstddef>
#include <functional>
#include <memory_resource>

inline bool operator==(const Vector2& a, const Vector2& b)
{
    return a.x == b.x && a.y == b.y;
}
template <>
struct std::hash<Vector2>
{
    size_t operator()(const Vector2& v) const noexcept
    {
        size_t hx = std::hash<float>{}(v.x);
        size_t hy = std::hash<float>{}(v.y);
        return hx ^(hy << 32);
    }
};

class Grid
{
    private:
        std::pmr::unordered_map<Vector2, Tile> GridMap;
    public:
        Grid() : GridMap(std::pmr::get_default_resource()) {}
        static constexpr int CellSize = 200;
        void Clear();
        Vector2 CellKey(Vector2 Position);
        void AddToGrid(Tile &Object);
        Tile* GetNearby(Player& Dude);
};
*/
