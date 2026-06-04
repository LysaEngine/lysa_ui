/*
 * Copyright (c) 2026-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.scroll_box;

import lysa.context;
import lysa.types;
import lysa.ui.alignment;
import lysa.ui.box;
import lysa.ui.event;
import lysa.ui.scroll_bar;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * A scrollable container with horizontal & vertical scroll bars.
     * Children added to the ScrollBox are placed in an inner box that is scrolled.
     */
    class ScrollBox : public Box {
    public:
        /**
         * Creates a default ScrollBox widget.
         */
        ScrollBox();

        /**
         * Adds a child widget to the scrollable inner box.
         * @param child Child widget to add.
         * @param alignment Placement alignment inside the inner box.
         * @param resource Resource string.
         * @return The added widget.
         */
        std::shared_ptr<Widget> addContent(
            const std::shared_ptr<Widget>& child,
            Alignment alignment = Alignment::TOPLEFT,
            const std::string& resource = "");

        /**
         * Removes a child widget from the inner box.
         */
        void removeContent(const std::shared_ptr<Widget>& child);

        /**
         * Removes all children from the inner box.
         */
        void removeAllContent();

        /**
         * Sets the UI resources for the scroll box.
         * @param resBox Resource for the inner box.
         * @param resVScroll Resource for the vertical scroll bar.
         * @param resHScroll Resource for the horizontal scroll bar.
         */
        void setResources(
            const std::string& resBox,
            const std::string& resVScroll,
            const std::string& resHScroll);

        /**
         * Returns the inner (scrolled) box.
         */
        auto getInnerBox() const { return innerBox; }

    protected:
        ScrollBox(Type type);

    private:
        std::shared_ptr<Box> innerBox;
        std::shared_ptr<VScrollBar> vscroll;
        std::shared_ptr<HScrollBar> hscroll;

        //! Recompute scroll ranges from the inner box children bounds.
        void computeSizes();

        void onVScrollChange(const UIEventValue& event);
        void onHScrollChange(const UIEventValue& event);
    };

}