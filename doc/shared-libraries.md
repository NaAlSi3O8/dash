Shared Libraries
================

## allgamescoinconsensus

The purpose of this library is to make the verification functionality that is critical to Allgamescoin's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `allgamescoinconsensus.h` located in  `src/script/allgamescoinconsensus.h`.

#### Version

`allgamescoinconsensus_version` returns an `unsigned int` with the the API version *(currently at an experimental `0`)*.

#### Script Validation

`allgamescoinconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `allgamescoinconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `allgamescoinconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `allgamescoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/allgamescoin/bips/blob/master/bip-0016.mediawiki)) subscripts
- `allgamescoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/allgamescoin/bips/blob/master/bip-0066.mediawiki)) compliance

##### Errors
- `allgamescoinconsensus_ERR_OK` - No errors with input parameters *(see the return value of `allgamescoinconsensus_verify_script` for the verification status)*
- `allgamescoinconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `allgamescoinconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `allgamescoinconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`

### Example Implementations
- [NAllgamescoin](https://github.com/NicolasDorier/NAllgamescoin/blob/master/NAllgamescoin/Script.cs#L814) (.NET Bindings)
- [node-liballgamescoinconsensus](https://github.com/bitpay/node-liballgamescoinconsensus) (Node.js Bindings)
- [java-liballgamescoinconsensus](https://github.com/dexX7/java-liballgamescoinconsensus) (Java Bindings)
- [allgamescoinconsensus-php](https://github.com/Bit-Wasp/allgamescoinconsensus-php) (PHP Bindings)
