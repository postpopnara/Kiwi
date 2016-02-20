//
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
//

#ifndef KIWI_DSP_PROCESSOR_H_INCLUDED
#define KIWI_DSP_PROCESSOR_H_INCLUDED

#include "KiwiDspInfos.hpp"

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
    //! @details You should implement the pure virtual methods prepare, perform and
    //! @details release.
    //! @see Buffer and Infos
    class Processor
    {
    public:
        //! @brief The constructor.
        //! @details Allocates and initializes a default Processor object.
        Processor() noexcept;
        
        //! @brief The destructor.
        virtual ~Processor() noexcept;
        
        //! @brief Retrieves the current number of inputs.
        //! @return The number of inputs of the Processor object.
        inline size_t getNumberOfInputs() const noexcept {return m_ninputs;}
        
        //! @brief Retrieves the current number of outputs.
        //! @return The number of outputs of the Processor object.
        inline size_t getNumberOfOutputs() const noexcept {return m_noutputs;}
        
    protected:
        //! @brief Sets the number of inputs.
        //! @details You should use this method while the DSP ins't running.
        //! @param nins The number of inputs.
        //! @see setNumberOfOutlets() and getNumberOfInputs()
        void setNumberOfInlets(const size_t nins) noexcept;
        
        //! @brief Sets the number of outputs.
        //! @details You should use this method while the DSP ins't running.
        //! @param nouts The number of outputs.
        //! @see setNumberOfInlets() and getNumberOfOutputs()
        void setNumberOfOutlets(const size_t nouts) noexcept;
        
    private:
        //! @brief Prepares everything for the perform method.
        //! @details This is a pure virtual method. You should use this method to check the
        //! @details vector size, the sample rate, the connected inputs and outputs and to
        //! @details allocate memory if needed. The method should return true if the perform
        //! @details method of the Processor object can be called, otherwise it should return
        //! @details false.
        //! @param infos The DSP informations.
        //! @return true if the perform method can be called, otherwise false.
        //! @see release()
        virtual bool prepare(Infos const& infos) = 0;
        
        //! @brief Performs the digital signal processing.
        //! @details This is a pure virtual method. You should use this method to perform the
        //! @details digital signal processing but you should avoid to allocate memory or do
        //! @details it asynchronously.
        //! @param input    The input Buffer object.
        //! @param output   The output Buffer object.
        virtual void perform(Buffer const& input, Buffer& output) noexcept = 0;
        
        //! @brief Releases everything after the digital signal processing.
        //! @details You can use this method to free the memory allocated during the call of
        //! @details the prepare method for example.
        //! @see prepare()
        virtual void release() {};
        
        size_t  m_ninputs;
        size_t  m_noutputs;
        bool    m_running;
        friend class Chain;
    };
}
}

#endif // KIWI_DSP_PROCESSOR_H_INCLUDED
