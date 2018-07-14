#define SCREEN_WIDTH  226
#define SCREEN_HEIGHT 248

// Layers
#define BACKGROUND_LAYER 0
#define DOTS_LAYER 1
#define PACMAN_LAYER 2
#define GHOSTS_LAYER 3
#define DEBUG_LAYER 99

// Binary directions
#define BINARY_LEFT  0x8
#define BINARY_RIGHT 0x4
#define BINARY_UP    0x2
#define BINARY_DOWN  0x1

#define WAYPOINTS_LENGTH 64
#define DOTS_LENGTH 246

#define INVALID_WAYPOINT_INDEX -1

const ldk::Vec3 LEFT_DIR  = {-1,  0,  0};
const ldk::Vec3 RIGHT_DIR = { 1,  0,  0};
const ldk::Vec3 DOWN_DIR  = { 0, -1,  0};
const ldk::Vec3 UP_DIR    = { 0,  1,  0};

struct Entity
{
	ldk::Sprite sprite;
	ldk::Vec3 direction;
	ldk::Vec3 previousPosition;
	float speed;
};

struct Waypoint
{
	ldk::Vec3 position;
	int allowedDirections;

	Waypoint(ldk::Vec3 pPos)
	{
		position = pPos;
		allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	}
};

struct Dot
{
	ldk::Vec3 position;
	bool isSpecial;
	bool isEnabled;

	Dot(ldk::Vec3 pPosition, bool pIsSpecial) :
		isEnabled(true)
	{
		position = pPosition;
		isSpecial = pIsSpecial;
	}
};

struct GameState
{
	ldk::Material spritesheet;
	ldk::Sprite background;
	ldk::Sprite dotSprite;
	Waypoint allWaypoints[WAYPOINTS_LENGTH];
	Dot allDots[DOTS_LENGTH];
	int curWaypointIndex;

	int playerPoints = 0;

	ldk::Vec3 desiredDir;
	float desiredAngle;
	Entity pacman;
} *gameState = nullptr;
