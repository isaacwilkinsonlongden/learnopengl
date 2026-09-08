#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/shader.h"
#include "include/camera.h"
#include "objects/room.h"
#include "objects/skate_box.h"
#include "objects/light_bar.h"

#include <iostream>

// struct bundling the VAO/VBO pair for a world object, plus how many vertices
// it holds (derived from the buffer size, so draw calls can't drift out of sync
// with the vertex data)
struct ObjectBuffers {
    unsigned int VAO;
    unsigned int VBO;
    int vertexCount;
};

// input handling
void processInput(GLFWwindow *window);

// buffer setup helper (upload vertex data, configure vertex attributes).
// lit objects carry position + normal + texcoord; the light object is unlit
// and carries position only.
ObjectBuffers setupBuffers(const float* vertices, size_t verticesSize, bool lit);

// texture loading
unsigned int loadTexture(const char* texturePath);

// GLFW callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH  = 1920;
const unsigned int SCR_HEIGHT = 1080; 

// live framebuffer size, kept up to date by framebuffer_size_callback so the
// projection's aspect ratio follows window resizes
int fbWidth  = SCR_WIDTH;
int fbHeight = SCR_HEIGHT;

// camera 
Camera camera(glm::vec3(0.0f, -1.5f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing 
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// light position 
glm::vec3 lightPos(0.0f, 2.0f, 0.0f); 
glm::vec3 lightColor(1.0f, 1.0f, 0.9f);

int main() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, "learnopengl");

    // glfw: window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "gallery", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // the window may not have opened at exactly the requested size (tiling WMs,
    // HiDPI scaling), so seed the framebuffer size from the real one
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    // tell glfw to capture our mouse 
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // configure global OpenGL state
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    Shader objectShader("shader.vs", "shader.fs");
    Shader lightShader("light_shader.vs", "light_shader.fs");

    // setup VAO's and VBO's for world objects 
    ObjectBuffers wallBuffers = setupBuffers(wallVertices, sizeof(wallVertices), true);
    ObjectBuffers floorCeilingBuffers = setupBuffers(floorCeilingVertices, sizeof(floorCeilingVertices), true);
    ObjectBuffers skateBoxBuffers = setupBuffers(skateBoxVertices, sizeof(skateBoxVertices), true);

    // setup VAO's and VBO's for light objects
    ObjectBuffers lightBuffers = setupBuffers(lightVertices, sizeof(lightVertices), false);

    // load and create textures: one diffuse color map + one grayscale specular
    // map per material, each pair loaded together below
    stbi_set_flip_vertically_on_load(true);

    // bricks (used on the walls)
    unsigned int textureBrick = loadTexture("Bricks097_1K-JPG_Color.jpg");
    unsigned int textureBrickSpecmap = loadTexture("Bricks097_1K_specmap.png");
    // concrete (used on the floor/ceiling)
    unsigned int textureConcrete = loadTexture("Concrete042A_1K-JPG_Color.jpg");
    unsigned int textureConcreteSpecmap = loadTexture("Concrete042A_1K_specmap.png");
    // wood (used on the skate box)
    unsigned int textureWood = loadTexture("Wood039_1K-JPG_Color.jpg");
    unsigned int textureWoodSpecmap = loadTexture("Wood039_1K_specmap.png");

    objectShader.use();

    // tell OpenGL for each sampler to which texture unit it belongs to. every
    // material binds its diffuse map to unit 0 and its specular map to unit 1,
    // so these never change -- set them once rather than every frame.
    objectShader.setInt("material.diffuse", 0);
    objectShader.setInt("material.specular", 1);

    // light properties: fixed for this scene, so set once here rather than every frame
    objectShader.setVec3("light.position", lightPos);
    objectShader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
    objectShader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f);
    objectShader.setVec3("light.specular", 0.5f, 0.5f, 0.5f);
    objectShader.setFloat("light.constant",  1.0f);
    objectShader.setFloat("light.linear",    0.045f);
    objectShader.setFloat("light.quadratic", 0.0075f);

    // the light object's color is constant too
    lightShader.use();
    lightShader.setVec3("lightColor", lightColor);

    // clear color never changes either
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // per frame time logic 
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // pass projection matrix to shader (aspect ratio from the current
        // framebuffer size; guard against a zero height while minimised)
        objectShader.use();
        objectShader.setVec3("viewPos", camera.Position);
        float aspect = fbHeight > 0 ? (float)fbWidth / (float)fbHeight : 1.0f;
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), aspect, 0.1f, 100.0f);
        objectShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        objectShader.setMat4("view", view);

        // walls (brick texture), drawn at the origin with no extra transform
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureBrick);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureBrickSpecmap);
        objectShader.setFloat("material.shininess", 16.0f);
        objectShader.setMat4("model", glm::mat4(1.0f));
        glBindVertexArray(wallBuffers.VAO);
        glDrawArrays(GL_TRIANGLES, 0, wallBuffers.vertexCount);

        // floor & ceiling (concrete texture), also at the origin
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureConcrete);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureConcreteSpecmap);
        objectShader.setFloat("material.shininess", 8.0f);
        objectShader.setMat4("model", glm::mat4(1.0f));
        glBindVertexArray(floorCeilingBuffers.VAO);
        glDrawArrays(GL_TRIANGLES, 0, floorCeilingBuffers.vertexCount);

        // skate box (wood texture), offset to one side of the room and rotated to face it
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureWood);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureWoodSpecmap);
        objectShader.setFloat("material.shininess", 48.0f);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0f, -2.5f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        objectShader.setMat4("model", model);
        glBindVertexArray(skateBoxBuffers.VAO);
        glDrawArrays(GL_TRIANGLES, 0, skateBoxBuffers.vertexCount);

        // draw light object (drawn last, using its own unlit shader)
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        lightShader.setMat4("model", model);
        glBindVertexArray(lightBuffers.VAO);
        glDrawArrays(GL_TRIANGLES, 0, lightBuffers.vertexCount);

        // glfw: swap buffers and poll IO events (keys pressed/ released, mouse moved etc.) 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &wallBuffers.VAO);
    glDeleteVertexArrays(1, &floorCeilingBuffers.VAO);
    glDeleteVertexArrays(1, &skateBoxBuffers.VAO);
    glDeleteVertexArrays(1, &lightBuffers.VAO);
    glDeleteBuffers(1, &wallBuffers.VBO);
    glDeleteBuffers(1, &floorCeilingBuffers.VBO);
    glDeleteBuffers(1, &skateBoxBuffers.VBO);
    glDeleteBuffers(1, &lightBuffers.VBO);

    // glfw: terminate, clearing all previously allocated glfw resources 
    glfwTerminate();
    return 0;
}

