/********************************************************************************
 *  File Name:
 *    chimera_gpio_backend.cpp
 *
 *  Description:
 *    Fake backend registration file for testing purposes
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/gpio>

/* Testing Includes */
#include "test_fixture_gpio.hpp"


namespace Chimera::GPIO::Testing
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static BackendDriverType currentDriver;
  static Chimera::GPIO::Driver_sPtr testDriverObj;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void loadDriverType( const BackendDriverType type )
  {
    currentDriver = type;
  }
}  // namespace Chimera::GPIO::Testing

namespace Chimera::GPIO::Backend
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

    static Chimera::GPIO::Driver_sPtr getDriver( const Port port, const Pin pin )
    {
      if( !Testing::testDriverObj )
      {
        Testing::testDriverObj = std::make_shared<Chimera::GPIO::Driver>();
      }

      return Testing::testDriverObj;
    }
  }


  Chimera::Status_t registerDriver( Chimera::GPIO::Backend::DriverConfig &registry )
  {
    switch( Testing::currentDriver )
    {
      case Testing::DRIVER_STANDARD:
        registry.isSupported = true;
        registry.getDriver   = Standard::getDriver;
        registry.initialize  = Standard::initialize;
        registry.reset       = Standard::reset;
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
        registry.isSupported = true;
        registry.getDriver   = nullptr;
        registry.initialize  = nullptr;
        registry.reset       = nullptr;
        return Chimera::Status::OK;
        break;

      default:
        registry.isSupported = false;
        registry.getDriver   = nullptr;
        registry.initialize  = nullptr;
        registry.reset       = nullptr;
        return Chimera::Status::FAILED_INIT;
        break;
    }
  }
}  // namespace Chimera::GPIO::Backend

namespace Chimera::GPIO
{
  /*-------------------------------------------------------------------------------
  Driver Implementation
  -------------------------------------------------------------------------------*/
  Driver::Driver() : mDriver( nullptr )
  {
  }


  Driver::~Driver()
  {
  }


  /*-------------------------------------------------
  Interface: Hardware
  -------------------------------------------------*/
  Chimera::Status_t Driver::init( const Chimera::GPIO::PinInit &pinInit )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::init( const Chimera::GPIO::Port port, const uint8_t pin )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setMode( const Chimera::GPIO::Drive drive, const Chimera::GPIO::Pull pull )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::setState( const Chimera::GPIO::State state )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::getState( Chimera::GPIO::State &state )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::toggle()
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
}    // namespace Chimera::GPIO