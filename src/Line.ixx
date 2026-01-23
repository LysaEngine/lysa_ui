/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.line;

import lysa.context;
import lysa.ui.widget;

export namespace lysa::ui {
    /**
     * A horizontal or vertical line widget.
     */
    class Line : public Widget {
    public:
        /**
         * Line orientation style.
         */
        enum LineStyle {
            HORIZ, //! Horizontal line
            VERT   //! Vertical line
        };

        /**
         * Constructor.
         * @param ctx The engine context.
         * @param style The line orientation.
         */
        Line( LineStyle style = HORIZ);

        /**
         * Returns the current line style.
         */
        auto getStyle() const { return style; }

        /**
         * Sets the line orientation style.
         */
        void setStyle(LineStyle style);

    private:
        LineStyle style;
    };

    /**
     * @class HLine
     * A horizontal line widget.
     */
    class HLine : public Line {
    public:
        HLine() : Line(HORIZ) {}
    };

    /**
     * @class VLine
     * A vertical line widget.
     */
    class VLine : public Line {
    public:
        VLine() : Line(VERT) {}
    };
}
