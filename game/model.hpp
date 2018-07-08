#define SCREEN_WIDTH 226
#define SCREEN_HEIGHT 248
#define BACKGROUND_LAYER 0
#define WAYPOINT_LAYER 1
#define PACMAN_LAYER 2
#define WAYPOINTS_LENGTH 64

#define BINARY_LEFT 0b00000000000000000000000000001000
#define BINARY_RIGHT 0b00000000000000000000000000000100
#define BINARY_UP 0b00000000000000000000000000000010
#define BINARY_DOWN 0b00000000000000000000000000000001

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
	ldk::Vec3 Position;
	int allowedMovements = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	
	Waypoint(ldk::Vec3 pos)
	{
		Position = pos;
	}
};

struct GameState
{
	ldk::Material spritesheet;
	ldk::Sprite background;
	ldk::Sprite WaypointSprite;
	Waypoint Waypoints[WAYPOINTS_LENGTH];
    int currentWaypointIndex;
    
    ldk::Vec3 desiredDir = {};
    float desireAngle;
	Entity pacman;
} *gameState = nullptr;