// process all input: query glfw whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// setup VAO and VBO for an object. `lit` objects use the 8-float layout
// (position + normal + texcoord) consumed by shader.vs; unlit ones (the light
// bar) use the 3-float position-only layout consumed by light_shader.vs.
ObjectBuffers setupBuffers(const float* vertices, size_t verticesSize, bool lit) {
    ObjectBuffers buffers;

    const size_t stride = lit ? 8 : 3;
    buffers.vertexCount = static_cast<int>(verticesSize / (stride * sizeof(float)));

    glGenVertexArrays(1, &buffers.VAO);
    glGenBuffers(1, &buffers.VBO);
    glBindVertexArray(buffers.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, buffers.VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    const GLsizei strideBytes = static_cast<GLsizei>(stride * sizeof(float));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)0);
    glEnableVertexAttribArray(0);
    if (lit) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, strideBytes, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return buffers;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (!data)
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        glDeleteTextures(1, &textureID);
        return 0;
    }

    // pick the upload format based on how many channels stb_image found in the file
    GLenum format;
    if (nrComponents == 1)
        format = GL_RED;   // grayscale, e.g. the specular maps
    else if (nrComponents == 3)
        format = GL_RGB;   // no alpha, e.g. the diffuse JPGs
    else if (nrComponents == 4)
        format = GL_RGBA;  // has alpha
    else
    {
        std::cout << "Unsupported channel count (" << nrComponents << ") in texture: " << path << std::endl;
        stbi_image_free(data);
        glDeleteTextures(1, &textureID);
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // a single-channel (GL_RED) texture is sampled by GLSL as (r, 0, 0, 1) by
    // default, so without this, reading it as a vec3 in the shader would only
    // fill the red channel. Swizzling broadcasts the one channel across R/G/B
    // so it behaves like a proper grayscale value when sampled.
    if (format == GL_RED)
    {
        GLint swizzle[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
        glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
    }

    stbi_image_free(data);

    return textureID;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
    // keep the projection's aspect ratio in step with the window
    fbWidth  = width;
    fbHeight = height;
}

// glfw: whenever the mouse moves this callback is called 
void mouse_callback(GLFWwindow*, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls this callback is called 
void scroll_callback(GLFWwindow*, double, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
