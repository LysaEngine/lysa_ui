/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.style_classic;

import lysa.log;
import lysa.types;
import lysa.utils;
import lysa.ui.image;
import lysa.ui.list_box;

namespace lysa::ui {

    void StyleClassic::updateOptions() {
        focus = extractColor("color_focus", 0.1f, 0.1f, 0.1f);
        fgUp = extractColor("color_foreground_up", 0.4,0.6,0.7, 1.0f);
        fgDown = extractColor("color_foreground_down", 0.65f, 0.86f, 0.86f, 1.0f);
        shadowDark = extractColor("color_shadow_dark", 0.25f,0.25f,0.25f, 1.0f);
        shadowBright = extractColor("color_shadow_bright", 0.9f,0.9f,0.9f, 1.0f);
        /*XXXX
        if (texture != nullptr) { delete texture; }
        if (Option("texture").Len() > 0) {
            DatatypePixmap dtype;
            texture = new GTexture(dtype.Load(Option("texture")),
                                   background);
        }*/
    }

    void StyleClassic::draw(const Widget &widget, UIResource &resources, Vector2DRenderer &renderer, const bool before) const {
        auto &res = static_cast<StyleClassicResource &>(resources);
        if (!widget.isVisible()) {
            return;
        }
        if (before) {
            switch (widget.getType()) {
                // case Widget::TEXTEDIT:
                // case Widget::UPDOWN:
                // case Widget::PROGRESSBAR:
            case Widget::PANEL:
                drawPanel((Panel &)widget, res, renderer);
                break;
            case Widget::BOX:
                // case Widget::SCROLLBOX:
                drawBox(widget, res, renderer, false);
                break;
            case Widget::LINE:
                drawLine((Line &)widget, res, renderer);
                break;
            case Widget::BUTTON:
                drawButton((Button &)widget, res, renderer);
                break;
            case Widget::TOGGLEBUTTON:
                drawToggleButton((ToggleButton &)(CheckWidget &)widget, res, renderer);
                break;
            case Widget::TEXT:
                drawText((Text &)widget, res, renderer);
                break;
            case Widget::FRAME:
                drawFrame((Frame &)widget, res, renderer);
                break;
            case Widget::IMAGE: {
                    auto &pic = dynamic_cast<const Image &>(widget);
                    if (pic.getImage()) {
                        renderer.setPenColor(pic.getColor());
                        renderer.drawFilledRect(widget.getRect(), pic.getImage()->id);
                    }
                }
                break;
            case Widget::SELECTION:
                drawSelection((const Selection &)widget, res, renderer);
            break;
                /*case Widget::GRIDCELL:
                    DrawGridCell((GGridCell&)W, D, res);
                    break;
                case Widget::ARROW:
                    DrawArrow((GArrow&)W, D, res);
                    break;
                case Widget::CHECKMARK:
                    DrawCheckmark((GCheckmark&)W, D, res);
                    break;
                case Widget::TRACKBAR:
                    DrawTrackBar((GTrackBar&)W, D, res);
                    break;
                case Widget::ROUNDBUTTON:
                    DrawRoundButton((GRoundButton&)W, D, res);
                    break;
                case Widget::TABBUTTON:
                    DrawTabButton((GTabButton&)W, D, res);
                    break;

                    break;*/
            default:
                break;
            }
        } else {
            switch (widget.getType()) {
                case Widget::TEXTEDIT:
                    drawTextEdit((TextEdit&)widget, renderer);
                    break;
            case Widget::PROGRESSBAR:
                drawProgressBar((const ProgressBar &)widget, res, renderer);
                break;
            /*
                case Widget::TABS:
                    DrawTabs((GTabs&)W, D, res, R);
                    break;*/
            default:
                break;
            }
        }
    }

