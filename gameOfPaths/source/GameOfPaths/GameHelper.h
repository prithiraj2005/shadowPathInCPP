#pragma once
#include "SFML\System.hpp"
#include "Library\Grid.h"
#include <shlwapi.h>
#include "Library\Pathfinding.h"
#include "Library\VisibilityComputer.h"
#include "SFML\Graphics.hpp"
#include "Player.h"
#include <thread>

namespace sf
{
    class RenderWindow;
}
class b2World;
class PathObstacle;

class GameHelper
{
public:
    static sf::Vector2f WorldToScreenPoint(const Vector2D& worldPoint);
    static Vector2D ScreenToWorldPoint(const sf::Vector2f& screenPoint);
    static float WorldToScreenRotation(float rotation);
    static std::wstring ExecutableDirectory();
    static GameHelper& GetInstance();
    static sf::RenderWindow* GetWindow();
    Vector2D GetScreenDimensions() const;
    std::shared_ptr<Player> CreatePlayer(const Vector2D& spawnPosition, const Vector2D& playerDimensions, float playerRotation);
    std::shared_ptr<Player> GetPlayer() const;
    void Init(sf::RenderWindow * window);
    std::shared_ptr<Visibility::VisibilityComputer> GetVisibility();
    std::shared_ptr<PathObstacle> AddObstacle(Vector2D position, Vector2D dimension, float rotation, bool isVisible /*= true*/, bool isHollow /*= false*/);
#if !RELEASE
    static void DrawHex(const Grid::Hex& hex, const sf::Color& color, bool filled = false) ;
    static void DrawHex(const Vector2D& hexPos, const sf::Color& color, bool filled = false) ;
#endif
private:
    GameHelper();
    GameHelper(GameHelper const&) = delete;              // Don't Implement
    void operator=(GameHelper const&) = delete; // Don't implement
    std::shared_ptr<Player> mPlayer;
    std::shared_ptr<Visibility::VisibilityComputer> mVisibility;
    std::shared_ptr<b2World> mPhysicsWorld;
    Vector2D mScreenDimensions;
    std::unordered_set<Grid::Hex> mWalkableHex;
    static sf::RenderWindow* mWindow;
};
