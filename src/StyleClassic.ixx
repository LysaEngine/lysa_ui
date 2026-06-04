/*
 * Copyright (c) 2024-resent Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.style_classic;

import lysa.math;
import lysa.rect;
import lysa.renderers.vector_2d;
import lysa.ui.button;
import lysa.ui.check_widget;
import lysa.ui.frame;
import lysa.ui.line;
import lysa.ui.panel;
import lysa.ui.progress_bar;
import lysa.ui.uiresource;
import lysa.ui.scroll_bar;
import lysa.ui.scroll_box;
import lysa.ui.selection;
import lysa.ui.style;
import lysa.ui.style_classic_resource;
import lysa.ui.text;
import lysa.ui.text_edit;
import lysa.ui.toggle_button;
import lysa.ui.tree_view;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * Classic vector style UI with 3D look.
     */
    class StyleClassic : public Style {
    public:
        ~StyleClassic() override = default;

        /**
         * Draws a widget using the classic 3D look.
         * @param widget Widget to draw.
         * @param resources Resources used for drawing.
         * @param renderer The 2D renderer.
         * @param before True when called before drawing children, false after.
         */
        void draw(const Widget &widget, UIResource &resources, Vector2DRenderer &renderer, bool before) const override;

        /**
         * Parses and applies a resource description string to a widget.
         * @param widget Widget to associate resources with.
         * @param resources String describing the style resources.
         */
        void addResource(Widget &widget, const std::string &resources) override;

        /**
         * Adjusts widget size to classic style constraints (borders, padding, etc.).
         * @param widget The widget being resized.
         * @param rect The rectangle to adjust.
         * @param resources The widget's UI resources.
         */
        void resize(Widget &widget, Rect &rect, UIResource &resources) override;

    private:
        float4 focus{};
        float4 shadowDark{};
        float4 shadowBright{};
        float4 fgUp{};
        float4 fgDown{};
        // GTexture	*texture;

        void updateOptions() override;

        float4 extractColor(const std::string &OPT, float R, float G, float B, float A = 1.0f) const;

        void drawPanel(const Panel &, StyleClassicResource &, Vector2DRenderer &) const;

        void drawBox(const Widget &, const StyleClassicResource &, Vector2DRenderer &, bool pushable) const;

        void drawLine(const Line &, const StyleClassicResource &, Vector2DRenderer &) const;

        void drawButton(const Button &, StyleClassicResource &, Vector2DRenderer &) const;

        void drawToggleButton(ToggleButton &, StyleClassicResource &, Vector2DRenderer &) const;

        void drawText(const Text &, const StyleClassicResource &, Vector2DRenderer &) const;

        void drawFrame(Frame &, StyleClassicResource &, Vector2DRenderer &) const;

        void drawTextEdit(const TextEdit&, Vector2DRenderer&) const;

        void drawSelection(const Selection &, const StyleClassicResource &, Vector2DRenderer &) const;

        void drawProgressBar(const ProgressBar &, const StyleClassicResource &, Vector2DRenderer &) const;

        /*void drawArrow(GArrow&, GLayoutVectorResource&, VectorRenderer&);
        void drawCheckmark(GCheckmark&, GLayoutVectorResource&, VectorRenderer&);
        void drawTrackBar(GTrackBar&, GLayoutVectorResource&, VectorRenderer&);
        void drawRoundButton(GRoundButton&, GLayoutVectorResource&, VectorRenderer&);
        void drawTabButton(GTabButton&, GLayoutVectorResource&, VectorRenderer&);
        void drawTabs(GTabs&, GLayoutVectorResource&, VectorRenderer&);
        void drawGridCell(GGridCell&, GLayoutVectorResource&, VectorRenderer&);*/
    };

} // namespace lysa::ui
