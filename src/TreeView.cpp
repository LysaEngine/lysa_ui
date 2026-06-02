/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.tree_view;

import lysa.ui.alignment;

namespace lysa::ui {

    TreeView::TreeView() :
        Widget(TREEVIEW),
        innerHeight(0),
        itemsHeight(0) {
        allowFocus = true;
        consumeMouseEvent = true;
    }

    void TreeView::setResources(const std::string& resBox, const std::string& resScroll, const std::string&) {
        if (box == nullptr) {
            box = std::make_shared<Box>();
            vScroll = std::make_shared<VScrollBar>(0.0f, 0.0f);
            add(vScroll, Alignment::RIGHT, resScroll);
            add(box, Alignment::FILL, resBox);
            box->setDrawBackground(false);
            box->setPadding(1);
            vScroll->setStep(2);
            ctx().events.subscribe(UIEvent::OnValueChange, vScroll->id, [this](auto evt) {
                this->onVScrollChange(std::any_cast<UIEventValue>(evt.payload));
            });
        }
    }

    void TreeView::removeAllItems() {
        box->removeAll();
        items.clear();
        computeSizes();
    }

    std::shared_ptr<TreeView::Item>& TreeView::addItem(std::shared_ptr<Widget> item) {
        items.push_back(std::make_shared<Item>(item));
        auto& newWidget = items.back();
        box->add(newWidget, Alignment::TOPLEFT);
        newWidget->handle = std::make_shared<Text>(" ");
        newWidget->add(newWidget->handle,Alignment:: LEFT, treeTabsSize);
        newWidget->add(item, Alignment::LEFT);
        newWidget->setSize(1000.0f, item->getHeight());
        newWidget->setDrawBackground(false);
        computeSizes();
        return newWidget;
    }

    std::shared_ptr<TreeView::Item>& TreeView::addItem(const std::shared_ptr<Item>& parent, std::shared_ptr<Widget> item) {
        parent->children.push_back(std::make_shared<Item>(item));
        auto& newWidget = parent->children.back();
        newWidget->level = parent->level + 1;
        box->add(newWidget, Alignment::TOPLEFT);
        for (int i = 0; i <= newWidget->level; i++) {
            if (i == (newWidget->level)) {
                newWidget->handle = std::make_shared<Text>(" ");
                newWidget->add(newWidget->handle, Alignment::LEFT, treeTabsSize);
            }
            else {
                newWidget->add(std::make_shared<Panel>(), Alignment::LEFT, treeTabsSize);
            }
        }
        parent->handle->setText("-");
        newWidget->add(item, Alignment::LEFT);
        newWidget->setSize(1000.0f, item->getHeight());
        newWidget->setDrawBackground(false);
        //expand(parent->item);
        computeSizes();
        return newWidget;
    }

    void TreeView::expand(const std::shared_ptr<Widget>& item) const {
        throw Exception("not implemented");
        // for (const auto& widget : box->_getChildren()) {
        //     if (const auto itemWidget = dynamic_cast<Item*>(item.get())) {
        //         if (itemWidget->item == item) {
        //             throw Exception("not implemented");
        //             // log("found");
        //         }
        //     }
        // }
    }

    void TreeView::computeSizes() {
        if (box == nullptr) { return; }
        innerHeight = box->getHeight() - box->getVBorder() * 2;
        itemsHeight = 0;
        for (const auto& child : box->getChildren()) {
            itemsHeight += child->getHeight() + box->getPadding() * 2;
        }
        vScroll->setMax(itemsHeight - innerHeight + vScroll->getStep());
    }

    void TreeView::onVScrollChange(const UIEventValue& event) {
        box->setChildrenOffset(0, event.value);
        refresh();
    }


}
