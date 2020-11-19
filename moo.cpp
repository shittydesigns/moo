#pragma once
#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <string>

using namespace eosio;
class [[eosio::contract]] whale : public contract {
  public:
      using contract::contract;
      [[eosio::action]]
      void payforcpu( name user ) {
      require_recipient( user );
}
      [[eosio::action]]
       void msg( name to, std::string message ) {
      require_recipient( to );
     }
      [[eosio::action]]
       void transfer( const name from,
                      const name to,
                      const asset quantity,
                      const std::string memo ) {
      require_auth(_self);
      require_recipient( from );
      require_recipient( to );
}

     [[eosio::action]]
      // Notes: Need to add permission @eosio.code to active or owner to exec this action!!!
      void claim(name to, eosio::asset quantity, std::string memo, name contract, unit32_t loops) {
      require_auth(_self);
      require_recipient( to );
      int i=0;
      for (i = 1; i <= loops; i++) {
      action{
           permission_level{get_self(), "active"_n},
           contract,
           "transfer"_n,
           std::make_tuple(get_self(), to, quantity, memo)
      }.send(); 
    }
    }
};
