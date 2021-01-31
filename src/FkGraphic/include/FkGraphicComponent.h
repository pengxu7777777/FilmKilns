/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef FK_GRAPHIC_FKGRAPHICCOMPONENT_H
#define FK_GRAPHIC_FKGRAPHICCOMPONENT_H

#include "FkObject.h"

FK_CLASS FkGraphicComponent FK_EXTEND FkObject {
public:
    FkGraphicComponent();

    FkGraphicComponent(const FkGraphicComponent &o);

    virtual ~FkGraphicComponent();
};


#endif //FK_GRAPHIC_FKGRAPHICCOMPONENT_H