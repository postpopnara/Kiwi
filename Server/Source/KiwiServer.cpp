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

#include "KiwiServer.hpp"

#include <sys/types.h>
#include <sys/stat.h>

namespace kiwi
{
    namespace server
    {
        // ================================================================================ //
        //                                      SERVER                                      //
        // ================================================================================ //
        
        const char* Server::kiwi_file_extension = "kiwi";
        
        Server::Server(uint16_t port) :
        m_port(port),
        m_server(model::DataModel::use(), m_port),
        m_service_document(model::DataModel::use(), 1, 'serv', 'serv'),
        m_service_provider(m_port, m_service_document, metadata_t())
        {
            using namespace std::placeholders; // for _1, _2 etc.
            
            m_server.bind_validator_factory(std::bind(&Server::createValidator, this, _1));
            m_server.bind_init(std::bind(&Server::initEmptyDocument, this, _1, _2));
            m_server.bind_read(std::bind(&Server::readSessionBackend, this, _1));
            m_server.bind_write(std::bind(&Server::writeSessionBackend, this, _1, _2));
            //m_server.bind_authenticate(std::bind(&Server::authenticateUser, this, _1, _2, _3));
            
            initBackendDirectory("server_backend");
        }
        
        Server::~Server()
        {
            ;
        }
        
        bool Server::initBackendDirectory(char const* name)
        {
            m_backend_files_path = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile).getSiblingFile(name);
            
            return juce::Result::ok() == m_backend_files_path.createDirectory();
        }
        
        void Server::setSessionsBackendDirectory(std::string const& directory)
        {
            m_backend_files_path = directory;
        }
        
        juce::File Server::getSessionFile(uint64_t session_id)
        {
            return m_backend_files_path.getChildFile(juce::String(session_id)).withFileExtension(kiwi_file_extension);
        }
        
        uint16_t Server::getPort() const noexcept
        {
            return m_port;
        }
        
        uint16_t Server::getNumberOfActiveSessions() const noexcept
        {
            return m_server.nbr_sessions();
        }
        
        void Server::process()
        {
            m_server.process();
            m_service_provider.process();
        }
        
        std::unique_ptr<flip::DocumentValidatorBase> Server::createValidator(uint64_t session_id)
        {
            std::cout << "createValidator - session_id : " << std::to_string(session_id) << '\n';
            
            return std::make_unique<PatcherValidator>();
        }
        
        void Server::initEmptyDocument(uint64_t session_id, flip::DocumentBase& document)
        {
            std::cout << "initEmptyDocument - session_id : " << std::to_string(session_id) << '\n';
            
            // init default patcher here.
            model::Patcher& patcher = document.root<model::Patcher>();
            patcher.setName("Untitled patcher");
        }
        
        flip::BackEndIR Server::readSessionBackend(uint64_t session_id)
        {
            std::cout << "readSessionBackend - session_id : " << std::to_string(session_id) << '\n';
            
            flip::BackEndIR backend;
            
            const auto session_file = getSessionFile(session_id);
            
            if (session_file.exists())
            {
                flip::DataProviderFile provider(session_file.getFullPathName().toStdString().c_str());
                
                backend.register_backend<flip::BackEndBinary>();
                backend.read(provider);
            }
            
            return backend;
        }
        
        void Server::writeSessionBackend(uint64_t session_id, flip::BackEndIR const& backend)
        {
            std::cout << "Saving session [ " << std::to_string(session_id) << " ]\n";
            
            const auto session_file = getSessionFile(session_id);
            
            if(!session_file.exists())
            {
                session_file.create();
            }
            
            flip::DataConsumerFile consumer(session_file.getFullPathName().toStdString().c_str());
            backend.write<flip::BackEndBinary>(consumer);
        }
        
        bool Server::authenticateUser(uint64_t user_id, uint64_t session_id, std::string metadata)
        {
            // @todo do something here
            return true;
        }
        
        void Server::run()
        {
            flip::RunLoopTimer run_loop ([this](){
                process();
                return true;
            });
            
            std::cout << "- KiwiServer running on port " << getPort() << '\n';
            
            run_loop.run();  // never returns
        }
    }
}
