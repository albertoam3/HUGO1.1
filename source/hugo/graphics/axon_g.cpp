//
// Created by alberto on 03/05/23.
//

#include "axon_g.h"
constexpr float pint=0.5f;

axon_g::axon_g(nsol::Axon* _ax): neurite_g( _ax)
  {
  
}
float axon_g::color(){
	return 1.0f;
}

