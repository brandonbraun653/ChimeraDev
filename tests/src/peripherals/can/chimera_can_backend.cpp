/********************************************************************************
 *  File Name:
 *    chimera_can_backend.cpp
 *
 *  Description:
 *    Fake backend registration file for testing purposes
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/can>

/* Testing Includes */
#include "test_fixture_can.hpp"


namespace Chimera::CAN::Testing
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static BackendDriverType currentDriver;
  static Chimera::CAN::Driver_sPtr testDriverObj;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void loadDriverType( const BackendDriverType type )
  {
    currentDriver = type;
  }
}  // namespace Chimera::CAN::Testing

namespace Chimera::CAN::Backend
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

    static Chimera::CAN::Driver_sPtr getDriver( const Channel channel )
    {
      if( !Testing::testDriverObj )
      {
        Testing::testDriverObj = std::make_shared<Chimera::CAN::Driver>();
      }

      return Testing::testDriverObj;
    }
  }


  Chimera::Status_t registerDriver( Chimera::CAN::Backend::DriverConfig &registry )
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
}  // namespace Chimera::CAN::Backend

namespace Chimera::CAN
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
  Chimera::Status_t open( const Channel channel )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t open( const Channel channel, const size_t txElements, const size_t rxElements )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t open( const Channel channel, BasicFrame *txBuffer, const size_t txElements, BasicFrame *rxBuffer, const size_t rxElements )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t close()
  {
    return Chimera::Status::OK;
  }


  CANStatus getStatus()
  {
    return Chimera::CAN::CANStatus();
  }


  Chimera::Status_t send( const BasicFrame &frame )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t receive( BasicFrame &frame, const size_t timeout )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t subscribe( const Identifier_t id, FrameCallback_t callback )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t unsubscribe( const Identifier_t id )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t filter( const Filter *const list, const size_t size )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t flush( BufferType buffer )
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
}    // namespace Chimera::CAN