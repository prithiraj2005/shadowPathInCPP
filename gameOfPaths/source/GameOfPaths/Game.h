#pragma once
#include "SFML\Graphics.hpp"
#include "Library\Pathfinding.h"
#include "pathobstacle.h"
#include "Enemy.h"
#include "Library\VisibilityComputer.h"
#include "SFML\System.hpp"
#include "Map.h"
#include "EnemyManager.h"
class Game : public Object::IUpdatableObject
{
public:
    Game(std::function<void*()> getWindow);
    void Init();
    virtual ~Game() = default;
    void Draw();

    void DrawHUD() const;
    void AddPlayer(const Object::Transform& playerSpawnTransform);
    void Update(float dT) override;
private:
    sf::RenderWindow* mWindow;
    std::shared_ptr<Map> mMap;
    std::shared_ptr<EnemyManager> mEnemyManager;
    std::list<std::shared_ptr<Object::Transform>> mTransforms;
    std::list<std::shared_ptr<Object::IRenderableObject>> mRenderables;
    std::list<std::shared_ptr<Object::IUpdatableObject>> mUpdatables;
    std::vector<Vector2D> mVisibilityPoints;
    float mFPSCounter;
    sf::Mutex mMutex;
#if !RELEASE
    std::list<Grid::Hex> mHexInPath;
    std::unordered_set<Grid::Hex> mTestedHex;
    std::shared_ptr<std::list<Vector2D>> mPath;
    long mTimeToFindPath;
    bool mEnablePathDebugDraw;
    bool mEnableBlockedHexDebugDraw;
#endif
};

