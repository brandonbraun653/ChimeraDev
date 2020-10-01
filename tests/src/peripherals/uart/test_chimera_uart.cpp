/********************************************************************************
 *  File Name:
 *    test_chimera_uart.cpp
 *
 *  Description:
 *    Tests the Chimera UART driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/uart>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_uart.hpp"


TEST( UARTTests, DriverStandard )
{
  using namespace Chimera::UART;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::UART::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::UART::reset(), Chimera::Status::OK );
  EXPECT_NE( Chimera::UART::getDriver( Chimera::Serial::Channel::SERIAL1 ), nullptr );
  EXPECT_EQ( Chimera::UART::isChannelUART( Chimera::Serial::Channel::SERIAL1 ), true );
}

TEST( UARTTests, DriverBadRegistration )
{
  using namespace Chimera::UART;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::UART::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::UART::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::UART::getDriver( Chimera::Serial::Channel::SERIAL1 ), nullptr );
  EXPECT_EQ( Chimera::UART::isChannelUART( Chimera::Serial::Channel::SERIAL1 ), false );
}


TEST( UARTTests, DriverRegisteredNotSupported )
{
  using namespace Chimera::UART;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::UART::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::UART::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::UART::getDriver( Chimera::Serial::Channel::SERIAL1 ), nullptr );
  EXPECT_EQ( Chimera::UART::isChannelUART( Chimera::Serial::Channel::SERIAL1 ), false );
}


TEST( UARTTests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::UART;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::UART::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::UART::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::UART::getDriver( Chimera::Serial::Channel::SERIAL1 ), nullptr );
  EXPECT_EQ( Chimera::UART::isChannelUART( Chimera::Serial::Channel::SERIAL1 ), false );
}
