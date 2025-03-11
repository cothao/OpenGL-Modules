////#define STB_IMAGE_IMPLEMENTATION
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "../../../stb_image.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <iostream>
//#include "../../../shader.h"
//#include "../../../camera.h"
//#include <memory>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void processInput(GLFWwindow* window);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//float deltaTime = 0.0f;	// Time between current frame and last frame
//float lastFrame = 0.0f; // Time of last frame
//float fov = 45.f;
//std::shared_ptr<Camera> camera = std::shared_ptr<Camera>(new Camera(cameraPos, deltaTime));
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
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    glEnable(GL_DEPTH_TEST);
//
//
//    std::shared_ptr<Shader> lightingShader = std::shared_ptr<Shader>(new Shader("./modules/Lighting/module_3_materials/materials_shader.vert", "./modules/Lighting/module_3_materials/materials_shader.frag"));
//    std::shared_ptr<Shader> lightCubeShader = std::shared_ptr<Shader>(new Shader("./modules/Lighting/module_3_materials/materials_light_shader.vert", "./modules/Lighting/module_3_materials/materials_light_shader.frag"));
//
//    glm::vec3 cubePositions[] = {
//    glm::vec3(0.0f,  0.0f,  0.0f),
//    glm::vec3(2.0f,  5.0f, -15.0f),
//    glm::vec3(-1.5f, -2.2f, -2.5f),
//    glm::vec3(-3.8f, -2.0f, -12.3f),
//    glm::vec3(2.4f, -0.4f, -3.5f),
//    glm::vec3(-1.7f,  3.0f, -7.5f),
//    glm::vec3(1.3f, -2.0f, -2.5f),
//    glm::vec3(1.5f,  2.0f, -2.5f),
//    glm::vec3(1.5f,  0.2f, -1.5f),
//    glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//
//    /*
//     * __   _____ ___ _____ ___ ___ ___ ___
//     * \ \ / / __| _ \_   _|_ _/ __| __/ __|
//     *  \ V /| _||   / | |  | | (__| _|\__ \
//     *   \_/ |___|_|_\ |_| |___\___|___|___/
//     *
//     */
//
//    float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//    };
//
//    unsigned int VBO, VAO, lightCubeVAO;
//
//    glGenBuffers(1, &VBO);
//    glGenVertexArrays(1, &VAO);
//
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
//    glBindVertexArray(0);
//
//    glGenVertexArrays(1, &lightCubeVAO);
//    glBindVertexArray(lightCubeVAO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//
//    lightingShader->Use();
//
//    while (!glfwWindowShouldClose(window))
//    {
//
//        processInput(window);
//
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        camera->Update(window, deltaTime);
//
//        glm::mat4 model = glm::mat4(1.0f);
//
//        glm::mat4 view = glm::mat4(1.0f);
//        // note that we're translating the scene in the reverse direction of where we want to move
//        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//
//        glm::mat4 projection;
//        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
//
//        view = glm::lookAt(camera->CameraPos, camera->CameraPos + camera->CameraFront, camera->CameraUp);
//
//        lightingShader->Use();
//
//        lightingShader->SetMat4("model", model);
//        lightingShader->SetMat4("view", view);
//        lightingShader->SetMat4("projection", projection);
//        lightingShader->SetVec3("lightPos", lightPos);
//        lightingShader->SetVec3("viewPos", camera->CameraPos);
//
//        lightingShader->SetVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
//        lightingShader->SetVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
//        lightingShader->SetVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
//        lightingShader->SetFloat("material.shininess", 32.0f);
//
//
//        /*
//         *  _    ___ ___ _  _ _____ 
//         * | |  |_ _/ __| || |_   _|
//         * | |__ | | (_ | __ | | |  
//         * |____|___\___|_||_| |_|  
//         *                          
//         */
//        
//        // Change Color Over Time
//        //glm::vec3 lightColor;
//        //lightColor.x = sin(glfwGetTime() * 2.0f);
//        //lightColor.y = sin(glfwGetTime() * 0.7f);
//        //lightColor.z = sin(glfwGetTime() * 1.3f);
//
//        //glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
//        //glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
//
//        //lightingShader->SetVec3("light.ambient", ambientColor);
//        //lightingShader->SetVec3("light.diffuse", diffuseColor);
//
//        lightingShader->SetVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
//        lightingShader->SetVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken diffuse light a bit
//        lightingShader->SetVec3("light.specular", glm::vec3( 1.0f, 1.0f, 1.0f));
//
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, lightPos);
//        model = glm::scale(model, glm::vec3(0.2f));
//
//        lightCubeShader->Use();
//
//        lightCubeShader->SetMat4("model", model);
//        lightCubeShader->SetMat4("view", view);
//        lightCubeShader->SetMat4("projection", projection);
//
//        glBindVertexArray(lightCubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
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
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    camera->MoveCamera(xpos, ypos);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    fov -= (float)yoffset;
//    if (fov < 1.0f)
//        fov = 1.0f;
//    if (fov > 45.0f)
//        fov = 45.0f;
//}