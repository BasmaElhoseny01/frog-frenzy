#pragma once

#include <application.hpp>
#include <iostream>
#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <asset-loader.hpp>
#include <irrKlang/irrKlang.h>
#include <systems/main-menu-controller.hpp>

class MainMenu : public our::State
{
    our::World world;
    our::ForwardRenderer renderer;
    our::MainMenuSystem mainMenu;
    ISoundEngine *engine;


    void onInitialize() override
    {
        // Read configuration from the file
        std::string config_path = "config/main-menu.jsonc";

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

        // Start the main menu State
        mainMenu.enter(getApp());

        // initialize renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);

        // start the sound engine with default parameters
        engine = createIrrKlangDevice();

        if (!engine)
            std::cout << "Could not startup engine" << std::endl;
        else
            engine->play2D("./media/getout.ogg", true);
    }

    void onDraw(double deltaTime) override
    {
        renderer.render(&world);
        mainMenu.update();
    }

    void onDestroy() override
    {
        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the meshRenderer controller system to make sure that the mouse is unlocked
        // meshRendererController.exit();
        // Clear the world
        world.clear();
        
        engine->drop(); // delete engine
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
    }

    void onImmediateGui() override
    {
        // start gui
        ImGui::Begin("Enter", false, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
        // set window position
        ImGui::SetWindowPos(ImVec2(400, 600));
        // set window size
        ImGui::SetWindowSize(ImVec2(800, 100));
        // set font
        ImGui::SetWindowFontScale(3.0f);
        // Start Game Text
        string pressEnter = "Press Space to start";
        // initialize color
        ImGui::TextColored(ImVec4(0.957f, 0.352f, 0.0f, 1.0f), pressEnter.c_str());

        // Exit Game Text
        string pressEscape = "Press Escape to Exit";
        // initialize color
        ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), pressEscape.c_str());
        // end gui
        ImGui::End();
    }
};