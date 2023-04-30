#pragma once

#include <glad/gl.h>
#include <glm/vec4.hpp>
#include <json/json.hpp>

namespace our {
    // There are some options in the render pipeline that we cannot control via shaders
    // such as blending, depth testing and so on
    // Since each material could require different options (e.g. transparent materials usually use blending),
    // we will encapsulate all these options into a single structure that will also be responsible for configuring OpenGL's pipeline
    struct PipelineState {
        // This set of pipeline options specifies whether face culling will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum culledFace = GL_BACK;
            GLenum frontFace = GL_CCW;
        } faceCulling;

        // This set of pipeline options specifies whether depth testing will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum function = GL_LEQUAL;
        } depthTesting;

        // This set of pipeline options specifies whether blending will be used or not and how it will be configured
        struct {
            bool enabled = false;
            GLenum equation = GL_FUNC_ADD;
            GLenum sourceFactor = GL_SRC_ALPHA;
            GLenum destinationFactor = GL_ONE_MINUS_SRC_ALPHA;
            glm::vec4 constantColor = {0, 0, 0, 0};
        } blending;

        // These options specify the color and depth mask which can be used to
        // prevent the rendering/clearing from modifying certain channels of certain targets in the framebuffer
        glm::bvec4 colorMask = {true, true, true, true}; // To know how to use it, check glColorMask
        bool depthMask = true; // To know how to use it, check glDepthMask


        // This function should set the OpenGL options to the values specified by this structure
        // For example, if faceCulling.enabled is true, you should call glEnable(GL_CULL_FACE), otherwise, you should call glDisable(GL_CULL_FACE)
        void setup() const {
            //TODO: (Req 4) Write this function
            glColorMask(colorMask[0],colorMask[1],colorMask[2],colorMask[3]);
            glDepthMask(depthMask);
            if(depthTesting.enabled){
                //to enable depth testing
                glEnable(GL_DEPTH_TEST); 
                if(depthMask)
                    glDepthMask(GL_TRUE);    // enable wirting un depth buffer
                else 
                    glDepthMask(GL_FALSE);   // disabled writing in depth buffer
                //update depth depending on the depth function ( GL_LEQUAL => if the fragment's depth value is less than the stored depth value ).
                glDepthFunc(depthTesting.function);  
            }
             else
            {
                //disable the depth test 
                glDisable(GL_DEPTH_TEST);
            }

            if(faceCulling.enabled){
                //to enable face culling 
                glEnable(GL_CULL_FACE);  
                //to cull front faces or the back faces (GL_BACK => to cull back faces not the front faces)
                glCullFace(faceCulling.culledFace);  
                //set how a face is determined to be afront face in opengl 
                glFrontFace(faceCulling.frontFace);  
            }
            else
            {
                //to disable cull face
                glDisable(GL_CULL_FACE);
            }

            if(blending.enabled){
                // to enable blending.
                glEnable(GL_BLEND);  
                // set the option for the source and destination factor.
                glBlendFunc(blending.sourceFactor, blending.destinationFactor);  
                // set the blinding equation 
                glBlendEquation(blending.equation);
                 (blending.constantColor[0],blending.constantColor[1],blending.constantColor[2],blending.constantColor[3]);
            }
            else
            {
                // to disable blinding
                glDisable(GL_BLEND);
            }

        }

        // Given a json object, this function deserializes a PipelineState structure
        void deserialize(const nlohmann::json& data);
    };

}