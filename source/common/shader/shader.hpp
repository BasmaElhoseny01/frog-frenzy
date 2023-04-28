#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our {

    class ShaderProgram {

    private:
        //Shader Program Handle (OpenGL object name)
        GLuint program;

    public:
        ShaderProgram(){
            //TODO: (Req 1) Create A shader program
            program = glCreateProgram(); // shader program
        }
        ~ShaderProgram(){
            //TODO: (Req 1) Delete a shader program
             glDeleteProgram(program); // Delete shader program
        }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use() { 
            glUseProgram(program);
        }

        GLuint getUniformLocation(const std::string &name) {
            //TODO: (Req 1) Return the location of the uniform with the given name
            return glGetUniformLocation(program, name.c_str()); // get location of the uniform with the given name
        }

        void set(const std::string &uniform, GLfloat value) {
            //TODO: (Req 1) Send the given float value to the given uniform
            GLuint location = getUniformLocation(uniform);//get location of the uniform
            glUniform1f(location, value); // set value
        }

        void set(const std::string &uniform, GLuint value) {
            //TODO: (Req 1) Send the given unsigned integer value to the given uniform
            GLuint location =  getUniformLocation(uniform);//get location of the uniform
            glUniform1ui(location, value);// set value
        }

        void set(const std::string &uniform, GLint value) {
            //TODO: (Req 1) Send the given integer value to the given uniform
            GLuint location =  getUniformLocation(uniform);//get location of the uniform
            glUniform1i(location, value);// set value
        }

        void set(const std::string &uniform, glm::vec2 value) {
            //TODO: (Req 1) Send the given 2D vector value to the given uniform
            GLuint location =  getUniformLocation(uniform);//get location of the uniform
            glUniform2fv(location, 1,&value[0]);// set value
        }

        void set(const std::string &uniform, glm::vec3 value) {
            //TODO: (Req 1) Send the given 3D vector value to the given uniform
            GLuint location =  getUniformLocation(uniform);//get location of the uniform
            glUniform3fv(location, 1,&value[0]);// set value
        }

        void set(const std::string &uniform, glm::vec4 value) {
            //TODO: (Req 1) Send the given 4D vector value to the given uniform
            GLuint location = getUniformLocation(uniform);//get location of the uniform
            glUniform4fv(location, 1,&value[0]);// set value

        }

        void set(const std::string &uniform, glm::mat4 matrix) {
            //TODO: (Req 1) Send the given matrix 4x4 value to the given uniform
            GLuint location = getUniformLocation(uniform);//get location of the uniform
            glUniformMatrix4fv(location, 1, false, &matrix[0][0]);// set value
        }

        //TODO: (Req 1) Delete the copy constructor and assignment operator.
        ShaderProgram (const  ShaderProgram &)  = delete;
        ShaderProgram &  operator=(const  ShaderProgram &)  = delete;
        //Question: Why do we delete the copy constructor and assignment operator?
            // Because in this case two program point to the same value 
            // when delete the first one the second will point to null


    };

}

#endif