    void StyleClassic::addResource(Widget &widget, const std::string &resources) {
        const auto& res = std::make_shared<StyleClassicResource>(resources);
        widget.setResource(res);
        widget.setSize(res->width, res->height);
        switch (widget.getType()) {
        case Widget::SCROLLBAR:
            static_cast<ScrollBar &>(widget).setResources("style=LOWERED", "style=FLAT;color=" + to_string(fgDown));
            break;
        case Widget::TREEVIEW:
            static_cast<TreeView &>(widget).setResources("style=LOWERED", "width=18;height=18;style=RAISED", "");
            break;
        case Widget::TEXTEDIT:
            static_cast<TextEdit&>(widget).setResources(resources);
            break;
        case Widget::LISTBOX:
            static_cast<ListBox &>(widget).setResources(
                "style=LOWERED",
                "width=18;height=18;style=RAISED",
                "style=FLAT;color=" + to_string(focus));
            break;
        case Widget::PROGRESSBAR:
            static_cast<ProgressBar &>(widget).setResources("style=LOWERED");
            break;
        case Widget::SCROLLBOX:
            static_cast<ScrollBox &>(widget).setResources(
                "style=LOWERED",
                "width=18;height=18;style=RAISED",
                "width=18;height=18;style=RAISED");
            break;
            // XXX
            /*case Widget::UPDOWN:
                ((GUpDown&)W).SetResources(RES, RES);
                break;
            case Widget::TRACKBAR:
                ((GTrackBar&)W).SetResources("12,12,RAISED");
                break;
            case Widget::TABS:
                ((GTabs&)W).SetResources(",,RAISED");
                break;
            case Widget::GRID:
                ((GGrid&)W).SetResources(",,LOWERED");*/
        default:
            break;
        }
    }

    void StyleClassic::resize(Widget &widget, Rect &rect, UIResource &) {
        switch (widget.getType()) {
        case Widget::BOX:
        case Widget::BUTTON:
        case Widget::LISTBOX:
        case Widget::SCROLLBOX:
            // case Widget::TABBUTTON:
            widget.setVBorder(2);
            widget.setHBorder(2);
            break;
        case Widget::FRAME: {
                widget.setHBorder(4);
                float w, h;
                widget.getFont()->getSize(
                    static_cast<Frame &>(widget).getTitle(),
                    widget.getFontScale(), w, h); // TODO text scale in Frame
                widget.setVBorder(h - 2);
            }
            break;
            widget.setVBorder(2);
            widget.setHBorder(2);
        /*case Widget::LINE:
            {
                GLine &L = (GLine&)W;
                if (L.Style() == GLine::HORIZ) {
                    R.height = 2;
                }
                else if (L.Style() == GLine::VERT) {
                    R.width = 2;
                }
            }
                break;*/
        default:
            break;
        }
    }

    float4 StyleClassic::extractColor(const std::string &OPT, const float R, const float G, const float B, const float A) const {
        const std::string opt = getOption(OPT);
        if (!opt.empty()) {
            const auto &rgb = split(opt, ',');
            if (rgb.size() == 3) {
                return float4{stof(std::string{rgb[0]}), stof(std::string{rgb[1]}), stof(std::string{rgb[2]}), 1.0f};
            }
            if (rgb.size() == 4) {
                return float4{stof(std::string{rgb[0]}), stof(std::string{rgb[1]}), stof(std::string{rgb[2]}), stof(std::string{rgb[3]})};
            }
        }
        return float4{R, G, B, A};
    }

    void StyleClassic::drawPanel(const Panel &widget, StyleClassicResource &resources, Vector2DRenderer &renderer) const {
        if (widget.isDrawBackground()) {
            auto c = resources.customColor ? resources.color : fgDown;
            c.a = widget.getTransparency();
            renderer.setPenColor(c);
            renderer.drawFilledRect(widget.getRect());
            // texture->Draw(D, W.Rect());
        }
    }

