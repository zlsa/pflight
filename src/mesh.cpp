
#include "mesh.hpp"

Mesh::Mesh() {
  this->uses = 0;

  this->vertex_array_object            = -1;
  this->vertex_buffer_object_triangles = -1;
  this->vertex_buffer_object_uvs       = -1;
}

// Ref-counting

void Mesh::use() {
  this->uses += 1;
}

void Mesh::unuse() {
  this->uses -= 1;
  if(this->uses == 0) delete this;
}

// get/set

void Mesh::setVertices(std::vector<glm::vec3> vertices) {
  this->vertices = vertices;
}

void Mesh::setTriangles(std::vector<Triangle> triangles) {
  this->triangles = triangles;
}

// OpenGL interface

void Mesh::createBuffer() {
  glGenVertexArrays(1, &this->vertex_array_object);
  glBindVertexArray(this->vertex_array_object);

  // triangles
  
  glGenBuffers(1, &this->vertex_buffer_object_triangles);
  glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object_triangles);

  int size = this->triangles.size() * 3 * 3 * sizeof(GLfloat);
  GLfloat *buf = new GLfloat[size];

  Triangle *triangle;
  glm::vec3 *vertex;
  for(int i=0; i<this->triangles.size(); i++) {
    triangle = &this->triangles[i];
    for(int j=0; j<3; j++) {
      vertex = &this->vertices[triangle->vertex[j]];
      buf[(i * 3 * 3) + (j * 3) + 0] = vertex->x;
      buf[(i * 3 * 3) + (j * 3) + 1] = vertex->y;
      buf[(i * 3 * 3) + (j * 3) + 2] = vertex->z;
    }
  }
  
  glBufferData(GL_ARRAY_BUFFER, size, buf, GL_STATIC_DRAW);

  // uvs
  
  glGenBuffers(1, &this->vertex_buffer_object_uvs);
  
  delete[] buf;
}