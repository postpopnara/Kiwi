/*
 ==============================================================================
 
 This file is part of the KIWI library.
 Copyright (c) 2014 Pierre Guillot & Eliott Paris.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 KIWI is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses KIWI, contact : guillotpierre6@gmail.com
 
 ==============================================================================
 */

#ifndef KIWI_MODEL_PATCHER_HPP_INCLUDED
#define KIWI_MODEL_PATCHER_HPP_INCLUDED

#include "KiwiLink.hpp"
#include "KiwiTypedObjects.hpp"

namespace kiwi
{
    namespace model
    {
        // ================================================================================ //
        //                                      PATCHER                                     //
        // ================================================================================ //
        
        //! @brief The Patcher manages a set of Object and Link
        class Patcher : public flip::Object
        {
        public:
            
            class User;
            class View;
            
            using object_array_t = flip::Array<model::Object>;
            using link_array_t = flip::Array<model::Link>;
            
            //! @brief Default constructor.
            Patcher();
            
            //! @brief Destructor.
            ~Patcher();
            
            //! @brief Try to create an Object with a text.
            //! @details This function will first parse the input string in a vector of atom
            //! to find a registered name object as first atom.
            //! the last atoms are passed to the created object as arguments.
            //! @param text A string composed by the name of the object optionnally followed by a space and a list of argument values (ex : "plus 42")
            //! @return A reference
            model::Object& addObject(std::string const& text);
            
            //! @brief Constructs and add a Link to the Patcher.
            //! @details Constructs a Link with given origin and destination Object
            //! and IO indexes then adds it in the Patcher.
            //! @param from     The origin Object.
            //! @param outlet   The origin outlet index.
            //! @param to       The destination Object.
            //! @param inlet    The destination inlet index.
            void addLink(model::Object const& from,
                         const uint32_t outlet,
                         model::Object const& to,
                         const uint32_t inlet);
            
            //! @brief Removes an object from the Patcher.
            //! @details This will also remove all links connected to this object.
            //! @param object The Object to remove.
            void removeObject(model::Object const& object);
            
            //! @brief Removes a link from the Patcher.
            //! @param link The Link to remove.
            void removeLink(model::Link const& link);
            
            //! @brief Returns true if an Object has been added, removed or changed.
            inline bool objectsChanged() const noexcept { return m_objects.changed(); }
            
            //! @brief Returns true if a Link has been added, removed or changed.
            inline bool linksChanged() const noexcept   { return m_links.changed(); }
            
            //! @brief Returns true if a User has been added, removed or changed.
            inline bool usersChanged() const noexcept { return m_users.changed(); }
            
            //! @brief Set the User.
            //! @param user_id The user unique id.
            //! @return The user.
            User& createUserIfNotAlreadyThere(uint32_t user_id);
            
            //! @brief Get a User by id.
            //! @param user_id The user unique id.
            //! @return The User pointer if found or nullptr.
            User* getUser(uint32_t user_id);
            
            //! @brief Get the first Object.
            object_array_t::const_iterator getFirstObject() const noexcept  { return m_objects.cbegin(); }
            
            //! @brief Get the first Object.
            object_array_t::iterator getFirstObject() noexcept              { return m_objects.begin(); }
            
            //! @brief Get the last Object.
            object_array_t::const_iterator getLastObject() const noexcept   { return m_objects.cend(); }
            
            //! @brief Get the last Object.
            object_array_t::iterator getLastObject() noexcept               { return m_objects.end(); }
            
            //! @brief Get the first Link.
            link_array_t::const_iterator getFirstLink() const noexcept      { return m_links.cbegin(); }
            
            //! @brief Get the first Link.
            link_array_t::iterator getFirstLink() noexcept                  { return m_links.begin(); }
            
            //! @brief Get the last Link.
            link_array_t::const_iterator getLastLink() const noexcept       { return m_links.cend(); }
            
            //! @brief Get the last Link.
            link_array_t::iterator getLastLink() noexcept                   { return m_links.end(); }
            
            //! @brief Get the objects.
            flip::Array<model::Object> const& getObjects() const noexcept   { return m_objects; }
            
            //! @brief Get the links.
            flip::Array<model::Link> const& getLinks() const noexcept       { return m_links; }
            
            //! @internal flip static declare method
            static void declare();
            
        private:
            
            bool canConnect(model::Object const& from, const uint32_t outlet,
                            model::Object const& to, const uint32_t inlet) const;
            
            object_array_t::const_iterator findObject(model::Object const& object) const;
            object_array_t::iterator findObject(model::Object const& object);
            
            link_array_t::const_iterator findLink(model::Link const& object) const;
            link_array_t::iterator findLink(model::Link const& object);
            
        private:
            
            //! objects and links are stored in a flip::Array to maintain a graphical z-order.
            flip::Array<model::Object>  m_objects;
            flip::Array<model::Link>    m_links;
            
            flip::Collection<User>      m_users;
        };
        
        
        // ================================================================================ //
        //                                   PATCHER VIEW                                   //
        // ================================================================================ //
        
        class Patcher::View : public flip::Object
        {
        public:
            
            View() = default;
            ~View() = default;
            
        public:
            
            struct Object : public flip::Object
            {
                Object() = default;
                Object(model::Object& object) : m_ref(&object) {}
                flip::ObjectRef<model::Object> m_ref;
            };
            
            struct Link : public flip::Object
            {
                Link() = default;
                Link(model::Link& link) : m_ref(&link) {}
                flip::ObjectRef<model::Link> m_ref;
            };
            
            // ================================================================================ //
            //                                   SELECTION                                      //
            // ================================================================================ //
            
            class Selection : public flip::Object
            {
            public:
                
                //! @brief Default constructor.
                Selection() = default;
                
                //! @brief Destructor.
                ~Selection()
                {
                    m_links.clear();
                    m_objects.clear();
                }
                
                std::vector<model::Object*> getObjects();
                std::vector<model::Link*> getLinks();
                bool isSelected(model::Object const& object);
                bool isSelected(model::Link const& link);
                
            private:
                flip::Collection<View::Object>  m_objects;
                flip::Collection<View::Link>    m_links;
                friend Patcher::View;
            };
            
        public:
            
            Patcher& getPatcher() { return parent<Patcher>(); }
            
            void unSelectAll();
            
            void selectAll();
            
            static void declare();
            
        private:

            Selection m_selection;
        };
        
        // ================================================================================ //
        //                                 PATCHER CLIENT                                   //
        // ================================================================================ //
        
        class Patcher::User : public flip::Object
        {
        public:
            
            User() = default;
            
            User(uint32_t user_id) : m_user_id(user_id) {}
            
            ~User() = default;
            
            //! @brief Add a new View.
            View& addView();
            
            //! @brief Remove a View.
            void removeView(View const& view);
            
            //! @brief Get the User id
            uint32_t getId() const;
            
        private:
            
            flip::Int                       m_user_id;
            flip::Collection<Patcher::View> m_views;
            
            friend Patcher;
        };
    }
}


#endif // KIWI_MODEL_PATCHER_HPP_INCLUDED
