/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosio.system/eosio.system.hpp>
#include <eosiolib/privileged.hpp>
#include "power_score.cpp"
#include "resource_tracking.cpp"
#include "resource_score.cpp"

namespace eosiosystem
{

   void system_contract::updaterscore(const name owner)
   {
      require_auth(owner);
      updatepscore(owner);
      updaterescore(owner);
   } 

}
