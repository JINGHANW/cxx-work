//
// Created by wjh on 22-10-7.
//

#ifndef CXX_TEMPLATE_NLCOMPONENT_H
#define CXX_TEMPLATE_NLCOMPONENT_H

#include<ostream>
#include<string>
using namespace std;
class NLcomponent {
private:
    string data;
public:
 virtual ostream & print(ostream & s) const =0;
 NLcomponent(){
     Name ="NLcomponent";
 }
 string Name;
};


#endif //CXX_TEMPLATE_NLCOMPONENT_H
