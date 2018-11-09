/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosio.system/eosio.system.hpp>
#include <eosiolib/privileged.hpp>

namespace eosiosystem
{
using eosio::bytes;
using eosio::const_mem_fun;
using eosio::indexed_by;
using eosio::print;
using eosio::singleton;
using eosio::transaction;

void system_contract::updatep_score(account_name owner)
{
   require_auth(owner);
   update_powerscore(owner);
   update_resource_score(owner);
}

}
