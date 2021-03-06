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


TEST( GPIOTests, DriverStandard )
{
  using namespace Chimera::GPIO;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::GPIO::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::GPIO::reset(), Chimera::Status::OK );
  EXPECT_NE( Chimera::GPIO::getDriver( Port::PORTA, 0 ), nullptr );
}

TEST( GPIOTests, DriverBadRegistration )
{
  using namespace Chimera::GPIO;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::GPIO::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::GPIO::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::GPIO::getDriver( Port::PORTA, 0 ), nullptr );
}


TEST( GPIOTests, DriverRegisteredNotSupported )
{
  using namespace Chimera::GPIO;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::GPIO::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::GPIO::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::GPIO::getDriver( Port::PORTA, 0 ), nullptr );
}


TEST( GPIOTests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::GPIO;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::GPIO::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::GPIO::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::GPIO::getDriver( Port::PORTA, 0 ), nullptr );
}