    void StyleClassic::drawBox(
        const Widget &widget,
        const StyleClassicResource &resources,
        Vector2DRenderer &renderer,
        const bool pushable) const {
        if ((widget.getWidth() < 4) || (widget.getHeight() < 4)) {
            return;
        }
        const auto x= widget.getRect().x;
        const auto y= widget.getRect().y;
        const auto w= widget.getRect().width - 1;
        const auto h= widget.getRect().height - 1;
        if (widget.isDrawBackground()) {
            if (pushable && widget.isPushed()) {
                auto fd= fgDown;
                fd.a -= 1.0f - widget.getTransparency();
                renderer.setPenColor(fd);
            } else {
                auto fu= widget.isEnabled() ? (resources.customColor ? resources.color : fgUp) : shadowDark;
                fu.a -= 1.0f - widget.getTransparency();
                renderer.setPenColor(fu);
            }
            renderer.drawFilledRect(x, y, w, h);
        }
        if (resources.style != StyleClassicResource::FLAT) {
            auto sb = shadowBright;
            sb.a = widget.getTransparency();
            auto sd = shadowDark;
            sd.a = widget.getTransparency();
            switch (resources.style) {
            case StyleClassicResource::LOWERED:
                renderer.setPenColor(sd);
                break;
            case StyleClassicResource::RAISED:
                renderer.setPenColor(sb);
                break;
            default:
                break;
            }
            renderer.drawLine({x, y + h}, {x + w, y + h}); // top
            renderer.drawLine({x, y}, {x, y + h}); // left
            switch (resources.style) {
            case StyleClassicResource::RAISED:
                renderer.setPenColor(sd);
                break;
            case StyleClassicResource::LOWERED:
                renderer.setPenColor(sb);
                break;
            default:
                break;
            }
            renderer.drawLine({x, y}, {x + w, y}); // bottom
            renderer.drawLine({x + w, y}, {x + w, y + h}); // right
        }
    }

    void StyleClassic::drawLine(const Line &widget, const StyleClassicResource &resource, Vector2DRenderer &renderer) const {
        float4 color;
        if (resource.customColor) {
            color = resource.color;
        } else {
            color = resource.style == StyleClassicResource::RAISED ? shadowDark : shadowBright;
        }
        color.a -= 1.0f - widget.getTransparency();
        auto& rect = widget.getRect();
        renderer.setPenColor(color);
        if (widget.getStyle() == Line::HORIZ) {
            renderer.drawLine({rect.x, rect.y}, {rect.x + rect.width, rect.y});
        } else if (widget.getStyle() == Line::VERT) {
            renderer.drawLine({rect.x, rect.y}, {rect.x, rect.y + rect.height});
        }
    }

    void StyleClassic::drawButton(const Button &widget, StyleClassicResource &resource, Vector2DRenderer &renderer) const {
        resource.style = widget.isPushed() ? StyleClassicResource::LOWERED : StyleClassicResource::RAISED;
        drawBox(widget, resource, renderer, true);
    }

    void StyleClassic::drawToggleButton(ToggleButton &widget, StyleClassicResource &resources, Vector2DRenderer &renderer) const {
        if (widget.getState() == CheckWidget::CHECK) {
            resources.style = StyleClassicResource::LOWERED;
            widget.setPushed(true);
        } else {
            resources.style = StyleClassicResource::RAISED;
            widget.setPushed(false);
        }
        drawBox(widget, resources, renderer, true);
    }

    void StyleClassic::drawText(const Text &widget, const StyleClassicResource &resources, Vector2DRenderer &renderer) const {
        renderer.setPenColor(
            widget.isEnabled() ? (resources.customColor ? resources.color :
            float4{widget.getTextColor().r, widget.getTextColor().g, widget.getTextColor().b, widget.getTransparency()}) :
            shadowBright);
        renderer.drawText(
            widget.getText(),
            *widget.getFont(),
            widget.getFontScale(),
            widget.getRect().x,
            widget.getRect().y);
    }

