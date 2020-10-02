/********************************************************************************
 *  File Name:
 *    test_chimera_power.cpp
 *
 *  Description:
 *    Tests the Chimera Power driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/power>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_power.hpp"


TEST( PowerTests, DriverStandard )
{
  using namespace Chimera::Power;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Power::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Power::reset(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Power::periphDisable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Power::periphEnable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Power::setPowerState( Chimera::Power::State::ON ), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Power::getPowerState( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Power::State::ON );
}

TEST( PowerTests, DriverBadRegistration )
{
  using namespace Chimera::Power;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Power::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::Power::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::periphDisable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::periphEnable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::setPowerState( Chimera::Power::State::ON ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::getPowerState( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Power::State::INVALID );

}


TEST( PowerTests, DriverRegisteredNotSupported )
{
  using namespace Chimera::Power;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Power::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::periphDisable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::periphEnable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::setPowerState( Chimera::Power::State::ON ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::getPowerState( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Power::State::INVALID );
}


TEST( PowerTests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::Power;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Power::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::periphDisable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::periphEnable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::setPowerState( Chimera::Power::State::ON ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Power::getPowerState( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Power::State::INVALID );
}
