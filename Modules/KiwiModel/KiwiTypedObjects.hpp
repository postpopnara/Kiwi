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

#ifndef KIWI_MODEL_TYPED_OBJECTS_HPP_INCLUDED
#define KIWI_MODEL_TYPED_OBJECTS_HPP_INCLUDED

#include "KiwiObject.hpp"
#include "KiwiObjectFactory.hpp"

namespace kiwi
{
    namespace model
    {
        // ================================================================================ //
        //                                    OBJECT PLUS                                   //
        // ================================================================================ //
        
        class ObjectPlus : public model::Object
        {
        public:
            
            //! @brief flip Default Constructor
            ObjectPlus(flip::Default& d) : model::Object(d) {}
            
            //! @brief Constructor
            ObjectPlus(std::string const& name, std::vector<Atom> const& args);
            
            //! @internal flip static declare method
            static void declare();
        };
        
        // ================================================================================ //
        //                                    OBJECT PRINT                                  //
        // ================================================================================ //
        
        class ObjectPrint : public model::Object
        {
        public:
            
            //! @brief flip Default Constructor
            ObjectPrint(flip::Default& d) : model::Object(d) {}
            
            //! @brief Constructor
            ObjectPrint(std::string const& name, std::vector<Atom> const& args);
            
            //! @internal flip static declare method
            static void declare();
        };
    }
}


#endif // KIWI_MODEL_TYPED_OBJECTS_HPP_INCLUDED
