/*
 * Copyright (c) 2026-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.list;

import lysa.ui.event;

namespace lysa::ui {

    List::List(const Type type):
        Widget{type} {
        consumeMouseEvent = true;
    }

    int32 List::addItem(
        const std::shared_ptr<Widget>& item,
        const Alignment alignment,
        const std::string& resource) {
        items.push_back(item);
        const auto index = static_cast<int32>(items.size()) - 1;
        computeSizes();
        ctx().events.push({UIEvent::OnInsertItem, UIEventItem{.index = index, .item = item}, id});
        refresh();
        return index;
    }

    void List::removeItem(const int32 index) {
        if ((index < 0) || (index >= getCount())) { return; }
        auto it = items.begin();
        std::advance(it, index);
        const auto removed = *it;
        ctx().events.push({UIEvent::OnRemoveItem, UIEventItem{.index = index, .item = removed}, id});
        items.erase(it);
        if (selected == index) {
            selected = NO_SELECTION;
        }
        computeSizes();
        refresh();
    }

    void List::removeAllItems() {
        while (getCount() > 0) {
            removeItem(0);
        }
    }

    std::shared_ptr<Widget> List::getItem(const int32 index) const {
        if ((index < 0) || (index >= getCount())) { return nullptr; }
        auto it = items.begin();
        std::advance(it, index); // check here if we need a caching system for long lists
        return *it;
    }

    int32 List::getCount() const {
        return static_cast<int32>(items.size());
    }

    std::shared_ptr<Widget> List::getSelectedItem() const {
        return getItem(selected);
    }

    void List::select(const int32 index) {
        eventSelectItem(index);
    }

    void List::eventSelectItem(const int32 index) {
        if (index == selected) { return; }
        prevSelected = selected;
        selected = index;
        ctx().events.push({UIEvent::OnSelectItem, UIEventItem{.index = index, .item = getItem(index)}, id});
        refresh();
    }

}