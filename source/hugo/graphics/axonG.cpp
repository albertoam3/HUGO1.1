//
// Created by alberto on 03/05/23.
//

#include "axonG.h"

axonG::axonG(nsol::Axon* _ax): neuriteG(_ax)
  {
      putColor();

}
void axonG::putColor(){
    color.x()=0.0f;
    color.y()=1.0f;
    color.z()=1.0f;
}

