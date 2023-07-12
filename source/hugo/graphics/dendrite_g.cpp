//
// Created by alberto on 03/05/23.
//

#include "dendrite_g.h"
constexpr float pint=0.7f;

dendrite_g::dendrite_g(nsol::Dendrite* _dend): neurite_g( _dend)
  {
      put_color();
}
void dendrite_g::put_color(){
    switch (_dendriteType) {
        case(TDendriteType::APICAL):
            color.x()=0.0f;
            color.y()=0.0f;
            color.z()=1.0f;
            break;
        case(TDendriteType::BASAL):
            color.x()=1.0f;
            color.y()=0.0f;
            color.z()=0.0f;
            break;
        default:
            color.x()=1.0f;
            color.y()=0.0f;
            color.z()=0.0f;
            break;
    }
}

void dendrite_g::setTDendriteType(TDendriteType den) {
    _dendriteType=den;
}

