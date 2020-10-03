/********************************************************************************
 *  File Name:
 *    test_chimera_dma.cpp
 *
 *  Description:
 *    Tests the Chimera DMA driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/dma>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_dma.hpp"


TEST( DMATests, DriverStandard )
{
  using namespace Chimera::DMA;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::DMA::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::DMA::reset(), Chimera::Status::OK );
  EXPECT_NE( Chimera::DMA::getDriver( Controller::CHANNEL1 ), nullptr );
}

TEST( DMATests, DriverBadRegistration )
{
  using namespace Chimera::DMA;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::DMA::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::DMA::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::DMA::getDriver( Controller::CHANNEL1 ), nullptr );
}


TEST( DMATests, DriverRegisteredNotSupported )
{
  using namespace Chimera::DMA;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::DMA::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::DMA::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::DMA::getDriver( Controller::CHANNEL1 ), nullptr );
}


TEST( DMATests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::DMA;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::DMA::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::DMA::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::DMA::getDriver( Controller::CHANNEL1 ), nullptr );
}
