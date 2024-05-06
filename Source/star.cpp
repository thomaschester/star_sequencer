#include "star.h"
#include <algorithm>
#include <cmath>
#include <iostream>

Star::Star(const std::string& _data)
{
    hipNumber = _data.substr(0, 1) + _data.substr(2, 6);
    hipNumber.erase(std::remove_if(hipNumber.begin(), hipNumber.end(), isspace), hipNumber.end());

    rightAscensionHours = std::stoi(_data.substr(11, 2));
    rightAscensionMinutes = std::stoi(_data.substr(14, 2));
    rightAscensionSeconds = std::stof(_data.substr(17, 5));

    declinationDegrees = std::stoi(_data.substr(23, 3));
    declinationMinutes = std::stoi(_data.substr(27, 2));
    declinationSeconds = std::stof(_data.substr(30, 4));

    meanBTMag = std::stof(_data.substr(209, 6));
    bv = std::stof(_data.substr(237, 5));
    
    calculateStereographicProjection();
    
}

float* Star::bvToRGB() {
    static float RGB[3];
    float t;
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    if (bv < -0.4)
        bv = -0.4;
    if (bv > 2.0)
        bv= 2.0;
    if ((bv >= -0.40) && (bv < 0.00)) {
        t = (bv + 0.40) / (0.00 + 0.40);
        r = 0.61 + (0.11 * t) + (0.1 * t * t);
    }
    else if ((bv >= 0.00) && (bv < 0.40)) {
        t = (bv - 0.00) / (0.40 - 0.00);
        r = 0.83 + (0.17 * t);
    }
    else if ((bv>= 0.40)&&(bv<2.10)) {
        t = (bv - 0.40) / (2.10 - 0.40);
        r = 1.00;
    }
    if ((bv>=-0.40)&&(bv<0.00)) {
        t=(bv+0.40)/(0.00+0.40);
        g=0.70+(0.07*t)+(0.1*t*t);
    }
    else if ((bv>= 0.00)&&(bv<0.40)) { t=(bv-0.00)/(0.40-0.00); g=0.87+(0.11*t)          ;
        
    }
    else if ((bv>= 0.40)&&(bv<1.60)) { t=(bv-0.40)/(1.60-0.40); g=0.98-(0.16*t)          ;
        
    }
    else if ((bv>= 1.60)&&(bv<2.00)) { t=(bv-1.60)/(2.00-1.60); g=0.82         -(0.5*t*t);
        
    }
         if ((bv>=-0.40)&&(bv<0.40)) { t=(bv+0.40)/(0.40+0.40); b=1.00                   ;
             
         }
    else if ((bv>= 0.40)&&(bv<1.50)) { t=(bv-0.40)/(1.50-0.40); b=1.00-(0.47*t)+(0.1*t*t);
        
    }
    else if ((bv>= 1.50)&&(bv<1.94)) { t=(bv-1.50)/(1.94-1.50); b=0.63         -(0.6*t*t);
        
    }
    
//    std::cout << "r: " << r << " g: " << g << " b: " << b << std::endl;
    
    RGB[0] = r;
    RGB[1] = g;
    RGB[2] = b;
    
    return RGB;
}

float Star::degToRad(const float degrees) {
    return degrees * M_PI / 180.0;
}

void Star::calculateStereographicProjection() {
    
    float phi = degToRad(90.0 - (declinationDegrees + declinationMinutes / 60.0f + declinationSeconds / 3600.0f));
    float theta = degToRad(15.0f * (rightAscensionHours + rightAscensionMinutes / 60.0f + rightAscensionSeconds / 3600.0f));
    
    x = sin(phi) * cos(theta);
    y = sin(phi) * sin(theta);
    z = cos(phi);

//    std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
//    std::cout << ", z: " << z << std::endl;
}

void Star::setColorAndSize(const float minBrightness, const float maxBrightness) {
    
    float* rgbArray = bvToRGB();
    
    color = color.fromFloatRGBA(rgbArray[0], rgbArray[1], rgbArray[2], 1.0f);
    
    float decayFactor = 0.9f;
    markerSize = 5.f * exp(-decayFactor * (meanBTMag - minBrightness) / (maxBrightness - minBrightness)) + 1.f;
    
//    std::cout << "marker size: " << markerSize << std::endl;
}
