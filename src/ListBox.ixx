/*
 * Copyright (c) 2026-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.list_box;

import lysa.context;
import lysa.input_event;
import lysa.types;
import lysa.ui.alignment;
import lysa.ui.box;
import lysa.ui.event;
import lysa.ui.list;
import lysa.ui.scroll_bar;
import lysa.ui.selection;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * A scrollable list of widgets with a selection highlight.
     */
    class ListBox : public List {
    public:
        /**
         * Creates a default ListBox widget.
         */
        ListBox();

        int32 addItem(
            const std::shared_ptr<Widget>& item,
            Alignment alignment = Alignment::LEFT,
            const std::string& resource = "") override;

        /**
         * Removes the item at the given index and updates the scroll range.
         * @param index Index (0-based) of the item to remove.
         */
        void removeItem(int32 index) override;

        /**
         * Sets the UI resources for the list box.
         * @param resBox Resource for the inner background box.
         * @param resScroll Resource for the vertical scroll bar.
         * @param resSel Resource for the selection highlight.
         */
        void setResources(
            const std::string& resBox,
            const std::string& resScroll,
            const std::string& resSel);

        /**
         * Returns the internal selection highlight widget.
         */
        auto getSelectionWidget() const { return selection; }

    private:
        float topSelected{0};
        float innerHeight{0};
        float totalHeight{0};
        int32 firstDisplayed{0};
        std::shared_ptr<Selection> selection;
        std::shared_ptr<Box> box;
        std::shared_ptr<VScrollBar> vscroll;

        //! Largest first-fully-visible index given a start index & a height.
        int32 maxDisplay(int32 start, float height) const;

        Alignment correctAlignment(Alignment alignment) const;

        void computeSizes() override;
        void eventSelectItem(int32 index) override;
        void setRectSelected(int32 index);

        void onBoxResize(const UIEvent& event);
        void onBoxMouseDown(const UIEventMouseButton& event);
        bool eventKeyDown(Key key) override;
        void onVScrollChange(const UIEventValue& event);
    };

}