/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.text;

import lysa.ui.window;
import lysa.ui.window_manager;

namespace lysa::ui {

    Text::Text(const std::string& text) :
        Widget{TEXT},
        text{text} {
        allowChildren  = false;
        drawBackground = false;
    }

    void Text::setText(const std::string & text) {
        this->text = text;
        if (window) {
            float w, h;
            getSize(w, h);
            setSize(w, h);
            if (parent) {
                parent->refresh();
            } else {
                refresh();
            }
        }
    }

    void Text::setFontScale(const float scale) {
        this->fontScale = scale;
        if (window) {
            float w, h;
            getSize(w, h);
            setSize(w, h);
            if (parent) {
                parent->refresh();
            } else {
                refresh();
            }
        }
    }

    void Text::setTextColor(const float4 &c) {
        textColor = c;
        if (window) {
            refresh();
        }
    }

    void Text::getSize(float &width, float &height) const {
        const auto& font = getFont();
        const auto scale = getFontScale();
        font->getSize(text, scale, width, height);
        if (window) {
            width /= static_cast<Window*>(window)->getAspectRatio();
        }
    }

    void Text::setSize(const float width, const float height) {
        if (!window) { return; }
        if (width == 0 && height == 0 && rect.width == 0 && rect.height == 0) {
            float w, h;
            getSize(w, h);
            Widget::setSize(w, h);
        } else {
            Widget::setSize(width, height);
        }
    }

    void Text::eventCreate() {
        if (all(textColor == float4{0.0f})) {
            textColor = static_cast<Window*>(window)->getTextColor();
        }
        getSize(rect.width, rect.height);
        Widget::eventCreate();
    }

}
