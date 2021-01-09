/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_FRAMEWORK_FKCALCULATEPROT_H
#define FK_FRAMEWORK_FKCALCULATEPROT_H

#include "FkProtocol.h"

FK_CLASS FkCalculatePrt FK_EXTEND FkProtocol {
public:
    FkCalculatePrt();

    FkCalculatePrt(const FkCalculatePrt &o);

    virtual ~FkCalculatePrt();

public:
    float number = 0;
};


#endif //FK_FRAMEWORK_FKCALCULATEPROT_H