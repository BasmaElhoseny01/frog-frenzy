#pragma once

#include <unordered_set>
#include "entity.hpp"
#include <iostream>
using namespace std;

namespace our
{

    // This class holds a set of entities
    class World
    {
        std::unordered_set<Entity *> entities;         // These are the entities held by this world
        std::unordered_set<Entity *> markedForRemoval; // These are the entities that are awaiting to be deleted
                                                       // when deleteMarkedEntities is called

        std::unordered_set<Entity *> hiddenEntities;  
        std::unordered_set<Entity *> markedToUnhide;  

    public:
        World() = default;

        // // For Debug inly Added by @BasmaElhoseny
        // const std::unordered_set<Entity *> &getmarkedForRemoval()
        // {
        //     return markedForRemoval;
        // }

        // This will deserialize a json array of entities and add the new entities to the current world
        // If parent pointer is not null, the new entities will be have their parent set to that given pointer
        // If any of the entities has children, this function will be called recursively for these children
        void deserialize(const nlohmann::json &data, Entity *parent = nullptr);

        // This adds an entity to the entities set and returns a pointer to that entity
        // WARNING The entity is owned by this world so don't use "delete" to delete it, instead, call "markForRemoval"
        // to put it in the "markedForRemoval" set. The elements in the "markedForRemoval" set will be removed and
        // deleted when "deleteMarkedEntities" is called.
        Entity *add()
        {
            // TODO: (Req 8) Create a new entity, set its world member variable to this,
            Entity *newEntity = new Entity();
            newEntity->world = this; // set Entity's world to be this world :D
            // and don't forget to insert it in the suitable container.
            entities.insert(newEntity); // Add new Entity to the list of entities of this competent
            return newEntity;
        }

        // This returns and immutable reference to the set of all entities in the world.
        const std::unordered_set<Entity *> &getEntities()
        {
            return entities;
        }

        // This returns and immutable reference to the set of all Hidden entities in the world.
        const std::unordered_set<Entity *> &getHiddenEntities()
        {
            return hiddenEntities;
        }

        // This marks an entity for removal by adding it to the "markedForRemoval" set.
        // The elements in the "markedForRemoval" set will be removed and deleted when "deleteMarkedEntities" is called.
        void markForRemoval(Entity *entity)
        {
            // TODO: (Req 8) If the entity is in this world, add it to the "markedForRemoval" set.
            if (entity->world == this)
            {
                // if entity belongs to this world Add it to the list of Entities that will be removed later
                markedForRemoval.insert(entity);
            }
        }

        // This removes the elements in "markedForRemoval" from the "entities" set.
        // Then each of these elements are deleted.
        void deleteMarkedEntities()
        {
            //cout << "Entereddelete MarkedEntities " << endl;
            // TODO: (Req 8) Remove and delete all the entities that have been marked for removal
            // CHECK: DIFFERGNEC
            // for (auto it = markedForRemoval.begin(); it != markedForRemoval.end(); it++)
            for (auto entity : markedForRemoval)
            {
                //cout << "1";
                // Note: the erase members shall invalidate only iterators and references to the erased elements.So Order here matters
                // Delete the Entity
                // delete *it; // delete pointer just *it =nullptr
                delete entity;

                // Remove from the entities list
                entities.erase(entity);
            }
            markedForRemoval.clear();
        }

        // This marks an entity for hiding by adding it to the "hiddenEntities" set.
        // The elements in the "hiddenEntities" set will be removed from world when "hideMarkedEntities" is called.
        void markToHide(Entity *entity)
        {
            // TODO: (Req 8) If the entity is in this world, add it to the "hiddenEntities" set.
            if (entity->world == this)
            {
                // if entity belongs to this world Add it to the list of Entities that will be removed later
                hiddenEntities.insert(entity);
            }
        }


        // This removes the elements in "markedForRemoval" from the "entities" set.
        // Then each of these elements are deleted.
        void hideMarkedEntities()
        {
          
            // TODO: (Req 8) Remove and delete all the entities that have been marked for removal
            for (auto entity : hiddenEntities)
            {
                // Remove from the entities list
                entities.erase(entity);
            }
        }

         // This marks an entity for hiding by adding it to the "hiddenEntities" set.
        // The elements in the "hiddenEntities" set will be removed from world when "hideMarkedEntities" is called.
        void markToUnhide(Entity *entity)
        {
            // TODO: (Req 8) If the entity is in this world, add it to the "hiddenEntities" set.
            if (entity->world == this)
            {
                // Add Back to Entities List
                markedToUnhide.insert(entity);
            }
        }


        // This removes the elements in "markedForRemoval" from the "entities" set.
        // Then each of these elements are deleted.
        void unhideMarkedEntities()
        {
            // TODO: (Req 8) Remove and delete all the entities that have been marked for removal
            for (auto entity : markedToUnhide)
            {
                // Remove from the Hidden list
                hiddenEntities.erase(entity);

                //Back to World
                entities.insert(entity);

            }
            markedToUnhide.clear();
        }



        // This deletes all entities in the world
        void clear()
        {
            // TODO: (Req 8) Delete all the entities and make sure that the containers are empty
            for (auto it = entities.begin(); it != entities.end(); it++)
            {
                delete *it;
            }

            // Empty entities and markedForRemoval sets
            entities.clear();
            markedForRemoval.clear();
        }

        // Since the world owns all of its entities, they should be deleted alongside it.
        ~World()
        {
            clear();
        }

        // The world should not be copyable
        World(const World &) = delete;
        World &operator=(World const &) = delete;
    };

}