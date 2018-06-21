// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ALLGAMESCOIN_QT_ALLGAMESCOINADDRESSVALIDATOR_H
#define ALLGAMESCOIN_QT_ALLGAMESCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class AllGamesCoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AllGamesCoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** AllGamesCoin address widget validator, checks for a valid allgamescoin address.
 */
class AllGamesCoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AllGamesCoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // ALLGAMESCOIN_QT_ALLGAMESCOINADDRESSVALIDATOR_H
