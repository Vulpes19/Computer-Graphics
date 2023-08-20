#include "App.hpp"

InputHandler *InputHandler::instancePtr = nullptr;

class InputHandler
{
    public:
        ~InputHandler( void );
        static InputHandler *getInstance( void );
        bool    isKeyPressed( void );
        void    keyCallBack(GLFWwindow *, int key, int , int action, int );
    private:
        InputHandler( void );
        static InputHandler *instancePtr;
        uint8_t keyStates[GLFW_KEY_LAST + 1] = {0};
};