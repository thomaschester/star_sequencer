#pragma once

#include <JuceHeader.h>

//#include <algorithm>
//#include <cmath>
//#include <iostream>
#include <string>

class Star
{
    juce::Colour color;
    float markerSize = 0.0f;
    float bv = 0.0f;
    
    int rightAscensionHours;
    int rightAscensionMinutes;
    float rightAscensionSeconds;

    int declinationDegrees;
    int declinationMinutes;
    float declinationSeconds;
    
    // using Oakland, CA for now
    const float latitude = 37.804363f;
    const float longitude = -122.271111f;
    
    float degToRad(const float degrees);
    float hmsToRad(const float hours, const float minutes, const float seconds);
    float dmsToRad(const float degrees, const float minutes, const float seconds);

    void calculateStereographicProjection();
    float* bvToRGB();
    
    // Star stats
    std::string hipNumber;
    float meanBTMag;
    float x;
    float y;
    float z;
public:
    Star(const std::string& _data);
    ~Star(){};
    
    inline juce::Colour& getColor() { return color; };
    inline const std::string getHipNumber() { return hipNumber; };
    inline const float getMarkerSize() { return markerSize; };
    inline const float getBTMag() { return meanBTMag; };
    inline const float getXCoord() { return x; };
    inline const float getYCoord() { return y; };
    inline const float getZCoord() { return z; };
    
    void setColorAndSize(const float minBrightness, const float maxBrightness);
};


// g|   HIP|y|RAhms       DEdms      | Vmag|g|g|       RAdeg        DEdeg|f|    Plx|    pmRA|    pmDE|_RAdeg|_DEdeg| e_Plx|e_pmRA|e_pmDE|DE:RA|lx:RA|lx:DE|RA:RA|RA:DE|A:Plx|DE:RA|DE:DE|E:Plx|:pmRA| F1|   F2       BTmag|BTmag| VTmag|VTmag|g|   B-V|e_B-V|V| V-I|_V-I|I|g|  Hpmag|_Hpmag|pscat|mag|g|Hpmax|HPmin| Period|e|r|o|CCDM      |M|ys|mp|g|e|l|IP|eta|    rho|e_rho|  dHp|_dHp|y|t|s|    HD|BD        |CoD       |CPD       |)red|SpType      |_
// 0         10        20        30        40        50        60        70        80        90        100       110       120       130       140       150       160       170       180       190       200       210       220       230       240       250       260       270       280       290       300       310       320       330       340       350       360       370       380       390       400       410       420       430       440
// 012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
// H|   213| |00 02 40.05 +51 28 20.7| 7.70| |H|000.66686344 +51.47241278| |   7.80|   42.82|   -4.99|  0.56|  0.56|  0.95|  0.71|  0.58|-0.37| 0.06| 0.18| 0.16|-0.02| 0.13|-0.04| 0.04| 0.10|-0.31|  1|-0.99   213 8.969|0.009| 7.800|0.006| | 1.003|0.008|T|0.98|0.01|L| | 7.8636|0.0011|0.013|186| | 7.84| 7.89|       |C| | |          | |  | 1| | | |  |   |       |     |     |    |S| | |225021|B+50 4226 |          |          |0.98|G5          |S
