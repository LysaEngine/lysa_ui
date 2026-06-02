/*
 * Copyright (c) 2026-present Henri Michelon
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.scroll_box;

import std;

namespace lysa::ui {

    ScrollBox::ScrollBox():
        Box{SCROLLBOX} {
        setHBorder(1);
        setVBorder(1);
        drawBackground = false;
        allowFocus = true;
    }

    ScrollBox::ScrollBox(const Type type):
        Box{type} {
        setHBorder(1);
        setVBorder(1);
        drawBackground = false;
        allowFocus = true;
    }

    std::shared_ptr<Widget> ScrollBox::addContent(
        const std::shared_ptr<Widget>& child,
        const Alignment alignment,
        const std::string& resource) {
        const auto w = innerBox->add(child, alignment, resource);
        computeSizes();
        return w;
    }

    void ScrollBox::removeContent(const std::shared_ptr<Widget>& child) {
        innerBox->remove(child);
        computeSizes();
    }

    void ScrollBox::removeAllContent() {
        innerBox->removeAll();
        computeSizes();
    }

    void ScrollBox::setResources(
        const std::string& resBox,
        const std::string& resVScroll,
        const std::string& resHScroll) {
        if (innerBox != nullptr) { return; }
        vscroll = create<VScrollBar>(resVScroll, Alignment::RIGHTTOP);
        hscroll = create<HScrollBar>(resHScroll, Alignment::BOTTOMLEFT);
        innerBox = create<Box>(resBox, Alignment::FILL);
        setPadding(0);

        innerBox->setDrawBackground(false);
        vscroll->setStep(4);
        hscroll->setStep(4);

        ctx().events.subscribe(UIEvent::OnValueChange, vscroll->id, [this](auto evt) {
            this->onVScrollChange(std::any_cast<UIEventValue>(evt.payload));
        });
        ctx().events.subscribe(UIEvent::OnValueChange, hscroll->id, [this](auto evt) {
            this->onHScrollChange(std::any_cast<UIEventValue>(evt.payload));
        });
    }

    void ScrollBox::computeSizes() {
        if ((innerBox == nullptr) ||
            (innerBox->getWidth() <= 0) || (innerBox->getHeight() <= 0)) {
            if (hscroll) { hscroll->setMax(0); }
            if (vscroll) { vscroll->setMax(0); }
            return;
        }
        // Bounds of the children relative to the inner box content origin.
        const auto& boxRect = innerBox->getRect();
        const auto leftOffset = innerBox->getPadding() - boxRect.x - innerBox->getHBorder();
        const auto topOffset  = innerBox->getPadding() - boxRect.y - innerBox->getVBorder();
        float maxWidth = 0;
        float maxHeight = 0;
        for (const auto& child : innerBox->getChildren()) {
            const auto& r = child->getRect();
            maxWidth  = std::max(maxWidth, r.x + leftOffset + r.width);
            maxHeight = std::max(maxHeight, r.y + topOffset + r.height);
        }
        hscroll->setMax(std::max(0.0f, maxWidth - innerBox->getWidth()));
        vscroll->setMax(std::max(0.0f, maxHeight - innerBox->getHeight()));
    }

    void ScrollBox::onVScrollChange(const UIEventValue& event) {
        innerBox->setChildrenOffset(hscroll->getValue(), event.value);
        refresh();
    }

    void ScrollBox::onHScrollChange(const UIEventValue& event) {
        innerBox->setChildrenOffset(event.value, vscroll->getValue());
        refresh();
    }

}