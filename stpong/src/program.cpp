#include <string>
#include <iostream>

#include "program.hpp"
#include "util/util.hpp"


void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void runProgram(GLFWwindow* window){

    // shader and vertex

    // Load shader from file as String
    std::string vertShaderStr = readFile("shader/simplestvert.glsl");
    std::string oFragShaderStr = readFile("shader/simplestfragorange.glsl");
    std::string yFragShaderStr = readFile("shader/simplestfragyellow.glsl");
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *oFragShaderSrc = oFragShaderStr.c_str();
    const char *yFragShaderSrc = yFragShaderStr.c_str();


    // Shader compilation errors utils
    int success;
    char infoLog[512];


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertexShader);
    // Check for vert shader compilation error
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int oFragmentShader;
    oFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(oFragmentShader, 1, &oFragShaderSrc, NULL);
    glCompileShader(oFragmentShader);
    // Check for frag shader compilation error
    glGetShaderiv(oFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(oFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int yFragmentShader;
    yFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(yFragmentShader, 1, &yFragShaderSrc, NULL);
    glCompileShader(yFragmentShader);
    // Check for frag shader compilation error
    glGetShaderiv(yFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(yFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // create shader program obj to link shaders
    unsigned int oShaderProgram;
    oShaderProgram = glCreateProgram();

    glAttachShader(oShaderProgram, vertexShader);
    glAttachShader(oShaderProgram, oFragmentShader);
    glLinkProgram(oShaderProgram);

    unsigned int yShaderProgram;
    yShaderProgram = glCreateProgram();

    glAttachShader(yShaderProgram, vertexShader);
    glAttachShader(yShaderProgram, yFragmentShader);
    glLinkProgram(yShaderProgram);


    glDeleteShader(vertexShader);
    glDeleteShader(oFragmentShader);
    glDeleteShader(yFragmentShader);

    float lVertices[] = {
        -0.1f,  0.5f, 0.0f,  // top right
        -0.1f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,   // top left 
    };
    unsigned int lIndices[] = {  
        0, 1, 3,   // first triangle
        1, 2, 3,    // second triangle
    };  

    float rVertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        0.1f, -0.5f, 0.0f,  // bottom left
        0.1f,  0.5f, 0.0f,   // top left 
    };
    unsigned int rIndices[] = {  
        0, 1, 3,   // first triangle
        1, 2, 3,    // second triangle
    }; 

    // Vertex Buffer Objects, Vertex Array Object, Element Buffer Objects 
    unsigned int VBOs[2], VAOs[2], EBOs[2]; 
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(2, EBOs);

    // set up first rectangle
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lVertices), lVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lIndices), lIndices, GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

   // set up second rectangle
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rVertices), rVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rIndices), rIndices, GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window)){

        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glUseProgram(oShaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glUseProgram(yShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}