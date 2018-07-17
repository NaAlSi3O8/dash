// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2017-2018 The AllGamesCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "uint256.h"
#include "arith_uint256.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>
#include <boost/assign/list_of.hpp>
#include <limits>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1522190273, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "The Times 30/Jun/2018 The great summer mortgage war";
    const CScript genesisOutputScript = CScript() << ParseHex("04621f7aea29e57493d33569f3cde075574b68a0016be44011097f51bab0c530407ef91647e570646c8bf061bae493abbb83635cbbcc631a986378c505450384e3") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 5040; // Note: actual number of blocks per calendar year with DGW v3 is ~200700 (for example 449750 - 249050)
        consensus.nMasternodePaymentsStartBlock = 2000; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 9999999999; // deactivated on initial launch
        consensus.nMasternodePaymentsIncreasePeriod = 9999999999; // deactivated on initial launch
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 9999999999; // Disabled
        consensus.nBudgetPaymentsCycleBlocks = 9999999999; // Disabled
        consensus.nBudgetPaymentsWindowBlocks = 9999999999; // Disabled
        consensus.nBudgetProposalEstablishingTime = 60*20*9999999999; // Disabled
        consensus.nSuperblockStartBlock = 99999999999; // Disabled
        consensus.nSuperblockCycle = 9999999999; // Disabled
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x000007d91d1254d60e2dd1ae580383070a4ddffa4c64c2eeb4a2f9ecc0414343");
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nZawyLwmaAveragingWindow = 65;
        consensus.nZawyLwmaAjustedWeight = 3927;

        consensus.nPowTargetTimespan = 30 * 60 * 2; // AllGamesCoin: 1 hour
        consensus.nPowTargetSpacing = 2 * 60; // AllGamesCoin: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.useDarkGravityWave = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1486252800; // Feb 5th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517788800; // Feb 5th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1508025600; // Oct 15th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1539561600; // Oct 15th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 3226; // 80% of 4032

        // The best chain should have at least this much work.
        //consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000100a308553b4863b755"); // 782700

        // By default assume that the signatures in ancestors of this block are valid.
        //consensus.defaultAssumeValid = uint256S("0x000000000000001c172f518793c3b9e83f202284615592f87fe3506ce964dcd4"); // 782700

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xbc;
        pchMessageStart[1] = 0x0d;
        pchMessageStart[2] = 0x6c;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("0463f1d71ae6731bba66d974fbc6f132525d541309b4f944dde855b6287e74468669499394c66e0741e5b6df0d1602a8f73cea195d334395799e958fff77ee9e32");
        nDefaultPort = 7208;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in allgamescoin
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1530678600, 432244, 0x1e0ffff0, 1, 50 * COIN);
        
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x00000475c48fb4eca6e368c5b72980055f66d36f95714bc01c139a53044880df"));
        assert(genesis.hashMerkleRoot == uint256S("0xb40d1b9a7e80e236b8afe6756b238766f567222b1214d1e25a6a054abc10856a"));

        vSeeds.push_back(CDNSSeedData("seed0_allgamescoin", "seed0.allgamescoin.org"));
        // vFixedSeeds.clear();
        // vSeeds.clear();

        // AllGamesCoin addresses start with 'A'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);
        // AllGamesCoin script addresses start with 'a'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,83);
        // AllGamesCoin private keys start with 't'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,23 + 128);
        // AllGamesCoin BIP32 pubkeys start with 'xpub' (AllGamesCoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // AllGamesCoin BIP32 prvkeys start with 'xprv' (AllGamesCoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // AllGamesCoin BIP44 coin type is '5'
        nExtCoinType = 5;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "04cdba5432c41747ab39695af8350ba5c3ba14b5c6a5c838e7d82a7a7f7f8ddbe55741fea8b3d1f83d9b713d95baaec2fc9c5b2988033efe6a5473f62de7ce1bb5";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x00000475c48fb4eca6e368c5b72980055f66d36f95714bc01c139a53044880df")),
            1530678600, // * UNIX timestamp of last checkpoint block
            0,    // * total number of transactions between genesis and last checkpoint
                  //   (the tx=... number in the SetBestChain debug.log lines)
            500   // * estimated number of transactions per day after checkpoint
        };
    }
};

static CMainParams mainParams;



