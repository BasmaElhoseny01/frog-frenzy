#pragma once
#include <string>
#include <application.hpp>
#include<iostream>
#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/free-frog-controller.hpp>
#include <systems/movement.hpp>
#include <systems/collision.hpp>
#include <systems/car.hpp>
#include <systems/ground.hpp>
#include <asset-loader.hpp>
#include <irrKlang/irrKlang.h>
using namespace irrklang;



#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

// This state shows how to use the ECS framework and deserialization.
class Playstate : public our::State
{
    int score;
    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::FreeFrogControllerSystem frogController;
    our::MovementSystem movementSystem;
    our::CarsSystem carsSystem;
    our::GroundSystem groundSystem;
    our::CollisionSystem collisionSystem;
    ISoundEngine *engine;

    void onInitialize() override
    {
        // First of all, we get the scene configuration from the app config
        auto &config = getApp()->getConfig()["scene"];
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
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        // We initialize the frog controller system since it needs a pointer to the app
        frogController.enter(getApp());
        // We initialize the collision  system since it needs a pointer to the app
        collisionSystem.enter(getApp());
        // Then we initialize the renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
        // start the sound engine with default parameters
         engine= createIrrKlangDevice();

        if (!engine)
            std::cout << "Could not startup engine" << std::endl;
        else
            engine->play2D("./media/getout.ogg", true);
        score = 0;// reset score of player
    }

    void onDraw(double deltaTime) override
    {
        groundSystem.update(&world, score);// To rerender ground
        // Here, we just run a bunch of systems to control the world logic
        carsSystem.update(&world); // To control Cars System to appear
        collisionSystem.update(&world);// To check collision
        movementSystem.update(&world, (float)deltaTime); // To update movement component 
        cameraController.update(&world, (float)deltaTime);
        //frogController.update(&world, (float)deltaTime);// To control frog movement
        
        

        // Remove Marked for removal Entities[Basma] so that they aren't rendered again
        world.deleteMarkedEntities();
        // Hide and Unhide Marked Entities :D
        world.hideMarkedEntities();
        world.unhideMarkedEntities();


       
        // And finally we use the renderer system to draw the scene
        renderer.render(&world);

        // Get a reference to the keyboard object
        auto &keyboard = getApp()->getKeyboard();

        if (keyboard.justPressed(GLFW_KEY_ESCAPE))
        {
            // If the escape  key is pressed in this frame, go to the play state
            getApp()->changeState("menu");
        }
    }

    void onDestroy() override
    {
        
        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        // Clear the world
        world.clear();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
        engine->drop(); // delete engine
    }
    
    void onImmediateGui() override
    {
        // start gui
        ImGui::Begin("Score", false, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
        // set window position
        ImGui::SetWindowPos(ImVec2(50, 50));
        // set window size
        ImGui::SetWindowSize(ImVec2(600, 100));
        // set font
        ImGui::SetWindowFontScale(5.0f);
        // initialize score
        string score_screen= "Score: " + to_string(score);
        // initialize color
        ImGui::TextColored(ImVec4(0.957f, 0.352f, 0.0f, 1.0f), score_screen.c_str());
        // end gui
        ImGui::End();
    }

};