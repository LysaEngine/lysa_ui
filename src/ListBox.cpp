/*
 * Copyright (c) 2026-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.list_box;

import std;
import lysa.input;

namespace lysa::ui {

    ListBox::ListBox():
        List{LISTBOX} {
        drawBackground = false;
        allowFocus = true;
    }

    int32 ListBox::maxDisplay(const int32 start, const float height) const {
        int32 md = getCount();
        float y = 0;
        for (int32 i = start; i < getCount(); i++) {
            y += getItem(i)->getHeight() + getPadding() * 2;
            if (y >= height) {
                md = i;
                break;
            }
        }
        return md;
    }

    void ListBox::computeSizes() {
        if (box == nullptr) { return; }
        innerHeight = box->getHeight() - box->getVBorder() * 2;
        totalHeight = 0;
        for (const auto& item : getItems()) {
            totalHeight += item->getHeight() + box->getPadding() * 2;
        }
        vscroll->setMax(totalHeight - innerHeight + vscroll->getStep());
    }

    Alignment ListBox::correctAlignment(const Alignment alignment) const {
        switch (alignment) {
        case Alignment::RIGHT:
            return Alignment::TOPRIGHT;
        case Alignment::CENTER:
            return Alignment::TOPCENTER;
        default:
            return Alignment::TOPLEFT;
        }
    }

    int32 ListBox::addItem(
        const std::shared_ptr<Widget>& item,
        const Alignment alignment,
        const std::string& resource) {
        box->add(item, correctAlignment(alignment), resource);
        return addItem(item, alignment, resource);
    }

    void ListBox::removeItem(const int32 index) {
        if ((index < 0) || (index >= getCount())) { return; }
        if ((index == getSelectedIndex()) && (index == getCount() - 1)) {
            select(index - 1);
        }
        box->remove(getItem(index));
        removeItem(index);
    }

    void ListBox::setResources(
        const std::string& resBox,
        const std::string& resScroll,
        const std::string& resSel) {
        if (box != nullptr) { return; }
        vscroll = create<VScrollBar>(resScroll, Alignment::RIGHT);
        box = create<Box>(resBox, Alignment::FILL);
        selection = box->create<Selection>(resSel, Alignment::NONE);

        box->setPadding(0);
        vscroll->setStep(2);
        selection->setVisible(false);

        ctx().events.subscribe(UIEvent::OnMouseDown, box->id, [this](auto evt) {
            this->onBoxMouseDown(std::any_cast<UIEventMouseButton>(evt.payload));
        });
        ctx().events.subscribe(UIEvent::OnResize, box->id, [this](auto evt) {
            this->onBoxResize(std::any_cast<UIEvent>(evt.payload));
        });
        ctx().events.subscribe(UIEvent::OnValueChange, vscroll->id, [this](auto evt) {
            this->onVScrollChange(std::any_cast<UIEventValue>(evt.payload));
        });
    }

    void ListBox::eventSelectItem(const int32 index) {
        auto idx = index;
        if (idx == getSelectedIndex()) { idx = NO_SELECTION; }
        setFreezed(true);
        setRectSelected(idx);
        box->refresh();
        setFreezed(false);
        eventSelectItem(idx);
    }

    void ListBox::setRectSelected(const int32 index) {
        if (index < 0) {
            selection->setVisible(false);
            return;
        }
        topSelected = box->getRect().y + box->getVBorder();
        for (int32 i = 0; i < index; i++) {
            topSelected += getItem(i)->getHeight() + box->getPadding();
        }
        const auto item = getItem(index);
        selection->setRect(
            box->getRect().x + box->getHBorder(),
            topSelected - box->getChildrenOffsetY(),
            box->getWidth() - box->getVBorder() * 2,
            item->getHeight() + box->getPadding() * 2);
        selection->setVisible(true);
        item->refresh();
    }

    void ListBox::onBoxResize(const UIEvent&) {
        computeSizes();
        setRectSelected(getSelectedIndex());
    }

    void ListBox::onBoxMouseDown(const UIEventMouseButton& event) {
        if (getCount() == 0) { return; }
        float y = (event.y - (box->getRect().y + box->getVBorder())) + box->getChildrenOffsetY();
        int32 hit = NO_SELECTION;
        int32 i = 0;
        for (const auto& w : getItems()) {
            y -= box->getPadding();
            if (y < w->getHeight()) {
                hit = i;
                break;
            }
            y -= w->getHeight();
            i++;
        }
        box->setPushed(false);
        if (hit >= 0) { select(hit); }
    }

    bool ListBox::eventKeyDown(const Key key) {
        if (getCount() == 0) { return Widget::eventKeyDown(key); }
        const auto idx = getSelectedIndex();
        const auto max = maxDisplay(idx < 0 ? 0 : idx, box->getHeight());
        const auto value = static_cast<int32>(vscroll->getValue());
        if ((key == KEY_UP) && (idx > 0)) {
            select(idx - 1);
        }
        else if ((key == KEY_DOWN) && (idx < getCount() - 1)) {
            select(idx + 1);
        }
        else if ((key == KEY_PAGE_UP) && (idx > 0)) {
            if ((idx - value) > 0) {
                select(value);
            }
            else if (value < max) {
                select(0);
            }
            else {
                select(value - max);
            }
        }
        else if ((key == KEY_PAGE_DOWN) && (idx < getCount() - 1)) {
            if ((idx - value) < max) {
                select(value + max - 1);
            }
            else if (idx > (getCount() - max)) {
                select(getCount() - 1);
            }
            else {
                select(idx + max);
            }
        }
        else {
            return Widget::eventKeyDown(key);
        }
        return true;
    }

    void ListBox::onVScrollChange(const UIEventValue& event) {
        float y = 0;
        int32 i = 0;
        for (const auto& w : getItems()) {
            y += w->getHeight() + box->getPadding() * 2;
            if (y > event.value) {
                firstDisplayed = i;
                break;
            }
            i++;
        }
        // Scroll the box content: resizeChildren() (triggered by setChildrenOffset)
        // re-lays out every item from the offset client origin.
        box->setChildrenOffset(0, event.value);
        if (getSelectedIndex() >= 0) {
            selection->setPos(selection->getRect().x, topSelected - event.value);
            if (const auto sel = getSelectedItem()) { sel->refresh(); }
        }
        refresh();
    }

}