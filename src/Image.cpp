/*
 * Copyright (c) 2024-2025 Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.image;

import lysa.ui.window;
import lysa.ui.window_manager;

namespace lysa::ui {

    Image::Image(const lysa::Image& image, const bool autoSize, const bool fixedSize) :
        Widget{IMAGE},
        autoSize{autoSize},
        fixedSize{fixedSize} {
        setImage(image);
    }

    Image::Image(const bool autoSize, const bool fixedSize) :
        Widget{IMAGE},
        autoSize{autoSize},
        fixedSize{fixedSize} {
    }

    void Image::_setSize(const float width, const float height) {
        if (autoSize) { return; }
        if ((fixedSize || (width == 0 && height == 0)) && rect.width == 0 && rect.height == 0) {
            const auto ratio = static_cast<WindowManager*>(static_cast<Window*>(window)->_getWindowManager())->getRenderer().getAspectRatio();
            Widget::_setSize(std::round(width / ratio), height);
        } else if (!fixedSize) {
            Widget::_setSize(width, height);
        }
    }

    void Image::autoResize() {
        if (window) {
            const auto ratio = static_cast<WindowManager*>(static_cast<Window*>(window)->_getWindowManager())->getRenderer().getAspectRatio();
            Widget::_setSize(std::round(image->getWidth() / ratio), static_cast<float>(image->getHeight()));
        }
    }

    void Image::eventCreate() {
        if (image && autoSize) {
            autoResize();
        }
        Widget::eventCreate();
    }

    void Image::setColor(const float4 &color) {
        this->color = color;
        refresh();
    }

    void Image::setAutoSize(const bool autoSize) {
        if (autoSize == this->autoSize) {
            return;
        }
        this->autoSize = autoSize;
        if (autoSize && image) {
            this->autoResize();
        }
    }

    void Image::setImage(const std::string& uri) {
        setImage(ctx().res.get<ImageManager>().load(uri));
    }

    void Image::setImage(const lysa::Image& image) {
        if (this->image == &image) {
            return;
        }
        this->image = &image;
        if (this->image) {
            if (autoSize) {
                autoResize();
            } else if (!fixedSize) {
                refresh();
            }
        }
    }

}
