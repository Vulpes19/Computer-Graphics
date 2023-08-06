#include "Draw.hpp"

Draw::Draw( void )
{
    this->vertexArrObj = 0;
    this->vertexBufferObj = 0;
    this->IndexBufferObj = 0;
    this->shaderProgram = 0;
    this->elementBufferObj = 0;
}

Draw::~Draw( void )
{}

void    Draw::initTriangle( vec3 p1, vec3 p2, vec3 p3 )
{
    compileShaderProgram();
    float vertices[] = {
        p1.x, p1.y, p1.z,
        p2.x, p2.y, p2.z,
        p3.x, p3.y, p3.z
    };
    //generating a vertex buffer object that can store a large
    //number of vertices in the GPU's memory
    glGenVertexArrays(1, &vertexArrObj);
    glGenBuffers(1, &vertexBufferObj);
    glBindVertexArray(vertexArrObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);

    //copies user defined data into the currently bound buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //specify how OpenGL should interpret the vertex data before rendering

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);
}

void    Draw::initRectangle( vec3 p1, vec3 p2, vec3 p3, vec3 p4 )
{
    compileShaderProgram();
    float vertices[] = {
        p1.x, p1.y, p1.z,
        p2.x, p2.y, p2.z,
        p3.x, p3.y, p3.z,
        p4.x, p4.y, p4.z
    };
    unsigned int indices[] = {
        0, 2, 3,
        0, 1, 3
    };
    glGenVertexArrays(1, &vertexArrObj);
    glGenBuffers(1, &vertexBufferObj);
    glGenBuffers(1, &elementBufferObj);
    glBindVertexArray(vertexArrObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
}

void    Draw::renderTriangle( void )
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrObj);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void    Draw::renderRectangle( void )
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrObj);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void    Draw::compileShaderProgram( void )
{
    //simple shaders to display the triangle

    //vertex shader in the OpenGL shader language (GLSL)
    const char *vertexShaderStr = "#version 330 core\n"
                            "layout (location = 0) in vec3 pos;\n"
                            "void main()\n"
                            "{\n"
                            "   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
                            "}\0";
    //creating a shader object providing the type of the shader which is GL_VERTEX_SHADER
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // exit(1);
    glShaderSource(vertexShader, 1, &vertexShaderStr, NULL);
    glCompileShader(vertexShader);

    //ERROR handling, checking if the compilation went well
    int success;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        char infoLog[512];
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        std::cerr << "Error: vertex shader compilation failed\n" << infoLog << std::endl;
    }

    //fragment shader in the OpenGL shader language (GLSL)
    const char *fragmentShaderStr = "#version 330 core\n"
                            "out vec4 fragColor;\n"
                            "void main()\n"
                            "{\n"
                            " fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                            "}\n\0";
    GLuint  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderStr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        char infoLog[512];
        glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
        std::cerr << "Error: fragment shader compilation failed\n" << infoLog << std::endl;
    }

    //creating the shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if ( !success)
    {
        char infoLog[512];
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
        std::cerr << "Error: shader program linking failed\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}