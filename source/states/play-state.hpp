#pragma once
#include <string>
#include <application.hpp>
#include <iostream>
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
#include <systems/gain-heart.hpp>

#include <iostream>
using namespace std;

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

// This state shows how to use the ECS framework and deserialization.
class Playstate : public our::State
{
    int score;                                        // score of player
    int bestScore;                                    // best score of player in the game
    our::World world;                                 // to get the world of game
    our::ForwardRenderer renderer;                    // render component
    our::FreeCameraControllerSystem cameraController; //  camera control system
    our::FreeFrogControllerSystem frogController;     // frag control system
    our::MovementSystem movementSystem;               // movement system
    our::GroundSystem groundSystem;                   // ground system
    our::CarsSystem carsSystem;                       // car system
    our::CollisionSystem collisionSystem;             // collision system
    our::GainHeartSystem gainHeartSystem;             // gain herat system
    ISoundEngine *engine;                             // engine to play sounds
    bool flagPostProcessing;                          // bool to Apply Post Processing Before GameOver (if he lost 3 hearts)
    int id;                                           // id of heart to know which heart remove or back it
    void onInitialize() override
    {
        // Step(1) Scene from Json
        std::string config_path = "config/app.jsonc";

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
        // Initializations
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        // We initialize the frog controller system since it needs a pointer to the app
        frogController.enter(getApp());
        // We initialize the collision  system since it needs a pointer to the app
        collisionSystem.enter(getApp());

        // Then we initialize the renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);

        score = 0;                              // reset score of player
        flagPostProcessing = false;             // reset flag bool of PostProcessing
        renderer.setApplyPostProcessing(false); // stop applying the post processing
        id = 0;                                 // start hearts counts from zero

        // Step(2) Best Score
        std::string Score_path = "config/score.jsonc";

        // Open the config file and exit if failed
        std::ifstream file_score(Score_path);
        if (!file_in)
        {
            std::cerr << "Couldn't open file: " << Score_path << std::endl;
            return;
        }

        // Read the file into a json object then close the file
        nlohmann::json configsScore = nlohmann::json::parse(file_score, nullptr, true, true);
        file_score.close();
        // read best score
        bestScore = configsScore["bestScore"];

        // Step (3) Start Music
        //  Initialize the sound engine with default parameters
        engine = createIrrKlangDevice();
        if (!engine)
            std::cout << "Could not startup engine" << std::endl;
        else
            engine->play2D("./media/play.mp3", true); // Play Music
    }

    void onDraw(double deltaTime) override
    {
        collisionSystem.checkGameOver(flagPostProcessing); // To check game over
        groundSystem.update(&world, score);                // To rerender street, grass,lakes, lamps and hearts to the forward space

        // Here, we just run a bunch of systems to control the world logic
        carsSystem.update(&world);                                                 // To control Cars System to appear
        movementSystem.update(&world, (float)deltaTime, flagPostProcessing);       // To update movement component
        frogController.update(&world, (float)deltaTime, flagPostProcessing);       // To control frog movement
        collisionSystem.update(&world, &renderer, flagPostProcessing, engine, id); // To check collision
        gainHeartSystem.update(&world, id);                                        // To check Gaining new Heart
        // cameraController.update(&world, (float)deltaTime);

        // Remove Marked for removal Entities[Basma] so that they aren't rendered again
        world.deleteMarkedEntities();

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
        // Open Score File to save the new score if it is better than the previous best score
        std::string config_path = "config/score.jsonc";

        // Open the config file and exit if failed
        std::ofstream file_out(config_path);
        if (!file_out)
        {
            std::cerr << "Couldn't open file: " << config_path << std::endl;
            return;
        }
        // // read file
        // nlohmann::json json = nlohmann::json::parse(file_out, nullptr, true, true);;

        // mutate the json
        nlohmann::json data;
        data["score"] = score;
        // check id the score are bigger than best score
        data["bestScore"] = (score > bestScore) ? score : bestScore;
        // write the JSON object to the file
        file_out << data;

        // close the file
        file_out.close();

        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        // Clear the world
        world.clear();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
        engine->drop(); // delete sound engine
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
        string score_screen = "Score: " + to_string(score);
        // initialize color
        ImGui::TextColored(ImVec4(0.957f, 0.352f, 0.0f, 1.0f), score_screen.c_str());
        // end gui
        ImGui::End();
    }
};