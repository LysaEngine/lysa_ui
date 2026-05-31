/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.image;

import lysa.context;
import lysa.math;
import lysa.rect;
import lysa.ui.widget;
import lysa.resources.image;

export namespace lysa::ui {

    /**
     * A widget to display a 2D image.
     */
    class Image : public Widget {
    public:
        /**
         * Constructor with image.
         * @param image The image to display.
         * @param autoSize Whether to automatically resize the widget to the image size.
         * @param fixedSize Size can't change
         */
        Image(const lysa::Image& image, bool autoSize = true, bool fixedSize = false);

        /**
         * Constructor without image.
         * @param autoSize Whether to automatically resize the widget.
         * @param fixedSize Size can't change
         */
        Image(bool autoSize = true, bool fixedSize = false);

        /**
         * Sets whether to automatically resize the widget to the image size.
         */
        void setAutoSize(bool autoSize);

        /**
         * Sets the image color tint.
         */
        void setColor(const float4& color);

        /**
         * Returns the image color tint.
         */
        auto getColor() const { return color; }

        /**
         * Sets the image to display.
         */
        void setImage(const lysa::Image& image);

        /**
         * Sets the image URI to load and display.
         */
        void setImage(const std::string& uri);

        void _setSize(float width, float height) override;

        /**
         * Returns the currently displayed image.
         * @return Pointer to the image, or nullptr.
         */
        auto getImage() const { return image; }

    private:
        float4 color{1.0f};
        bool autoSize;
        bool fixedSize;
        const lysa::Image* image{nullptr};

        void autoResize();

        void eventCreate() override;
    };
}
