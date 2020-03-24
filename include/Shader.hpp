#pragma once

#include <glm/mat4x4.hpp>
#include <string>

class Shader
{
private:
  unsigned int m_program;

public:
  Shader (const char* vertexShader, const char* fragmentShader);
  ~Shader ();

  void UniformMatrix4fv (const std::string& name, glm::mat4& matrix);

  void Bind ();



  static void UnbindAll ();
};
