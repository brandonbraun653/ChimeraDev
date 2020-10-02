/********************************************************************************
 *  File Name:
 *    chimera_power_backend.cpp
 *
 *  Description:
 *    Fake backend registration file for testing purposes
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/power>

/* Testing Includes */
#include "test_fixture_power.hpp"


namespace Chimera::Power::Testing
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
}  // namespace Chimera::Power::Testing

namespace Chimera::Power::Backend
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  namespace Standard
  {
    Chimera::Status_t initialize()
    {
      return Chimera::Status::OK;
    }


    Chimera::Status_t reset()
    {
      return Chimera::Status::OK;
    }


    Chimera::Status_t periphEnable( const Chimera::Peripheral::Type periph )
    {
      return Chimera::Status::OK;
    }


    Chimera::Status_t periphDisable( const Chimera::Peripheral::Type periph )
    {
      return Chimera::Status::OK;
    }


    Chimera::Status_t setPowerState( const Chimera::Power::State state )
    {
      return Chimera::Status::OK;
    }


    Chimera::Power::State getPowerState( const Chimera::Peripheral::Type periph )
    {
      return Chimera::Power::State::ON;
    }


  }


  Chimera::Status_t registerDriver( Chimera::Power::Backend::DriverConfig &registry )
  {
    switch( Testing::currentDriver )
    {
      case Testing::DRIVER_STANDARD:
        registry.isSupported   = true;
        registry.initialize    = Standard::initialize;
        registry.reset         = Standard::reset;
        registry.getPowerState = Standard::getPowerState;
        registry.periphDisable = Standard::periphDisable;
        registry.periphEnable  = Standard::periphEnable;
        registry.setPowerState = Standard::setPowerState;
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
        registry.initialize    = nullptr;
        registry.reset         = nullptr;
        registry.getPowerState = nullptr;
        registry.periphDisable = nullptr;
        registry.periphEnable  = nullptr;
        registry.setPowerState = nullptr;
        return Chimera::Status::OK;
        break;

      default:
        registry.isSupported = false;
        registry.initialize    = nullptr;
        registry.reset         = nullptr;
        registry.getPowerState = nullptr;
        registry.periphDisable = nullptr;
        registry.periphEnable  = nullptr;
        registry.setPowerState = nullptr;
        return Chimera::Status::FAILED_INIT;
        break;
    }
  }
}  // namespace Chimera::Power::Backend
