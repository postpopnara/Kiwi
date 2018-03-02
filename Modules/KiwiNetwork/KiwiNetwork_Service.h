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

#include <memory>

#include <boost/asio/io_service.hpp>

namespace kiwi { namespace network {

    // ================================================================================ //
    //                                       SERVICE                                    //
    // ================================================================================ //
    
    //! @brief Service is class used to process network events.
    //! @details Call the use method to access the boost network processor.
    class Service
    {
    public: // methods
        
        //! @brief Returns the underlying boost network processor.
        static boost::asio::io_service & use();
        
    private: // members
        
        static std::unique_ptr<boost::asio::io_service> m_io_service;
        
    private: // deleted methods
        
        Service() = delete;
        Service(Service const& other) = delete;
        Service(Service && other) = delete;
        Service& operator=(Service const& other) = delete;
        Service& operator=(Service && other) = delete;
        ~Service() = delete;
    };
    
}} // namespace kiwi::network
