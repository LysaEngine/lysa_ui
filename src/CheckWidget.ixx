/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.check_widget;

import lysa.context;
import lysa.input_event;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * Base class for all two-states widgets.
     */
    class CheckWidget : public Widget {
    public:
        /**
         * State of the widget.
         */
        enum State {
            UNCHECK = 0, //! Unchecked (aka OFF)
            CHECK = 1,   //! Checked (aka ON)
        };

        /**
         * Returns the current state of the widget.
         */
        auto getState() const { return state; }

        /**
         * Changes the state of the widget.
         */
        virtual void setState(State newState);

        /**
         * Called when a mouse button is pressed; toggles the check state.
         * @param button The mouse button pressed.
         * @param x Mouse X coordinate.
         * @param y Mouse Y coordinate.
         * @return True if the event was consumed.
         */
        bool eventMouseDown(MouseButton button, float x, float y) override;

    protected:
        CheckWidget(Type type);

    private:
        State state{UNCHECK};
    };
}
