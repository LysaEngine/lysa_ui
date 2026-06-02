/*
 * Copyright (c) 2026-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.selection;

import lysa.context;
import lysa.ui.panel;

export namespace lysa::ui {

    /**
     * Selection highlight rectangle, drawn behind the selected item of a ListBox.
     */
    class Selection : public Panel {
    public:
        Selection(): Panel{SELECTION} {}
    };

}