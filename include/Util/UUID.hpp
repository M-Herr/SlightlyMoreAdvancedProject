#pragma once
#ifndef __UUID_HH__
#define __UUID_HH__

#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstddef>
#include <bitset>
#include <random>
#include <map>
#include <array>
#include <memory>
#include <chrono>


namespace Utils
{   
  //TODO: Assuming whatever compiler is being used supports 128 bit integers.  Fix this.
  

  struct uuid {
    std::array<std::string, 5> hex;
    std::bitset<128> bits;

    std::string GetFormatted() 
    {
        return hex[0] + "-" + hex[1] + "-" + hex[2] + "-" + hex[3] + "-" + hex[4];
    }
  };    

  using uuid_t = uuid;
  struct VariantMsb {
    std::array<int, 3> msb_arragenemnt;
  };

  struct VersionMsb {
    std::array<int,4> msb_arragenemnt;
  };

  //Identified in Most Significant Bits in N position
  enum class UUIDVariant {
    Apollo, 
    OSF,
    COM_DCOM,
    Reserved,
    None
  };

  //Identified in Most Significant Bits in M position
  enum class UUIDVersion {
    V_ONE,
    V_TWO,
    V_THREE,
    V_FOUR,
    V_FIVE,
    NONE  
  };

    //Generate a UUID in 8-4-4-4-12 format
    //xxxxxxxx-xxxx-Mxxx-Nxxx-xxxxxxxxxxxx
    //M: UUIDVersion
    //N: UUIDVariant

  class UUIDGenerator {
    public:
    UUIDGenerator(UUIDVersion in_version, UUIDVariant in_variant);
    ~UUIDGenerator() = default;


    uuid Generate(); 
   

    static std::shared_ptr<UUIDGenerator> GetInstance(UUIDVersion in_version, UUIDVariant in_variant)
    {
        if(instance == nullptr)
        {
            instance = std::make_shared<UUIDGenerator>(in_version, in_variant);
        }

        return instance;
    }


    UUIDVersion GetVersion() const { return version;}
    UUIDVariant GetVariant() const { return variant;}


    private:
    UUIDVersion version;
    UUIDVariant variant;
    
    std::bitset<4> GetMBits();
    std::byte GetNByte();

    std::bitset<32> GetTimeLow();
    std::bitset<16> GetTimeMid();
    std::bitset<16> GetTimeHighWithVersion();
    std::bitset<48> GetLastBit();

    std::map<UUIDVersion, VersionMsb> version_to_bit;
    std::map<UUIDVariant, VariantMsb> variant_to_bit;

    static std::shared_ptr<UUIDGenerator> instance;
    
    std::bitset<32> timeLow;
    std::bitset<16> timeMid;
    std::bitset<16> timeHighWithVersion;
    std::bitset<48> lastBit;
    
    std::mt19937_64 gen64;
    std::uniform_int_distribution<> dist;
    
    uint64_t last_time_stamp;
    uint64_t current_time_stamp;
    uint64_t seed;
    unsigned long clock_sequence=0;
  };    


}

#endif //__UUID_HH__