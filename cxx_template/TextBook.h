//
// Created by wjh on 22-10-7.
//

#ifndef CXX_TEMPLATE_TEXTBOOK_H
#define CXX_TEMPLATE_TEXTBOOK_H
#include"NLcomponent.h"

class TextBook:NLcomponent{
    ostream & print(std::ostream &s) const override;
};


#endif //CXX_TEMPLATE_TEXTBOOK_H
