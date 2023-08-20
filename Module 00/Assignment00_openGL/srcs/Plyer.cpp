#include "Player.hpp"
#include <fstream>
#include <string>

Player::~Player( void )
{}

const char *Player::loadShaderFromFile( enum SHADER sh )
{
    std::ifstream file;
    if ( sh == VERTEX )
        file.open("srcs/vertexShader.glsl");
    else
        file.open("srcs/plFragmentShader.glsl");
    
    if ( !file.is_open() )
        return (nullptr);
    std::string shader( (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() );
    return (shader.c_str());
}