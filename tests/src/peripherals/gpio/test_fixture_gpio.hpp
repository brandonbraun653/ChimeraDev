/********************************************************************************
 *  File Name:
 *    test_fixture_gpio.hpp
 *
 *  Description:
 *    Fixtures for helping configure the test
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef CHIMERA_TEST_GPIO_FIXTURES_HPP
#define CHIMERA_TEST_GPIO_FIXTURES_HPP

/* STL Includes */
#include <cstdint>

namespace Chimera::GPIO::Testing
{
  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum BackendDriverType : uint8_t
  {
    DRIVER_STANDARD,

    DRIVER_NUM_OPTIONS,
    DRIVER_UNKNOWN
  };

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void loadDriverType( const BackendDriverType type );

}  // namespace Chimera::GPIO::Testing

#endif  /* !CHIMERA_TEST_GPIO_FIXTURES_HPP */
