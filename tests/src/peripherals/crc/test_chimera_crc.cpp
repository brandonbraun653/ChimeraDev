/********************************************************************************
 *  File Name:
 *    test_chimera_crc.cpp
 *
 *  Description:
 *    Tests the Chimera crc driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/crc>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_crc.hpp"


TEST( CRCTests, DriverStandard )
{
  using namespace Chimera::CRC;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::CRC::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::CRC::reset(), Chimera::Status::OK );
  EXPECT_NE( Chimera::CRC::getDriver( Channel::CHANNEL1 ), nullptr );
}

TEST( CRCTests, DriverBadRegistration )
{
  using namespace Chimera::CRC;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::CRC::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::CRC::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CRC::getDriver( Channel::CHANNEL1 ), nullptr );
}


TEST( CRCTests, DriverRegisteredNotSupported )
{
  using namespace Chimera::CRC;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::CRC::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CRC::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CRC::getDriver( Channel::CHANNEL1 ), nullptr );
}


TEST( CRCTests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::CRC;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::CRC::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CRC::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::CRC::getDriver( Channel::CHANNEL1 ), nullptr );
}
