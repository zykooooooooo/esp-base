#pragma once
#include <include.h>
#include <src/engine/sdk.h>
#include <thirdparty/imgui/imgui.h>
#include <thirdparty/imgui/imgui_impl_win32.h>
#include <thirdparty/imgui/imgui_impl_dx11.h>
#include <thirdparty/imgui/imgui_internal.h>
#include <mutex>
#include <atomic>
#include <vector>

inline ImFont* interFont;

namespace updater {

    void run( );
    void env_run( );
} // namespace updater

namespace aimbot {
    inline bool enabled = false;
}

namespace visuals {
    void draw_actors( ImDrawList* drawlist );
    inline bool boxes = true;
    inline bool corner_boxes = true;
    inline int thickness = 1;
    inline bool corner_box_outlined = false;
    inline bool distance = false;
    inline bool skeletonesp = false;
    inline bool username = true;
    inline bool rankesp = false;
    inline bool use_text = false;
    inline bool weaponesp = false;
}

namespace misc {
    inline bool vsync = false;
    inline bool showfps = true;
}