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

            // Step(1) Create Vertex Array
            //  Syntax: void glGenVertexArrays(GLsizei n, GLuint *arrays);
            glGenVertexArrays(1, &VAO);
            // Syntax: void glBindVertexArray(GLuint array);
            glBindVertexArray(VAO);
            //glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // Step(2) Create Vertex Buffer
            //  Syntax: void glGenBuffers(GLsizei n,GLuint * buffers);
            glGenBuffers(1, &VBO);
            // Syntax: void glBindBuffer(GLenum target,GLuint buffer);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            // Buffer Data To VBO
            // Syntax: void glBufferData(GLenum target,GLsizeiptr size [total size of the data to be stored in the buffer],const void * data, GLenum usage);
            // size= # of vertices in the vector * size of each Vertex
            // STATIC_DRAW => the data store contents will be modified once and used many times.
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            // Step(3) Create Attr Array Buffer [Set Set attributes] [Add these attributes to the vertices in the vertex buffer]
            //  1.Position Attribute
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);
            // Syntax: void glVertexAttribPointer (GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,const void * pointer);
            // How will we read bits inside the buffer ??
            // size:3 ➡ vec3 position
            // type:FLOAT ➡ typedef vec<3, float, defaultp>	vec3;
            // non-normalized
            // stride: complete vertex
            // offset: from start
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, false, sizeof(Vertex), 0);

            // 2. Color Attribute
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);
            // How will we read bits inside the buffer ??
            // size:4 ➡ vec<4, glm::uint8, glm::defaultp> Color; (vec4)
            // type:GL_UNSIGNED_BYTE ➡ vec<4, glm::uint8, glm::defaultp> Color; (uint8)
            // normalized: true ==> uint8 =>0-255 so we need to make it normalized
            // stride: complete vertex
            // offset: skip position
            // Write color attribute value to the vertex buffer by leaving offset of the postion
            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void *)offsetof(Vertex, color));

            // 3. Texture Attribute
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);
            // How will we read bits inside the buffer ??
            // size:4 ➡ vec<4, glm::uint8, glm::defaultp> Color; (vec4)
            // type:GL_UNSIGNED_BYTE ➡ vec<4, glm::uint8, glm::defaultp> Color; (uint8)
            // normalized: true ==> uint8 =>0-255 so we need to make it normalized
            // stride: complete vertex
            // offset: skip position
            // Write Text attribute value to the vertex buffer by leaving offset of the postion
            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, false, sizeof(Vertex), (void *)(offsetof(Vertex, tex_coord)));

            // 4. normal Attribute
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);
            // How will we read bits inside the buffer ??
            // size:4 ➡ vec<4, glm::uint8, glm::defaultp> Color; (vec4)
            // type:GL_UNSIGNED_BYTE ➡ vec<4, glm::uint8, glm::defaultp> Color; (uint8)
            // normalized: true ==> uint8 =>0-255 so we need to make it normalized
            // stride: complete vertex
            // offset: skip position
            // Write normal attribute value to the vertex buffer by leaving offset of the postion
            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, false, sizeof(Vertex), (void *)(offsetof(Vertex, normal)));

            // Step(4) Create Element Buffer
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            // 2.Buffer Data To EBO
            // size= # of elements in the vector * size of each element
            // &elements[0] => reference for the first element in the vector
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), &elements[0], GL_STATIC_DRAW);

            // Unbind the Vertex array [Must]
            // To prevent Adding data from other meshes to this VAO we need to disconnect it :D
            glBindVertexArray(0);

            // Unbind Vertex buffer and element buffer[optional]
            // We think here it is optional because just binding a new buffer unbind previous one
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            // 10.Set Num of Elements to size of the vector
            elementCount = elements.size();
        }

        // this function should render the mesh
        void draw()
        {
            // TODO: (Req 2) Write this function
            // 1. Bind Vertex Array
            glBindVertexArray(VAO);

            // 2. Draw what is in the Element Buffer attached to this VAO :D
            //  Syntax: void glDrawElements(GLenum mode,GLsizei count,GLenum type,const void * indices);
            //  CHECK: count:  => # of the elements in elements vector
            // type: type of one element is unsigned int
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void *)0);

            // 3.Unbind the Vertex Array
            glBindVertexArray(0);
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