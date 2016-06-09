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

#ifndef KIWI_JOBJECT_HPP_INCLUDED
#define KIWI_JOBJECT_HPP_INCLUDED

#include <KiwiModel/KiwiPatcher.hpp>

#include "../JuceLibraryCode/JuceHeader.h"

namespace kiwi
{
    class HitTester;
    class jPatcher;
    class jClassicBox;
    
    // ================================================================================ //
    //                                      JOBJECT                                     //
    // ================================================================================ //
    
    //! @brief The juce object Component.
    class jObject : public juce::Component
    {
    public:
        
        jObject(jPatcher& patcher_view, model::Object& object_m);
        ~jObject();
        
        void objectChanged(model::Patcher::View& view, model::Object& object);
        void localSelectionChanged(bool selected_for_view);
        void distantSelectionChanged(std::set<uint64_t> distant_user_id_selection);
        void lockStatusChanged(bool locked);
        void patcherViewOriginPositionChanged();
        
        // juce::Component
        void paint(juce::Graphics& g) override;
        void mouseDown(juce::MouseEvent const& event) override;
        void mouseDrag(juce::MouseEvent const& event) override;
        
        //! @brief Returns The box bounds relative to the parent Component
        juce::Rectangle<int> getBoxBounds() const;
        
        //! @brief Returns the inlet position relative to the parent jPatcher component for a given index.
        juce::Point<int> getInletPatcherPosition(const size_t index) const;
        
        //! @brief Returns the outlet position relative to the parent jPatcher component for a given index.
        juce::Point<int> getOutletPatcherPosition(const size_t index) const;
        
        //! Get the Object model
        model::Object& getModel() const {return *m_model;};
        
        //! @brief overloaded from Component to exclude border size.
        bool hitTest(int x, int y) override;
        
        //! @brief internal kiwi jPatcher HitTesting.
        bool hitTest(juce::Point<int> const& pt, HitTester& result) const;
        
        //! @brief internal kiwi jPatcher HitTesting (overlaps a rectangle).
        bool hitTest(juce::Rectangle<int> const& rect);
        
        //! Returns true if the object is selected.
        bool isSelected();
        
    private:
        
        void updateBounds();
        void drawInletsOutlets(juce::Graphics & g);
        
        //! @brief Returns the inlet local bounds for a given index.
        juce::Rectangle<int> getInletLocalBounds(const size_t index,
                                                 juce::Rectangle<int> const& object_bounds) const;
        
        //! @brief Returns the outlet local bounds for a given index.
        juce::Rectangle<int> getOutletLocalBounds(const size_t index,
                                                  juce::Rectangle<int> const& object_bounds) const;
        
    private: // members
        
        jPatcher&               m_patcher_view;
        model::Object*          m_model = nullptr;
        const unsigned int      m_io_width = 6;
        const unsigned int      m_io_height = 3;
        size_t                  m_inlets = 0;
        size_t                  m_outlets = 0;
        const juce::Colour      m_io_color;
        float                   m_selection_width = 3.;
        juce::Rectangle<int>    m_local_box_bounds;
        
        bool                    m_is_locked = 0;
        
        bool                    m_is_selected = 0;
        std::set<uint64_t>      m_distant_selection;
        bool                    m_is_editing;
        bool                    m_is_errorbox;
        
        friend jClassicBox;
    };
    
    // ================================================================================ //
    //                                   JOBJECT BOX                                    //
    // ================================================================================ //
    
    //! @brief The jClassicBox let the user change the text of the box
    class jClassicBox : public jObject, public juce::TextEditor::Listener
    {
    public:
        
        //! @brief Constructor.
        jClassicBox(jPatcher& patcher_view, model::Object& object_m);
        
        //! @brief Destructor.
        ~jClassicBox();
        
        //! @brief Give focus to the text editor.
        void grabKeyboardFocus();
        
        //! @brief Remove the text editor and give focus back to the jPatcher.
        void removeTextEditor();
        
        //! @brief Called when this component has just gained the keyboard focus.
        void focusGained(FocusChangeType cause) override;
        
        //! @brief Called when this component has just lost the keyboard focus.
        void focusLost(FocusChangeType cause) override;
        
        //! @brief called when the object is resized.
        void resized() override;
        
        void textEditorTextChanged(juce::TextEditor&) override;
        void textEditorReturnKeyPressed(juce::TextEditor&) override;
        void textEditorEscapeKeyPressed(juce::TextEditor&) override;
        void textEditorFocusLost(juce::TextEditor&) override;
        
    private: // members
        
        std::unique_ptr<juce::TextEditor> m_editor;
    };
}

#endif // KIWI_JOBJECT_HPP_INCLUDED
