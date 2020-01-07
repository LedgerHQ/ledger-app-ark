
////////////////////////////////////////////////////////////////////////////////

// The Following are only examples and places where this code could be implemented.
//  It is not final or guaranteed working.
//  This should only serve as a reference for implementing.

////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
*   Ark Wallet
*   (c) 2017 Ledger
*   (c) ARK Ecosystem
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#include "transactions/types/type_4.h"

#include <stdint.h>

#include <os.h>

#include "constants.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// MultiSignature Registration (Type 4)
//
// @param MultiSignature *muSig: The MultiSignature (Type 4) Asset.
// @param uint8_t *buffer: The serialized buffer beginning at the Assets offset.
// @param uint32_t length: The Asset Length.
//
// ---
// Internals:
//
// Minimum Participants - 1 Byte:
// - multiSig->min = buffer[0];
//
// Key Count
// - multiSig->count = buffer[1];
//
// PublicKeys - 33N Bytes
// - bytecpy(&multiSig->keys[0], &buffer[2], multiSig->count);
//
// ---
bool deserializeMultiSignature(MultiSignatureAsset *multiSig,
                                       const uint8_t *buffer,
                                       const uint32_t length) {
    if ((length % 34U) != 0) {
        return false;
    }

    multiSig->min = buffer[0];
    multiSig->count = buffer[1];
    bytecpy(&multiSig->keys[0], &buffer[2], multiSig->count);

    return true;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

static bool internalDeserializeAsset(Transaction *transaction,
                                             const uint8_t *buffer,
                                             const uint32_t length) {
/////////
    case TRANSACTION_TYPE_MULTI_SIGNATURE:
        status = deserializeMultiSignature(&transaction->asset.multiSignature,
                                            &buffer[assetOffset],
                                            assetSize);
        break;
/////////
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void setDisplayMultiSignature(const Transaction *transaction) {
    bytecpy((char *)displayCtx.operation, "MultiSignature", 15);
    bytecpy((char *)displayCtx.title[0], "Key Count", 10);
    bytecpy((char *)displayCtx.title[1], "Fees", 5);

    // Key Count
    printAmount(transaction->asset.multiSignature.count,
                (uint8_t *)displayCtx.text[0], sizeof(displayCtx.text[0]),
                "", 0, 0);

    // Fee
    printAmount(transaction->fee,
                (uint8_t *)displayCtx.text[1], sizeof(displayCtx.text[1]),
                TOKEN_NAME, TOKEN_NAME_SIZE, TOKEN_DECIMALS);
}

////////////////////////////////////////////////////////////////////////////////

void setDisplay(const Transaction *transaction) {
/////////
    case TRANSACTION_TYPE_MULTI_SIGNATURE:
        setDisplayMultiSignature(transaction);
        setDisplaySteps(2U);
        break;
/////////
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
