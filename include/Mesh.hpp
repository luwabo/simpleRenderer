#pragma once

#include <glm/glm.hpp>


struct Vertex {
  float u, v;
  float x, y, z;
};

class Mesh
{
private:
  int vbo;
  Vertex verticies[];
  
  

protected:

public:
};
