/*
 * Copyright (c) 2026-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.list;

import lysa.context;
import lysa.types;
import lysa.ui.alignment;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * Super class for all list-of-widgets based widgets.
     */
    class List : public Widget {
    public:
        //! Value returned by getSelectedIndex() when nothing is selected.
        static constexpr int32 NO_SELECTION{-1};

        List(Type type);

        /**
         * Adds a widget at the end of the list.
         * @param item Widget to add.
         * @param alignment Placement alignment.
         * @param resource Resource string.
         * @return The index (0-based) of the inserted item.
         */
        virtual int32 addItem(
            const std::shared_ptr<Widget>& item,
            Alignment alignment = Alignment::LEFT,
            const std::string& resource = "");

        /**
         * Removes the item at the given index.
         * @param index Index (0-based) of the item to remove.
         */
        virtual void removeItem(int32 index);

        /**
         * Removes all items.
         */
        virtual void removeAllItems();

        /**
         * Returns the widget at the given index.
         */
        std::shared_ptr<Widget> getItem(int32 index) const;

        /**
         * Returns the number of items in the list.
         */
        int32 getCount() const;

        /**
         * Returns the index of the selected item, or NO_SELECTION.
         */
        int32 getSelectedIndex() const { return selected; }

        /**
         * Returns the selected widget, or nullptr.
         */
        std::shared_ptr<Widget> getSelectedItem() const;

        /**
         * Selects an item by index. Pass NO_SELECTION to clear the selection.
         */
        void select(int32 index);

        /**
         * Returns the list of item widgets.
         */
        const std::list<std::shared_ptr<Widget>>& getItems() const { return items; }

    protected:
        int32 prevSelected{NO_SELECTION};
        std::list<std::shared_ptr<Widget>> items;

        // Recompute internal sizes after items change (scroll range, etc.).
        virtual void computeSizes() = 0;

        // Selection logic, overridable by subclasses.
        virtual void eventSelectItem(int32 index);

    private:
        int32 selected{NO_SELECTION};
    };
}