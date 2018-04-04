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

#include "../../KiwiExternal/Kiwi_Loader.hpp"

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
        try
        {
            m_object = external::Loader::create("", args[2].getString());
        }
        catch (external::kerror_t& e)
        {
            error(std::string("faust~: ") + e.what());
        }
        if(m_object)
        {
            const auto ninlets = m_object->getNumberOfInputs() > 0 ? m_object->getNumberOfInputs() : 1;
            const auto noutlets = m_object->getNumberOfOutputs() + 1;
            
            if(ninlets != getNumberOfInputs())
            {
                error(std::string("faust~: " + args[2].getString() + " wrong number of inputs, " +
                                  std::to_string(m_object->getNumberOfInputs()) + " inputs expected"));
            }
            if(noutlets != getNumberOfOutputs())
            {
                error(std::string("faust~: " + args[2].getString() + " wrong number of outputs, " +
                                  std::to_string(m_object->getNumberOfOutputs()) + " outputs expected"));
            }
        }
    }
    
    FaustTilde::~FaustTilde()
    {
        if(m_object)
        {
            try
            {
                external::Loader::dispose(m_object);
            }
            catch (external::kerror_t& e)
            {
                error(std::string("faust~: ") + e.what());
            }
        }
    }
    
    void FaustTilde::prepare(PrepareInfo const& infos)
    {
        
    }
    
}}
