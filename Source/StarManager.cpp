/*
  ==============================================================================

    StarManager.cpp
    Created: 29 Aug 2023 4:35:12pm
    Author:  thomas chester

  ==============================================================================
*/

#include "StarManager.h"

void StarManager::addStar(std::string _data) {
    // Some fields contain no brightness
    if (_data.substr(209, 6).find_first_not_of(' ') == std::string::npos) { return; }
    
    // 6.0 BTmean is the threshold of visibility to the human eye
    if (std::stof(_data.substr(209, 6)) <= 6.f) {
        std::shared_ptr<Star> star = std::make_shared<Star>(_data);
        stars.insert({star->getHipNumber(), star});
        
        auto brightness = star->getBTMag();
        if (brightness < minBrightness) {
            minBrightness = brightness;
        }
        else if (brightness > maxBrightness) {
            maxBrightness = brightness;
        }
    }
    
}

void StarManager::addStars(std::ifstream& _inputFile) {
    std::string line;
    while (std::getline(_inputFile, line)) {
        if (line.substr(0, 1) == "H")
        {
            addStar(line);
        }
    }
    
    std::cout << minBrightness << "min" << std::endl;
    std::cout << maxBrightness << "max" << std::endl;
    
    for (auto& [name, star] : stars) {
        star->setColorAndSize(minBrightness, maxBrightness);
    }
}