    void StyleClassic::drawFrame(Frame &widget, StyleClassicResource &resources, Vector2DRenderer &renderer) const {
        if ((widget.getWidth() < 4) || (widget.getHeight() < 4)) {
            return;
        }
        constexpr int32 LEFTOFFSET = 8;
        float l = widget.getRect().x;
        float b =  widget.getRect().y;
        float w = widget.getRect().width;
        float h = widget.getRect().height;
        float4 c1;
        float4 c2;
        auto sb = shadowBright;
        sb.a = widget.getTransparency();
        auto sd = shadowDark;
        sd.a = widget.getTransparency();
        switch (resources.style) {
        case StyleClassicResource::RAISED:
            c1 = sb;
            c2 = sd;
            break;
        case StyleClassicResource::LOWERED:
            c1 = sd;
            c2 = sb;
            break;
        case StyleClassicResource::FLAT:
            c1 = sd;
            c2 = sd;
            break;
        }
        float fh, fw;
        widget.getFont()->getSize(widget.getTitle(), widget.getFontScale(), fw, fh);
        // fw /= renderer.getAspectRatio();
        renderer.setPenColor(c2);
        if ((!widget.getTitle().empty()) && (widget.getWidth() >= (fw + LEFTOFFSET)) && (widget.getHeight() >= fh)) {
            renderer.drawLine(
                {l, b + h},
                {l + LEFTOFFSET, b + h});
            renderer.drawLine(
                {l + fw + LEFTOFFSET + 1, b + h},
                {l + w, b + h});
            renderer.setPenColor(float4{widget.getTitleColor().r, widget.getTitleColor().g, widget.getTitleColor().b, widget.getTransparency()});
            renderer.drawText(
                widget.getTitle(),
                *widget.getFont(),
                widget.getFontScale(),
                l + LEFTOFFSET,
                 (b + h) - (fh / 2) - widget.getFont()->getDescender()*widget.getFontScale());
            renderer.setPenColor(c2);
        } else {
            renderer.drawLine({l + w, b + h}, {l, b + h}); // top
        }
        renderer.drawLine({l, b}, {l, b + h}); // left
        renderer.setPenColor(c1);
        renderer.drawLine({l + w, b}, {l + w, b + h}); // right
        renderer.drawLine({l, b}, {l + w, b}); // bottom
    }

    void StyleClassic::drawTextEdit(const TextEdit& widget, Vector2DRenderer& renderer) const {
        if (widget.isFocused() && (!widget.isReadOnly())) {
            float w, h;
            const auto txt = widget.getDisplayedText().substr(
                0,
                widget.getSelStart() - widget.getFirstDisplayedChar());
            widget.getFont()->getSize(txt, widget.getFontScale(), w, h);
            h = widget.getTextBox()->getHeight();
            auto l = widget.getTextBox()->getRect().x + w;
            auto t =  widget.getTextBox()->getRect().y - 2 ;
            // renderer.setPenColor(shadowDark);
            renderer.setPenColor({1.0, 0.0, 0.0, 1.0});
            renderer.drawLine({l - 2, t}, {l - 2 + 5, t});
            renderer.drawLine({l - 2, t + h}, {l - 2 + 5, t + h});
            renderer.drawLine({l, t}, {l, t + h});
        }
    }

    void StyleClassic::drawSelection(
        const Selection &widget,
        const StyleClassicResource &resources,
        Vector2DRenderer &renderer) const {
        if (!widget.isDrawBackground()) { return; }
        auto c = resources.customColor ? resources.color : focus;
        c.a = widget.getTransparency();
        renderer.setPenColor(c);
        renderer.drawFilledRect(widget.getRect());
    }

