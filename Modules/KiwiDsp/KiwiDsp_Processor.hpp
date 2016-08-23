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

#ifndef KIWI_DSP_PROCESSOR_HPP_INCLUDED
#define KIWI_DSP_PROCESSOR_HPP_INCLUDED

#include "KiwiDsp_Infos.hpp"
#include "KiwiDsp_Buffer.hpp"

namespace kiwi
{
    namespace dsp
    {
        class Chain;
        
        // ==================================================================================== //
        //                                      PROCESSOR                                       //
        // ==================================================================================== //
        
        //! @brief The pure virtual class that processes digital signal in a Chain object.
        //! @details The class is pure virtual and allows to implement digital signal processing.
        //! You should implement the virtual methods prepare, perform and release.
        //! @see Buffer and Infos
        class Processor
        {
        public: // methods
            
            //! @brief The constructor.
            //! @details Allocates and initializes a default Processor object.
            //! @param ninputs The number of inputs.
            //! @param noutputs The number of outputs.
            Processor(const size_t ninputs, const size_t noutputs) noexcept :
            m_ninputs(ninputs), m_noutputs(noutputs) {}
            
            //! @brief The destructor.
            virtual ~Processor() = default;
            
            //! @brief Gets the current number of inputs.
            //! @return The number of inputs of the Processor object.
            //! @see getNumberOfOutputs()
            inline size_t getNumberOfInputs() const noexcept {return m_ninputs;}
            
            //! @brief Gets the current number of outputs.
            //! @return The number of outputs of the Processor object.
            //! @see getNumberOfInputs()
            inline size_t getNumberOfOutputs() const noexcept {return m_noutputs;}
            
            //! @brief Returns true if the corresponding inlet should be inplace.
            //! @details If given a size_t pointer sets it to the corresponding outlet index.
            //! @details Default behavior is returning true if an outlet has the same index.
            virtual bool isInletInplace(const size_t index, size_t * const outlet_index = nullptr) const;
            
            //! @brief Returns true if the corresponding outlet should be inplace.
            //! @details If given a size_t pointer sets it to the corresponding inlet index.
            //! @details Default behavior is returning true if an inlet has the same index.
            virtual bool isOutletInplace(const size_t index, size_t * const outlet_index = nullptr) const;
            
        private: // methods
            
            //! @brief Prepares everything for the perform method.
            //! @details You should use this method to check the vector size, the sample rate,
            //! the connected inputs and outputs and to allocate memory if needed.
            //! The method should return true if the perform method of the
            //! Processor object can be called, otherwise it should return false.
            //! @param infos The DSP informations.
            //! @return true if the perform method can be called, otherwise false.
            //! @see perform() and release()
            virtual bool prepare(Infos& infos) { return true; };
            
            //! @brief Performs the digital signal processing.
            //! @details This is a pure virtual method. You should use this method to perform the
            //! digital signal processing but you should avoid to allocate memory or do it
            //! asynchronously.
            //! @param input    The input Buffer object.
            //! @param output   The output Buffer object.
            //! @see prepare() and release()
            virtual void perform(Buffer const& input, Buffer& output) noexcept = 0;
            
            //! @brief Releases everything after the digital signal processing.
            //! @details You can use this method to free the memory allocated during the call of
            //! the prepare method for example.
            //! @see prepare() and perform()
            virtual void release() {};
            
        private: // members
            
            const size_t        m_ninputs;
            const size_t        m_noutputs;
            friend Node;
            friend Chain;
        };
    }
}

#endif // KIWI_DSP_PROCESSOR_HPP_INCLUDED
