/********************************************************************************
 *  File Name:
 *    chimera_clock_backend.cpp
 *
 *  Description:
 *    Fake backend registration file for testing purposes
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/clock>

/* Testing Includes */
#include "test_fixture_clock.hpp"


namespace Chimera::Clock::Testing
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static BackendDriverType currentDriver;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void loadDriverType( const BackendDriverType type )
  {
    currentDriver = type;
  }
}  // namespace Chimera::Clock::Testing

namespace Chimera::Clock::Backend
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

    static Chimera::Status_t periphEnable( const Chimera::Peripheral::Type periph )
    {
      return Chimera::Status::OK;
    }

    static Chimera::Status_t periphDisable( const Chimera::Peripheral::Type periph )
    {
      return Chimera::Status::OK;
    }

    static Chimera::Status_t enableClock( const Chimera::Clock::Bus bus )
    {
      return Chimera::Status::OK;
    }

    static Chimera::Status_t disableClock( const Chimera::Clock::Bus bus )
    {
      return Chimera::Status::OK;
    }

    static bool isEnabled( const Chimera::Clock::Bus bus )
    {
      return true;
    }

    static size_t getFrequency( const Chimera::Clock::Bus bus )
    {
      return 84000000;
    }

    static Chimera::Status_t setFrequency( const Chimera::Clock::Bus bus, const size_t freq )
    {
      return Chimera::Status::OK;
    }
  }  // namespace Standard


  Chimera::Status_t registerDriver( Chimera::Clock::Backend::DriverConfig &registry )
  {
    switch( Testing::currentDriver )
    {
      case Testing::DRIVER_STANDARD:
        registry.isSupported   = true;
        registry.disableClock  = Standard::disableClock;
        registry.enableClock   = Standard::enableClock;
        registry.getFrequency  = Standard::getFrequency;
        registry.initialize    = Standard::initialize;
        registry.isEnabled     = Standard::isEnabled;
        registry.periphDisable = Standard::periphDisable;
        registry.periphEnable  = Standard::periphEnable;
        registry.setFrequency  = Standard::setFrequency;
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
        registry.disableClock  = nullptr;
        registry.enableClock   = nullptr;
        registry.getFrequency  = nullptr;
        registry.initialize    = nullptr;
        registry.isEnabled     = nullptr;
        registry.periphDisable = nullptr;
        registry.periphEnable  = nullptr;
        registry.setFrequency  = nullptr;
        return Chimera::Status::OK;
        break;

      default:
        registry.isSupported = false;
        registry.disableClock  = nullptr;
        registry.enableClock   = nullptr;
        registry.getFrequency  = nullptr;
        registry.initialize    = nullptr;
        registry.isEnabled     = nullptr;
        registry.periphDisable = nullptr;
        registry.periphEnable  = nullptr;
        registry.setFrequency  = nullptr;
        return Chimera::Status::FAILED_INIT;
        break;
    }
  }
}  // namespace Chimera::Clock::Backend