    void StyleClassic::drawProgressBar(
        const ProgressBar &widget,
        const StyleClassicResource &resources,
        Vector2DRenderer &renderer) const {
        const auto range = widget.getMax() - widget.getMin();
        if (range <= 0.0f) { return; }
        const auto ratio = (widget.getValue() - widget.getMin()) / range;
        const auto& r = widget.getRect();
        const auto x = r.x + widget.getHBorder();
        const auto y = r.y + widget.getVBorder();
        const auto w = r.width - widget.getHBorder() * 2;
        const auto h = r.height - widget.getVBorder() * 2;
        auto c = resources.customColor ? resources.color : fgUp;
        c.a = widget.getTransparency();
        renderer.setPenColor(c);
        if (widget.getOrientation() == ProgressBar::VERTICAL) {
            const auto fh = h * ratio;
            renderer.drawFilledRect(x, y, w, fh, INVALID_ID);
        }
        else {
            const auto fw = w * ratio;
            renderer.drawFilledRect(x, y, fw, h, INVALID_ID);
        }
        if (widget.getDisplay() != ProgressBar::NONE) {
            std::string text;
            if (widget.getDisplay() == ProgressBar::PERCENT) {
                text = std::to_string(static_cast<int32>(ratio * 100.0f)) + "%";
            }
            else {
                text = std::to_string(static_cast<int32>(widget.getValue()));
            }
            float tw, th;
            widget.getFont()->getSize(text, widget.getFontScale(), tw, th);
            renderer.setPenColor(float4{0.0f, 0.0f, 0.0f, widget.getTransparency()});
            renderer.drawText(
                text,
                *widget.getFont(),
                widget.getFontScale(),
                r.x + (r.width - tw) / 2,
                r.y + (r.height - th) / 2);
        }
    }

