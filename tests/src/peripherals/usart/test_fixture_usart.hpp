/********************************************************************************
 *  File Name:
 *    test_fixture_usart.hpp
 *
 *  Description:
 *    Fixtures for helping configure the test
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_TEST_USART_FIXTURES_HPP
#define CHIMERA_TEST_USART_FIXTURES_HPP

/* STL Includes */
#include <cstdint>

namespace Chimera::USART::Testing
{
  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum BackendDriverType : uint8_t
  {
    DRIVER_STANDARD,
    DRIVER_BAD_REGISTRATION,
    DRIVER_REGISTERED_NOT_SUPPORTED,
    DRIVER_REGISTERED_MISSING_FUNCS,

    DRIVER_NUM_OPTIONS,
    DRIVER_UNKNOWN
  };

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void loadDriverType( const BackendDriverType type );

}  // namespace Chimera::USART::Testing

#endif  /* !CHIMERA_TEST_USART_FIXTURES_HPP */
