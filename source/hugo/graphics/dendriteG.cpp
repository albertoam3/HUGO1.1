//
// Created by alberto on 03/05/23.
//

#include "dendriteG.h"


dendriteG::dendriteG(nsol::Dendrite* _dend): neuriteG(_dend)
  {
      putColor();
}
void dendriteG::putColor(){
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

void dendriteG::setTDendriteType(TDendriteType den) {
    _dendriteType=den;
}

