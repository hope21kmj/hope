// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa8;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x4f;
        pchMessageStart[3] = 0xf7;
        vAlertPubKey = ParseHex("048df19e4703ea1453953eb7f205114388089666fc7096406261c449c1b5416d1e2186faeeead72ec85c0ce5138b8c817cd9bc7cff4cd45e247505a310fbddff28");
        nDefaultPort = 15722;
        nRPCPort = 15733;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        // Genesis info:
        //Found Genesis, Nonce: 45707, Hash: 000007d69ba0f79b4823effb06b08663e2e4c51ed03aaeb547e2e0b83fd37b73
        //Gensis Hash Merkle: 73513debc549137a47f2afb73173a2d2b4b0c13f57a57387ae3849a928e1e08d
        const char* pszTimestamp = "On january 17,2019 Hopecoin was created.";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1548587400, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1548587400;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 895940;

        hashGenesisBlock = genesis.GetHash();
// Genesis start//
/*
        hashGenesisBlock = uint256("0x0");
        if (true && genesis.GetHash() != hashGenesisBlock)
        {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                    LogPrintf("recalculating params for mainnet.\n");
                    LogPrintf("old TestNet genesis nonce: %d\n", genesis.nNonce);
                    LogPrintf("old TestNet genesis hash:  %s\n", hashGenesisBlock.ToString().c_str());
                    // deliberately empty for loop finds nonce value.

                    for(genesis.nNonce == 0; genesis.GetHash() > hashTarget; genesis.nNonce++){ }

                    LogPrintf(" genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
                    LogPrintf(" genesis nonce: %d\n", genesis.nNonce);
                    LogPrintf(" genesis hash: %s\n", genesis.GetHash().ToString().c_str());
        }
*/
// Genesis end  //

        assert(hashGenesisBlock == uint256("0x00000c772518889a82ac9032de27af413f5e720faca91e3e9543629ac881a8c5"));
        assert(genesis.hashMerkleRoot == uint256("0x672a17258a9f34644424e09103fd2eec491b94174bf92411d0f78d6da1ff4887"));

//        vSeeds.push_back(CDNSSeedData("dnsseed-eu", "dnsseed.oizopower.nl"));
//        vSeeds.push_back(CDNSSeedData("dnsseed-cn", "dnsseed-cn.hopecoin.info"));
//       vSeeds.push_back(CDNSSeedData("seed1", "seed1.oizopower.nl"));
//        vSeeds.push_back(CDNSSeedData("seed3", "seed3.oizopower.nl"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 41);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 135);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 73+128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0x7F)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0x94)(0xED).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 200;
        
        //Registered Message PubKey
        mapBroadcastMessPubKey.insert(pair<std::string,vector<unsigned char> >("Ray",   ParseHex("048df19e4703ea1453953eb7f205114388089666fc7096406261c449c1b5416d1e2186faeeead72ec85c0ce5138b8c817cd9bc7cff4cd45e247505a310fbddff28")));
 //       mapBroadcastMessPubKey.insert(pair<std::string,vector<unsigned char> >("Lizhi", ParseHex("04cd377cb31be7b1b4484f8b42e9ca3b748fa9fb3ab1f877ecb9907bfd8623cdaba04c15db1ac897bc384a355e3e099bd78696b3ff03e7955ab43bf3c30bb6e7ec")));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xdf;
        pchMessageStart[3] = 0xe7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("049eed0b2ac81317d8e04af43ab4dd46b848b8e236ec62a32d66c98d8d69554a9b21978b8c78635ef5c922e66b5d7f4bf67eaf858027c2084fc6357108ae756fb6");
        nDefaultPort = 15704;
        nRPCPort = 15705;
        strDataDir = "testnet";


        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2199;
        genesis.nTime    = 1548586787;
        hashGenesisBlock = genesis.GetHash();

//genesisblock-testnet start
/*
        hashGenesisBlock = uint256("0x01");
        if (true && genesis.GetHash() != hashGenesisBlock)
        {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                    LogPrintf("recalculating params for mainnet.\n");
                    LogPrintf("old TestNet genesis nonce: %d\n", genesis.nNonce);
                    LogPrintf("old TestNet genesis hash:  %s\n", hashGenesisBlock.ToString().c_str());
                    // deliberately empty for loop finds nonce value.

                    for(genesis.nNonce == 0; genesis.GetHash() > hashTarget; genesis.nNonce++){ }

                    LogPrintf("new TestNet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString().c_str());
                    LogPrintf("new TestNet genesis nonce: %d\n", genesis.nNonce);
                    LogPrintf("new TestNet genesis hash: %s\n", genesis.GetHash().ToString().c_str());
        }
*/
//genesisblock-testnet end

       assert(hashGenesisBlock == uint256("00002bb1de674fcd8da1a6505733b76cdd6668edacbc0b71bb62a5a1c9d3439d"));

        vFixedSeeds.clear();
        vSeeds.clear();
//        vSeeds.push_back(CDNSSeedData("172.104.117.39", "172.104.117.39"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 100);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 135);

        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 200;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x7c;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xde;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1548586717;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 15706;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x523dda6d336047722cbaf1c5dce622298af791bac21b33bf6e2d5048b2a13e3d"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}


