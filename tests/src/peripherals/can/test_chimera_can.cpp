/********************************************************************************
 *  File Name:
 *    test_chimera_can.cpp
 *
 *  Description:
 *    Tests the Chimera CAN driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/can>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_can.hpp"


TEST( CANTests, DriverStandard )
{
  using namespace Chimera::CAN;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::CAN::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::CAN::reset(), Chimera::Status::OK );
  EXPECT_NE( Chimera::CAN::getDriver( Chimera::CAN::Channel::CAN0 ), nullptr );
}

TEST( CANTests, DriverBadRegistration )
{
  using namespace Chimera::CAN;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::CAN::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::CAN::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CAN::getDriver( Chimera::CAN::Channel::CAN0 ), nullptr );
}


TEST( CANTests, DriverRegisteredNotSupported )
{
  using namespace Chimera::CAN;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::CAN::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CAN::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CAN::getDriver( Chimera::CAN::Channel::CAN0 ), nullptr );
}


TEST( CANTests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::CAN;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::CAN::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CAN::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CAN::getDriver( Chimera::CAN::Channel::CAN0 ), nullptr );
}
