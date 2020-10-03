/********************************************************************************
 *  File Name:
 *    chimera_timer_backend.cpp
 *
 *  Description:
 *    Fake backend registration file for testing purposes
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/timer>

/* Testing Includes */
#include "test_fixture_timer.hpp"


namespace Chimera::Timer::Testing
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static BackendDriverType currentDriver;
  static Chimera::Timer::Driver_sPtr testDriverObj;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void loadDriverType( const BackendDriverType type )
  {
    currentDriver = type;
  }
}  // namespace Chimera::Timer::Testing

namespace Chimera::Timer::Backend
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


    size_t millis()
    {
      return 0;
    }


    size_t micros()
    {
      return 0;
    }


    void delayMilliseconds( const size_t val )
    {
    }


    void delayMicroseconds( const size_t val )
    {
    }


    static Chimera::Timer::Driver_sPtr getDriver( const Chimera::Timer::Peripheral peripheral )
    {
      if ( !Testing::testDriverObj )
      {
        Testing::testDriverObj = std::make_shared<Chimera::Timer::Driver>();
      }

      return Testing::testDriverObj;
    }
  }  // namespace Standard


  Chimera::Status_t registerDriver( Chimera::Timer::Backend::DriverConfig &registry )
  {
    switch ( Testing::currentDriver )
    {
      case Testing::DRIVER_STANDARD:
        registry.isSupported       = true;
        registry.getDriver         = Standard::getDriver;
        registry.initialize        = Standard::initialize;
        registry.reset             = Standard::reset;
        registry.delayMicroseconds = Standard::delayMicroseconds;
        registry.delayMilliseconds = Standard::delayMilliseconds;
        registry.micros            = Standard::micros;
        registry.millis            = Standard::millis;
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
        registry.isSupported       = true;
        registry.getDriver         = nullptr;
        registry.initialize        = nullptr;
        registry.reset             = nullptr;
        registry.delayMicroseconds = nullptr;
        registry.delayMilliseconds = nullptr;
        registry.micros            = nullptr;
        registry.millis            = nullptr;
        return Chimera::Status::OK;
        break;

      default:
        registry.isSupported       = false;
        registry.getDriver         = nullptr;
        registry.initialize        = nullptr;
        registry.reset             = nullptr;
        registry.delayMicroseconds = nullptr;
        registry.delayMilliseconds = nullptr;
        registry.micros            = nullptr;
        registry.millis            = nullptr;
        return Chimera::Status::FAILED_INIT;
        break;
    }
  }
}  // namespace Chimera::Timer::Backend

namespace Chimera::Timer
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
}  // namespace Chimera::Timer