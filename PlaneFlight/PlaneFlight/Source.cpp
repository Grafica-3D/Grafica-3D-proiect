#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 50.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	//Shader vertexShader("shader.vs", "shader.fs");
	Shader modelShader("modelShader.vs", "modelShader.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//float vertices[] = {
	//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	//};
	//// world space positions of our cubes
	//glm::vec3 cubePositions[] = {
	//	glm::vec3(0.0f,  0.0f,  0.0f),
	//	glm::vec3(2.0f,  5.0f, -15.0f),
	//	glm::vec3(-1.5f, -2.2f, -2.5f),
	//	glm::vec3(-3.8f, -2.0f, -12.3f),
	//	glm::vec3(2.4f, -0.4f, -3.5f),
	//	glm::vec3(-1.7f,  3.0f, -7.5f),
	//	glm::vec3(1.3f, -2.0f, -2.5f),
	//	glm::vec3(1.5f,  2.0f, -2.5f),
	//	glm::vec3(1.5f,  0.2f, -1.5f),
	//	glm::vec3(-1.3f,  1.0f, -1.5f)
	//};
	//unsigned int VBO, VAO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);

	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// texture coord attribute
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);


	// load and create a texture 
	// -------------------------
	//Texture texture("images/awesomeface.png", true);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	/*vertexShader.use();
	vertexShader.setInt("texture", 0);*/

	Model terrain("models/terrain/final_terrain.obj");

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture.id);

		// activate shader
		//vertexShader.use();

		//// pass projection matrix to shader (note that in this case it could change every frame)
		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//vertexShader.setMat4("projection", projection);

		//// camera/view transformation
		//glm::mat4 view = camera.GetViewMatrix();
		//vertexShader.setMat4("view", view);

		//// render boxes
		//glBindVertexArray(VAO);
		//for (unsigned int i = 0; i < 10; i++)
		//{
		//	// calculate the model matrix for each object and pass it to shader before drawing
		//	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//	model = glm::translate(model, cubePositions[i]);
		//	float angle = 20.0f * i;
		//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	vertexShader.setMat4("model", model);

		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		// activate shader
		modelShader.use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		modelShader.setMat4("projection", projection);
		modelShader.setMat4("view", view);

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		modelShader.setMat4("model", model);
		//nanosuitModel.Draw(modelShader);
		terrain.Draw(modelShader);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);*/

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
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

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}