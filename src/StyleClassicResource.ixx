/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.style_classic_resource;

import lysa.math;
import lysa.types;

import lysa.ui.uiresource;

export namespace lysa::ui {

    /**
     * UI resources for the classic style.
     */
    class StyleClassicResource : public UIResource {
    public:
        /**
         * Style appearance options.
         */
        enum Style {
            FLAT,    //! Flat appearance
            RAISED,  //! 3D raised appearance
            LOWERED  //! 3D lowered appearance
        };

        Style style{RAISED};     //! Current style appearance
        float width{0};          //! Requested width
        float height{0};         //! Requested height
        bool customColor{false}; //! Whether a custom color is used
        float4 color{0.0f};      //! Custom color value

        /**
         * Constructor.
         * @param resource Resource description string made of comma-separated
         *        "key=value" pairs, in any order. Supported keys:
         *        - width=<float>
         *        - height=<float>
         *        - style=FLAT|RAISED|LOWERED
         *        - color=<r> <g> <b> <a> (space-separated floats)
         *        Example: "style=RAISED,width=100,color=1 0 0 1".
         */
        explicit StyleClassicResource(const std::string& resource);

    private:
        void splitResString(const std::string& resource);
    };
}
