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

/*
x : average resource usage ratio of account in 30 days

0%  x < 68.8% use formula y =-0.01+228e^(-9.9(1-x)) * (1-x)^2.
68.8%  x < 87.86% use formula y = 1.
87.86% x<100% use formula y= e^(-(x-0.8786)^2/0.01125))

*/

float calcusagew(float ratio) 
{
    if (0 < ratio && ratio < 0.688) 
    {
        return  -0.01 + 228 * exp(-9.9*(1- ratio)) * pow((1 - ratio),2);
    }
    else if (0.688 <= ratio && ratio < 0.8786) 
    {
        return 1;
    }
    
    return exp( - pow(ratio - 0.8786 , 2)/ 0.01125);
}

void system_contract::updaterescore(const name account)
{
    /*
       user monthly net_weight & cpu_weight calculate use moving average
    */
    // int64_t net_weight, cpu_weight;
    // get_monthly_resource_usage(account.value, &net_weight, &cpu_weight);
    // print("Monthly usage net_weight: ", net_weight, ", cpu_weight:", cpu_weight);

    // int64_t net_weight_limit, cpu_weight_limit, ram_bytes_limit;
    // get_resource_limits(account.value, &ram_bytes_limit, &net_weight_limit, &cpu_weight_limit);
    // print("Resource limit net_weight: ", net_weight, ", cpu_weight:", cpu_weight);

    // float   net_usage_ratio = (float) (net_weight/net_weight_limit);
    // int64_t net_score = calcusagew(net_usage_ratio) * net_weight;
    // print("Net Score: ", net_score);

    // float   cpu_usage_ratio = (float) (cpu_weight/cpu_weight_limit);
    // int64_t cpu_score =  calcusagew(cpu_usage_ratio) * cpu_weight;
    // print("Cpu Score: ", cpu_score);

    // auto it = _voters.find(account.value);
    // if (it != _voters.end()) {
    //      _voters.modify(it, account, [&](auto &rs) {
    //            rs.net_score = net_score;
    //            rs.cpu_score = cpu_score;
    //         });
    // }
}

} // namespace eosiosystem
