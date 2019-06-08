class InputController
{
    protected:
        InputController() {}

    public:
        virtual void getDesiredDir(Entity& entity) = 0;
};

class KeyboardController : public InputController
{
    public:
        KeyboardController() : InputController() {}
    
        void getDesiredDir(Entity& entity)
        {
            if (ldk::input::isKeyDown(LDK_KEY_LEFT))
            {
                entity.desiredDir = LEFT_DIR;
            }
            else if (ldk::input::isKeyDown(LDK_KEY_RIGHT))
            {
                entity.desiredDir = RIGHT_DIR;
            }
            else if (ldk::input::isKeyDown(LDK_KEY_UP))
            {
                entity.desiredDir = UP_DIR;
            }
            else if (ldk::input::isKeyDown(LDK_KEY_DOWN))
            {
                entity.desiredDir = DOWN_DIR;
            }
        };
};

class JoystickController : public InputController
{
    public:
        JoystickController() : InputController() {}
    
        void getDesiredDir(Entity& entity)
        {
            if (ldk::input::getJoystickButton(LDK_JOYSTICK_DPAD_LEFT))
            {
                entity.desiredDir = LEFT_DIR;
            }
            else if (ldk::input::getJoystickButton(LDK_JOYSTICK_DPAD_RIGHT))
            {
                entity.desiredDir = RIGHT_DIR;
            }
            else if (ldk::input::getJoystickButton(LDK_JOYSTICK_DPAD_UP))
            {
                entity.desiredDir = UP_DIR;
            }
            else if (ldk::input::getJoystickButton(LDK_JOYSTICK_DPAD_DOWN))
            {
                entity.desiredDir = DOWN_DIR;
            }
        };
};
