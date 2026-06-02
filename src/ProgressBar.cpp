/*
* Copyright (c) 2026-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.progress_bar;

import lysa.ui.alignment;

namespace lysa::ui {

    ProgressBar::ProgressBar(
        const Orientation orientation,
        const float min,
        const float max,
        const float value,
        const float step):
        ValueSelect{PROGRESSBAR, min, max, value, step},
        orientation{orientation} {
        drawBackground = false;
    }

    void ProgressBar::setResources(const std::string& resBox) {
        if (box != nullptr) { return; }
        box = create<Box>(resBox, Alignment::FILL);
    }

    void ProgressBar::setDisplay(const Display display) {
        this->display = display;
        refresh();
    }

    void ProgressBar::setOrientation(const Orientation orientation) {
        this->orientation = orientation;
        refresh();
    }

}