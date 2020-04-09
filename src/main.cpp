#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/mat4x3.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Display.hpp>
#include <Input.hpp>
#include <Util.hpp>
#include <Shader.hpp>
#include <Camera.hpp>

#include <iostream>


struct vertex
{
  float x, y, z;
};

int main ()
{
  Display display(640, 480, "SimpleRenderer");

  float ratio = display.m_height / (float) display.m_width;

  Camera camera(75.0f, ratio, 0.003f, 1000.0f);

  std::cout << glGetString(GL_VERSION) << std::endl;

  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  vertex verticiesStack [] =
    {
     {0.0f, 0.5f, 0.4f},
     {-0.5f, -0.5f, 0.4f},
     {0.5f, -0.5f, 0.4f}
    };

  // create vertex-object-buffer (buffer on the VRAM to store verticies (super fast))
  unsigned int vbo;
  glGenBuffers(1, &vbo);

  // bind the generated buffer (context-machine!)
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // specify the layout of the buffer:
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*) 0);

  // supply data to that buffer:
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticiesStack), (void*) verticiesStack, GL_STATIC_DRAW);


  Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");

  while (!display.ShouldClose()) {

    Input::Update();

    if (Input::IsKeyPressed(GLFW_KEY_Q)) {
      display.RequestClose();
    }

    if (Input::IsKeyPressed(GLFW_KEY_W)) {
      glm::vec3 tmp = glm::vec3(0.0f, 0.0f, 0.02f);
      camera.MoveAlongDir(tmp);
    }


    if (Input::IsKeyPressed(GLFW_KEY_A)) {
      glm::vec3 tmp = glm::vec3(0.02f, 0.0f, 0.0f);
      camera.MoveAlongDir(tmp);
    }

    if (Input::IsKeyPressed(GLFW_KEY_S)) {
      glm::vec3 tmp = glm::vec3(0.0f, 0.0f, -0.02f);
      camera.MoveAlongDir(tmp);
    }

    if (Input::IsKeyPressed(GLFW_KEY_D)) {
      glm::vec3 tmp = glm::vec3(-0.02f, 0.0f, 0.0f);
      camera.MoveAlongDir(tmp);
    }

    camera.m_rot.y = Input::GetMouseX() * 0.001f;
    camera.m_rot.x = Input::GetMouseY() * 0.001f * (640.0f / 480.0f);

    shader.Bind();
    glm::mat4 model = glm::mat4(1.0f);
    shader.UniformMatrix4fv("model", model);
    glm::mat4 view = camera.GetViewMatrix();
    shader.UniformMatrix4fv("view", view);
    glm::mat4 perspective = camera.GetPerspective();
    shader.UniformMatrix4fv("perspective", perspective);

    // simple openGL-stuff to get to know openGL:
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    display.Present();
  }
}
