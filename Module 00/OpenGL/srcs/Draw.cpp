#include "Draw.hpp"

Draw::Draw( void )
{
    this->vertexArrObj = 0;
    this->vertexBufferObj = 0;
    this->IndexBufferObj = 0;
    this->shaderProgram1 = 0;
    this->shaderProgram2 = 0;
    this->elementBufferObj = 0;
}

Draw::~Draw( void )
{}

void    Draw::initTriangle( vec3 p1, vec3 p2, vec3 p3 )
{
    compileShaderProgram();
    vertices[0] = p1.x;
    vertices[0] = p1.y;
    vertices[0] = p1.z;
    vertices[1] = p2.x;
    vertices[1] = p2.y;
    vertices[1] = p2.z;
    vertices[2] = p3.x;
    vertices[2] = p3.y;
    vertices[2] = p3.z;
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

void    Draw::initTwoTriangles( vec3 p1, vec3 p2, vec3 p3, vec3 p4, vec3 p5 )
{
    compileShaderProgram();
    float vertices[] = {
        p1.x, p1.y, p1.z,
        p2.x, p2.y, p2.z,
        p3.x, p3.y, p3.z,
        p4.x, p4.y, p4.z,
        p5.x, p5.y, p5.z,
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

void    Draw::initTwoTrianglesDifferentBuf( vec3 p1, vec3 p2, vec3 p3, vec3 p4, vec3 p5 )
{
    compileShaderProgram();
    float triangle1_vertices[] = {
        p1.x, p1.y, p1.z,
        p2.x, p2.y, p2.z,
        p3.x, p3.y, p3.z
    };
    float triangle2_vertices[] = {
        p4.x, p4.y, p4.z,
        p5.x, p5.y, p5.z,
        p3.x, p3.y, p3.z
    };
    //generating a vertex buffer object that can store a large
    //number of vertices in the GPU's memory
    glGenVertexArrays(2, vertexArrObjs);
    glGenBuffers(2, vertexBufferObjs);
    glBindVertexArray(vertexArrObjs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjs[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1_vertices), triangle1_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);
    
    glBindVertexArray(vertexArrObjs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2_vertices), triangle2_vertices, GL_STATIC_DRAW);
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
    glUseProgram(shaderProgram1);
    glBindVertexArray(vertexArrObj);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void    Draw::renderTwoTriangles( void )
{
    glUseProgram(shaderProgram1);
    glBindVertexArray(vertexArrObjs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(shaderProgram2);
    glBindVertexArray(vertexArrObjs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void    Draw::renderRectangle( void )
{
    glUseProgram(shaderProgram1);
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
    int success_frag1, success_frag2;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        char infoLog[512];
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        std::cerr << "Error: vertex shader compilation failed\n" << infoLog << std::endl;
    }

    //fragment shader in the OpenGL shader language (GLSL)
    const char *fragmentShaderStr = { 
                            "#version 330 core\n"
                            "out vec4 fragColor;\n"
                            "void main()\n"
                            "{\n"
                            " fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                            "}\n\0"
                            };
    const char *fragmentShaderStr2 = {
                            "#version 330 core\n"
                            "out vec4 fragColor;\n"
                            "void main()\n"
                            "{\n"
                            " fragColor = vec4(0.5f, 0.5f, 1.0f, 1.0f);\n"
                            "}\n\0" 
                            };
    GLuint  fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint  fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderStr, NULL);
    glShaderSource(fragmentShader2, 1, &fragmentShaderStr2, NULL);
    glCompileShader(fragmentShader1);
    glCompileShader(fragmentShader2);

    glGetShaderiv( fragmentShader1, GL_COMPILE_STATUS, &success_frag1 );
    glGetShaderiv( fragmentShader2, GL_COMPILE_STATUS, &success_frag2 );
    if ( !success_frag1 )
    {
        char infoLog[512];
        glGetShaderInfoLog( fragmentShader1, 512, NULL, infoLog );
        std::cerr << "Error: fragment shader compilation failed\n" << infoLog << std::endl;
    }
    if ( !success_frag2 )
    {
        char infoLog[512];
        glGetShaderInfoLog( fragmentShader2, 512, NULL, infoLog );
        std::cerr << "Error: fragment shader compilation failed\n" << infoLog << std::endl;
    }
    //creating the shader program
    shaderProgram1 = glCreateProgram();
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram1);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success_frag1);
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success_frag2);
    if ( !success_frag1 )
    {
        char infoLog[512];
        glGetProgramInfoLog( shaderProgram1, 512, NULL, infoLog );
        std::cerr << "Error: shader program linking failed\n" << infoLog << std::endl;
    }
    if ( !success_frag2 )
    {
        char infoLog[512];
        glGetProgramInfoLog( shaderProgram2, 512, NULL, infoLog );
        std::cerr << "Error: shader program linking failed\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);
}