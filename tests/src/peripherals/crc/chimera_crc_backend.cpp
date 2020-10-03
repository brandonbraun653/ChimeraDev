/********************************************************************************
 *  File Name:
 *    chimera_crc_backend.cpp
 *
 *  Description:
 *    Fake backend registration file for testing purposes
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/crc>

/* Testing Includes */
#include "test_fixture_crc.hpp"


namespace Chimera::CRC::Testing
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static BackendDriverType currentDriver;
  static Chimera::CRC::Driver_sPtr testDriverObj;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void loadDriverType( const BackendDriverType type )
  {
    currentDriver = type;
  }
}  // namespace Chimera::CRC::Testing

namespace Chimera::CRC::Backend
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

    static Chimera::CRC::Driver_sPtr getDriver( const Channel channel )
    {
      if( !Testing::testDriverObj )
      {
        Testing::testDriverObj = std::make_shared<Chimera::CRC::Driver>();
      }

      return Testing::testDriverObj;
    }
  }


  Chimera::Status_t registerDriver( Chimera::CRC::Backend::DriverConfig &registry )
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
}  // namespace Chimera::CRC::Backend

namespace Chimera::CRC
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
  Chimera::Status_t init( const uint32_t polynomial, const uint8_t crcWidth )
  {
    return Chimera::Status::OK;
  }


  uint32_t accumulate( const uint32_t *const buffer, const uint32_t length )
  {
    return 0;
  }


  uint32_t calculate( const uint32_t *const buffer, const uint32_t length )
  {
    return 0;
  }


  uint32_t getPolynomial()
  {
    return 0;
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
}    // namespace Chimera::CRC