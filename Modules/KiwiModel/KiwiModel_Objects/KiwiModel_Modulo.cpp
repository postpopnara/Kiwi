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

#include <KiwiModel/KiwiModel_Objects/KiwiModel_Modulo.h>
#include <KiwiModel/KiwiModel_Factory.h>

namespace kiwi { namespace model {
    
    // ================================================================================ //
    //                                    OBJECT MODULO                                 //
    // ================================================================================ //
    
    void Modulo::declare()
    {
        if (!DataModel::has<model::Operator>())
        {
            Operator::declare();
        }
        
        std::unique_ptr<ObjectClass> modulo_class(new ObjectClass("%",
                                                                  &Modulo::create));
        
        flip::Class<Modulo> & modulo_model = DataModel::declare<Modulo>()
                                            .name(modulo_class->getModelName().c_str())
                                            .inherit<Operator>();
        
        Factory::add<Modulo>(std::move(modulo_class), modulo_model);
    }
    
    std::unique_ptr<Object> Modulo::create(std::vector<tool::Atom> const& args)
    {
        return std::make_unique<Modulo>(args);
    }
    
    Modulo::Modulo(std::vector<tool::Atom> const& args):
    Operator(args)
    {
    }
    
}}
