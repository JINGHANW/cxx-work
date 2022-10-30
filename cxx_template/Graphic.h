//
// Created by wjh on 22-10-7.
//

#ifndef CXX_TEMPLATE_GRAPHIC_H
#define CXX_TEMPLATE_GRAPHIC_H

#include"NLcomponent.h"
class Graphic:NLcomponent {
    ostream & print(std::ostream &s) const override;
    Graphic(){

    }
};


#endif //CXX_TEMPLATE_GRAPHIC_H
