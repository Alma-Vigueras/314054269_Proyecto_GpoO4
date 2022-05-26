// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = -90.0f;
float rot2 = 180.0f;
bool anim = false;
bool anim2 = false;




int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "314054269 Proyecto Final 2022-2 Gpo04", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");

    // Load models
    Model Casa((char*)"Models/Casa/Casa.obj");
    Model Puerta((char*)"Models/Door/Puerta2.obj"); 
    Model Wind((char*)"Models/Ventanas/Window1.obj");
    Model Wind2((char*)"Models/Ventanas/Window2.obj");
    Model Cristal((char*)"Models/Ventanas/Glass.obj");
    Model Balcon((char*)"Models/Door/PuertaBalcon.obj");
    Model Grass((char*)"Models/Grass/Pasto.obj");
    Model Jardinera((char*)"Models/Jardinera/Planter.obj");
    Model banco((char*)"Models/Element/Banco.obj");
    Model sillon((char*)"Models/Couch/Couch.obj");
    Model table((char*)"Models/Mesa/Mesa.obj");
    Model Ant((char*)"Models/Anthurium/Anturio.obj");
    Model Clock((char*)"Models/Clock/WallClock.obj");
    Model Projector((char*)"Models/Projector/Projector.obj");
    Model Woofer((char*)"Models/Woofer/bocina.obj");

    Model Mesa((char*)"Models/Table/WoodTable.obj");
    Model Silla((char*)"Models/Chair/Silla.obj");

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);



    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.964f, 0.964f, 0.635f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Casa.Draw(shader);
        
        //Puerta principal
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.68f, 1.2f, 3.15f));
        model = glm::scale(model, glm::vec3(1.1f, 1.28f, 1.3f));
        //model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Puerta.Draw(shader);

        //Puerta de balcon
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.95f, 4.55f, 5.15f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::scale(model, glm::vec3(0.7f, 1.08f, 1.3f));
        //model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Balcon.Draw(shader);

        //Ventanal
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.913f, 4.26f, 5.4f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::scale(model, glm::vec3(1.2f, 0.845f, 1.85f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Wind.Draw(shader);
        
        //Ventana Chica
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.85f, 4.6f, 4.6f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::scale(model, glm::vec3(0.174f, 1.2f, 1.3f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Wind.Draw(shader);

        //Ventana sala
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.75f, 1.1f, 2.9f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::scale(model, glm::vec3(0.685f, 0.92f, 1.3f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Wind.Draw(shader);

        //Ventana baño
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.5f, 1.2f, 3.4f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::scale(model, glm::vec3(0.1f, 0.07f, 0.07f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Wind2.Draw(shader);


        //Jardinera
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.4f, -0.2f, 4.5f));
        //model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::scale(model, glm::vec3(1.1f, 1.0f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Jardinera.Draw(shader);

        //Franja pasto delgado
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.15f, -0.22f, 7.0f));
        model = glm::scale(model, glm::vec3(0.03f, 1.0f, 0.25f));
        //model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Grass.Draw(shader);

        //Franja pasto grueso
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.4f, -0.22f, 7.1f));
        model = glm::scale(model, glm::vec3(0.045f, 1.0f, 0.25f));
        //model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Grass.Draw(shader);

        //Proyector
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.95f, 0.78f, 1.5f));
        model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Projector.Draw(shader);

        //Reloj
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.5f, 1.8f, 1.7f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Clock.Draw(shader);

        //Maceta anturio
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.1f, 0.65f, 0.5f));
        //model = glm::rotate(model,glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ant.Draw(shader);

        //Mesa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.9f, -0.3f, 0.8f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        table.Draw(shader);

        //Sillon 1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.7f, -0.1f, 0.5f));
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sillon.Draw(shader);

        //Sillon 2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.6f, -0.1f, 2.4f));
        model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sillon.Draw(shader);

        //Banco
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.1f, 0.5f, 0.5f));
        //model = glm::rotate(model,glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        banco.Draw(shader);

        //Bocina
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.1f, 0.49f, 2.5f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Woofer.Draw(shader);

        //Segunda Habitación

        //Mesa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.0f, 0.2f, -3.0f));
        model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Mesa.Draw(shader);

        //silla 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.7f, 0.2f, -2.0f));
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
        //model = glm::translate(model, glm::vec3(1.7f, 0.5f, -2.9f));
        model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Silla.Draw(shader);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }



}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


