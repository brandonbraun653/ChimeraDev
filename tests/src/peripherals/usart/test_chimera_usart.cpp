/********************************************************************************
 *  File Name:
 *    test_chimera_usart.cpp
 *
 *  Description:
 *    Tests the Chimera USART driver interface
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes  */
#include <Chimera/usart>

/* Testing Includes */
#include <gtest/gtest.h>
#include "test_fixture_usart.hpp"


TEST( USARTTests, DriverStandard )
{
  using namespace Chimera::USART;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_STANDARD );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::USART::initialize(), Chimera::Status::OK );
  EXPECT_EQ( Chimera::USART::reset(), Chimera::Status::OK );
  EXPECT_NE( Chimera::USART::getDriver( Chimera::Serial::Channel::SERIAL1 ), nullptr );
  EXPECT_EQ( Chimera::USART::isChannelUSART( Chimera::Serial::Channel::SERIAL1 ), true );
}

TEST( USARTTests, DriverBadRegistration )
{
  using namespace Chimera::USART;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_BAD_REGISTRATION );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::USART::initialize(), Chimera::Status::FAILED_INIT );
  EXPECT_EQ( Chimera::USART::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::USART::getDriver( Chimera::Serial::Channel::SERIAL1 ), nullptr );
  EXPECT_EQ( Chimera::USART::isChannelUSART( Chimera::Serial::Channel::SERIAL1 ), false );
}


TEST( USARTTests, DriverRegisteredNotSupported )
{
  using namespace Chimera::USART;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_NOT_SUPPORTED );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::USART::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::USART::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::USART::getDriver( Chimera::Serial::Channel::SERIAL1 ), nullptr );
  EXPECT_EQ( Chimera::USART::isChannelUSART( Chimera::Serial::Channel::SERIAL1 ), false );
}


TEST( USARTTests, DriverRegisteredMissingFunctions )
{
  using namespace Chimera::USART;

  /*-------------------------------------------------
  Initialize
  -------------------------------------------------*/
  Testing::loadDriverType( Testing::DRIVER_REGISTERED_MISSING_FUNCS );

  /*-------------------------------------------------
  Call & Verify
  -------------------------------------------------*/
  EXPECT_EQ( Chimera::USART::initialize(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::USART::reset(), Chimera::Status::NOT_SUPPORTED );
  EXPECT_EQ( Chimera::USART::getDriver( Chimera::Serial::Channel::SERIAL1 ), nullptr );
  EXPECT_EQ( Chimera::USART::isChannelUSART( Chimera::Serial::Channel::SERIAL1 ), false );
}
