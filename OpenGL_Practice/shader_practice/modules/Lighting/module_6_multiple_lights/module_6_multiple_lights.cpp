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
//    std::shared_ptr<Shader> lightingShader = std::shared_ptr<Shader>(new Shader("./modules/Lighting/module_6_multiple_lights/multiple_lights_shader.vert", "./modules/Lighting/module_6_multiple_lights/multiple_lights_shader.frag"));
//    std::shared_ptr<Shader> lightCubeShader = std::shared_ptr<Shader>(new Shader("./modules/Lighting/module_6_multiple_lights/multiple_lights_light_shader.vert", "./modules/Lighting/module_6_multiple_lights/multiple_lights_light_shader.frag"));
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
//    glm::vec3 pointLightPositions[] = {
//    glm::vec3(0.7f,  0.2f,  2.0f),
//    glm::vec3(2.3f, -3.3f, -4.0f),
//    glm::vec3(-4.0f,  2.0f, -12.0f),
//    glm::vec3(0.0f,  0.0f, -3.0f)
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
//        // positions          // normals           // texture coords
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
// 
//    /*
//     *  _    ___ ___ _  _ _____      ___ _   _ ___ ___ 
//     * | |  |_ _/ __| || |_   _|    / __| | | | _ ) __|
//     * | |__ | | (_ | __ | | |     | (__| |_| | _ \ _| 
//     * |____|___\___|_||_| |_|      \___|\___/|___/___|
//     *                                                 
//     */
//
//    glGenVertexArrays(1, &lightCubeVAO);
//    glBindVertexArray(lightCubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//
//    glEnableVertexAttribArray(0);
//
//    /*
//     *  _____ _____  _______ _   _ ___ ___ ___ 
//     * |_   _| __\ \/ /_   _| | | | _ \ __/ __|
//     *   | | | _| >  <  | | | |_| |   / _|\__ \
//     *   |_| |___/_/\_\ |_|  \___/|_|_\___|___/
//     *                                         
//     */
//    
//     unsigned int diffuseMap, specularMap;
// 
//     glGenTextures(1, &diffuseMap);
// 
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, diffuseMap);
// 
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 
//     int width, height, nrChannels;
//     unsigned char* data = stbi_load("../images/container2.png", &width, &height, &nrChannels, 0);
//     
//     if (data)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to Load Texture\n";
//     }
//    
//     stbi_image_free(data);
//
//     glGenTextures(1, &specularMap);
//
//     glActiveTexture(GL_TEXTURE1);
//     glBindTexture(GL_TEXTURE_2D, specularMap);
//
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//     data = stbi_load("../images/container2_specular.png", &width, &height, &nrChannels, 0);
//
//     if (data)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to Load Texture\n";
//     }
//
//     stbi_image_free(data);
//
//    lightingShader->Use();
//    lightingShader->SetInt("material.diffuse", 0);
//    lightingShader->SetInt("material.specular", 1);
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
//        lightingShader->SetVec3("light.position", lightPos);
//        lightingShader->SetVec3("viewPos", camera->CameraPos);
//
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
//        lightingShader->SetVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
//        lightingShader->SetVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken diffuse light a bit
//        lightingShader->SetVec3("light.specular", glm::vec3( 1.0f, 1.0f, 1.0f));
//        lightingShader->SetVec3("light.direction", glm::vec3( - 0.2f, -1.0f, -0.3f));
//
//        lightingShader->SetFloat("light.constant", 1.0f);
//        lightingShader->SetFloat("light.linear", 0.09f);
//        lightingShader->SetFloat("light.quadratic", 0.032f);
//
//        lightingShader->SetVec3("light.position", camera->CameraPos);
//        lightingShader->SetVec3("light.direction", camera->CameraFront);
//        lightingShader->SetFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
//        lightingShader->SetFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
//        // directional light
//        lightingShader->SetVec3("dirLight.direction", glm::vec3(- 0.2f, -1.0f, -0.3f));
//        lightingShader->SetVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
//        lightingShader->SetVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
//        lightingShader->SetVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
//        // point light 1
//        lightingShader->SetVec3("pointLights[0].position", pointLightPositions[0]);
//        lightingShader->SetVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
//        lightingShader->SetVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
//        lightingShader->SetVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        lightingShader->SetFloat("pointLights[0].constant", 1.0f);
//        lightingShader->SetFloat("pointLights[0].linear", 0.09f);
//        lightingShader->SetFloat("pointLights[0].quadratic", 0.032f);
//        // point light 2
//        lightingShader->SetVec3("pointLights[1].position", pointLightPositions[1]);
//        lightingShader->SetVec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
//        lightingShader->SetVec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
//        lightingShader->SetVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        lightingShader->SetFloat("pointLights[1].constant", 1.0f);
//        lightingShader->SetFloat("pointLights[1].linear", 0.09f);
//        lightingShader->SetFloat("pointLights[1].quadratic", 0.032f);
//        // point light 3
//        lightingShader->SetVec3("pointLights[2].position", pointLightPositions[2]);
//        lightingShader->SetVec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
//        lightingShader->SetVec3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
//        lightingShader->SetVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        lightingShader->SetFloat("pointLights[2].constant", 1.0f);
//        lightingShader->SetFloat("pointLights[2].linear", 0.09f);
//        lightingShader->SetFloat("pointLights[2].quadratic", 0.032f);
//        // point light 4
//        lightingShader->SetVec3("pointLights[3].position", pointLightPositions[3]);
//        lightingShader->SetVec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
//        lightingShader->SetVec3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
//        lightingShader->SetVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        lightingShader->SetFloat("pointLights[3].constant", 1.0f);
//        lightingShader->SetFloat("pointLights[3].linear", 0.09f);
//        lightingShader->SetFloat("pointLights[3].quadratic", 0.032f);
//        // spotLight
//        lightingShader->SetVec3("spotLight.position", camera->CameraPos);
//        lightingShader->SetVec3("spotLight.direction", camera->CameraFront);
//        lightingShader->SetVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
//        lightingShader->SetVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
//        lightingShader->SetVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
//        lightingShader->SetFloat("spotLight.constant", 1.0f);
//        lightingShader->SetFloat("spotLight.linear", 0.09f);
//        lightingShader->SetFloat("spotLight.quadratic", 0.032f);
//        lightingShader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//        lightingShader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//        glBindVertexArray(VAO);
//
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            lightingShader->SetMat4("model", model);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, lightPos);
//
//        lightCubeShader->Use();
//
//        lightCubeShader->SetMat4("view", view);
//        lightCubeShader->SetMat4("projection", projection);
//
//        glBindVertexArray(lightCubeVAO);
//
//        for (unsigned int i = 0; i < 4; i++)
//        {
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, pointLightPositions[i]);
//            model = glm::scale(model, glm::vec3(0.2f));
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            lightCubeShader->SetMat4("model", model);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
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