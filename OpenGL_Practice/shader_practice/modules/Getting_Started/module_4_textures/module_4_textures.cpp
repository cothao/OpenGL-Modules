////#define STB_IMAGE_IMPLEMENTATION
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"
//#include <iostream>
//#include "shader.h"
//#include <memory>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//int main() {
//
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//
//    glfwMakeContextCurrent(window);
//
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//
//    std::shared_ptr<Shader> shader = std::shared_ptr<Shader>(new Shader("./textures_shader.vert", "./textures_shader.frag"));
//
///*
// * __   _____ ___ _____ ___ ___ ___ ___ 
// * \ \ / / __| _ \_   _|_ _/ __| __/ __|
// *  \ V /| _||   / | |  | | (__| _|\__ \
// *   \_/ |___|_|_\ |_| |___\___|___|___/
// *                                      
// */
//
//
//    float vertices[] = {
//        // positions          // colors           // texture coords
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
//    };
//
//    unsigned int indices[] = {  // note that we start from 0!
//        0, 1, 3,   // first triangle
//        1, 2, 3    // second triangle
//    };
//
//    unsigned int VBO, VAO, EBO;
//
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//    glGenVertexArrays(1, &VAO);
//
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//
//    glEnableVertexAttribArray(1);
//
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//
//    glEnableVertexAttribArray(2);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//
///*
// *  _____ _____  _______ _   _ ___ ___ ___ 
// * |_   _| __\ \/ /_   _| | | | _ \ __/ __|
// *   | | | _| >  <  | | | |_| |   / _|\__ \
// *   |_| |___/_/\_\ |_|  \___/|_|_\___|___/
// *                                         
// */
//    
//    unsigned int texture1, texture2;
//
//    glGenTextures(1, &texture1);
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    int width, height, nrChannels;
//    unsigned char* data = stbi_load("../images/container.jpg", &width, &height, &nrChannels, 0);
//    
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to Load Texture\n";
//    }
//   
//    stbi_image_free(data);
//
//    stbi_set_flip_vertically_on_load(true);
//
//    glGenTextures(1, &texture2);
//
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    data = stbi_load("../images/awesomeface.png", &width, &height, &nrChannels, 0);
//
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to Load Texture\n";
//    }
//
//
//    stbi_image_free(data);
//
//    shader->Use();
//
//    shader->SetInt("texture1", 0);
//    shader->SetInt("texture2", 1);
//
//    while (!glfwWindowShouldClose(window))
//    {
//
//        processInput(window);
//
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        shader->Use();
//
//        glBindVertexArray(VAO);
//
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
//        
//
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//
//
//    }
//
//    glfwTerminate();
//
//    return 0;
//
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
//
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}