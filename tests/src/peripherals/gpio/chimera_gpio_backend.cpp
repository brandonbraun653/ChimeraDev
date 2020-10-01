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
      return nullptr;
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

      default:
        registry.isSupported = false;
        registry.getDriver   = nullptr;
        registry.initialize  = nullptr;
        registry.reset       = nullptr;
        return Chimera::Status::FAIL;
        break;
    }
  }
}  // namespace Chimera::GPIO::Backend
