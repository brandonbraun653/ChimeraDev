/********************************************************************************
 *  File Name:
 *    test_chimera_clock.cpp
 *
 *  Description:
 *    Tests the Chimera Clock driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/clock>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_clock.hpp"


TEST( ClockTests, DriverStandard )
{
  using namespace Chimera::Clock;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Clock::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Clock::periphEnable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Clock::periphDisable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Clock::enableClock( Chimera::Clock::Bus::HCLK ), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Clock::disableClock( Chimera::Clock::Bus::HCLK ), Chimera::Status::OK );
  EXPECT_EQ( Chimera::Clock::isEnabled( Chimera::Clock::Bus::APB2 ), true );
  EXPECT_GE( Chimera::Clock::getFrequency( Chimera::Clock::Bus::APB2 ), 0 );
  EXPECT_EQ( Chimera::Clock::setFrequency( Chimera::Clock::Bus::PCLK1, 100 ), Chimera::Status::OK );
}

TEST( ClockTests, DriverBadRegistration )
{
  using namespace Chimera::Clock;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Clock::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::Clock::periphEnable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::periphDisable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::enableClock( Chimera::Clock::Bus::HCLK ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::disableClock( Chimera::Clock::Bus::HCLK ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::isEnabled( Chimera::Clock::Bus::APB2 ), false );
  EXPECT_GE( Chimera::Clock::getFrequency( Chimera::Clock::Bus::APB2 ), 0 );
  EXPECT_EQ( Chimera::Clock::setFrequency( Chimera::Clock::Bus::PCLK1, 100 ), Chimera::Status::NOT_SUPPORTED );
}


TEST( ClockTests, DriverRegisteredNotSupported )
{
  using namespace Chimera::Clock;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Clock::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::periphEnable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::periphDisable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::enableClock( Chimera::Clock::Bus::HCLK ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::disableClock( Chimera::Clock::Bus::HCLK ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::isEnabled( Chimera::Clock::Bus::APB2 ), false );
  EXPECT_GE( Chimera::Clock::getFrequency( Chimera::Clock::Bus::APB2 ), 0 );
  EXPECT_EQ( Chimera::Clock::setFrequency( Chimera::Clock::Bus::PCLK1, 100 ), Chimera::Status::NOT_SUPPORTED );
}


TEST( ClockTests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::Clock;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::Clock::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::periphEnable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::periphDisable( Chimera::Peripheral::Type::PERIPH_ADC ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::enableClock( Chimera::Clock::Bus::HCLK ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::disableClock( Chimera::Clock::Bus::HCLK ), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::Clock::isEnabled( Chimera::Clock::Bus::APB2 ), false );
  EXPECT_GE( Chimera::Clock::getFrequency( Chimera::Clock::Bus::APB2 ), 0 );
  EXPECT_EQ( Chimera::Clock::setFrequency( Chimera::Clock::Bus::PCLK1, 100 ), Chimera::Status::NOT_SUPPORTED );
}
