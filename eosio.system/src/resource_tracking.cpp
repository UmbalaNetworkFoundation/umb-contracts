/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosio.system/eosio.system.hpp>

#include <eosiolib/privileged.hpp>

namespace eosiosystem
{

using eosio::const_mem_fun;
using eosio::indexed_by;
using eosio::print;
using eosio::singleton;
using eosio::transaction;

/**
    *  This method will return daily resouce usage of a given user
    * 
    *  @pre account 
    */
void system_contract::getdailyusage(const name account)
{  
//    int64_t net_weight, cpu_weight;
//    get_daily_resource_usage(account.value, &net_weight, &cpu_weight);
//    print("Daily net_weight: ", net_weight, ", cpu_weight:", cpu_weight);

}


/**
    *  This method will return daily resouce usage of a given user
    * 
    *  @pre account 
    */
// void system_contract::getmonthlyusage(const name account)
// {  
//    int64_t net_weight, cpu_weight;
//    get_monthly_resource_usage(account, &net_weight, &cpu_weight);
//    print("Monthly net_weight: ", net_weight, ", cpu_weight:", cpu_weight);
// }

} // namespace eosiosystem
