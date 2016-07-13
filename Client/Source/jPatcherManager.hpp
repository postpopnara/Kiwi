/*
 ==============================================================================
 
 This file is part of the KIWI library.
 - Copyright (c) 2014-2016, Pierre Guillot & Eliott Paris.
 - Copyright (c) 2016, CICM, ANR MUSICOLL, Eliott Paris, Pierre Guillot, Jean Millot.
 
 Permission is granted to use this software under the terms of the GPL v2
 (or any later version). Details can be found at: www.gnu.org/licenses
 
 KIWI is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 Contact : cicm.mshparisnord@gmail.com
 
 ==============================================================================
 */

#ifndef KIWI_JPATCHER_MANAGER_HPP_INCLUDED
#define KIWI_JPATCHER_MANAGER_HPP_INCLUDED

#include "flip/Document.h"

#include <KiwiModel/KiwiModelPatcher.hpp>
#include <KiwiEngine/KiwiEngineInstance.hpp>

#include "jWindow.hpp"
#include "jPatcher.hpp"

namespace kiwi
{
    class Instance;
    
    // ================================================================================ //
    //                                  JPATCHER WINDOW                                 //
    // ================================================================================ //
    
    class jPatcherWindow : public jWindow
    {
    public:
        jPatcherWindow(jPatcherManager& manager, jPatcher& jpatcher);
        void closeButtonPressed() override;
        
        //! @brief returns the patcher manager.
        jPatcherManager& getManager() const;
        
        //! @brief returns the jPatcher.
        jPatcher& getjPatcher() const;
        
    private:
        jPatcherManager& m_manager;
        jPatcher& m_jpatcher;
    };
    
    // ================================================================================ //
    //                                  JPATCHER MANAGER                                //
    // ================================================================================ //
    
    //! @brief The main DocumentObserver.
    //! @details The Instance dispatch changes to all other DocumentObserver objects
    class jPatcherManager : public flip::DocumentObserver<model::Patcher>
    {
    public:
        
        //! @brief Constructor.
        jPatcherManager(Instance& instance);
        
        //! @brief Constructs and load patcher from file
        jPatcherManager(Instance& instance, juce::File const& file);

        //! @brief Construct and connect to remote server
        jPatcherManager(Instance & instance, const std::string host, uint16_t port);
        
        //! @brief Destructor.
        ~jPatcherManager();
        
        //! @brief Returns the Patcher model
        model::Patcher& getPatcher();
        
        //! @brief Returns the Patcher model
        model::Patcher const& getPatcher() const;
        
        //! @brief Initialize the patcher manager by creating a new document.
        //! @return The newly created the Patcher model.
        model::Patcher& init();
        
        //! @brief Returns the number of patcher views.
        size_t getNumberOfView();
        
        //! @brief create a new patcher view window.
        void newView();
        
        //! @brief Force all windows to close without asking user to save document.
        void forceCloseAllWindows();
        
        //! @brief Attempt to close all document windows, after asking user to save them if needed.
        //! @return True if all document have been closed, false if the user cancel the action.
        bool askAllWindowsToClose();
        
        //! @brief Close the window that contains a given jpatcher.
        //! @details if it's the last patcher view, it will ask the user the save the document before closing
        bool closePatcherViewWindow(jPatcher& jpatcher);
        
        //! @brief Save the document.
        bool saveDocument();
        
        //! @brief Returns true if the patcher needs to be saved.
        bool needsSaving() const;
        
    private:
        
        //! @internal flip::DocumentObserver<model::Patcher>::document_changed
        void document_changed(model::Patcher& patcher) override final;
        
        //! @internal Notify and create jPatchers.
        void notifyPatcherViews(model::Patcher& patcher);
        
        //! @internal React to the fact that a View has just been added to the document.
        //! @details create a jPatcherWindow.
        void createPatcherWindow(model::Patcher& patcher,
                                 model::Patcher::User& user,
                                 model::Patcher::View& view);
        
        //! @internal View is resident and internal value changed.
        void notifyPatcherView(model::Patcher& patcher,
                               model::Patcher::User& user,
                               model::Patcher::View& view);
        
        //! @internal Vser will be removed from the document.
        void removePatcherWindow(model::Patcher& patcher,
                                 model::Patcher::User& user,
                                 model::Patcher::View& view);
        
        //! @internal Save document if needed and if user agrees.
        juce::FileBasedDocument::SaveResult saveIfNeededAndUserAgrees();

    private: // members
        
        Instance&       m_instance;
        flip::Document  m_document;
        bool            m_need_saving_flag;
        bool            m_is_remote;
    };
}

#endif // KIWI_JPATCHER_MANAGER_HPP_INCLUDED
