#pragma once

#include <glad/gl.h>
#include "vertex.hpp"
#include <iostream>
using namespace std;
namespace our
{

#define ATTRIB_LOC_POSITION 0
#define ATTRIB_LOC_COLOR 1
#define ATTRIB_LOC_TEXCOORD 2
#define ATTRIB_LOC_NORMAL 3

    class Mesh
    {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        // A vertex array object,
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements
        GLsizei elementCount;

    public:
        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &elements)
        {
            // TODO: (Req 2) Write this function
            //  remember to store the number of elements in "elementCount" since you will need it for drawing
            //  For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc

            //  1.Create Vertex Buffer
            // Syntax: void glGenBuffers(GLsizei n,GLuint * buffers);
            glGenBuffers(1, &VBO);
            // Syntax: void glBindBuffer(GLenum target,GLuint buffer);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // 2.Buffer Data To VBO
            // Syntax: void glBufferData(GLenum target,GLsizeiptr size [total size of the data to be stored in the buffer],const void * data, GLenum usage);
            // size= # of vertices in the vector * size of each Vertex
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
            // FIXME: Unbind Vertex Buffer
            // glBindBuffer(GL_ARRAY_BUFFER,0);

            // 3.Create Element Buffer
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            // 4.Buffer Data To EBO
            // size= # of elements in the vector * size of each element
            // CHECK: @AhmedHosny2024 .data()??
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);
            // FIXME: Unbind Element Buffer
            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

            // 5.Vertex Array
            // Syntax: void glGenVertexArrays(GLsizei n, GLuint *arrays);
            glGenVertexArrays(1, &VAO);
            // Syntax: void glBindVertexArray(GLuint array);
            glBindVertexArray(VAO);
            // FIXME: glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // 6. Position Attribute
            // FIXME:what does it do??
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);
            // Syntax: void glVertexAttribPointer (GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,const void * pointer);
            // How will we read bits inside the buffer ??
            // size:3 ➡ vec3 position
            // type:FLOAT ➡ typedef vec<3, float, defaultp>	vec3;
            // non-normalized
            // stride: complete vertex
            // offset: from start
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, false, sizeof(Vertex), 0);

            // 7. Color Attribute
            // FIXME: what does it do??
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);
            // How will we read bits inside the buffer ??
            // size:4 ➡ vec<4, glm::uint8, glm::defaultp> Color; (vec4)
            // type:GL_UNSIGNED_BYTE ➡ vec<4, glm::uint8, glm::defaultp> Color; (uint8)
            // normalized: true ==> uint8 =>0-255 so we need to make it normalized
            // stride: complete vertex
            // offset: skip position
            // CHECK: @AhmedHosny2024 is it Normalized??
            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void *)offsetof(Vertex, color));

            // 8. Texture Attribute
            // FIXME: what does it do??
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);
            // How will we read bits inside the buffer ??
            // size:4 ➡ vec<4, glm::uint8, glm::defaultp> Color; (vec4)
            // type:GL_UNSIGNED_BYTE ➡ vec<4, glm::uint8, glm::defaultp> Color; (uint8)
            // normalized: true ==> uint8 =>0-255 so we need to make it normalized
            // stride: complete vertex
            // offset: skip position
            // CHECK: @AhmedHosny2024 is it Normalized??
            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, false, sizeof(Vertex), (void *)(offsetof(Vertex, tex_coord)));

            // 9. normal Attribute
            // FIXME: what does it do??
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);
            // How will we read bits inside the buffer ??
            // size:4 ➡ vec<4, glm::uint8, glm::defaultp> Color; (vec4)
            // type:GL_UNSIGNED_BYTE ➡ vec<4, glm::uint8, glm::defaultp> Color; (uint8)
            // normalized: true ==> uint8 =>0-255 so we need to make it normalized
            // stride: complete vertex
            // offset: skip position
            // CHECK: @AhmedHosny2024 is it Normalized??
            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, false, sizeof(Vertex), (void *)(offsetof(Vertex, normal)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            // FIXME: Unbind Vertex Array
            glBindVertexArray(0);

            // 10.Set Num of Elements to size of the vector
            elementCount = elements.size();
        }

        // this function should render the mesh
        void draw()
        {
            // TODO: (Req 2) Write this function
            // 1. Bind Vertex Array
            glBindVertexArray(VAO);

            // 2. Draw
            //  Syntax: void glDrawElements(GLenum mode,GLsizei count,GLenum type,const void * indices);
            //  CHECK: count:  => # of the elements in elements vector
            // type: type of one element is unsigned int
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
           // cout << "Drawn" << endl;
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh()
        {
            // TODO: (Req 2) Write this function
            // Syntax: void glDeleteBuffers(GLsizei n,const GLuint * buffers);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            // Syntax: void glDeleteVertexArrays(GLsizei n,const GLuint *arrays);
            glDeleteVertexArrays(1, &VAO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}