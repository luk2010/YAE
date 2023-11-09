/**
 * @file Error.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_ERROR_H__
#define __YAE_ERROR_H__

#include "YAE/Common.h"

namespace YAE 
{
    /**
     * @brief 
     *     An Error base class.
     */
    struct Error : public std::exception 
    {
        //! @brief The error message.
        std::string message;

        //! @brief Constructs a new Error instance.
        template < class... Args > Error(Args&&... args)
        {
            std::stringstream stream;
            ((stream << args), ...);
            message = stream.str();
        }

        //! @brief Returns the error message.
        inline const char* what() const noexcept { return message.data(); }
    };
}

#endif 