/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosio.system/eosio.system.hpp>
#include <cmath>

using namespace std;

namespace eosiosystem
{

using eosio::const_mem_fun;
using eosio::indexed_by;
using eosio::print;
using eosio::singleton;
using eosio::transaction;


/**
 * @private
 */
void system_contract::updatepscore(const name owner)
{
   auto it = _voters.find(owner.value);
   if (it != _voters.end())
   {
      if (it->last_update_time > 0 && now() - it->last_update_time >= seconds_per_day)
      {
         //TODO: recheck this
         // compute net and cpu change from unstake to stake
         // new_stake = unstake > 10? 0.1 * un_stake: unstake
         double converted_percent = 1 - pow(0.9, (now() - it->last_update_time) / seconds_per_day);
         int64_t converted_amount = (int64_t)ceil(it->unvested_power * converted_percent);
         if (converted_amount == 0)
         {
            //the remaining unvested token is too small, so convert them all
            converted_amount = it->unvested_power;
         }

         // update voting power
         {
            // update user table resource
            _gstate.total_powerscore += converted_amount;
            _voters.modify(it, owner, [&](auto &rs) {
               rs.power_score += converted_amount;
               rs.unvested_power -= converted_amount;
               rs.last_update_time = now();
               rs.update_score();
            });
            // asset total_update = stake_net_delta + stake_cpu_delta;
            eosio_assert(0 <= it->power_score, "powerscore for voting cannot be negative");
            eosio_assert(0 <= it->unvested_power, "unvested powerscore for voting cannot be negative");

            if (it->producers.size() || it->proxy)
            {
               update_votes(owner, it->proxy, it->producers, false);
            }
         }
      }
   }
}

void system_contract::changepscore(name account, asset delta_asset)
{
   auto delta = delta_asset.amount;
   auto it = _voters.find(account.value);
   if (delta < 0)
   {
      // unstake powerscore
      // unstake vested power token first. So user should not do this often
      // because it takes time to switch from unvested powertoken to vested token
      // (~30d)
      delta = -delta;
      int64_t unstake = delta;
      if (it != _voters.end())
      {
         eosio_assert(unstake <= it->power_score + it->unvested_power, "Attempt to unstake more than staked");
         int64_t sub = it->power_score > delta ? delta : it->power_score;
         _voters.modify(it, account, [&](auto &rs) {
            rs.power_score -= sub;
            rs.unvested_power -= (unstake - sub);
            // update score
            rs.update_score();
         });

         // update total powerscore
         _gstate.total_powerscore -= sub;
      }
   }
   else
   {
      //update unconverted tokens
      updatepscore(account);

      // spend new tokens for powerscore
      if (it != _voters.end())
      {
         _voters.modify(it, account, [&](auto &rs) {
            rs.unvested_power += delta;
         });
      }
      else
      {

         it = _voters.emplace(account, [&](auto &rs) {
            rs.owner = account;
            rs.unvested_power = delta;
            rs.last_update_time = now();
         });
      }
   }
}
} // namespace eosiosystem
