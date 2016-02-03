/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "KiwiEngine/KiwiEngine.h"

#include "flip/Document.h"
#include "flip/DocumentObserver.h"
#include "flip/History.h"
#include "flip/HistoryStoreMemory.h"
#include "flip/DataConsumerMemory.h"
#include "flip/BackEndBinary.h"

#include "flip/BackEndMl.h"

#include "../JuceLibraryCode/JuceHeader.h"

using namespace std;

namespace kiwi
{
    //==============================================================================
    class KiwiApplication  : public JUCEApplication
    {
    private:
        unique_ptr<Instance> m_instance;
        
    public:
        //==============================================================================
        KiwiApplication() {}
        
        const String getApplicationName() override       { return ProjectInfo::projectName; }
        const String getApplicationVersion() override    { return ProjectInfo::versionString; }
        bool moreThanOneInstanceAllowed() override       { return true; }
        
        //==============================================================================
        void initialise (const String& commandLine) override
        {
            m_instance = Instance::create(123456789ULL, "Main");
            cout << "Kiwi instance : " << m_instance->getName()->getName() << endl;
            
            sPatcher patcher = m_instance->createPatcher();
            
            // change grid size and commit
            cout << "\n\n------ Change things ------\n\n";
            patcher->setGridSize(40, true);
            
            cout << "\n\n------ Change unlocked_bgcolor & gridsize ------\n\n";
            patcher->beginTransaction("Change unlocked_bgcolor & gridsize");
            patcher->setAttributeValue(Tags::unlocked_bgcolor, Atom{0.1, 0.2, 0.3, 1.});
            patcher->setAttributeValue(Tags::gridsize, Atom(45));
            patcher->setAttributeValue(Tag::create("attr_bool"), Atom(true));
            patcher->setAttributeValue(Tag::create("attr_tag"), "zozo");
            patcher->endTransaction();
            
            cout << "\n\n------ Change things ------\n\n";
            patcher->beginTransaction("Change things");
            patcher->setAttributeValue(Tags::unlocked_bgcolor, Colors::green);
            patcher->setAttributeValue(Tags::gridsize, 10ll);
            patcher->setAttributeValue(Tag::create("attr_bool"), Atom(false));
            patcher->setAttributeValue(Tag::create("attr_tag"), Atom("lolo"));
            patcher->endTransaction();
            
            cout << "\n\n------ undo (1) ------\n\n";
            patcher->undo(true);
            cout << "\n\n------ undo (2) ------\n\n";
            patcher->undo(true);
            cout << "\n\n------ redo ------\n\n";
            patcher->redo(true);
        }
        
        void shutdown() override
        {
        }
        
        //==============================================================================
        void systemRequestedQuit() override
        {
            m_instance.reset();
            
            // This is called when the app is being asked to quit: you can ignore this
            // request and let the app carry on running, or call quit() to allow the app to close.
            quit();
        }
        
        void anotherInstanceStarted (const String& commandLine) override
        {
            // When another instance of the app is launched while this one is running,
            // this method is invoked, and the commandLine parameter tells you what
            // the other instance's command-line arguments were.
        }
    };
    
    //==============================================================================
    // This macro generates the main() routine that launches the app.
    START_JUCE_APPLICATION (KiwiApplication)
}