    /*
    //----------------------------------------------
        void GLayoutVector::DrawArrow(GArrow&W, GLayoutVectorResource&, Vector2DRenderer&, float)
        {
            if ((W.Width() < 4) || (W.Height() < 4)) return;
            //dprintf("Draw Arrow %x\n", &W);

            uint32_t i, w, h, xpos, ypos, left, top;
            switch (W.Kind()) {
                case GArrow::UP:
                case GArrow::DOWN:
                    w = W.Width() - 4;
                    if (!(w % 2)) w--;
                    h = (w/2+1);
                    xpos = (W.Width() - w)/2;
                    ypos = (W.Width() - h)/2;
                    break;
                case GArrow::LEFT:
                case GArrow::RIGHT:
                default:
                    h = W.Height() - 4;
                    if (!(h % 2)) h--;
                    w = (h/2+1);
                    xpos = (W.Height() - w)/2;
                    ypos = (W.Height() - h)/2;
                    break;
            }


            left = W.Left() + xpos;
            top = W.Top() + ypos;
            if (W.Enabled())
                D.SetPenColor(shadowDark);
            else
                D.SetPenColor(fgUp);
            switch (W.Kind()) {
                case GArrow::UP:
                    for (i=0; i<h; i++)
                        D.DrawLine(i+left, h-i+top-1,
                                   (w-i)+left, h-i+top-1);
                    break;
                case GArrow::DOWN:
                    for (i=0; i<h; i++)
                        D.DrawLine(i+left, i+top,
                                   (w-i)+left, i+top);
                    break;
                case GArrow::LEFT:
                    for (i=0; i<w; i++)
                        D.DrawLine(w-i+left-1, top+i,
                                   w-i+left-1, top+h-i);
                    break;
                case GArrow::RIGHT:
                    for (i=0; i<w; i++)
                        D.DrawLine(i+left+1, top+i,
                                   i+left+1, top+h-i);
                    break;
            }
        }

    //----------------------------------------------
        void GLayoutVector::DrawCheckmark(GCheckmark&W, GLayoutVectorResource&, Vector2DRenderer&, float)
        {
            if ((W.Width() < 5) || (W.Height() < 5)) return;

            _LONG l = W.Left()+1;
            _LONG t = W.Top()+1;
            _LONG r = l+W.Width()-3;
            _LONG b = t+W.Height()-3;

            D.SetPenColor(shadowDark);
            //if (kind == CROSS)
            {
                D.DrawLine(l+1,	t,		r,		b-1);
                D.DrawLine(l,	t,		r,		b);
                D.DrawLine(l,	t+1,	r-1,	b);
                D.DrawLine(l,	b-1,	r-1,	t);
                D.DrawLine(l,	b,		r,		t);
                D.DrawLine(l+1,	b,		r,		t+1);
            }

        }


    //--------------------------------------------------------------------------
        void GLayoutVector::DrawTrackBar(GTrackBar&W, Vector2DRenderer&D,
                                         GLayoutVectorResource&)
        {
            if (W.TrackBarType() == GTrackBar::HORIZ) {
                _LONG left = W.Left() + W.tracker.Width()/2 - 1;
                _LONG right = W.Left() + W.Width() - W.tracker.Width()/2 - 1;
                D.SetPenColor(shadowBright);
                D.DrawHLine(left, W.Top() + W.Height() / 2, right - left - 1);
                D.SetPenColor(shadowDark);
                D.DrawLine(left, W.Top() + 2, left, W.Top() + W.Height() - 2);
                D.DrawLine(right, W.Top() + 2, right, W.Top() + W.Height() - 2);
                for (_LONG idx = W.Min(); idx < W.Max(); idx += W.Step()) {
                    _LONG l = left + (idx - W.Min()) *
                                     (W.Width() - W.tracker.Width()) / (W.Max() - W.Min());
                    D.DrawLine(l, W.Top() + W.Height()/4, l,
                               W.Top() + W.Height() - W.Height()/4);
                }
            }
            else {
                _LONG top = W.Top() + W.tracker.Height()/2 - 1;
                _LONG bottom = W.Top() + W.Height() - W.tracker.Height()/2 - 1;
                D.SetPenColor(shadowBright);
                D.DrawLine(W.Left() + W.Width() / 2, top, W.Left() + W.Width() / 2, bottom);
                D.SetPenColor(shadowDark);
                D.DrawLine(W.Left() + 2, top, W.Left() + W.Width() - 2, top);
                D.DrawLine(W.Left() + 2, bottom, W.Left() + W.Width() - 2, bottom);
                for (_LONG idx = W.Min(); idx < W.Max(); idx += W.Step()) {
                    _LONG t = top + (idx - W.Min()) *
                                    (W.Height() - W.tracker.Height()) / (W.Max() - W.Min());
                    D.DrawLine(W.Left() + W.Width()/4, t,
                               W.Left() + W.Width() - W.Width()/4, t);
                }
            }
        }


    //--------------------------------------------------------------------------
        void GLayoutVector::DrawTabs(GTabs&W, Vector2DRenderer&D,
                                     GLayoutVectorResource&)
        {
            D.SetPenColor(shadowBright);
            if (W.Childs().Count() == 0) {
                D.DrawLine(W.Left(), W.Top() + W.Height() - 1,
                           W.Left() + W.Width() - 1,  W.Top() + W.Height() - 1);
                return;
            }
            uint32_t wtab = MAX(_LONG(W.Width() / (W.Childs().Count() ) - W.Padding() * 2),
                              0l);
            uint32_t nsel = W.IndexSelected() - 1;
            uint32_t t = W.Top() + W.Height() - 1;
            D.DrawLine(W.Left(), t,
                       W.Left() + wtab * nsel - 1, t);
            D.SetPenColor(background);
            D.DrawLine(W.Left() + wtab * nsel, t,
                       W.Left() + wtab * (nsel + 1) - 2, t);
            D.SetPenColor(shadowBright);
            D.DrawLine(W.Left() + wtab * (nsel + 1) - 1, t,
                       W.Left() + W.Width() - 1, t);
        }


    //--------------------------------------------------------------------------
        void GLayoutVector::DrawTabButton(GTabButton&W, Vector2DRenderer&D,
                                          GLayoutVectorResource&RES)
        {
            if ((W.Width()<4) || (W.Height()<4)) { return; }
            uint32_t l = W.Rect().left;
            uint32_t t = W.Rect().top;
            uint32_t w = W.Rect().width;
            uint32_t h = W.Rect().height;
            w -= 1;
            h -= 2;
            D.SetPenColor(shadowBright);
            D.DrawLine(l, t, l+w, t);
            D.DrawLine(l, t, l, t+h);
            D.SetPenColor(shadowDark);
            D.DrawLine(l+w, t, l+w, t+h);
            l += 1;
            t += 1;
            w -= 1;
            if (W.DrawBackground() && (!RES.flat)) {
                if (W.Pushed() && W.MoveChildsOnPush()) {
                    D.SetPenColor(fgDown);
                    D.DrawRect(l, t, w, h);
                }
                else if (W.State() == GCheckWidget::CHECK) {
                    //D.SetPenColor(background);
                    texture->Draw(D, l, t, w, h+1);
                }
                else {
                    D.SetPenColor(fgUp);
                    D.DrawRect(l, t, w, h);
                }
            }
        }


    //--------------------------------------------------------------------------
        void GLayoutVector::DrawRoundButton(GRoundButton&W, Vector2DRenderer&D,
                                            GLayoutVectorResource&)
        {
            uint32_t beam = MIN(W.Width() / 2, W.Height() / 2);
            uint32_t outer = beam / 3;
            beam -= outer;
            _LONG x = W.Left() + W.Width() / 2;
            _LONG y = W.Top() + W.Height() / 2;

            const _DOUBLE RAD = 1.57079632679;
            //const uint32_t OFFSET = 3;

            _DOUBLE aMin;
            switch (W.RoundButtonType()) {
                case GRoundButton::RB_TOP: aMin = RAD; break;
                case GRoundButton::RB_LEFT: aMin = RAD * 2; break;
                case GRoundButton::RB_BOTTOM: aMin = RAD * 3; break;
                case GRoundButton::RB_RIGHT:
                default: aMin = 0.0; break;
            }

            _DOUBLE angle = ((RAD * 4 * (W.Value() - W.Min())) / (W.Max() - W.Min())) + aMin;

            D.SetPenColor(shadowBright);
            D.DrawCircle(x - 1,
                         y - 1,
                         beam,
                         FALSE);
            D.SetPenColor(shadowDark);
            D.DrawCircle(x + 1,
                         y + 1,
                         beam,
                         FALSE);
            //D.SetPenColor(fgUp);
            if (W.Pushed()) {
                D.SetPenColor(fgDown);
            }
            else {
                D.SetPenColor(fgUp);
            }
            D.DrawCircle(x, y, beam);

            D.SetPenColor(shadowBright);
            D.DrawCircle(x, y, beam + outer / 2 + 2, FALSE, W.Step());

            D.SetPenColor(shadowDark);
            D.DrawCircle(x, y, beam + outer / 2 + 1, FALSE, W.Step());
            D.DrawLine(x + _LONG(beam / 3 * cos(angle)),
                       y - _LONG(beam / 3 * sin(angle)),
                       x + _LONG((beam )  * cos(angle)),
                       y - _LONG((beam )* sin(angle)));
            D.DrawLine(x + _LONG((beam + outer) * cos(aMin)),
                       y - _LONG((beam + outer) * sin(aMin)),
                       x + _LONG((beam + 2) * cos(aMin)),
                       y - _LONG((beam + 2) * sin(aMin)));
        }


    //--------------------------------------------------------------------------
        void GLayoutVector::DrawGridCell(GGridCell&W, Vector2DRenderer&D,
                                         GLayoutVectorResource&RES)
        {
            if ((W.Width()<2) || (W.Height()<2)) { return; }
            uint32_t l = W.Rect().left;
            uint32_t t = W.Rect().top;
            uint32_t w = W.Rect().width;
            uint32_t h = W.Rect().height;
            --w;
            --h;
            switch (RES.style) {
                case GLayoutVectorResource::LOWERED:
                    D.SetPenColor(shadowBright);
                    break;
                default:
                    D.SetPenColor(shadowDark);
                    break;
            }
            D.DrawLine(l+w, t, l+w, t+h);
            D.DrawLine(l+w, t+h, l, t+h);

            if (W.DrawBackground()) {
                if (W.Pushed() || W.Selected()) {
                    D.SetPenColor(fgDown);
                }
                else {
                    D.SetPenColor(fgUp);
                }
                D.DrawRect(l, t, w, h);
            }
        }*/
} // namespace lysa::ui
