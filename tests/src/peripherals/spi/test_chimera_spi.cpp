/********************************************************************************
 *  File Name:
 *    test_chimera_spi.cpp
 *
 *  Description:
 *    Tests the Chimera SPI driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/spi>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_spi.hpp"


TEST( SPITests, DriverStandard )
{
  using namespace Chimera::SPI;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::SPI::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::SPI::reset(), Chimera::Status::OK );
  EXPECT_NE( Chimera::SPI::getDriver( Channel::SPI1 ), nullptr );
}

TEST( SPITests, DriverBadRegistration )
{
  using namespace Chimera::SPI;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::SPI::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::SPI::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::SPI::getDriver( Channel::SPI1 ), nullptr );
}


TEST( SPITests, DriverRegisteredNotSupported )
{
  using namespace Chimera::SPI;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::SPI::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::SPI::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::SPI::getDriver( Channel::SPI1 ), nullptr );
}


TEST( SPITests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::SPI;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::SPI::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::SPI::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::SPI::getDriver( Channel::SPI1 ), nullptr );
}
