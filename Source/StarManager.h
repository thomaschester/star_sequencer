/*
  ==============================================================================

    StarManager.h
    Created: 29 Aug 2023 4:35:12pm
    Author:  thomas chester

  ==============================================================================
*/

#pragma once
#include "star.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>

class StarManager {
    
    float minBrightness = 1.f;
    float maxBrightness = 1.f;
    
    std::map<const std::string, std::shared_ptr<Star>> stars;
public:
    StarManager(){};
    ~StarManager(){};
    
    void addStar(std::string _data);
    void addStars(std::ifstream& _inputFile);
    
    const float getMaxBrightness() { return maxBrightness; };
    const float getMinBrightness() { return minBrightness; };
    
    const std::map<const std::string, std::shared_ptr<Star>>& getStars() { return stars; };
};
