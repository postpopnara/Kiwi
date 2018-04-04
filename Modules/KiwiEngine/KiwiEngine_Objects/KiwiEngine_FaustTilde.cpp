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

#include <KiwiEngine/KiwiEngine_Objects/KiwiEngine_FaustTilde.h>
#include <KiwiEngine/KiwiEngine_Factory.h>
#include <stdlib.h>
#include <dlfcn.h>

namespace kiwi { namespace engine {
    
    // ================================================================================ //
    //                                       PLUS~                                      //
    // ================================================================================ //
    
    void FaustTilde::declare()
    {
        Factory::add<FaustTilde>("faust~", &FaustTilde::create);
    }
    
    std::unique_ptr<Object> FaustTilde::create(model::Object const& model, Patcher & patcher)
    {
        return std::make_unique<FaustTilde>(model, patcher);
    }
    
    FaustTilde::FaustTilde(model::Object const& model, Patcher& patcher):
    AudioObject(model, patcher)
    {
        auto const& args = model.getArguments();
        std::string const name = args[2].getString() + ".kiwix";
        void* lib_handle = dlopen(name.c_str(), RTLD_LOCAL|RTLD_LAZY);
        if (!lib_handle)
        {
            post(name + " : Unable to load library");
        }
        else
        {
            post(name + " : loaded");
        }
        /*
        // Print data entered and call libRatings.A:addRating().
        void (*addRating)(char*) = dlsym(lib_handle, "addRating");
        if (!addRating) {       // addRating is guaranteed to exist in libRatings.A.dylib
            printf("[%s] Unable to get symbol: %s\n", __FILE__, dlerror());
            exit(EXIT_FAILURE);
        }
         */
    }
    
    void FaustTilde::prepare(PrepareInfo const& infos)
    {
        
    }
    
}}
