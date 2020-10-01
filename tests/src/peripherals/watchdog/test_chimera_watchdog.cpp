/********************************************************************************
 *  File Name:
 *    test_chimera_watchdog.cpp
 *
 *  Description:
 *    Tests the Chimera Watchdog driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/watchdog>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_watchdog.hpp"


TEST( WatchdogTests, DriverStandard )
{
  using namespace Chimera::Watchdog;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Watchdog::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Watchdog::reset(), Chimera::Status::OK );
  EXPECT_NE( Chimera::Watchdog::getDriver( Channel::WATCHDOG1 ), nullptr );
}

TEST( WatchdogTests, DriverBadRegistration )
{
  using namespace Chimera::Watchdog;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Watchdog::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::Watchdog::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Watchdog::getDriver( Channel::WATCHDOG1 ), nullptr );
}


TEST( WatchdogTests, DriverRegisteredNotSupported )
{
  using namespace Chimera::Watchdog;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Watchdog::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Watchdog::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Watchdog::getDriver( Channel::WATCHDOG1 ), nullptr );
}


TEST( WatchdogTests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::Watchdog;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Watchdog::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Watchdog::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Watchdog::getDriver( Channel::WATCHDOG1 ), nullptr );
}


TEST( WatchdogTests, InvokeTimeout )
{
  using namespace Chimera::Watchdog;

  /*-------------------------------------------------
  Gain coverage for the timeout func
  -------------------------------------------------*/
  invokeTimeout();
}
