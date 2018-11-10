/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosio.system/eosio.system.hpp>
#include <eosiolib/privileged.hpp>

#include "power_score.cpp"
#include "resource_score.cpp"

namespace eosiosystem
{

void system_contract::updaterscore(name owner)
{
   require_auth(owner);
   updatepwscore(owner);
   update_resource_score(owner);
}

}