/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 21600;
        consensus.nMasternodePaymentsStartBlock = 2000; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 9999;
        consensus.nMasternodePaymentsIncreasePeriod = 9999;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 9999999999; // Disabled
        consensus.nBudgetPaymentsCycleBlocks = 9999999999; // Disabled
        consensus.nBudgetPaymentsWindowBlocks = 9999999999; // Disabled
        consensus.nBudgetProposalEstablishingTime = 60*20*9999999999; // Disabled
        consensus.nSuperblockStartBlock = 99999999999; // Disabled
        consensus.nSuperblockCycle = 9999999999; // Disabled
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x0000047d24635e347be3aaaeb66c26be94901a2f962feccd4f95090191f208c1");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");

        consensus.nZawyLwmaAveragingWindow = 65;
        consensus.nZawyLwmaAjustedWeight = 3927;

        consensus.nPowTargetTimespan = 30 * 60 * 2; // AllGamesCoin: 1 hour
        consensus.nPowTargetSpacing = 2 * 60; // AllGamesCoin: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.useDarkGravityWave = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1506556800; // September 28th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1538092800; // September 28th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1505692800; // Sep 18th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1537228800; // Sep 18th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 50; // 50% of 100

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xbd;
        pchMessageStart[1] = 0x0a;
        pchMessageStart[2] = 0x6b;
        pchMessageStart[3] = 0xab;
        vAlertPubKey = ParseHex("04621f7aea29e57493d33569f3cde075574b68a0016be44011097f51bab0c530407ef91647e570646c8bf061bae493abbb83635cbbcc631a986378c505450384e3");
        nDefaultPort = 17208;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1530678600UL, 155965UL, 0x1e0ffff0, 1, 150000 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0x8efde483cc07f2076b04d42f05ee6a12f0b5c57a058bd9e56635ff9794f42f78"));
        //assert(genesis.hashMerkleRoot == uint256S("0xd5dec0980d7b84cc1c048eb8706afe68bbbdb07fdefab76de8d176dfcb858ae8"));

        //vSeeds.push_back(CDNSSeedData("testnet.allgamescoin.org", "testnet.seed.allgamescoin.org"));
        //vSeeds.push_back(CDNSSeedData("fixed-seeds.allgamescoin.org", "testnet.fixed-seeds.allgamescoin.org"));
        // vFixedSeeds.clear();
        // vSeeds.clear();

        // Testnet AllGamesCoin addresses start with 'A'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,24);
        // Testnet AllGamesCoin script addresses start with 'a'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,84);
        // Testnet AllGamesCoin private keys start with 't'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,24 + 128);
        // Testnet AllGamesCoin BIP32 pubkeys start with 'tpub' (AllGamesCoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet AllGamesCoin BIP32 prvkeys start with 'tprv' (AllGamesCoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Testnet AllGamesCoin BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04aeecccbab9f4c573afcbfb613a63d9efaf40429fe41fd0787174fc0fbf16be819d40d90f0d6e937cc3d0d6832d005d8897c3c3261dff074b0aa65e0616cb9350";

        // checkpointData = (CCheckpointData) {
        //     boost::assign::map_list_of
        //     (  0, uint256S("0x00000ba049e5c1f95474ea3fc62d5f1b1632a294c20c22fea701134a43cf3068"))
        //     ( 22520, uint256S("00000002c95eb91831bb7cb51ba6f5f39311b76280720f3aa02f8fafbeda0993")),
        //     1525413615, // * UNIX timestamp of last checkpoint block
        //     22520,       // * total number of transactions between genesis and last checkpoint
        //                 //   (the tx=... number in the SetBestChain debug.log lines)
        //     250         // * estimated number of transactions per day after checkpoint
        // };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 2;
        consensus.nMasternodePaymentsIncreaseBlock = 999;
        consensus.nMasternodePaymentsIncreasePeriod = 999;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nZawyLwmaAveragingWindow = 65;
        consensus.nZawyLwmaAjustedWeight = 3927;

        consensus.nPowTargetTimespan = 30 * 60 * 2; // AllGamesCoin: 1 hour
        consensus.nPowTargetSpacing = 2 * 60; // AllGamesCoin: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.useDarkGravityWave = false;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xf2;
        pchMessageStart[1] = 0xbc;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0xdf;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in allgamescoin
        nDelayGetHeadersTime = 0; // never delay GETHEADERS in regtests
        nDefaultPort = 17108;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1530678600, 1282268, 0x1e0ffff0, 1, 150000 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x000005ec6d48ac579d697448a82e93127b94403770629399cf561caa216a694b"));
        //assert(genesis.hashMerkleRoot == uint256S("0xd5dec0980d7b84cc1c048eb8706afe68bbbdb07fdefab76de8d176dfcb858ae8"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        //checkpointData = (CCheckpointData){
            //boost::assign::map_list_of
            //( 0, uint256S("0x000005ec6d48ac579d697448a82e93127b94403770629399cf561caa216a694b")),
            //1530678600,
            //0,
            //0
        //};
        // Regtest AllGamesCoin addresses start with 'A'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,25);
        // Regtest AllGamesCoin script addresses start with 'a'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        // Regtest AllGamesCoin private keys start with 't'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,25 + 128);
        // Regtest AllGamesCoin BIP32 pubkeys start with 'tpub' (AllGamesCoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest AllGamesCoin BIP32 prvkeys start with 'tprv' (AllGamesCoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Regtest AllGamesCoin BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
