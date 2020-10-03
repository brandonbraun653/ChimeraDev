/********************************************************************************
 *  File Name:
 *    test_chimera_timer.cpp
 *
 *  Description:
 *    Tests the Chimera Timer driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/timer>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_timer.hpp"


TEST( TimerTests, DriverStandard )
{
  using namespace Chimera::Timer;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Timer::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Timer::reset(), Chimera::Status::OK );
  EXPECT_NE( Chimera::Timer::getDriver( Chimera::Timer::Peripheral::TIMER1 ), nullptr );
  EXPECT_GE( Chimera::Timer::micros(), 0 );
  EXPECT_GE( Chimera::Timer::millis(), 0 );

  // Coverage calls
  Chimera::Timer::delayMicroseconds( 100 );
  Chimera::Timer::delayMilliseconds( 100 );
}

TEST( TimerTests, DriverBadRegistration )
{
  using namespace Chimera::Timer;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Timer::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::Timer::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Timer::getDriver( Chimera::Timer::Peripheral::TIMER1 ), nullptr );
  EXPECT_GE( Chimera::Timer::micros(), 0 );
  EXPECT_GE( Chimera::Timer::millis(), 0 );

  // Coverage calls
  Chimera::Timer::delayMicroseconds( 100 );
  Chimera::Timer::delayMilliseconds( 100 );
}


TEST( TimerTests, DriverRegisteredNotSupported )
{
  using namespace Chimera::Timer;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Timer::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Timer::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Timer::getDriver( Chimera::Timer::Peripheral::TIMER1 ), nullptr );
  EXPECT_GE( Chimera::Timer::micros(), 0 );
  EXPECT_GE( Chimera::Timer::millis(), 0 );

  // Coverage calls
  Chimera::Timer::delayMicroseconds( 100 );
  Chimera::Timer::delayMilliseconds( 100 );
}


TEST( TimerTests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::Timer;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Timer::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Timer::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Timer::getDriver( Chimera::Timer::Peripheral::TIMER1 ), nullptr );
  EXPECT_GE( Chimera::Timer::micros(), 0 );
  EXPECT_GE( Chimera::Timer::millis(), 0 );

  // Coverage calls
  Chimera::Timer::delayMicroseconds( 100 );
  Chimera::Timer::delayMilliseconds( 100 );
}
