//
//  spectrum.hpp
//  fgt
//
//  Created by Albin Stigö on 04/12/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef spectrum_hpp
#define spectrum_hpp

#include <stdio.h>
#include "shader.hpp"
#include "vbo.hpp"

class Spectrum {
    Shader m_line;
    
    VBO *m_pow;
    VBO *m_bin;
    int m_N;
    
public:
    Spectrum(VBO *pow, VBO *bin, int N);
    ~Spectrum();
    void draw();
};


#endif /* spectrum_hpp */
