/*
 * Copyright (c) 2024-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.popup;

import lysa.context;
import lysa.ui.panel;

export namespace lysa::ui {

    /**
     * A Panel widget rendered at a fixed (x, y) position relative to its parent,
     * always drawn on top of sibling widgets.
     *
     * Unlike other widgets whose position is controlled by an alignment, a Popup
     * is placed at the explicit coordinates given at construction time and is
     * automatically flagged as overlapping so it is painted last (on top).
     */
    class Popup : public Panel {
    public:
        /**
         * Creates a Popup at the given position relative to its parent's origin.
         * @param x Horizontal offset from the parent widget's top-left corner.
         * @param y Vertical offset from the parent widget's top-left corner.
         */
        Popup(float x, float y) : Panel{POPUP}, posX{x}, posY{y} {
            overlap = true;
        }

        /**
         * Returns the X offset from the parent's origin.
         */
        float getX() const { return posX; }

        /**
         * Returns the Y offset from the parent's origin.
         */
        float getY() const { return posY; }

        /**
         * Positions the popup at its fixed (x, y) coordinates after creation.
         */
        void eventCreate() override {
            Panel::eventCreate();
            setPos(posX, posY);
        }

    private:
        float posX;
        float posY;
    };

}