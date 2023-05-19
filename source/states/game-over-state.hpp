#pragma once

#include <application.hpp>
#include <iostream>
#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <asset-loader.hpp>
#include <irrKlang/irrKlang.h>
#include <systems/game-over-controller.hpp>

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
// This state shows how to use the ECS framework and deserialization.
class GameOver : public our::State
{

    our::World world;
    our::ForwardRenderer renderer;
    ISoundEngine *engine;
    our::GameOverSystem gameOver;
    void onInitialize() override
    {
        std::string config_path = "config/game-over.jsonc";

        // Open the config file and exit if failed
        std::ifstream file_in(config_path);
        if (!file_in)
        {
            std::cerr << "Couldn't open file: " << config_path << std::endl;
            return;
        }

        // Read the file into a json object then close the file
        nlohmann::json fileConfigs = nlohmann::json::parse(file_in, nullptr, true, true);
        file_in.close();

        // First of all, we get the scene configuration from the app config
        auto &config = fileConfigs["scene"];

        // If we have assets in the scene config, we deserialize them
        if (config.contains("assets"))
        {
            our::deserializeAllAssets(config["assets"]);
        }
        // If we have a world in the scene config, we use it to populate our world
        if (config.contains("world"))
        {
            world.deserialize(config["world"]);
        }
        gameOver.enter(getApp());
        // We initialize the mesh renderer controller system since it needs a pointer to the app
        // meshRendererController.enter(getApp());
        // Then we initialize the renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
         // start the sound engine with default parameters
         engine= createIrrKlangDevice();

        if (!engine)
            std::cout << "Could not startup engine" << std::endl;
        else
            engine->play2D("./media/ophelia.mp3", true);
     
    }

    void onDraw(double deltaTime) override
    {
        renderer.render(&world);
        gameOver.update();
        // auto& keyboard = getApp()->getKeyboard();
        // if(keyboard.justPressed(GLFW_KEY_ENTER)){
        //     // go to game
        //     getApp()->registerState<Playstate>("play");
        //     getApp()->changeState("play");
        // }
    }

    void onDestroy() override
    {
        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the meshRenderer controller system to make sure that the mouse is unlocked
        // meshRendererController.exit();
        // Clear the world
        world.clear();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
        engine->drop(); // delete engine
    }
     void onImmediateGui() override
    {
        // start gui
        ImGui::Begin("Enter", false, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
        // set window position
        ImGui::SetWindowPos(ImVec2(350, 530));
        // set window size
        ImGui::SetWindowSize(ImVec2(800, 100));
        // set font
        ImGui::SetWindowFontScale(3.0f);
        // initialize score
        string pressEnter= "Press Enter to play again... ";
        // initialize color
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), pressEnter.c_str());
        // end gui
        ImGui::End();
    }
};