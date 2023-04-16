#pragma once

#include "component.hpp"
#include "transform.hpp"
#include <list>
#include <iterator>
#include <string>
#include <glm/glm.hpp>


namespace our
{

    class World; // A forward declaration of the World Class

    class Entity
    {
        World *world;                      // This defines what world own this entity
        std::list<Component *> components; // A list of components that are owned by this entity

        friend World;       // The world is a friend since it is the only class that is allowed to instantiate an entity
        Entity() = default; // The entity constructor is private since only the world is allowed to instantiate an entity [=default  Defaulted default constructor: the compiler will define the implicit default constructor even if other constructors are present]
    public:
        std::string name;         // The name of the entity. It could be useful to refer to an entity by its name
        Entity *parent;           // The parent of the entity. The transform of the entity is relative to its parent.
                                  // If parent is null, the entity is a root entity (has no parent).
        Transform localTransform; // The transform of this entity relative to its parent.

        World *getWorld() const { return world; } // Returns the world to which this entity belongs

        glm::mat4 getLocalToWorldMatrix() const;  // Computes and returns the transformation from the entities local space to the world space
        void deserialize(const nlohmann::json &); // Deserializes the entity data and components from a json object

        // This template method create a component of type T,
        // adds it to the components map and returns a pointer to it
        template <typename T>
        T *addComponent()
        {
            // Note: Just An Asset thrown if T isn't a child of class Component :D
            static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
            // TODO: (Req 8) Create an component of type T, set its "owner" to be this entity, then push it into the component's list
            // CHECK: @BasmaElhoseny01 Type T
            T *newComponent = new T();
            newComponent->owner = this;
            components.push_back(newComponent);

            // Don't forget to return a pointer to the new component
            return newComponent;
        }

        //This template method searches for a component of type T and returns a pointer to it
        //If no component of type T was found, it returns a nullptr
        template <typename T>
        T *getComponent()
        {
            // TODO: (Req 8) Go through the components list and find the first component that can be dynamically cast to "T*".
            //  for(int i=0;i<components.size();i++){
            //  T* casted_component=dynamic_cast<T*>(components[i]);
            for (auto it = components.begin(); it != components.end(); it++)
            {
                // Dynamic Casting [Down Casting from Component* to T*]
                T *casted_component = dynamic_cast<T *>(*it);
                if (casted_component != nullptr)
                    return casted_component;
            }
            // Return the component you found, or return null of nothing was found.
            // No Component with type T is found
            return nullptr;
        }
        // This template method seacrhes for a component of type T and returns a pointer to it
        // If no component of type T was found, it returns a nullptr 
        // template<typename T>
        // T* getComponent(){
        //     //TODO: (Req 8) Go through the components list and find the first component that can be dynamically cast to "T*".
        //     // Return the component you found, or return null of nothing was found.
        //     for(auto& component : components){
        //     T* ptr = dynamic_cast<T*>(component);
        //     if(ptr) {
        //         return ptr;
        //     }
        // }
        // return nullptr;
        // }

        // Note: By index
        //  This template method dynamic and returns a pointer to it
        //  If no component of type T was found, it returns a nullptr
        template <typename T>
        T *getComponent(size_t index)
        {
            auto it = components.begin();
            std::advance(it, index);
            if (it != components.end())
                return dynamic_cast<T *>(*it);
            return nullptr;
        }

        // This template method searches for a component of type T and deletes it
        template <typename T>
        void deleteComponent()
        {
            // TODO: (Req 8) Go through the components list and find the first component that can be dynamically cast to "T*".
            T *component = this->getComponent<T>();
            // If found, delete the found component and remove it from the components list
            if (component)
            {
                this->deleteComponent<T>(component);
            }
        }

        // This template method searches for a component of type T and deletes it
        void deleteComponent(size_t index)
        {
            auto it = components.begin();
            std::advance(it, index);
            if (it != components.end())
            {
                delete *it;
                components.erase(it);
            }
        }

        // This template method searches for the given component and deletes it
        template <typename T>
        void deleteComponent(T const *component)
        {
            // TODO: (Req 8) Go through the components list and find the given component "component".
            for (auto it = components.begin(); it != components.end(); it++)
            {
                // If found, delete the found component and remove it from the components list
                if (component == *it)
                {
                    delete *it;           // T Destructor is called
                    components.erase(it); // Erase Postion pointed to by the iterator it
                    return;
                }
            }
        }

        // Since the entity owns its components, they should be deleted alongside the entity
        ~Entity()
        {
            // TODO: (Req 8) Delete all the components in "components".
            for (auto it = components.begin(); it != components.end(); it++)
            {
                delete *it;
            }
            // CHECK: NO need to clear because we are already in teh destructor components will be destructed now :D
            //  //Clear list :D
            //  components.clear();
        }

        // Entities should not be copyable
        Entity(const Entity &) = delete;
        Entity &operator=(Entity const &) = delete;
    };

}