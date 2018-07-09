#define SCREEN_WIDTH  226
#define SCREEN_HEIGHT 248
// Layers
#define BACKGROUND_LAYER 0
#define WAYPOINT_LAYER   1
#define PACMAN_LAYER     2
// Binary directions
#define BINARY_LEFT  0b1000
#define BINARY_RIGHT 0b100
#define BINARY_UP    0b0010
#define BINARY_DOWN  0b0001

#define WAYPOINTS_LENGTH 64

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
	int allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);

	Waypoint(ldk::Vec3 pos)
	{
		position = pos;
	}
};

struct GameState
{
	ldk::Material spritesheet;
	ldk::Sprite background;
	ldk::Sprite waypointSprite;
	Waypoint waypoints[WAYPOINTS_LENGTH];
	int currentWaypointIndex;

	ldk::Vec3 desiredDir = {};
	float desiredAngle;
	Entity pacman;
} *gameState = nullptr;
