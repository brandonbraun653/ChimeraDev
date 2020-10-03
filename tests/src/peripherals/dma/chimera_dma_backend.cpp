/********************************************************************************
 *  File Name:
 *    chimera_dma_backend.cpp
 *
 *  Description:
 *    Fake backend registration file for testing purposes
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/dma>

/* Testing Includes */
#include "test_fixture_dma.hpp"


namespace Chimera::DMA::Testing
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static BackendDriverType currentDriver;
  static Chimera::DMA::Driver_sPtr testDriverObj;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void loadDriverType( const BackendDriverType type )
  {
    currentDriver = type;
  }
}  // namespace Chimera::DMA::Testing

namespace Chimera::DMA::Backend
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

    static Chimera::DMA::Driver_sPtr getDriver( const Controller channel )
    {
      if( !Testing::testDriverObj )
      {
        Testing::testDriverObj = std::make_shared<Chimera::DMA::Driver>();
      }

      return Testing::testDriverObj;
    }
  }


  Chimera::Status_t registerDriver( Chimera::DMA::Backend::DriverConfig &registry )
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
}  // namespace Chimera::DMA::Backend

namespace Chimera::DMA
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
  Chimera::Status_t Driver::init()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::reset()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::start()
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::configure( const Init &config, const TCB &transfer, const size_t timeout, TransferHandle_t *const handle )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::abort( TransferHandle_t handle, const size_t timeout )
  {
    return Chimera::Status::OK;
  }


  Chimera::Status_t Driver::status( TransferHandle_t handle, const size_t timeout )
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
}    // namespace Chimera::DMA