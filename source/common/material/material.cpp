#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

namespace our {

    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const {
        //TODO: (Req 7) Write this function
        pipelineState.setup(); // setup the pipeline
        shader->use(); // set the shader to be used
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;

        if(data.contains("pipelineState")){
            pipelineState.deserialize(data["pipelineState"]);
        }
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint 
    void TintedMaterial::setup() const {
        //TODO: (Req 7) Write this function
        Material::setup();// setup of its parent
        shader->set("tint" , tint);// set tint value
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json& data){
        Material::deserialize(data);
        if(!data.is_object()) return;
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex" 
    void TexturedMaterial::setup() const {
        //TODO: (Req 7) Write this function
        TintedMaterial::setup();// setup of its parent
        shader->set("alphaThreshold" , alphaThreshold);// set alphaThreshold value
        glActiveTexture(GL_TEXTURE0);//selects which texture unit subsequent texture state calls will affect
        texture->bind();// bind texture
        sampler->bind(0);// bind sampler by giving it textureUnit 0
        shader->set("tex", 0);// set tex value
    }

    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json& data){
        TintedMaterial::deserialize(data);
        if(!data.is_object()) return;
        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }


    void LightingMaterial::setup() const {
        Material::setup();// setup of its parent
        //TODO: (Req 7) Write this function
        if(albedo != nullptr) {
            glActiveTexture(GL_TEXTURE0);//selects which texture unit subsequent texture state calls will affect
            albedo->bind();// bind texture
            sampler->bind(0);// bind sampler by giving it textureUnit 0
            shader->set("material.albedo", 0);
        }
        if(specular != nullptr) {
            glActiveTexture(GL_TEXTURE1);//selects which texture unit subsequent texture state calls will affect
            specular->bind();// bind texture
            sampler->bind(1);// bind sampler by giving it textureUnit 0
            shader->set("material.specular", 1);
        }
        if(roughness != nullptr) {
            glActiveTexture(GL_TEXTURE2);//selects which texture unit subsequent texture state calls will affect
            roughness->bind();// bind texture
            sampler->bind(2);// bind sampler by giving it textureUnit 0
            shader->set("material.roughness", 2);
        }
        if(ambient_occlusion != nullptr) {
            glActiveTexture(GL_TEXTURE3);//selects which texture unit subsequent texture state calls will affect
            ambient_occlusion->bind();// bind texture
            sampler->bind(3);// bind sampler by giving it textureUnit 0
            shader->set("material.ambient_occlusion", 3);
        }
        if(emissive != nullptr) {
            glActiveTexture(GL_TEXTURE4);//selects which texture unit subsequent texture state calls will affect
            emissive->bind();// bind texture
            sampler->bind(4);// bind sampler by giving it textureUnit 0
            shader->set("material.emissive", 4);
        }
        // shader->set("tex", 0);// set tex value
    }

    // This function read the material data from a json object
    void LightingMaterial::deserialize(const nlohmann::json& data){
        Material::deserialize(data);
        if(!data.is_object()) return;
        albedo = AssetLoader<Texture2D>::get(data.value("albedo", ""));
        specular = AssetLoader<Texture2D>::get(data.value("specular", ""));
        roughness = AssetLoader<Texture2D>::get(data.value("roughness", ""));
        ambient_occlusion = AssetLoader<Texture2D>::get(data.value("ambient_occlusion", ""));
        emissive = AssetLoader<Texture2D>::get(data.value("emissive", ""));
        
    }

}