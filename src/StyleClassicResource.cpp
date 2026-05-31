/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.style_classic_resource;

import lysa.utils;

namespace lysa::ui {

    StyleClassicResource::StyleClassicResource(const std::string &resource) :
        UIResource{resource} {
        splitResString(resource);
    }
    void StyleClassicResource::splitResString(const std::string &resource) {
        for (const auto &token : split(resource, ';')) {
            const auto pos = token.find('=');
            if (pos == std::string::npos) { continue; }
            const auto key = token.substr(0, pos);
            const std::string value{token.substr(pos + 1)};
            if (value.empty()) { continue; }
            if (key == "width") {
                width = stof(value);
            } else if (key == "height") {
                height = stof(value);
            } else if (key == "style") {
                if (value == "RAISED") {
                    style = RAISED;
                } else if (value == "LOWERED") {
                    style = LOWERED;
                } else if (value == "FLAT") {
                    style = FLAT;
                }
            } else if (key == "color") {
                const auto components = split(value, ',');
                if (components.size() >= 4) {
                    color = float4{
                        stof(std::string{components[0]}),
                        stof(std::string{components[1]}),
                        stof(std::string{components[2]}),
                        stof(std::string{components[3]})};
                    customColor = true;
                }
            }
        }
    }

}