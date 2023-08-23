#include <fstream>
#include <iostream>

using namespace std;
int main( void )
{
    ifstream file("srcs/vertexShader.glsl");
     std::string shader( (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() );
    if ( !file.is_open() )
        cerr << "not open\n";
    else
        cerr << "opened\n";
    cout << shader << endl;
}