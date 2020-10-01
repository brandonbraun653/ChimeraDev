/********************************************************************************
 *  File Name:
 *    test_chimera_gpio.cpp
 *
 *  Description:
 *    Tests the Chimera GPIO driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/gpio>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_gpio.hpp"


TEST( GPIOTests, Normal_Initialize )
{
  using namespace Chimera::GPIO;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call
  -------------------------------------------------*/
  auto result = Chimera::GPIO::initialize();

  /*-------------------------------------------------
  Verify
  -------------------------------------------------*/
  EXPECT_EQ( result, Chimera::Status::OK );
}
