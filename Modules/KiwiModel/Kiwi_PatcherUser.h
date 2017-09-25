/*
 ==============================================================================
 
 This file is part of the KIWI library.
 - Copyright (c) 2014-2016, Pierre Guillot & Eliott Paris.
 - Copyright (c) 2016-2017, CICM, ANR MUSICOLL, Eliott Paris, Pierre Guillot, Jean Millot.
 
 Permission is granted to use this software under the terms of the GPL v3
 (or any later version). Details can be found at: www.gnu.org/licenses
 
 KIWI is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 Contact : cicm.mshparisnord@gmail.com
 
 ==============================================================================
 */

#pragma once

#include <KiwiModel/Kiwi_ObjectBase.h>
#include <KiwiModel/Kiwi_PatcherView.h>

#include "flip/Collection.h"

namespace kiwi { namespace model {
    
    class Patcher;
    
    // ================================================================================ //
    //                               PATCHER USER MODEL                                 //
    // ================================================================================ //
    
    //! @brief Represents and stores informations about a user of a patcher document.
    class PatcherUser : public ObjectBase
    {
    public: // methods
        
        using Views = flip::Collection<PatcherView>;
        
        //! @brief Constructor.
        PatcherUser() = default;
        
        //! @brief Destructor.
        ~PatcherUser() = default;
        
        //! @brief Add a new View.
        PatcherView& addView();
        
        //! @brief Remove a View.
        Views::iterator removeView(PatcherView const& view);
        
        //! @brief Get views.
        Views& getViews() noexcept;
        
        //! @brief Get views.
        Views const& getViews() const noexcept;
        
        //! @brief Get the number of active views.
        size_t getNumberOfViews() const noexcept;
        
        //! @brief Get the User id
        uint64_t getId() const;
        
    public: // internal methods
        
        //! @brief flip class declaration
        template<class TDataModel>
        static void declare();
        
    private: // members
        
        Views m_views;
        
        friend Patcher;
    };
    
}}

#include <KiwiModel/Kiwi_PatcherUser.hpp>
