/********************************************************************************
 *  File Name:
 *    chimera_usart_backend.cpp
 *
 *  Description:
 *    Fake backend registration file for testing purposes
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/usart>

/* Testing Includes */
#include "test_fixture_usart.hpp"


namespace Chimera::USART::Testing
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static BackendDriverType currentDriver;
  static Chimera::USART::Driver_sPtr testDriverObj;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void loadDriverType( const BackendDriverType type )
  {
    currentDriver = type;
  }
}  // namespace Chimera::USART::Testing

namespace Chimera::USART::Backend
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  namespace Standard
  {
    static Chimera::Status_t initialize()
    {
      return Chimera::Status::OK;
    }

    static Chimera::Status_t reset()
    {
      return Chimera::Status::OK;
    }

    static bool isChannelUSART( const Chimera::Serial::Channel channel )
    {
      return true;
    }

    static Chimera::USART::Driver_sPtr getDriver( const Chimera::Serial::Channel channel )
    {
      if ( !Testing::testDriverObj )
      {
        Testing::testDriverObj = std::make_shared<Chimera::USART::Driver>();
      }

      return Testing::testDriverObj;
    }
  }  // namespace Standard


  Chimera::Status_t registerDriver( Chimera::USART::Backend::DriverConfig &registry )
  {
    switch ( Testing::currentDriver )
    {
      case Testing::DRIVER_STANDARD:
        registry.isSupported   = true;
        registry.getDriver     = Standard::getDriver;
        registry.initialize    = Standard::initialize;
        registry.reset         = Standard::reset;
        registry.isChannelUSART = Standard::isChannelUSART;
        return Chimera::Status::OK;
        break;

      case Testing::DRIVER_BAD_REGISTRATION:
        registry.isSupported = false;
        return Chimera::Status::FAILED_INIT;
        break;

      case Testing::DRIVER_REGISTERED_NOT_SUPPORTED:
        registry.isSupported = false;
        return Chimera::Status::OK;
        break;

      case Testing::DRIVER_REGISTERED_MISSING_FUNCS:
        registry.isSupported   = true;
        registry.getDriver     = nullptr;
        registry.initialize    = nullptr;
        registry.reset         = nullptr;
        registry.isChannelUSART = nullptr;
        return Chimera::Status::OK;
        break;

      default:
        registry.isSupported   = false;
        registry.getDriver     = nullptr;
        registry.initialize    = nullptr;
        registry.reset         = nullptr;
        registry.isChannelUSART = nullptr;
        return Chimera::Status::FAILED_INIT;
        break;
    }
  }
}  // namespace Chimera::USART::Backend

namespace Chimera::USART
{
  /*-------------------------------------------------------------------------------
  Driver Implementation
  -------------------------------------------------------------------------------*/
  Driver::Driver() : mChannel( Chimera::Serial::Channel::NOT_SUPPORTED )
  {
  }

  Driver::~Driver()
  {
  }

  /*-------------------------------------------------
  Interface: Hardware
  -------------------------------------------------*/
  Chimera::Status_t Driver::assignHW( const Chimera::Serial::Channel channel, const Chimera::Serial::IOPins &pins )
  {
    mChannel = channel;
    return Chimera::Status::FAIL;
  }


  Chimera::Status_t Driver::begin( const Chimera::Hardware::PeripheralMode txMode,
                                   const Chimera::Hardware::PeripheralMode rxMode )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::end()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::configure( const Chimera::Serial::Config &config )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setBaud( const uint32_t baud )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setMode( const Chimera::Hardware::SubPeripheral periph,
                                     const Chimera::Hardware::PeripheralMode mode )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::write( const void *const buffer, const size_t length )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::read( void *const buffer, const size_t length )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::flush( const Chimera::Hardware::SubPeripheral periph )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::toggleAsyncListening( const bool state )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::readAsync( uint8_t *const buffer, const size_t len )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::enableBuffering( const Chimera::Hardware::SubPeripheral periph,
                                             boost::circular_buffer<uint8_t> *const userBuffer, uint8_t *const hwBuffer,
                                             const size_t hwBufferSize )
  {
    return Chimera::Status::OK;
  }

  Chimera::Status_t Driver::disableBuffering( const Chimera::Hardware::SubPeripheral periph )
  {
    return Chimera::Status::OK;
  }


  bool Driver::available( size_t *const bytes )
  {
    return false;
  }


  void Driver::postISRProcessing()
  {
  }


  /*-------------------------------------------------
  Interface: Listener
  -------------------------------------------------*/
  Chimera::Status_t Driver::registerListener( Chimera::Event::Actionable &listener, const size_t timeout,
                                              size_t &registrationID )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::removeListener( const size_t registrationID, const size_t timeout )
  {
    return Chimera::Status::OK;
  }


  /*-------------------------------------------------
  Interface: AsyncIO
  -------------------------------------------------*/
  Chimera::Status_t Driver::await( const Chimera::Event::Trigger event, const size_t timeout )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::await( const Chimera::Event::Trigger event, Chimera::Threading::BinarySemaphore &notifier,
                                   const size_t timeout )
  {
    return Chimera::Status::OK;
  }

  /*-------------------------------------------------
  Interface: Lockable
  -------------------------------------------------*/
  void Driver::lock()
  {
  }

  void Driver::lockFromISR()
  {
  }

  bool Driver::try_lock_for( const size_t timeout )
  {
    return true;
  }

  void Driver::unlock()
  {
  }

  void Driver::unlockFromISR()
  {
  }

}  // namespace Chimera::USART