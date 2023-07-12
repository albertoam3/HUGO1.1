//
// Created by alberto on 03/05/23.
//

#include "axon_g.h"

axon_g::axon_g(nsol::Axon* _ax): neurite_g( _ax)
  {
      put_color();

}
void axon_g::put_color(){
    color.x()=0.0f;
    color.y()=1.0f;
    color.z()=1.0f;
}

