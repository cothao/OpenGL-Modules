//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
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
//    std::shared_ptr<Shader> shader = std::shared_ptr<Shader>(new Shader("./shaders_shader.vert", "./shaders_shader.frag"));
//
//    float vertices[] = {
//        // positions         // colors
//         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
//        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
//         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
//    };
//
//    unsigned int VBO, VAO;
//
//    glGenBuffers(1, &VBO);
//
//    glGenVertexArrays(1, &VAO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//
//    while (!glfwWindowShouldClose(window))
//    {
//
//        processInput(window);
//
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        float timeValue = glfwGetTime();
//        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//
//        shader->Use();
//
//        glBindVertexArray(VAO);
//
//        glDrawArrays(GL_TRIANGLES,0, 6);
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