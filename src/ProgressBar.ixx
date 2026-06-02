/*
 * Copyright (c) 2026-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.progress_bar;

import std;
import lysa.context;
import lysa.ui.box;
import lysa.ui.value_select;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * A rectangular progress bar.
     */
    class ProgressBar : public ValueSelect {
    public:
        /**
         * Progress bar orientation.
         */
        enum Orientation {
            HORIZONTAL, //! Fills horizontally
            VERTICAL    //! Fills vertically
        };

        /**
         * Optional textual display drawn over the bar.
         */
        enum Display {
            NONE,    //! No text
            PERCENT, //! Display a percentage
            VALUE    //! Display the raw value
        };

        /**
         * Constructor.
         * @param orientation Orientation (HORIZONTAL or VERTICAL).
         * @param min Minimum value.
         * @param max Maximum value.
         * @param value Initial value.
         * @param step Step increment.
         */
        ProgressBar(
            Orientation orientation = HORIZONTAL,
            float min = 0,
            float max = 0,
            float value = 0,
            float step = 1);

        /**
         * Returns the orientation.
         */
        auto getOrientation() const { return orientation; }

        /**
         * Sets the orientation.
         */
        void setOrientation(Orientation orientation);

        /**
         * Returns the textual display mode.
         */
        auto getDisplay() const { return display; }

        /**
         * Sets the textual display mode.
         */
        void setDisplay(Display display);

        /**
         * Sets the UI resources for the progress bar.
         * @param resBox Resource for the inner box.
         */
        void setResources(const std::string& resBox);

    private:
        Display display{NONE};
        Orientation orientation;
        std::shared_ptr<Box> box;
    };

    /**
     * A vertical progress bar.
     */
    class VProgressBar : public ProgressBar {
    public:
        VProgressBar(const float min = 0, const float max = 0, const float value = 0):
            ProgressBar(VERTICAL, min, max, 1, value) {
        }
    };

    /**
     * A horizontal progress bar.
     */
    class HProgressBar : public ProgressBar {
    public:
        HProgressBar(const float min = 0, const float max = 0, const float value = 0):
            ProgressBar(HORIZONTAL, min, max, 1, value) {
        }
    };

}