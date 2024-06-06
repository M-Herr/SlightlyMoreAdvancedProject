#include "Util/UUID.hpp"
#include "Core/Logging.hpp"

namespace Utils
{

    std::shared_ptr<UUIDGenerator> UUIDGenerator::instance = nullptr;

    UUIDGenerator::UUIDGenerator(UUIDVersion in_version, UUIDVariant in_variant)
    : version(in_version), variant(in_variant)
    {
        version_to_bit = {
            {UUIDVersion::V_ONE, {0, 0, 0, 1}},
            {UUIDVersion::V_TWO, {0, 0, 1, 0}},
            {UUIDVersion::V_THREE, {0, 0, 1, 1}},
            {UUIDVersion::V_FOUR, {0, 1, 0, 0}},
            {UUIDVersion::V_FIVE, {0, 1, 0, 1}}
        };

        variant_to_bit = {
            {UUIDVariant::Apollo, {0, -1, -1}},
            {UUIDVariant::OSF, {1, 0, -1}},
            {UUIDVariant::COM_DCOM, {1, 1, 0}},
            {UUIDVariant::Reserved, {1, 1, 1}}
        };

        std::random_device rd;
        seed = rd();
        gen64 = std::mt19937_64(seed);
        dist = std::uniform_int_distribution(0,1);
    }


    //This get's combined with some more bits from the clock
    std::bitset<4> UUIDGenerator::GetMBits() 
    {   
        const int num_bits_reserved = 4;
        std::array<int, num_bits_reserved> msb = version_to_bit[version].msb_arragenemnt;

        std::bitset<4> m_bitset;
        //MSB left to right.  Copy in first 4
        for(size_t i = 0; i < num_bits_reserved; i++)
        {
            m_bitset[i] = msb[i];
        }

        return m_bitset;
    }


    std::byte UUIDGenerator::GetNByte()
    {

        if(clock_sequence = 0)
        {
            std::bitset<4> clock_sequence_bits;

            for(size_t i = 0; i < 4; i++)
            {
            clock_sequence_bits[i] =  dist(gen64);
            }

            clock_sequence = clock_sequence_bits.to_ulong();
        }
        else 
        {
            clock_sequence += 1;   
        }
        

        const int num_bits_reserved = 3;
        std::array<int, num_bits_reserved> msb = variant_to_bit[variant].msb_arragenemnt;
        
        std::bitset<8> m_bitset;
        //MSB left to right.  Copy in first 4

        //bits to set
        int bits_to_set = 0;
        for(size_t i = 0; i < num_bits_reserved; i++)
        {
            if(msb[i] >= 0)
            {
                m_bitset[i] = msb[i];
            }
            else 
            {
                bits_to_set++; // "Clock sequence"
            }
        
        }

        const size_t start_index = num_bits_reserved - bits_to_set;

        for(size_t i = start_index; i < 8; i++)
        {
            m_bitset[i] = dist(gen64);
        }

        std::byte m_byte = static_cast<std::byte>(m_bitset.to_ulong());
        return m_byte;
    }

    std::bitset<32> UUIDGenerator::GetTimeLow()
    {
        uint64_t now = std::chrono::system_clock::now().time_since_epoch().count();
        return std::bitset<32>(now & 0xFFFFFFFF);
    }
    
    std::bitset<16> UUIDGenerator::GetTimeMid() 
    {
        uint64_t now = std::chrono::system_clock::now().time_since_epoch().count();
        //Shift now to the right 32 bits (we already caputured those bits in GetTimeLow()) and
        //then & by 0xFFF, which is 111111111111 in binary which will capture 12 bits from the middle of now
        return std::bitset<16>((now >> 32) & 0xFFF); 
    }

    std::bitset<16> UUIDGenerator::GetTimeHighWithVersion()
    {
        uint64_t now = std::chrono::system_clock::now().time_since_epoch().count();
        //We already capture 32 + 16 = 48 bits so shift 48 over and capture 12
        // with 0x0FFF, which as 4 leading zeros
        std::bitset<16> time_high((now >> 48) & 0x0FF);
        std::bitset<4> versionBits = GetMBits();

        for(int i = 0 ; i < 4; i++)
        {
            time_high[i + 12] = versionBits[i];
        }

        return time_high;
    }

    std::bitset<48> UUIDGenerator::GetLastBit()
    {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis(0, 0xFFFFFFFFFFFF);
        return std::bitset<48>(dis(gen));
    }


    uuid UUIDGenerator::Generate()
    {   
        
        auto uint64_t = std::chrono::system_clock::now().time_since_epoch().count();

        timeLow = GetTimeLow();
        timeMid = GetTimeMid();
        timeHighWithVersion = GetTimeHighWithVersion();
        lastBit = GetLastBit();

        //4 hex characters(2 Bytes)
        auto n_byte = GetNByte(); //Variant

    
        uuid new_uuid;

        for(size_t i = 0; i < timeLow.size(); i++)
        {
            new_uuid.bits[i] = timeLow[i];
        }

        for(size_t i = timeLow.size(); i < timeMid.size() +  timeLow.size(); i++)
        {
            new_uuid.bits[i] = timeMid[i - timeLow.size()];
        }

        for(size_t i = timeMid.size() + timeLow.size(); i <  timeMid.size() + timeLow.size() + timeHighWithVersion.size(); i++)
        {
            new_uuid.bits[i] = timeMid[i -timeMid.size() + timeLow.size()];
        }

        uint8_t n_byte_int = std::to_integer<uint8_t>(n_byte);
        std::bitset<8> n_byte_bitset(n_byte_int);

        for(size_t i = timeMid.size() + timeLow.size() + timeHighWithVersion.size(); i < timeMid.size() + timeLow.size() + timeHighWithVersion.size() + n_byte_bitset.size(); i++)
        {
            new_uuid.bits[i] = n_byte_bitset[i - timeMid.size() + timeLow.size() + timeHighWithVersion.size()];
        }

        for(size_t i = new_uuid.bits.size(); i > new_uuid.bits.size() - lastBit.size(); i--)
        {
            new_uuid.bits[i] = lastBit[i];
        }

        std::stringstream ss;

        unsigned long value_1 = timeLow.to_ulong();
        ss << std::hex << std::setw(8) << std::setfill('0') << value_1;

        unsigned long value_2 = timeMid.to_ulong();
        ss << std::hex << std::setw(4) << std::setfill('0') << value_2;

        unsigned long value_3 = timeHighWithVersion.to_ulong();
        ss << std::hex << std::setw(4) << std::setfill('0') << value_3;

        unsigned long value_4 = static_cast<unsigned long>(n_byte);
        ss << std::hex << std::setw(4) << std::setfill('0') << value_4;

        unsigned long value_5 = lastBit.to_ulong();
        ss << std::hex << std::setw(4) << std::setfill('0') << value_5;

        std::string uuid_str = ss.str();

        new_uuid.hex[0] = uuid_str.substr(0, 8);
        new_uuid.hex[1] = uuid_str.substr(8, 4);
        new_uuid.hex[2] = uuid_str.substr(12, 4);
        new_uuid.hex[3] = uuid_str.substr(16, 4);
        new_uuid.hex[4] = uuid_str.substr(20, 12);

        return new_uuid;
    }

}