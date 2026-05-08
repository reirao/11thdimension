/*
    zero_0000.c
    -----------
    Canonical ZERO consolidation generated from D:\ZERO on 2026-05-07.

    Build TCC:
        tcc zero_0000.c -o zero_0000.exe -lgdi32 -luser32 -lkernel32

    Runtime base:
        D:\ZERO\01001.c
        BHB GraphField v0.10.1.1-m1 - Visual Mirror

    Consolidation rule:
        This is not a raw concatenation of all prototypes. The older files are
        standalone historical programs with duplicate WinMain, global state,
        enums and message loops. zero_0000.c keeps the latest integrated runtime
        as the executable body and records the prior sources below as lineage.

    Source lineage:
    - pixelfield0.c  (4184 bytes, 2026-05-06 13:15:36)
    - bhb_zone_a0.c  (14030 bytes, 2026-05-06 17:53:16)
    - graphfield_win0.c  (13029 bytes, 2026-05-06 17:53:42)
    - graphfield_win0 (1).c  (13542 bytes, 2026-05-06 18:55:28)
    - graphfield_win0 (2).c  (13029 bytes, 2026-05-06 18:55:39)
    - graphfield_win0 (3).c  (13542 bytes, 2026-05-06 18:57:46)
    - bhb_one_world_projection_demo.c  (19070 bytes, 2026-05-06 20:20:55)
    - bhb_one_world_graphfield_win_v0_2.c  (33652 bytes, 2026-05-06 20:33:42)
    - bhb_one_world_graphfield_win_v0_2_1.c  (33750 bytes, 2026-05-06 20:54:39)
    - bhb_one_world_graphfield_win_v0_3.c  (55115 bytes, 2026-05-06 21:12:01)
    - bhb_one_world_graphfield_win_v0_4_ui_engine.c  (64112 bytes, 2026-05-06 21:20:11)
    - bhb_graphfield_strict_engine_v0_6_1.c  (35817 bytes, 2026-05-06 21:38:50)
    - bhb_graphfield_object_panels_v0_7.c  (52747 bytes, 2026-05-06 22:06:03)
    - bhb_graphfield_blackhole_pixelspace_v0_8.c  (36754 bytes, 2026-05-06 22:10:38)
    - bhb_graphfield_blackhole_pixelspace_v0_8_1.c  (37260 bytes, 2026-05-06 22:12:34)
    - bhb_graphfield_emergent_infinity_v0_9.c  (43878 bytes, 2026-05-06 22:17:04)
    - bhb_graphfield_emergent_infinity_v0_9_1.c  (44723 bytes, 2026-05-06 22:20:50)
    - bhb_graphfield_emergent_infinity_v0_9_2_micro_merge0.c  (47735 bytes, 2026-05-06 22:28:22)
    - bhb_graphfield_emergent_infinity_v0_9_3_micro_merge1.c  (52703 bytes, 2026-05-06 22:41:30)
    - bhb_graphfield_multiscale_camera_v0_9_4.c  (58309 bytes, 2026-05-07 08:52:31)
    - last.c  (64740 bytes, 2026-05-07 09:16:36)
    - bhb_graphfield_blackhole_feeder_v0_9_5.c  (64875 bytes, 2026-05-07 09:54:39)
    - 096.c  (78863 bytes, 2026-05-07 10:11:39)
    - 097.c  (103102 bytes, 2026-05-07 11:13:31)
    - 098.c  (103180 bytes, 2026-05-07 11:42:06)
    - bhb_graphfield_window_action_registry_v0_9_9.c  (110753 bytes, 2026-05-07 11:48:44)
    - 099.c  (110753 bytes, 2026-05-07 11:59:12)
    - 09910.c  (111486 bytes, 2026-05-07 12:15:23)
    - 09911.c  (112681 bytes, 2026-05-07 12:27:53)
    - 01000.c  (128070 bytes, 2026-05-07 12:40:29)
    - 01001.c  (136476 bytes, 2026-05-07 13:13:06)
*/
/*
    zero_0000.c
    ----------------------------------------
    ZERO 0000 - GraphField Visual Mirror

    Focus:
        - unbounded sparse pixel-space
        - camera over infinite coordinate field
        - chunk grid as projection, not hard border
        - pixels are registered objects
        - blackhole is registered object
        - clusters can become BODY objects
        - "real things" begin to emerge:
              pixel dust -> local cluster -> registered body
        - no objective loop
        - no artificial completion

    Build TCC:
        tcc zero_0000.c -o zero_0000.exe -lgdi32 -luser32 -lkernel32

    Controls:
        LMB drag             use current desktop tool (emit/erase/select/BH)
        RMB                  place/move blackhole
        MMB                  select nearest object
        Wheel                brush radius
        +/-                  zoom
        W/A/S/D              pan camera
        Arrow keys           pan camera
        Space                pause/resume
        N                    single step
        1                    material DUST
        2                    material METAL
        3                    material LIGHT
        4                    material STONE
        5                    tool BH
        6                    tool EMIT
        7                    tool ERASE
        8                    tool SELECT
        Y                    cycle tool
        B                    blackhole at mouse
        F                    forge bodies from pixel clusters
        A                    auto-forge on/off
        K                    kill selected
        C                    clear pixels
        R                    reset
        G                    gravity on/off
        O                    cohesion on/off
        H                    horizon absorption on/off
        T                    trails on/off
        I                    inspector on/off
        L                    labels on/off
        Tab                  cycle selection
        Q/Esc                quit
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define APP_W 1400
#define APP_H 880

#define MAX_ENT 8192
#define MAX_TRACE 512
#define MAX_TEXT 160

#define CHUNK_SIZE 64.0
#define BODY_FORGE_DIST 5.2
#define MULTISCALE_PIXEL_LEVEL 1.40
#define MULTISCALE_BODY_LEVEL 0.42
#define MULTISCALE_META_LEVEL 0.14
#define CAMERA_PAN_BASE 18.0
#define CAMERA_FAST_MULT 5.0
#define CAMERA_SLOW_MULT 0.22
#define CAMERA_ZOOM_STEP 1.18
#define CAMERA_ZOOM_FAST_STEP 1.75

#define FEEDER_DEFAULT_RATE 24
#define FEEDER_DEFAULT_SPEED 32.0
#define FEEDER_DEFAULT_SPREAD 0.35
#define FEEDER_MAX_RATE 240
#define FORCE_STEP 1.25
#define BH_RADIUS_STEP 1.15
#define BH_HORIZON_STEP 1.15

#define MAX_CONTROL_BINDINGS 96

typedef enum {
    ACT_NONE = 0,
    ACT_PAN_UP,
    ACT_PAN_DOWN,
    ACT_PAN_LEFT,
    ACT_PAN_RIGHT,
    ACT_ZOOM_IN,
    ACT_ZOOM_OUT,
    ACT_CAMERA_HOME,
    ACT_CAMERA_FOCUS,
    ACT_PAUSE,
    ACT_STEP,
    ACT_RESET,
    ACT_QUIT,
    ACT_MAT_DUST,
    ACT_MAT_METAL,
    ACT_MAT_LIGHT,
    ACT_MAT_STONE,
    ACT_BLACKHOLE_AT_MOUSE,
    ACT_FEEDER_TOGGLE,
    ACT_FEEDER_BURST,
    ACT_FEEDER_RATE_DOWN,
    ACT_FEEDER_RATE_UP,
    ACT_BH_FORCE_DOWN,
    ACT_BH_FORCE_UP,
    ACT_BH_RADIUS_DOWN,
    ACT_BH_RADIUS_UP,
    ACT_BH_HORIZON_DOWN,
    ACT_BH_HORIZON_UP,
    ACT_FORCE_RINGS_TOGGLE,
    ACT_KICK_SELECTED,
    ACT_FORGE_BODY,
    ACT_SPAWN_ATOM,
    ACT_ELEMENT_PREV,
    ACT_ELEMENT_NEXT,
    ACT_ATOM_VIEW_TOGGLE,
    ACT_SAVE_ASSET,
    ACT_GRAVITY_TOGGLE,
    ACT_COHESION_TOGGLE,
    ACT_HORIZON_TOGGLE,
    ACT_TRAILS_TOGGLE,
    ACT_INSPECTOR_TOGGLE,
    ACT_LABELS_TOGGLE,
    ACT_MULTISCALE_TOGGLE,
    ACT_VECTORS_TOGGLE,
    ACT_SMOOTH_CAMERA_TOGGLE,
    ACT_SELECT_NEXT,
    ACT_DELETE_SELECTED,
    ACT_CLEAR_PIXELS,
    ACT_AUTO_FORGE_TOGGLE,
    ACT_CONTROLS_TOGGLE,
    ACT_REMAP_SELECTED,
    ACT_REMAP_NEXT,
    ACT_REMAP_PREV,
    ACT_EVENT_PANEL_TOGGLE,
    ACT_WINDOW_REGISTRY_TOGGLE,
    ACT_WIRING_PANEL_TOGGLE,
    ACT_WIRING_STRIP_TOGGLE,
    ACT_SELF_STUDIO_TOGGLE,
    ACT_NODE_SELECT_NEXT,
    ACT_NODE_SELECT_PREV,
    ACT_NODE_TOGGLE_EDIT,
    ACT_NODE_DUPLICATE_SELECTED,
    ACT_WINDOW_SELECT_NEXT,
    ACT_WINDOW_SELECT_PREV,
    ACT_WINDOW_TOGGLE_SELECTED,
    ACT_WINDOW_MOVE_LEFT,
    ACT_WINDOW_MOVE_RIGHT,
    ACT_WINDOW_MOVE_UP,
    ACT_WINDOW_MOVE_DOWN,
    ACT_WINDOW_GROW,
    ACT_WINDOW_SHRINK,
    ACT_WINDOW_DECORATOR_NEXT,
    ACT_WINDOW_LAYOUT_CASCADE,
    ACT_COUNT
} ActionId;

typedef struct {
    int alive;
    ActionId action;
    int key;
    int default_key;
    char name[40];
    char description[96];
} ControlBinding;


#define MAX_EVENT_RECORDS 2048
#define MAX_CONTEXT_BINDINGS 192

#define CTX_ANY              0x00000000u
#define CTX_WORLD            0x00000001u
#define CTX_CONTROLS_PANEL   0x00000002u
#define CTX_CAPTURE          0x00000004u
#define CTX_ATOM_SELECTED    0x00000008u
#define CTX_BLACKHOLE_SEL    0x00000010u
#define CTX_BODY_SELECTED    0x00000020u
#define CTX_MOUSE_OVER_FIELD 0x00000040u
#define CTX_SCALE_PIXEL      0x00000080u
#define CTX_SCALE_BODY       0x00000100u
#define CTX_SCALE_META       0x00000200u
#define CTX_SCALE_MAP        0x00000400u
#define CTX_WINDOW_REGISTRY  0x00000800u

typedef enum {
    EVT_NONE = 0,
    EVT_KEY_DOWN,
    EVT_MOUSE_MOVE,
    EVT_MOUSE_DOWN,
    EVT_MOUSE_UP,
    EVT_MOUSE_WHEEL,
    EVT_TIMER
} EventType;

typedef struct {
    int alive;
    int id;
    EventType type;
    int code;
    int mouse_x;
    int mouse_y;
    int wheel_delta;
    int source_entity;
    int target_entity;
    unsigned int context_mask;
    double time;
    char note[96];
} EventRecord;

typedef struct {
    int focused_entity;
    int hovered_entity;
    int selected_entity;
    int active_panel;
    int active_tool;
    int scale_level;
    int capture_mode;
    int mouse_over_field;
    unsigned int mask;
} EventContext;

typedef struct {
    int alive;
    EventType event_type;
    int event_code;
    unsigned int required_mask;
    unsigned int forbidden_mask;
    int priority;
    ActionId action;
    char name[48];
} ContextBinding;


#define MAX_WINDOW_RECORDS 32
#define MAX_WINDOW_ACTION_BINDINGS 64
#define WINDOW_DECORATOR_COUNT 5
#define WIN_CAP_MOVABLE       0x00000001u
#define WIN_CAP_RESIZABLE     0x00000002u
#define WIN_CAP_CLOSABLE      0x00000004u
#define WIN_CAP_BLOCKS_FIELD  0x00000008u
#define WIN_CAP_DECORATED     0x00000010u

typedef enum {
    WIN_NONE = 0,
    WIN_INSPECTOR,
    WIN_TRACE,
    WIN_CONTROLS,
    WIN_EVENTS,
    WIN_WINDOW_REGISTRY,
    WIN_WIRING,
    WIN_SELF_STUDIO,
    WIN_FIELD
} WindowId;

typedef struct {
    int alive;
    WindowId id;
    int open;
    int modal;
    int z_order;
    RECT rc;
    int user_placed;
    unsigned int caps;
    int decorator;
    double last_touched;
    ActionId toggle_action;
    char name[48];
    char role[96];
} WindowRecord;

typedef struct {
    const char *name;
    COLORREF panel;
    COLORREF title;
    COLORREF edge;
    COLORREF accent;
    COLORREF text;
} WindowDecorator;

typedef struct {
    int alive;
    WindowId window_id;
    ActionId action;
    char relation[48];
    char note[96];
} WindowActionBinding;


#define MAX_NODES 256
#define MAX_NODE_PROPS 512

#define ROLE_CONTROL  0x00000001u
#define ROLE_EDIT     0x00000002u
#define ROLE_CONTENT  0x00000004u
#define ROLE_ACTION   0x00000008u
#define ROLE_WINDOW   0x00000010u
#define ROLE_BUTTON   0x00000020u
#define ROLE_PANEL    0x00000040u
#define ROLE_TOOL     0x00000080u
#define ROLE_ENTITY   0x00000100u
#define ROLE_MENU     0x00000200u
#define ROLE_WORKFLOW 0x00000400u
#define ROLE_PREFAB   0x00000800u

#define CAP_DRAG      0x00000001u
#define CAP_RESIZE    0x00000002u
#define CAP_EDIT      0x00000004u
#define CAP_DELETE    0x00000008u
#define CAP_DUPLICATE 0x00000010u
#define CAP_CONTAIN   0x00000020u
#define CAP_BIND      0x00000040u
#define CAP_RUN       0x00000080u
#define CAP_SAVE      0x00000100u
#define CAP_DEFINE    0x00000200u

typedef enum {
    PROP_NONE = 0,
    PROP_INT,
    PROP_FLOAT,
    PROP_BOOL,
    PROP_STRING,
    PROP_REF
} PropType;

typedef struct {
    int alive;
    int id;
    int parent_id;
    int first_child;
    int child_count;
    unsigned int roles;
    unsigned int caps;
    int window_id;
    ActionId primary_action;
    int selected;
    int open;
    int visible;
    int editable;
    double x, y, w, h;
    char name[48];
    char label[96];
    char kind[32];
    char workflow[96];
} BHBNode;

typedef struct {
    int alive;
    int id;
    int owner_node_id;
    PropType type;
    char key[48];
    char value[128];
} BHBProperty;


#define BODY_MIN_PIXELS 6
#define FORGE_MAX_CLUSTER 512
#define FORGE_MAX_SCAN 8192


/*
    Visual Mirror from blackhole_desktop.c:
    Only a tiny stable preset is imported here, not the full desktop system.
    Source constants preserved as BHD_* so their origin is visible.
*/
#define BHD_BH_MASS 3200.0
#define BHD_BH_SPIN 160.0
#define BHD_BH_SOFTEN 42.0
#define BHD_BH_RADIUS 12.0
#define BHD_CAM_MIN_ZOOM 0.002
#define BHD_CAM_MAX_ZOOM 6000.0
#define BHD_EMIT_COUNT 140
#define BHD_EMIT_RADIUS 36.0
#define BHD_EMIT_SPEED 90.0
#define BHD_EMIT_MASS 1.4
#define BHD_ERASE_RADIUS 28.0
#define BHD_BH_GROW_MASS 18.0
#define BHD_BH_GROW_RADIUS 0.03
#define BHD_BH_MASS_MAX 200000.0
#define BHD_BH_RADIUS_MAX 400.0
#define BHD_CURSOR_DOT_RADIUS 3

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef enum {
    ENT_NONE = 0,
    ENT_PIXEL,
    ENT_BLACKHOLE,
    ENT_PROBE,
    ENT_BODY,
    ENT_BODY_CORE,
    ENT_SUBPARTICLE,
    ENT_NUCLEON,
    ENT_ATOM,
    ENT_ELEMENT_ASSET
} EntityKind;

typedef enum {
    MAT_NONE = 0,
    MAT_DUST,
    MAT_METAL,
    MAT_LIGHT,
    MAT_STONE
} MaterialKind;

typedef enum {
    PT_NONE = 0,
    PT_UP_QUARK,
    PT_DOWN_QUARK,
    PT_ELECTRON,
    PT_PROTON,
    PT_NEUTRON,
    PT_NUCLEUS,
    PT_ATOM
} ParticleKind;

typedef enum {
    TOOL_BH = 0,
    TOOL_EMIT,
    TOOL_ERASE,
    TOOL_SELECT,
    TOOL_COUNT
} ToolMode;


typedef enum {
    MODE_DEF = 0,
    MODE_OBS,
    MODE_INF,
    MODE_ABD,
    MODE_UNKNOWN,
    MODE_CONFLICT
} EMode;

typedef struct { double x, y; } Vec2;

typedef struct {
    double bh_mass;
    double bh_spin;
    double bh_soften;
    double bh_radius;
    double cam_min_zoom;
    double cam_max_zoom;
    int emit_count;
    double emit_radius;
    double emit_speed;
    double emit_mass;
    double erase_radius;
    double bh_grow_mass;
    double bh_grow_radius;
    double bh_mass_max;
    double bh_radius_max;
    int cursor_dot_radius;
    int imported;
} DesktopKernelPreset;

typedef struct {
    int alive;
    int id;
    EntityKind kind;
    MaterialKind material;
    ParticleKind particle;
    EMode mode;

    char name[32];
    char label[MAX_TEXT];
    char origin[MAX_TEXT];
    char definition[MAX_TEXT];
    char storage[MAX_TEXT];

    Vec2 pos;
    Vec2 prev;
    Vec2 vel;

    double radius;
    double mass;
    double damping;
    double heat;
    double electric_charge;
    int atomic_number;
    int mass_number;
    int protons;
    int neutrons;
    int electrons;
    int parent_atom_id;
    int reusable_asset_id;

    /* blackhole */
    double gravity_strength;
    double gravity_radius;
    double event_horizon;
    int absorbs;

    /* emergent body */
    int body_id;
    int child_count;
    double cohesion;
    double spin;
    double stiffness;
    double fracture_limit;
    double density;
    double meta_vx;
    double meta_vy;

    /* object state */
    int selected;
    int hovered;
    int editable;
    int visible;
    int locked;
    int version;
    int dirty;

    double pulse;
} Entity;

typedef struct {
    int alive;
    int id;
    double t;
    char action[32];
    int actor_id;
    int target_id;
    char note[MAX_TEXT];
} Trace;

typedef struct {
    int alive;
    int atomic_number;
    int mass_number;
    char symbol[4];
    char name[32];
    double atomic_mass;
    char storage[64];
    char definition[MAX_TEXT];
} ElementPreset;

typedef struct {
    Entity ent[MAX_ENT];
    Trace trace[MAX_TRACE];
    ElementPreset preset[16];
    ControlBinding controls[MAX_CONTROL_BINDINGS];
    EventRecord events[MAX_EVENT_RECORDS];
    ContextBinding ctx_bind[MAX_CONTEXT_BINDINGS];
    WindowRecord windows[MAX_WINDOW_RECORDS];
    WindowActionBinding win_actions[MAX_WINDOW_ACTION_BINDINGS];
    BHBNode nodes[MAX_NODES];
    BHBProperty props[MAX_NODE_PROPS];

    int next_ent_id;
    int next_trace_id;
    int next_event_id;

    int selected_id;
    int hovered_id;
    int blackhole_id;
    int probe_id;

    MaterialKind mat;
    ToolMode tool;

    int paused;
    int step_once;
    int gravity_on;
    int cohesion_on;
    int absorb_on;
    int trails_on;
    int inspector_on;
    int labels_on;
    int auto_forge;
    int feeder_on;
    int feeder_rate;
    double feeder_speed;
    double feeder_spread;
    double feeder_accum;
    int feeder_emit_total;
    int show_force_field;
    int forge_element_index;
    int atom_view_on;
    int atom_component_count;
    int saved_asset_count;
    int controls_panel_on;
    int controls_selected;
    int controls_capture;
    int controls_conflict_count;
    int event_resolver_on;
    int event_panel_on;
    int last_event_id;
    int last_resolved_action;
    int last_context_mask;
    int event_conflict_count;
    int window_registry_panel_on;
    int wiring_panel_on;
    int wiring_strip_on;
    int window_registry_selected;
    int next_window_z;
    WindowId window_active_id;
    WindowId window_drag_id;
    int window_drag_dx;
    int window_drag_dy;
    WindowId window_resize_id;
    int window_resize_dx;
    int window_resize_dy;
    int self_studio_on;
    int node_selected_index;
    int next_node_id;
    int next_prop_id;

    int brush_radius;
    int mouse_x;
    int mouse_y;
    int mouse_l;
    int mouse_r;

    double cam_x;
    double cam_y;
    double zoom;
    double target_cam_x;
    double target_cam_y;
    double target_zoom;
    int camera_smooth;
    int show_vectors;
    int multiscale_mode;

    double time;
    double last_clock;
    double accumulator;
    double fps;
    double frame_ms;
    double sim_ms;

    int pixels_alive;
    int bodies_alive;
    int absorbed_count;
    int forged_count;
    double auto_forge_timer;
    int chunk_x;
    int chunk_y;

    RECT field_rc;
    RECT self_studio_rc;
    RECT self_tree_rc;
    RECT self_canvas_rc;
    RECT self_editor_rc;
    int node_dragging;
    int node_drag_id;
    double node_drag_dx;
    double node_drag_dy;

    HDC memdc;
    HBITMAP membmp;
    HBITMAP oldbmp;
    int back_w, back_h;

    DesktopKernelPreset desktop_preset;
    int desktop_preset_applied;

    char status[MAX_TEXT];
} World;

static World g;
static LARGE_INTEGER qpf;

/* ---------- util ---------- */

static double clock_s(void) {
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart / (double)qpf.QuadPart;
}

static void copy_s(char *dst, int n, const char *src) {
    if (!dst || n <= 0) return;
    if (!src) src = "";
    lstrcpynA(dst, src, n);
    dst[n - 1] = 0;
}

static double clampd(double v, double lo, double hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static double dist2(double ax, double ay, double bx, double by) {
    double dx = ax - bx;
    double dy = ay - by;
    return dx*dx + dy*dy;
}

static double deterministic_unit(int seed) {
    /* small deterministic pseudo-random 0..1 for stable C89/TCC behavior */
    unsigned int x = (unsigned int)seed * 1103515245u + 12345u;
    x ^= (x >> 16);
    x *= 2246822519u;
    x ^= (x >> 13);
    return (double)(x & 0xffffu) / 65535.0;
}

static int rect_contains(RECT r, int x, int y) {
    return x >= r.left && x <= r.right && y >= r.top && y <= r.bottom;
}

static const char *kind_name(EntityKind k) {
    switch (k) {
        case ENT_PIXEL: return "PIXEL";
        case ENT_BLACKHOLE: return "BLACKHOLE";
        case ENT_PROBE: return "PROBE";
        case ENT_BODY: return "BODY";
        case ENT_BODY_CORE: return "BODY_CORE";
        case ENT_SUBPARTICLE: return "SUBPARTICLE";
        case ENT_NUCLEON: return "NUCLEON";
        case ENT_ATOM: return "ATOM";
        case ENT_ELEMENT_ASSET: return "ELEMENT_ASSET";
        default: return "NONE";
    }
}


static const char *particle_name(ParticleKind p) {
    switch (p) {
        case PT_UP_QUARK: return "UP_QUARK";
        case PT_DOWN_QUARK: return "DOWN_QUARK";
        case PT_ELECTRON: return "ELECTRON";
        case PT_PROTON: return "PROTON";
        case PT_NEUTRON: return "NEUTRON";
        case PT_NUCLEUS: return "NUCLEUS";
        case PT_ATOM: return "ATOM";
        default: return "NONE";
    }
}

static const char *mat_name(MaterialKind m) {
    switch (m) {
        case MAT_DUST: return "DUST";
        case MAT_METAL: return "METAL";
        case MAT_LIGHT: return "LIGHT";
        case MAT_STONE: return "STONE";
        default: return "NONE";
    }
}

static const char *tool_name(ToolMode t) {
    switch (t) {
        case TOOL_BH: return "BH";
        case TOOL_EMIT: return "EMIT";
        case TOOL_ERASE: return "ERASE";
        case TOOL_SELECT: return "SELECT";
        default: return "?";
    }
}

static const char *mode_name(EMode m) {
    switch (m) {
        case MODE_DEF: return "DEF";
        case MODE_OBS: return "OBS";
        case MODE_INF: return "INF";
        case MODE_ABD: return "ABD";
        case MODE_UNKNOWN: return "UNKNOWN";
        case MODE_CONFLICT: return "CONFLICT";
        default: return "?";
    }
}

static COLORREF mat_color(MaterialKind m) {
    switch (m) {
        case MAT_DUST: return RGB(210,190,130);
        case MAT_METAL: return RGB(160,190,220);
        case MAT_LIGHT: return RGB(255,245,130);
        case MAT_STONE: return RGB(135,145,155);
        default: return RGB(210,220,230);
    }
}

static COLORREF kind_color(EntityKind k) {
    switch (k) {
        case ENT_PIXEL: return RGB(210,220,230);
        case ENT_BLACKHOLE: return RGB(255,96,96);
        case ENT_PROBE: return RGB(76,210,255);
        case ENT_BODY: return RGB(120,255,150);
        case ENT_BODY_CORE: return RGB(255,220,90);
        case ENT_SUBPARTICLE: return RGB(255,180,90);
        case ENT_NUCLEON: return RGB(255,120,120);
        case ENT_ATOM: return RGB(120,220,255);
        case ENT_ELEMENT_ASSET: return RGB(200,140,255);
        default: return RGB(180,180,180);
    }
}

static COLORREF mode_color(EMode m) {
    switch (m) {
        case MODE_DEF: return RGB(226,234,242);
        case MODE_OBS: return RGB(76,210,255);
        case MODE_INF: return RGB(120,255,150);
        case MODE_ABD: return RGB(255,220,90);
        case MODE_UNKNOWN: return RGB(150,135,255);
        case MODE_CONFLICT: return RGB(255,96,96);
        default: return RGB(180,180,180);
    }
}

/* ---------- gdi ---------- */

static HPEN pen(COLORREF c, int w) { return CreatePen(PS_SOLID, w, c); }
static HBRUSH brush(COLORREF c) { return CreateSolidBrush(c); }

static void draw_text(HDC dc, int x, int y, const char *s) {
    if (s && *s) TextOutA(dc, x, y, s, lstrlenA(s));
}

static void fill_rect_c(HDC dc, RECT r, COLORREF c) {
    HBRUSH b = brush(c);
    FillRect(dc, &r, b);
    DeleteObject(b);
}

static void line_c(HDC dc, int x1, int y1, int x2, int y2, COLORREF c, int w) {
    HPEN p = pen(c, w);
    HGDIOBJ old = SelectObject(dc, p);
    MoveToEx(dc, x1, y1, 0);
    LineTo(dc, x2, y2);
    SelectObject(dc, old);
    DeleteObject(p);
}

static void rect_outline(HDC dc, RECT r, COLORREF c, int w) {
    line_c(dc, r.left, r.top, r.right, r.top, c, w);
    line_c(dc, r.right, r.top, r.right, r.bottom, c, w);
    line_c(dc, r.right, r.bottom, r.left, r.bottom, c, w);
    line_c(dc, r.left, r.bottom, r.left, r.top, c, w);
}

static void ellipse_c(HDC dc, int x, int y, int r, COLORREF edge, COLORREF fill, int lw) {
    HPEN p = pen(edge, lw);
    HBRUSH b = brush(fill);
    HGDIOBJ oldp = SelectObject(dc, p);
    HGDIOBJ oldb = SelectObject(dc, b);
    Ellipse(dc, x-r, y-r, x+r, y+r);
    SelectObject(dc, oldb);
    SelectObject(dc, oldp);
    DeleteObject(b);
    DeleteObject(p);
}

/* ---------- trace ---------- */

static void trace_add(const char *action, int actor, int target, const char *note) {
    int slot = (g.next_trace_id - 1) % MAX_TRACE;
    Trace *t = &g.trace[slot];
    memset(t, 0, sizeof(*t));
    t->alive = 1;
    t->id = g.next_trace_id++;
    t->t = g.time;
    t->actor_id = actor;
    t->target_id = target;
    copy_s(t->action, sizeof(t->action), action);
    copy_s(t->note, sizeof(t->note), note);
    copy_s(g.status, sizeof(g.status), note);
}

/* ---------- registry ---------- */

static Entity *entity_by_id(int id) {
    int i;
    if (id <= 0) return 0;
    for (i = 0; i < MAX_ENT; ++i)
        if (g.ent[i].alive && g.ent[i].id == id)
            return &g.ent[i];
    return 0;
}

static Entity *entity_new(EntityKind kind, MaterialKind mat, EMode mode,
                          const char *name, const char *label,
                          double x, double y, double radius, double mass) {
    int i;
    for (i = 0; i < MAX_ENT; ++i) {
        if (!g.ent[i].alive) {
            Entity *e = &g.ent[i];
            memset(e, 0, sizeof(*e));
            e->alive = 1;
            e->id = g.next_ent_id++;
            e->kind = kind;
            e->material = mat;
            e->mode = mode;
            copy_s(e->name, sizeof(e->name), name);
            copy_s(e->label, sizeof(e->label), label);
            e->pos.x = x;
            e->pos.y = y;
            e->prev = e->pos;
            e->radius = radius;
            e->mass = mass;
            e->damping = 0.995;
            e->visible = 1;
            e->editable = 1;
            copy_s(e->origin, sizeof(e->origin), "runtime.registry");
            copy_s(e->definition, sizeof(e->definition), "registered sparse-space entity");
            copy_s(e->storage, sizeof(e->storage), "entity-reg");
            trace_add("create", 0, e->id, "entity registered");
            return e;
        }
    }
    trace_add("create_failed", 0, 0, "entity registry full");
    return 0;
}

static void entity_delete(int id) {
    Entity *e = entity_by_id(id);
    if (!e) return;
    e->alive = 0;
    if (g.selected_id == id) g.selected_id = 0;
    if (g.hovered_id == id) g.hovered_id = 0;
    if (g.blackhole_id == id) g.blackhole_id = 0;
    trace_add("delete", 0, id, "entity removed");
}

static void select_entity(int id) {
    Entity *old = entity_by_id(g.selected_id);
    Entity *e = entity_by_id(id);
    if (old) old->selected = 0;
    g.selected_id = id;
    if (e) {
        e->selected = 1;
        e->pulse = 0.5;
        trace_add("select", g.probe_id, e->id, "selected entity");
    }
}

static void hover_entity(int id) {
    Entity *old = entity_by_id(g.hovered_id);
    Entity *e = entity_by_id(id);
    if (old) old->hovered = 0;
    g.hovered_id = id;
    if (e) e->hovered = 1;
}

static void cycle_selected(void) {
    int i, after = (g.selected_id == 0);
    for (i = 0; i < MAX_ENT; ++i) {
        Entity *e = &g.ent[i];
        if (!e->alive) continue;
        if (after) { select_entity(e->id); return; }
        if (e->id == g.selected_id) after = 1;
    }
}


/* ---------- micro merge preset ---------- */

static void desktop_preset_init(void) {
    g.desktop_preset.bh_mass = BHD_BH_MASS;
    g.desktop_preset.bh_spin = BHD_BH_SPIN;
    g.desktop_preset.bh_soften = BHD_BH_SOFTEN;
    g.desktop_preset.bh_radius = BHD_BH_RADIUS;
    g.desktop_preset.cam_min_zoom = BHD_CAM_MIN_ZOOM;
    g.desktop_preset.cam_max_zoom = BHD_CAM_MAX_ZOOM;
    g.desktop_preset.emit_count = BHD_EMIT_COUNT;
    g.desktop_preset.emit_radius = BHD_EMIT_RADIUS;
    g.desktop_preset.emit_speed = BHD_EMIT_SPEED;
    g.desktop_preset.emit_mass = BHD_EMIT_MASS;
    g.desktop_preset.erase_radius = BHD_ERASE_RADIUS;
    g.desktop_preset.bh_grow_mass = BHD_BH_GROW_MASS;
    g.desktop_preset.bh_grow_radius = BHD_BH_GROW_RADIUS;
    g.desktop_preset.bh_mass_max = BHD_BH_MASS_MAX;
    g.desktop_preset.bh_radius_max = BHD_BH_RADIUS_MAX;
    g.desktop_preset.cursor_dot_radius = BHD_CURSOR_DOT_RADIUS;
    g.desktop_preset.imported = 1;
}

static void apply_desktop_blackhole_preset(void) {
    Entity *bh = entity_by_id(g.blackhole_id);
    if (!bh) return;
    bh->mass = g.desktop_preset.bh_mass;
    bh->spin = g.desktop_preset.bh_spin;
    bh->gravity_strength = g.desktop_preset.bh_mass * 0.08;
    bh->event_horizon = g.desktop_preset.bh_radius;
    bh->gravity_radius = g.desktop_preset.bh_radius * 18.0;
    bh->pulse = 1.0;
    bh->version++;
    g.desktop_preset_applied = 1;
    copy_s(bh->origin, sizeof(bh->origin), "blackhole_desktop.c::APP_BH_* micro preset");
    copy_s(bh->definition, sizeof(bh->definition), "blackhole using imported desktop kernel preset: mass/spin/soften/radius only");
    trace_add("micro_merge", g.probe_id, bh->id, "applied blackhole_desktop BH preset");
}

static void material_physics(MaterialKind m, double *density, double *stiffness, double *fracture);
static void controls_init(void);
static ActionId controls_action_for_key(WPARAM key);
static void controls_execute(ActionId action, WPARAM raw_key);
static void controls_begin_capture(void);
static void controls_capture_key(WPARAM key);
static const char *key_name_simple(int key);
static ControlBinding *control_by_action(ActionId action);
static int controls_key_is_used(int key, ActionId except_action);
static void reset_world(void);
static EventContext collect_context(void);
static EventRecord *event_register(EventType type, int code, int mx, int my, int wheel, const char *note);
static ActionId resolve_event(EventRecord *ev, EventContext *ctx, int *conflict_count);
static void context_bindings_init(void);
static void event_dispatch(EventType type, int code, int mx, int my, int wheel, const char *note);
static const char *event_type_name(EventType type);
static const char *action_name(ActionId action);
static void window_registry_init(void);
static WindowRecord *window_by_id(WindowId id);
static RECT window_resolve_rect(WindowId id, RECT client);
static const WindowDecorator *window_decorator(WindowRecord *w);
static void window_render_chrome(HDC dc, WindowRecord *w);
static int window_begin_chrome_interaction(int x, int y);
static int window_begin_content_interaction(int x, int y);
static int window_point_blocks_field(int x, int y);
static WindowRecord *window_selected_or_active(void);
static void window_select_delta(int delta);
static void window_edit_selected(ActionId action);
static void window_layout_cascade(void);
static int window_drag_active(void);
static void window_drag_move(int x, int y, RECT client);
static void window_drag_end(void);
static void window_set_open(WindowId id, int open);
static void window_toggle(WindowId id);
static void window_sync_runtime(void);
static void window_action_bind(WindowId id, ActionId action, const char *relation, const char *note);
static const char *window_name(WindowId id);
static void render_wiring_panel(HDC dc, RECT r);
static void self_studio_init(void);
static BHBNode *node_by_id(int id);
static BHBNode *node_selected(void);
static int node_add(int parent_id, unsigned int roles, unsigned int caps, const char *kind, const char *name, const char *label, WindowId win, ActionId action);
static void node_prop_add(int owner_id, PropType type, const char *key, const char *value);
static void node_select_delta(int delta);
static void node_duplicate_selected(void);
static void render_self_studio_panel(HDC dc, RECT r);
static void node_set_selected_id(int id);
static int self_studio_pick_node(int x, int y);
static int self_studio_pick_tree_index(int x, int y);
static void self_studio_begin_interaction(int x, int y);
static void self_studio_drag_move(int x, int y);
static void self_studio_end_interaction(void);
static Entity *spawn_element_atom(double x, double y, int preset_index);
static void cycle_element_preset(int delta);
static void save_selected_as_asset(void);
static void build_atom_components(Entity *atom, double x, double y);
static void feeder_emit(int count);
static void blackhole_scale_force(double factor);
static void blackhole_scale_radius(double factor);
static void blackhole_scale_horizon(double factor);
static void blackhole_kick_selected(void);

/* ---------- material / spawn ---------- */

static void material_props(MaterialKind m, double *mass, double *radius, double *damping, double *cohesion) {
    switch (m) {
        case MAT_DUST:  *mass = 0.5;  *radius = 0.55; *damping = 0.993; *cohesion = 0.18; break;
        case MAT_METAL: *mass = 2.8;  *radius = 0.62; *damping = 0.998; *cohesion = 0.48; break;
        case MAT_LIGHT: *mass = 0.16; *radius = 0.42; *damping = 0.986; *cohesion = 0.06; break;
        case MAT_STONE: *mass = 4.0;  *radius = 0.72; *damping = 0.996; *cohesion = 0.36; break;
        default: *mass = 1.0; *radius = 0.5; *damping = 0.995; *cohesion = 0.1; break;
    }
}

static Entity *spawn_pixel(double x, double y, MaterialKind mat) {
    double mass, radius, damping, cohesion;
    Entity *e;
    char name[32], label[MAX_TEXT];

    material_props(mat, &mass, &radius, &damping, &cohesion);
    sprintf(name, "%s_px", mat_name(mat));
    sprintf(label, "pixel mat=%s mass=%.2f cohesion=%.2f", mat_name(mat), mass, cohesion);
    e = entity_new(ENT_PIXEL, mat, MODE_DEF, name, label, x, y, radius, mass);
    if (!e) return 0;
    e->damping = damping;
    e->cohesion = cohesion;
    material_physics(mat, &e->density, &e->stiffness, &e->fracture_limit);
    e->vel.x = ((g.next_ent_id % 11) - 5) * 0.025;
    e->vel.y = ((g.next_ent_id % 7) - 3) * 0.025;
    copy_s(e->origin, sizeof(e->origin), "brush.spawn");
    copy_s(e->definition, sizeof(e->definition), "pixel entity in unbounded sparse field");
    copy_s(e->storage, sizeof(e->storage), "pixel-reg/runtime");
    return e;
}

static Entity *spawn_blackhole(double x, double y) {
    Entity *old = entity_by_id(g.blackhole_id);
    Entity *bh;
    if (old) {
        old->pos.x = x;
        old->pos.y = y;
        old->pulse = 1.0;
        trace_add("move_blackhole", g.probe_id, old->id, "blackhole moved");
        return old;
    }

    bh = entity_new(ENT_BLACKHOLE, MAT_NONE, MODE_CONFLICT,
                    "BLACKHOLE", "editable gravity sink in sparse field",
                    x, y, 2.8, 650.0);
    if (!bh) return 0;
    bh->gravity_strength = 900.0;
    bh->gravity_radius = 160.0;
    bh->event_horizon = 8.0;
    bh->absorbs = 1;
    bh->damping = 1.0;
    copy_s(bh->origin, sizeof(bh->origin), "blackhole.spawn");
    copy_s(bh->definition, sizeof(bh->definition), "massive editable gravity object; can forge structure by attraction");
    copy_s(bh->storage, sizeof(bh->storage), "entity-reg[blackhole]");
    g.blackhole_id = bh->id;
    select_entity(bh->id);
    trace_add("blackhole", g.probe_id, bh->id, "blackhole registered");
    return bh;
}


static void world_to_screen(double x, double y, int *sx, int *sy);
static void screen_to_world(int sx, int sy, double *x, double *y);

/* ---------- blackhole feeder / visible controls ---------- */

static double rand_unit_from_int(int n) {
    unsigned int x = (unsigned int)(n * 1103515245u + 12345u + g.next_ent_id * 97u);
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return ((double)(x & 0xffff) / 65535.0) * 2.0 - 1.0;
}

static void feeder_emit(int count) {
    Entity *bh = entity_by_id(g.blackhole_id);
    double wx, wy;
    int i;
    if (!bh) return;

    screen_to_world(g.mouse_x, g.mouse_y, &wx, &wy);

    for (i = 0; i < count; ++i) {
        Entity *p;
        double a = rand_unit_from_int(i + g.feeder_emit_total) * M_PI;
        double rr = 2.0 + fabs(rand_unit_from_int(i * 3 + 17)) * 10.0;
        double dx = cos(a) * rr;
        double dy = sin(a) * rr;
        double tx = bh->pos.x - (wx + dx);
        double ty = bh->pos.y - (wy + dy);
        double d = sqrt(tx*tx + ty*ty);
        double spread = g.feeder_spread;
        if (d < 0.001) d = 0.001;

        p = spawn_pixel(wx + dx, wy + dy, g.mat);
        if (!p) continue;

        p->vel.x = (tx / d) * g.feeder_speed + rand_unit_from_int(i+101) * g.feeder_speed * spread;
        p->vel.y = (ty / d) * g.feeder_speed + rand_unit_from_int(i+202) * g.feeder_speed * spread;
        copy_s(p->origin, sizeof(p->origin), "blackhole_feeder.emit");
        copy_s(p->definition, sizeof(p->definition), "feeder pixel with initial vector toward blackhole");
        p->pulse = 0.25;
    }

    g.feeder_emit_total += count;
    trace_add("feeder", g.probe_id, g.blackhole_id, "emitted pixels toward blackhole");
}

static void blackhole_scale_force(double factor) {
    Entity *bh = entity_by_id(g.blackhole_id);
    char msg[128];
    if (!bh) return;
    bh->gravity_strength *= factor;
    if (bh->gravity_strength < 1.0) bh->gravity_strength = 1.0;
    if (bh->gravity_strength > 25000.0) bh->gravity_strength = 25000.0;
    sprintf(msg, "gravity_strength now %.2f", bh->gravity_strength);
    trace_add("bh_force", g.probe_id, bh->id, msg);
}

static void blackhole_scale_radius(double factor) {
    Entity *bh = entity_by_id(g.blackhole_id);
    char msg[128];
    if (!bh) return;
    bh->gravity_radius *= factor;
    if (bh->gravity_radius < 4.0) bh->gravity_radius = 4.0;
    if (bh->gravity_radius > 2000.0) bh->gravity_radius = 2000.0;
    sprintf(msg, "gravity_radius now %.2f", bh->gravity_radius);
    trace_add("bh_radius", g.probe_id, bh->id, msg);
}

static void blackhole_scale_horizon(double factor) {
    Entity *bh = entity_by_id(g.blackhole_id);
    char msg[128];
    if (!bh) return;
    bh->event_horizon *= factor;
    if (bh->event_horizon < 0.5) bh->event_horizon = 0.5;
    if (bh->event_horizon > 300.0) bh->event_horizon = 300.0;
    sprintf(msg, "event_horizon now %.2f", bh->event_horizon);
    trace_add("bh_horizon", g.probe_id, bh->id, msg);
}

static void blackhole_kick_selected(void) {
    Entity *bh = entity_by_id(g.blackhole_id);
    Entity *s = entity_by_id(g.selected_id);
    double dx, dy, d;
    if (!bh || !s || s->id == bh->id) return;
    dx = s->pos.x - bh->pos.x;
    dy = s->pos.y - bh->pos.y;
    d = sqrt(dx*dx + dy*dy);
    if (d < 0.001) d = 0.001;
    s->vel.x += (dx / d) * 80.0;
    s->vel.y += (dy / d) * 80.0;
    s->pulse = 1.0;
    trace_add("kick", g.probe_id, s->id, "selected object kicked outward from blackhole");
}


/* ---------- asset forge / atom components ---------- */

static void init_element_presets(void) {
    int i;
    for (i = 0; i < 16; ++i) memset(&g.preset[i], 0, sizeof(g.preset[i]));

    g.preset[0].alive = 1; g.preset[0].atomic_number = 1; g.preset[0].mass_number = 1;
    copy_s(g.preset[0].symbol, sizeof(g.preset[0].symbol), "H");
    copy_s(g.preset[0].name, sizeof(g.preset[0].name), "Hydrogen");
    g.preset[0].atomic_mass = 1.008;
    copy_s(g.preset[0].storage, sizeof(g.preset[0].storage), "periodic-table[1]");
    copy_s(g.preset[0].definition, sizeof(g.preset[0].definition), "1 proton, usually 0 neutrons, 1 electron when neutral");

    g.preset[1].alive = 1; g.preset[1].atomic_number = 2; g.preset[1].mass_number = 4;
    copy_s(g.preset[1].symbol, sizeof(g.preset[1].symbol), "He");
    copy_s(g.preset[1].name, sizeof(g.preset[1].name), "Helium");
    g.preset[1].atomic_mass = 4.0026;
    copy_s(g.preset[1].storage, sizeof(g.preset[1].storage), "periodic-table[2]");
    copy_s(g.preset[1].definition, sizeof(g.preset[1].definition), "2 protons, 2 neutrons, 2 electrons when neutral");

    g.preset[2].alive = 1; g.preset[2].atomic_number = 6; g.preset[2].mass_number = 12;
    copy_s(g.preset[2].symbol, sizeof(g.preset[2].symbol), "C");
    copy_s(g.preset[2].name, sizeof(g.preset[2].name), "Carbon");
    g.preset[2].atomic_mass = 12.011;
    copy_s(g.preset[2].storage, sizeof(g.preset[2].storage), "periodic-table[6]");
    copy_s(g.preset[2].definition, sizeof(g.preset[2].definition), "6 protons, about 6 neutrons in C-12, 6 electrons when neutral");

    g.preset[3].alive = 1; g.preset[3].atomic_number = 8; g.preset[3].mass_number = 16;
    copy_s(g.preset[3].symbol, sizeof(g.preset[3].symbol), "O");
    copy_s(g.preset[3].name, sizeof(g.preset[3].name), "Oxygen");
    g.preset[3].atomic_mass = 15.999;
    copy_s(g.preset[3].storage, sizeof(g.preset[3].storage), "periodic-table[8]");
    copy_s(g.preset[3].definition, sizeof(g.preset[3].definition), "8 protons, about 8 neutrons in O-16, 8 electrons when neutral");

    g.preset[4].alive = 1; g.preset[4].atomic_number = 26; g.preset[4].mass_number = 56;
    copy_s(g.preset[4].symbol, sizeof(g.preset[4].symbol), "Fe");
    copy_s(g.preset[4].name, sizeof(g.preset[4].name), "Iron");
    g.preset[4].atomic_mass = 55.845;
    copy_s(g.preset[4].storage, sizeof(g.preset[4].storage), "periodic-table[26]");
    copy_s(g.preset[4].definition, sizeof(g.preset[4].definition), "26 protons, about 30 neutrons in Fe-56, 26 electrons when neutral");
}

static ElementPreset *current_element_preset(void) {
    int count = 0, i;
    for (i = 0; i < 16; ++i) if (g.preset[i].alive) count++;
    if (count <= 0) return 0;
    if (g.forge_element_index < 0) g.forge_element_index = count - 1;
    g.forge_element_index %= count;

    count = 0;
    for (i = 0; i < 16; ++i) {
        if (g.preset[i].alive) {
            if (count == g.forge_element_index) return &g.preset[i];
            count++;
        }
    }
    return 0;
}

static void cycle_element_preset(int delta) {
    g.forge_element_index += delta;
    if (g.forge_element_index < 0) g.forge_element_index = 4;
    trace_add("element", g.probe_id, 0, "cycled periodic element preset");
}

static Entity *spawn_particle_component(int parent_atom_id, ParticleKind pt, double x, double y, double ox, double oy, int index) {
    Entity *e;
    char name[32], label[MAX_TEXT];
    double mass = 1.0;
    double radius = 0.35;
    double charge = 0.0;

    if (pt == PT_UP_QUARK) { mass = 0.025; radius = 0.18; charge =  0.666; }
    else if (pt == PT_DOWN_QUARK) { mass = 0.05; radius = 0.18; charge = -0.333; }
    else if (pt == PT_ELECTRON) { mass = 0.00055; radius = 0.22; charge = -1.0; }
    else if (pt == PT_PROTON) { mass = 1.0; radius = 0.42; charge = 1.0; }
    else if (pt == PT_NEUTRON) { mass = 1.0; radius = 0.42; charge = 0.0; }

    sprintf(name, "%s_%d", particle_name(pt), index);
    sprintf(label, "component of atom=%d particle=%s charge=%.3f", parent_atom_id, particle_name(pt), charge);

    e = entity_new((pt == PT_ELECTRON || pt == PT_UP_QUARK || pt == PT_DOWN_QUARK) ? ENT_SUBPARTICLE : ENT_NUCLEON,
                   MAT_NONE, MODE_DEF, name, label, x + ox, y + oy, radius, mass);
    if (!e) return 0;

    e->particle = pt;
    e->parent_atom_id = parent_atom_id;
    e->electric_charge = charge;
    e->damping = 0.999;
    e->cohesion = 0.65;
    e->visible = 1;
    copy_s(e->origin, sizeof(e->origin), "asset_forge.atom_component");
    copy_s(e->definition, sizeof(e->definition), "reusable atom component generated by atom forge");
    copy_s(e->storage, sizeof(e->storage), "atom-component-reg/runtime");
    return e;
}

static void spawn_quarks_for_nucleon(int parent_atom_id, int nucleon_id, ParticleKind nucleon_type, double x, double y, int base_index) {
    double qoff = 0.23;
    if (nucleon_type == PT_PROTON) {
        spawn_particle_component(parent_atom_id, PT_UP_QUARK, x, y,  qoff, 0.0, base_index + 0);
        spawn_particle_component(parent_atom_id, PT_UP_QUARK, x, y, -qoff, 0.0, base_index + 1);
        spawn_particle_component(parent_atom_id, PT_DOWN_QUARK, x, y, 0.0, qoff, base_index + 2);
    } else if (nucleon_type == PT_NEUTRON) {
        spawn_particle_component(parent_atom_id, PT_UP_QUARK, x, y, 0.0, -qoff, base_index + 0);
        spawn_particle_component(parent_atom_id, PT_DOWN_QUARK, x, y, qoff,  qoff, base_index + 1);
        spawn_particle_component(parent_atom_id, PT_DOWN_QUARK, x, y, -qoff, qoff, base_index + 2);
    }
    (void)nucleon_id;
}

static void build_atom_components(Entity *atom, double x, double y) {
    int i;
    int component_index = 0;
    double nucleus_radius;
    double electron_radius;
    if (!atom || atom->kind != ENT_ATOM) return;

    nucleus_radius = 1.2 + sqrt((double)(atom->protons + atom->neutrons)) * 0.22;
    electron_radius = 4.0 + sqrt((double)atom->electrons) * 0.75;

    for (i = 0; i < atom->protons; ++i) {
        double a = (2.0 * M_PI * i) / (double)(atom->protons > 0 ? atom->protons : 1);
        double rr = nucleus_radius * (0.35 + 0.65 * ((i % 3) / 2.0));
        Entity *p = spawn_particle_component(atom->id, PT_PROTON, x, y, cos(a)*rr, sin(a)*rr, component_index++);
        if (p) {
            p->body_id = atom->id;
            spawn_quarks_for_nucleon(atom->id, p->id, PT_PROTON, p->pos.x, p->pos.y, component_index * 3);
        }
    }

    for (i = 0; i < atom->neutrons; ++i) {
        double a = (2.0 * M_PI * i) / (double)(atom->neutrons > 0 ? atom->neutrons : 1) + 0.31;
        double rr = nucleus_radius * (0.25 + 0.75 * ((i % 4) / 3.0));
        Entity *n = spawn_particle_component(atom->id, PT_NEUTRON, x, y, cos(a)*rr, sin(a)*rr, component_index++);
        if (n) {
            n->body_id = atom->id;
            spawn_quarks_for_nucleon(atom->id, n->id, PT_NEUTRON, n->pos.x, n->pos.y, component_index * 3);
        }
    }

    for (i = 0; i < atom->electrons; ++i) {
        double shell = 1.0 + (double)(i / 8);
        double a = (2.0 * M_PI * (i % 8)) / 8.0 + shell * 0.43;
        Entity *el = spawn_particle_component(atom->id, PT_ELECTRON, x, y, cos(a)*electron_radius*shell, sin(a)*electron_radius*shell, component_index++);
        if (el) {
            el->body_id = atom->id;
            el->vel.x = -sin(a) * 12.0 / shell;
            el->vel.y =  cos(a) * 12.0 / shell;
        }
    }

    atom->child_count = atom->protons + atom->neutrons + atom->electrons;
    g.atom_component_count += atom->child_count;
}

static Entity *spawn_element_atom(double x, double y, int preset_index) {
    ElementPreset *p = current_element_preset();
    Entity *atom;
    char name[32], label[MAX_TEXT];

    (void)preset_index;
    if (!p) return 0;

    sprintf(name, "ATOM_%s", p->symbol);
    sprintf(label, "%s atom Z=%d A=%d", p->name, p->atomic_number, p->mass_number);

    atom = entity_new(ENT_ATOM, MAT_NONE, MODE_DEF, name, label, x, y, 5.5 + sqrt((double)p->atomic_number), p->atomic_mass);
    if (!atom) return 0;

    atom->particle = PT_ATOM;
    atom->atomic_number = p->atomic_number;
    atom->mass_number = p->mass_number;
    atom->protons = p->atomic_number;
    atom->neutrons = p->mass_number - p->atomic_number;
    if (atom->neutrons < 0) atom->neutrons = 0;
    atom->electrons = p->atomic_number;
    atom->electric_charge = 0.0;
    atom->cohesion = 0.75;
    atom->damping = 0.999;
    copy_s(atom->origin, sizeof(atom->origin), p->storage);
    copy_s(atom->definition, sizeof(atom->definition), p->definition);
    copy_s(atom->storage, sizeof(atom->storage), "asset-forge/atom-registry/runtime");

    build_atom_components(atom, x, y);
    select_entity(atom->id);
    trace_add("atom_forge", g.probe_id, atom->id, "spawned reusable element atom with components");
    return atom;
}

static void save_selected_as_asset(void) {
    Entity *s = entity_by_id(g.selected_id);
    char msg[128];
    if (!s) return;
    s->reusable_asset_id = ++g.saved_asset_count;
    copy_s(s->storage, sizeof(s->storage), "asset-library/reusable");
    s->dirty = 0;
    sprintf(msg, "saved selected as reusable asset #%d", s->reusable_asset_id);
    trace_add("asset_save", g.probe_id, s->id, msg);
}

/* ---------- projection ---------- */

static void update_field_rect(int w, int h) {
    g.field_rc.left = 14;
    g.field_rc.top = 54;
    g.field_rc.right = w - 364;
    g.field_rc.bottom = h - 152;
}

static double field_scale(void) {
    return 8.0 * g.zoom;
}

static void world_to_screen(double x, double y, int *sx, int *sy) {
    double s = field_scale();
    double cx = (g.field_rc.left + g.field_rc.right) * 0.5;
    double cy = (g.field_rc.top + g.field_rc.bottom) * 0.5;
    *sx = (int)(cx + (x - g.cam_x) * s);
    *sy = (int)(cy + (y - g.cam_y) * s);
}

static void screen_to_world(int sx, int sy, double *x, double *y) {
    double s = field_scale();
    double cx = (g.field_rc.left + g.field_rc.right) * 0.5;
    double cy = (g.field_rc.top + g.field_rc.bottom) * 0.5;
    *x = ((double)sx - cx) / s + g.cam_x;
    *y = ((double)sy - cy) / s + g.cam_y;
}

static double zoom_pan_amount(void) {
    double z = g.zoom;
    if (z < 0.001) z = 0.001;
    return CAMERA_PAN_BASE / z;
}

static int current_scale_level(void) {
    if (g.zoom >= MULTISCALE_PIXEL_LEVEL) return 0;   /* pixel/component scale */
    if (g.zoom >= MULTISCALE_BODY_LEVEL) return 1;    /* object/body scale */
    if (g.zoom >= MULTISCALE_META_LEVEL) return 2;    /* meta-vector scale */
    return 3;                                        /* deep map scale */
}

static const char *scale_level_name(void) {
    switch (current_scale_level()) {
        case 0: return "PIXEL";
        case 1: return "BODY";
        case 2: return "META";
        default: return "MAP";
    }
}

static void camera_apply_target(void) {
    if (g.camera_smooth) {
        g.cam_x += (g.target_cam_x - g.cam_x) * 0.18;
        g.cam_y += (g.target_cam_y - g.cam_y) * 0.18;
        g.zoom  += (g.target_zoom  - g.zoom ) * 0.18;
    } else {
        g.cam_x = g.target_cam_x;
        g.cam_y = g.target_cam_y;
        g.zoom  = g.target_zoom;
    }
    if (g.zoom < 0.01) g.zoom = 0.01;
    if (g.zoom > 64.0) g.zoom = 64.0;
}

static void camera_pan(double dx, double dy) {
    g.target_cam_x += dx;
    g.target_cam_y += dy;
}

static void camera_zoom_at_mouse(double factor) {
    double before_x, before_y;
    double after_x, after_y;
    screen_to_world(g.mouse_x, g.mouse_y, &before_x, &before_y);
    g.target_zoom *= factor;
    if (g.target_zoom < 0.01) g.target_zoom = 0.01;
    if (g.target_zoom > 64.0) g.target_zoom = 64.0;
    /* apply immediately enough to keep mouse anchor stable */
    {
        double old_zoom = g.zoom;
        g.zoom = g.target_zoom;
        screen_to_world(g.mouse_x, g.mouse_y, &after_x, &after_y);
        g.zoom = old_zoom;
    }
    g.target_cam_x += before_x - after_x;
    g.target_cam_y += before_y - after_y;
}

static void camera_focus_selected(void) {
    Entity *s = entity_by_id(g.selected_id);
    if (!s) return;
    g.target_cam_x = s->pos.x;
    g.target_cam_y = s->pos.y;
    trace_add("camera", g.probe_id, s->id, "camera target set to selected object");
}

static void camera_home(void) {
    g.target_cam_x = 0.0;
    g.target_cam_y = 0.0;
    g.target_zoom = 1.0;
    trace_add("camera", g.probe_id, 0, "camera home");
}

static void material_physics(MaterialKind m, double *density, double *stiffness, double *fracture) {
    switch (m) {
        case MAT_DUST:  *density = 0.7; *stiffness = 0.08; *fracture = 0.12; break;
        case MAT_LIGHT: *density = 0.2; *stiffness = 0.03; *fracture = 0.05; break;
        case MAT_METAL: *density = 7.8; *stiffness = 0.85; *fracture = 0.95; break;
        case MAT_STONE: *density = 3.2; *stiffness = 0.55; *fracture = 0.48; break;
        default: *density = 1.0; *stiffness = 0.1; *fracture = 0.1; break;
    }
}


static int nearest_entity_screen(int sx, int sy, double max_px);

/* ---------- brush/actions ---------- */

static void emit_desktop_burst_at(int sx, int sy) {
    double wx, wy;
    int i;
    int count = g.desktop_preset.emit_count;
    double radius = g.desktop_preset.emit_radius;
    double speed = g.desktop_preset.emit_speed;
    double mass = g.desktop_preset.emit_mass;

    if (count < 1) count = 1;
    if (count > 300) count = 300; /* small safety cap for our current registry/render loop */
    screen_to_world(sx, sy, &wx, &wy);

    for (i = 0; i < count; ++i) {
        double a = deterministic_unit(g.next_ent_id + i * 17) * 6.28318530718;
        double rr = sqrt(deterministic_unit(g.next_ent_id + i * 29)) * radius / (field_scale() > 0.0001 ? field_scale() : 1.0);
        Entity *p = spawn_pixel(wx + cos(a) * rr, wy + sin(a) * rr, g.mat);
        if (p) {
            double vj = 0.35 + deterministic_unit(g.next_ent_id + i * 31) * 0.85;
            p->vel.x += cos(a) * speed * 0.015 * vj;
            p->vel.y += sin(a) * speed * 0.015 * vj;
            p->mass = mass;
            p->version++;
            copy_s(p->origin, sizeof(p->origin), "blackhole_desktop.c::APP_TOOL_EMIT_* micro merge");
            copy_s(p->definition, sizeof(p->definition), "desktop emit profile particle: count/radius/speed/mass imported");
        }
    }
    trace_add("tool_emit", g.probe_id, 0, "desktop emit burst spawned");
}

static void erase_at(int sx, int sy) {
    double wx, wy;
    double rad_world;
    double r2;
    int i, n = 0;
    screen_to_world(sx, sy, &wx, &wy);
    rad_world = g.desktop_preset.erase_radius / (field_scale() > 0.0001 ? field_scale() : 1.0);
    if (rad_world < 1.5) rad_world = 1.5;
    r2 = rad_world * rad_world;

    for (i = 0; i < MAX_ENT; ++i) {
        Entity *e = &g.ent[i];
        if (!e->alive) continue;
        if (e->kind != ENT_PIXEL && e->kind != ENT_BODY) continue;
        if (dist2(e->pos.x, e->pos.y, wx, wy) <= r2) {
            e->alive = 0;
            n++;
        }
    }
    trace_add("tool_erase", g.probe_id, 0, n ? "desktop erase radius removed objects" : "erase radius found nothing");
}

static void tool_apply_at(int sx, int sy) {
    double wx, wy;
    screen_to_world(sx, sy, &wx, &wy);

    if (g.tool == TOOL_BH) {
        spawn_blackhole(wx, wy);
    } else if (g.tool == TOOL_EMIT) {
        emit_desktop_burst_at(sx, sy);
    } else if (g.tool == TOOL_ERASE) {
        erase_at(sx, sy);
    } else if (g.tool == TOOL_SELECT) {
        int id = nearest_entity_screen(sx, sy, 28.0);
        if (id) select_entity(id);
    }
}

static void brush_spawn_at(int sx, int sy) {
    /* Backwards-compatible brush call now routes through the imported desktop tool mode. */
    tool_apply_at(sx, sy);
}

static void clear_pixels(void) {
    int i;
    for (i = 0; i < MAX_ENT; ++i) {
        if (g.ent[i].alive && g.ent[i].kind == ENT_PIXEL)
            g.ent[i].alive = 0;
    }
    trace_add("clear_pixels", g.probe_id, 0, "pixels cleared; bodies remain");
}

static void clear_all_dynamic(void) {
    int i;
    for (i = 0; i < MAX_ENT; ++i) {
        if (g.ent[i].alive && (g.ent[i].kind == ENT_PIXEL || g.ent[i].kind == ENT_BODY || g.ent[i].kind == ENT_BODY_CORE))
            g.ent[i].alive = 0;
    }
    trace_add("clear_dynamic", g.probe_id, 0, "pixels and bodies cleared");
}

/* ---------- emergence: body forge ---------- */

static int pixel_is_unassigned(Entity *e) {
    return e && e->alive && e->kind == ENT_PIXEL && e->body_id == 0;
}

static void forge_bodies(void) {
    /*
        v0.9.1 safe forge:
        The v0.9 forge used a broad repeated scan. With many pixels that could explode
        into huge work and feel like a crash/hang. This version forges at most one
        local cluster per call, starting near the mouse/selection, with hard caps.
    */
    static int idx[FORGE_MAX_CLUSTER];
    static int used[MAX_ENT];

    int i, j, head, tail, seed_slot = -1;
    int count = 0;
    double wx, wy;
    double bestd = 1e100;
    double dist_lim2 = BODY_FORGE_DIST * BODY_FORGE_DIST;
    double sx = 0.0, sy = 0.0, sm = 0.0, maxd2 = 0.0;
    int mat_count[5] = {0,0,0,0,0};
    MaterialKind dominant = MAT_DUST;
    Entity *body;
    char name[32], label[MAX_TEXT];

    memset(used, 0, sizeof(used));
    screen_to_world(g.mouse_x, g.mouse_y, &wx, &wy);

    /* Prefer selected pixel, otherwise pixel closest to mouse. */
    {
        Entity *sel = entity_by_id(g.selected_id);
        if (sel && pixel_is_unassigned(sel)) {
            seed_slot = (int)(sel - &g.ent[0]);
        }
    }

    if (seed_slot < 0) {
        for (i = 0; i < MAX_ENT; ++i) {
            Entity *p = &g.ent[i];
            double d;
            if (!pixel_is_unassigned(p)) continue;
            d = dist2(p->pos.x, p->pos.y, wx, wy);
            if (d < bestd) {
                bestd = d;
                seed_slot = i;
            }
        }
    }

    if (seed_slot < 0) {
        trace_add("forge", g.probe_id, 0, "no unassigned pixels available");
        return;
    }

    /* Breadth-first local cluster expansion with hard cap. */
    head = 0;
    tail = 0;
    idx[tail++] = seed_slot;
    used[seed_slot] = 1;

    while (head < tail && tail < FORGE_MAX_CLUSTER) {
        int cur_i = idx[head++];
        Entity *cur = &g.ent[cur_i];

        for (j = 0; j < MAX_ENT && tail < FORGE_MAX_CLUSTER; ++j) {
            Entity *p = &g.ent[j];
            if (used[j] || !pixel_is_unassigned(p)) continue;
            if (dist2(p->pos.x, p->pos.y, cur->pos.x, cur->pos.y) <= dist_lim2) {
                used[j] = 1;
                idx[tail++] = j;
            }
        }
    }

    count = tail;
    if (count < BODY_MIN_PIXELS) {
        trace_add("forge", g.probe_id, 0, "cluster too small; paint denser pixels or increase brush");
        return;
    }

    for (i = 0; i < count; ++i) {
        Entity *p = &g.ent[idx[i]];
        sx += p->pos.x * p->mass;
        sy += p->pos.y * p->mass;
        sm += p->mass;
        if (p->material >= MAT_DUST && p->material <= MAT_STONE)
            mat_count[p->material]++;
    }

    if (sm <= 0.0) {
        trace_add("forge", g.probe_id, 0, "cluster has no mass");
        return;
    }

    sx /= sm;
    sy /= sm;

    for (i = MAT_DUST; i <= MAT_STONE; ++i) {
        if (mat_count[i] > mat_count[dominant]) dominant = (MaterialKind)i;
    }

    for (i = 0; i < count; ++i) {
        Entity *p = &g.ent[idx[i]];
        double d2 = dist2(p->pos.x, p->pos.y, sx, sy);
        if (d2 > maxd2) maxd2 = d2;
    }

    sprintf(name, "BODY_%d", g.forged_count + 1);
    sprintf(label, "emergent body from %d pixels / dominant=%s", count, mat_name(dominant));
    body = entity_new(ENT_BODY, dominant, MODE_ABD, name, label, sx, sy, sqrt(maxd2) + 1.5, sm);
    if (!body) {
        trace_add("forge", g.probe_id, 0, "body registry failed");
        return;
    }

    body->child_count = count;
    body->cohesion = 0.42;
    body->spin = 0.0;
    material_physics(dominant, &body->density, &body->stiffness, &body->fracture_limit);
    body->version++;
    copy_s(body->origin, sizeof(body->origin), "body_forge.safe_local_cluster_scan");
    copy_s(body->definition, sizeof(body->definition), "registered emergent body derived from capped local pixel cluster");
    copy_s(body->storage, sizeof(body->storage), "body-reg/runtime");

    for (i = 0; i < count; ++i) {
        Entity *p = &g.ent[idx[i]];
        p->body_id = body->id;
        p->mode = MODE_INF;
        p->damping = 0.999;
    }

    g.forged_count++;
    select_entity(body->id);
    trace_add("forge", g.probe_id, body->id, "safe local cluster forged into BODY");
}

/* ---------- physics ---------- */

static void apply_blackhole(double dt) {
    int i;
    Entity *bh = entity_by_id(g.blackhole_id);
    if (!bh || !g.gravity_on) return;

    for (i = 0; i < MAX_ENT; ++i) {
        Entity *p = &g.ent[i];
        double dx, dy, d2, d, falloff, force, ax, ay;

        if (!p->alive || (p->kind != ENT_PIXEL && p->kind != ENT_BODY)) continue;
        if (p->id == bh->id) continue;

        dx = bh->pos.x - p->pos.x;
        dy = bh->pos.y - p->pos.y;
        d2 = dx*dx + dy*dy;
        if (d2 < 0.0001) d2 = 0.0001;
        d = sqrt(d2);

        if (d > bh->gravity_radius) continue;

        if (g.absorb_on && bh->absorbs && p->kind == ENT_PIXEL && d < bh->event_horizon) {
            p->alive = 0;
            g.absorbed_count++;
            bh->mass += g.desktop_preset.bh_grow_mass + p->mass * 0.04;
            if (bh->mass > g.desktop_preset.bh_mass_max) bh->mass = g.desktop_preset.bh_mass_max;
            bh->event_horizon += g.desktop_preset.bh_grow_radius;
            if (bh->event_horizon > g.desktop_preset.bh_radius_max) bh->event_horizon = g.desktop_preset.bh_radius_max;
            bh->gravity_radius = bh->event_horizon * 18.0;
            bh->pulse = 1.0;
            continue;
        }

        falloff = (1.0 - d / bh->gravity_radius);
        force = bh->gravity_strength * sqrt(bh->mass) / (d2 * 0.08 + 18.0) * falloff;
        ax = (dx / d) * force / (p->mass + 0.01);
        ay = (dy / d) * force / (p->mass + 0.01);

        p->vel.x += ax * dt;
        p->vel.y += ay * dt;

        /* swirl */
        p->vel.x += (-dy / d) * (bh->spin * 0.025) * dt * falloff;
        p->vel.y += ( dx / d) * (bh->spin * 0.025) * dt * falloff;
    }
}

static void apply_body_cohesion(double dt) {
    int i;
    if (!g.cohesion_on) return;

    for (i = 0; i < MAX_ENT; ++i) {
        Entity *body = &g.ent[i];
        int j;
        if (!body->alive || body->kind != ENT_BODY) continue;

        body->child_count = 0;
        body->mass = 0.0;

        for (j = 0; j < MAX_ENT; ++j) {
            Entity *p = &g.ent[j];
            double dx, dy, d2, d, pull;
            if (!p->alive || p->kind != ENT_PIXEL || p->body_id != body->id) continue;

            dx = body->pos.x - p->pos.x;
            dy = body->pos.y - p->pos.y;
            d2 = dx*dx + dy*dy;
            if (d2 < 0.0001) d2 = 0.0001;
            d = sqrt(d2);

            pull = body->cohesion * p->cohesion;
            p->vel.x += (dx / d) * pull * dt * 12.0;
            p->vel.y += (dy / d) * pull * dt * 12.0;

            body->mass += p->mass;
            body->child_count++;
        }
    }
}

static void update_bodies_from_pixels(void) {
    int i, j;
    for (i = 0; i < MAX_ENT; ++i) {
        Entity *body = &g.ent[i];
        double sx=0, sy=0, sm=0, maxd2=0;
        int count=0;
        if (!body->alive || body->kind != ENT_BODY) continue;

        for (j = 0; j < MAX_ENT; ++j) {
            Entity *p = &g.ent[j];
            if (!p->alive || p->kind != ENT_PIXEL || p->body_id != body->id) continue;
            sx += p->pos.x * p->mass;
            sy += p->pos.y * p->mass;
            sm += p->mass;
            count++;
        }

        if (count <= 0 || sm <= 0.0) {
            body->alive = 0;
            continue;
        }

        sx /= sm; sy /= sm;

        for (j = 0; j < MAX_ENT; ++j) {
            Entity *p = &g.ent[j];
            double d2;
            if (!p->alive || p->kind != ENT_PIXEL || p->body_id != body->id) continue;
            d2 = dist2(p->pos.x, p->pos.y, sx, sy);
            if (d2 > maxd2) maxd2 = d2;
        }

        body->prev = body->pos;
        body->meta_vx = (sx - body->pos.x) * 60.0;
        body->meta_vy = (sy - body->pos.y) * 60.0;
        body->pos.x = sx;
        body->pos.y = sy;
        body->mass = sm;
        body->child_count = count;
        body->radius = sqrt(maxd2) + 1.2;
    }
}

static void physics_step(double dt) {
    int i;
    double t0 = clock_s();
    g.time += dt;
    g.pixels_alive = 0;
    g.bodies_alive = 0;
    g.atom_component_count = 0;

    if (g.feeder_on) {
        g.feeder_accum += dt * (double)g.feeder_rate;
        while (g.feeder_accum >= 1.0) {
            feeder_emit(1);
            g.feeder_accum -= 1.0;
        }
    }

    /* Atom component binding: simplified, inspectable, not quantum-exact. */
    {
        int ai;
        for (ai = 0; ai < MAX_ENT; ++ai) {
            Entity *c = &g.ent[ai];
            Entity *atom;
            double dx, dy, d2, d, k;
            if (!c->alive || c->parent_atom_id <= 0) continue;
            atom = entity_by_id(c->parent_atom_id);
            if (!atom || !atom->alive) continue;
            dx = atom->pos.x - c->pos.x;
            dy = atom->pos.y - c->pos.y;
            d2 = dx*dx + dy*dy;
            if (d2 < 0.001) d2 = 0.001;
            d = sqrt(d2);
            k = (c->particle == PT_ELECTRON) ? 0.45 : 1.8;
            c->vel.x += (dx / d) * k * dt * 18.0;
            c->vel.y += (dy / d) * k * dt * 18.0;
            if (c->particle == PT_ELECTRON) {
                c->vel.x += (-dy / d) * dt * 7.5;
                c->vel.y += ( dx / d) * dt * 7.5;
            }
        }
    }

    apply_blackhole(dt);
    apply_body_cohesion(dt);

    for (i = 0; i < MAX_ENT; ++i) {
        Entity *e = &g.ent[i];
        if (!e->alive) continue;

        e->prev = e->pos;

        if (e->kind == ENT_PIXEL || e->kind == ENT_BODY) {
            e->pos.x += e->vel.x * dt;
            e->pos.y += e->vel.y * dt;
            e->vel.x *= e->damping;
            e->vel.y *= e->damping;
        }

        if (e->pulse > 0) {
            e->pulse -= dt * 1.5;
            if (e->pulse < 0) e->pulse = 0;
        }

        if (e->kind == ENT_PIXEL) g.pixels_alive++;
        if (e->kind == ENT_BODY || e->kind == ENT_ATOM) g.bodies_alive++;
        if (e->parent_atom_id > 0) g.atom_component_count++;
    }

    update_bodies_from_pixels();

    if (g.auto_forge) {
        g.auto_forge_timer += dt;
        if (g.auto_forge_timer > 1.25) {
            g.auto_forge_timer = 0.0;
            forge_bodies();
        }
    }

    {
        Entity *s = entity_by_id(g.selected_id);
        if (s) {
            g.chunk_x = (int)floor(s->pos.x / CHUNK_SIZE);
            g.chunk_y = (int)floor(s->pos.y / CHUNK_SIZE);
        } else {
            g.chunk_x = (int)floor(g.cam_x / CHUNK_SIZE);
            g.chunk_y = (int)floor(g.cam_y / CHUNK_SIZE);
        }
    }

    g.sim_ms = (clock_s() - t0) * 1000.0;
}

static void tick(void) {
    const double fixed_dt = 1.0 / 60.0;
    double now = clock_s();
    double dt = now - g.last_clock;
    if (dt > 0.25) dt = 0.25;
    g.last_clock = now;
    g.accumulator += dt;

    if (!g.paused || g.step_once) {
        while (g.accumulator >= fixed_dt) {
            physics_step(fixed_dt);
            g.accumulator -= fixed_dt;
            if (g.step_once) break;
        }
        g.step_once = 0;
    } else {
        g.accumulator = 0;
    }

    if (dt > 0.0001) g.fps = 1.0 / dt;
}

/* ---------- selection / hover ---------- */

static int nearest_entity_screen(int sx, int sy, double max_px) {
    int i, best=0, ex, ey;
    double bd = max_px * max_px;
    for (i = 0; i < MAX_ENT; ++i) {
        Entity *e = &g.ent[i];
        double dx, dy, d2;
        if (!e->alive || !e->visible) continue;
        world_to_screen(e->pos.x, e->pos.y, &ex, &ey);
        dx = (double)sx - ex;
        dy = (double)sy - ey;
        d2 = dx*dx + dy*dy;
        if (d2 < bd) {
            bd = d2;
            best = e->id;
        }
    }
    return best;
}

static void update_hover(int sx, int sy) {
    hover_entity(nearest_entity_screen(sx, sy, 20.0));
}

/* ---------- rendering ---------- */

static void draw_header(HDC dc) {
    char buf[512];
    SetTextColor(dc, RGB(226,234,242));
    draw_text(dc, 14, 10, "ZERO 0000 - GraphField Visual Mirror");
    SetTextColor(dc, RGB(145,165,185));
    sprintf(buf, "fps=%.1f frame=%.2fms sim=%.3fms pixels=%d bodies=%d forged=%d mat=%s brush=%d zoom=%.4f preset=%s chunk=<%d,%d> paused=%s status=%s",
            g.fps, g.frame_ms, g.sim_ms, g.pixels_alive, g.bodies_alive, g.forged_count,
            mat_name(g.mat), g.brush_radius, g.zoom, g.desktop_preset_applied ? "BHD" : "native", g.chunk_x, g.chunk_y,
            g.paused ? "yes" : "no", g.status);
    draw_text(dc, 14, 30, buf);
}

static void draw_chunk_grid(HDC dc) {
    RECT rc = g.field_rc;
    double s = field_scale();
    double left_w, right_w, top_w, bot_w;
    int cx0, cx1, cy0, cy1;
    int cx, cy;
    int sx1, sy1, sx2, sy2;
    char buf[80];

    fill_rect_c(dc, rc, RGB(2,5,9));
    rect_outline(dc, rc, RGB(56,74,92), 1);

    screen_to_world(rc.left, rc.top, &left_w, &top_w);
    screen_to_world(rc.right, rc.bottom, &right_w, &bot_w);

    if (left_w > right_w) { double t=left_w; left_w=right_w; right_w=t; }
    if (top_w > bot_w) { double t=top_w; top_w=bot_w; bot_w=t; }

    cx0 = (int)floor(left_w / CHUNK_SIZE) - 1;
    cx1 = (int)floor(right_w / CHUNK_SIZE) + 1;
    cy0 = (int)floor(top_w / CHUNK_SIZE) - 1;
    cy1 = (int)floor(bot_w / CHUNK_SIZE) + 1;

    for (cx = cx0; cx <= cx1; ++cx) {
        double wx = cx * CHUNK_SIZE;
        world_to_screen(wx, top_w, &sx1, &sy1);
        world_to_screen(wx, bot_w, &sx2, &sy2);
        line_c(dc, sx1, sy1, sx2, sy2, RGB(16,30,46), 1);
        SetTextColor(dc, RGB(42,60,78));
        sprintf(buf, "cx%d", cx);
        draw_text(dc, sx1 + 4, rc.top + 22, buf);
    }

    for (cy = cy0; cy <= cy1; ++cy) {
        double wy = cy * CHUNK_SIZE;
        world_to_screen(left_w, wy, &sx1, &sy1);
        world_to_screen(right_w, wy, &sx2, &sy2);
        line_c(dc, sx1, sy1, sx2, sy2, RGB(16,30,46), 1);
        SetTextColor(dc, RGB(42,60,78));
        sprintf(buf, "cy%d", cy);
        draw_text(dc, rc.left + 8, sy1 + 4, buf);
    }

    SetTextColor(dc, RGB(90,110,130));
    draw_text(dc, rc.left+10, rc.top+8, "UNBOUNDED SPARSE FIELD: chunks are projected coordinates, not borders");
}

static void draw_blackhole_field(HDC dc, Entity *bh) {
    int sx, sy;
    int rr, eh;
    double s = field_scale();
    if (!bh) return;
    world_to_screen(bh->pos.x, bh->pos.y, &sx, &sy);
    rr = (int)(bh->gravity_radius * s);
    eh = (int)(bh->event_horizon * s);

    if (rr > 2 && rr < 2000) {
        HPEN p = pen(RGB(60,65,105), 1);
        HBRUSH oldb = (HBRUSH)SelectObject(dc, GetStockObject(NULL_BRUSH));
        HGDIOBJ oldp = SelectObject(dc, p);
        Ellipse(dc, sx-rr, sy-rr, sx+rr, sy+rr);
        SelectObject(dc, oldp);
        SelectObject(dc, oldb);
        DeleteObject(p);
    }

    if (g.show_force_field) {
        int k;
        for (k = 1; k <= 4; ++k) {
            int ar = (rr * k) / 4;
            if (ar > 4 && ar < 2200) {
                HPEN fp = pen(RGB(26 + k*8, 34 + k*8, 70 + k*12), 1);
                HBRUSH oldfb = (HBRUSH)SelectObject(dc, GetStockObject(NULL_BRUSH));
                HGDIOBJ oldfp = SelectObject(dc, fp);
                Ellipse(dc, sx-ar, sy-ar, sx+ar, sy+ar);
                SelectObject(dc, oldfp);
                SelectObject(dc, oldfb);
                DeleteObject(fp);
            }
        }
    }

    ellipse_c(dc, sx, sy, eh > 2 ? eh : 2, RGB(255,96,96), RGB(0,0,0), 2);
    ellipse_c(dc, sx, sy, eh/2 + 2, RGB(150,50,255), RGB(0,0,0), 1);
}

static void draw_entity(HDC dc, Entity *e) {
    int sx, sy, px, py, r;
    COLORREF c, edge;
    char buf[160];

    if (!e || !e->alive || !e->visible) return;
    if (!g.atom_view_on && e->parent_atom_id > 0) return;
    if (g.multiscale_mode && current_scale_level() >= 2 && (e->kind == ENT_PIXEL || e->kind == ENT_SUBPARTICLE || e->kind == ENT_NUCLEON)) return;
    world_to_screen(e->pos.x, e->pos.y, &sx, &sy);

    if (sx < g.field_rc.left-80 || sx > g.field_rc.right+80 || sy < g.field_rc.top-80 || sy > g.field_rc.bottom+80)
        return;

    if ((e->kind == ENT_PIXEL || e->kind == ENT_BODY) && g.trails_on) {
        world_to_screen(e->prev.x, e->prev.y, &px, &py);
        line_c(dc, px, py, sx, sy, e->kind == ENT_BODY ? RGB(45,80,65) : RGB(40,48,58), 1);
    }

    if (e->kind == ENT_BLACKHOLE) {
        draw_blackhole_field(dc, e);
        return;
    }

    c = e->kind == ENT_PIXEL ? mat_color(e->material) : kind_color(e->kind);
    if (e->particle == PT_ELECTRON) c = RGB(90,180,255);
    else if (e->particle == PT_PROTON) c = RGB(255,90,90);
    else if (e->particle == PT_NEUTRON) c = RGB(180,180,190);
    else if (e->particle == PT_UP_QUARK) c = RGB(255,190,80);
    else if (e->particle == PT_DOWN_QUARK) c = RGB(190,120,255);
    edge = e->selected ? RGB(255,255,255) : (e->hovered ? RGB(255,220,90) : c);
    r = (int)(e->radius * field_scale());
    if (r < 2) r = 2;
    if (e->kind == ENT_BODY && r < 8) r = 8;
    if (r > 160) r = 160;
    if (e->pulse > 0) r += (int)(e->pulse * 8);

    if (e->kind == ENT_PROBE) {
        ellipse_c(dc, sx, sy, 7, RGB(76,210,255), RGB(8,14,22), e->selected ? 3 : 1);
        line_c(dc, sx-14, sy, sx+14, sy, RGB(76,210,255), 1);
        line_c(dc, sx, sy-14, sx, sy+14, RGB(76,210,255), 1);
    } else if (e->kind == ENT_ATOM) {
        HPEN p = pen(edge, e->selected ? 3 : 2);
        HBRUSH oldb = (HBRUSH)SelectObject(dc, GetStockObject(NULL_BRUSH));
        HGDIOBJ oldp = SelectObject(dc, p);
        Ellipse(dc, sx-r, sy-r, sx+r, sy+r);
        if (g.atom_view_on) Ellipse(dc, sx-(r/2), sy-(r/2), sx+(r/2), sy+(r/2));
        SelectObject(dc, oldp);
        SelectObject(dc, oldb);
        DeleteObject(p);
        ellipse_c(dc, sx, sy, 5, RGB(255,220,90), RGB(8,14,22), 1);
    } else if (e->kind == ENT_BODY) {
        if (g.multiscale_mode && current_scale_level() >= 2) {
            r = 5 + (int)clampd(log(e->mass + 1.0), 1.0, 18.0);
        }
        HPEN p = pen(edge, e->selected ? 3 : 2);
        HBRUSH oldb = (HBRUSH)SelectObject(dc, GetStockObject(NULL_BRUSH));
        HGDIOBJ oldp = SelectObject(dc, p);
        Ellipse(dc, sx-r, sy-r, sx+r, sy+r);
        SelectObject(dc, oldp);
        SelectObject(dc, oldb);
        DeleteObject(p);
        ellipse_c(dc, sx, sy, 4, edge, RGB(8,14,22), 1);
        if (g.show_vectors) {
            int vx = sx + (int)(e->meta_vx * field_scale() * 0.08);
            int vy = sy + (int)(e->meta_vy * field_scale() * 0.08);
            line_c(dc, sx, sy, vx, vy, RGB(120,255,150), 2);
        }
    } else {
        ellipse_c(dc, sx, sy, r, edge, RGB(8,14,22), e->selected ? 3 : 1);
    }

    if (g.labels_on && (e->selected || e->hovered || e->kind != ENT_PIXEL)) {
        SetTextColor(dc, edge);
        sprintf(buf, "#%d %s", e->id, e->name);
        draw_text(dc, sx+10, sy-10, buf);
    }
}

static void render_field(HDC dc) {
    int i;
    Entity *bh = entity_by_id(g.blackhole_id);
    draw_chunk_grid(dc);

    if (bh) draw_blackhole_field(dc, bh);

    for (i = 0; i < MAX_ENT; ++i) {
        if (g.ent[i].alive && g.ent[i].kind == ENT_PIXEL)
            draw_entity(dc, &g.ent[i]);
    }

    for (i = 0; i < MAX_ENT; ++i) {
        if (g.ent[i].alive && g.ent[i].kind == ENT_BODY)
            draw_entity(dc, &g.ent[i]);
    }

    for (i = 0; i < MAX_ENT; ++i) {
        if (g.ent[i].alive && g.ent[i].kind != ENT_PIXEL && g.ent[i].kind != ENT_BODY && g.ent[i].kind != ENT_BLACKHOLE)
            draw_entity(dc, &g.ent[i]);
    }

    if (bh) draw_entity(dc, bh);
}

static void panel_frame(HDC dc, RECT r, const char *title) {
    fill_rect_c(dc, r, RGB(9,16,24));
    rect_outline(dc, r, RGB(56,74,92), 1);
    SetTextColor(dc, RGB(226,234,242));
    draw_text(dc, r.left+10, r.top+8, title);
}

static void render_inspector(HDC dc, RECT r) {
    Entity *sel = entity_by_id(g.selected_id);
    Entity *hov = entity_by_id(g.hovered_id);
    Entity *bh = entity_by_id(g.blackhole_id);
    int y = r.top + 36;
    char buf[512];

    panel_frame(dc, r, "INSPECTOR / REGISTRY");

    SetTextColor(dc, RGB(255,220,90));
    sprintf(buf, "tool=%s material=%s brush=%d", tool_name(g.tool), mat_name(g.mat), g.brush_radius);
    draw_text(dc, r.left+14, y, buf); y += 18;

    sprintf(buf, "gravity=%s cohesion=%s horizon=%s auto_forge=%s multiscale=%s vectors=%s",
            g.gravity_on ? "on" : "off", g.cohesion_on ? "on" : "off",
            g.absorb_on ? "on" : "off", g.auto_forge ? "on" : "off",
            g.multiscale_mode ? "on" : "off", g.show_vectors ? "on" : "off");
    draw_text(dc, r.left+14, y, buf); y += 18;

    SetTextColor(dc, RGB(76,210,255));
    sprintf(buf, "micro-merge1 BHD: emit=%d r=%.0f spd=%.0f mass=%.1f erase=%.0f",
            g.desktop_preset.emit_count, g.desktop_preset.emit_radius, g.desktop_preset.emit_speed,
            g.desktop_preset.emit_mass, g.desktop_preset.erase_radius);
    draw_text(dc, r.left+14, y, buf); y += 18;
    sprintf(buf, "BH grow: +mass=%.0f +radius=%.2f caps=<%.0f %.0f>",
            g.desktop_preset.bh_grow_mass, g.desktop_preset.bh_grow_radius,
            g.desktop_preset.bh_mass_max, g.desktop_preset.bh_radius_max);
    draw_text(dc, r.left+14, y, buf); y += 24;

    if (bh) {
        SetTextColor(dc, RGB(255,96,96));
        sprintf(buf, "BH #%d mass=%.1f radius=%.1f", bh->id, bh->mass, bh->gravity_radius);
        draw_text(dc, r.left+14, y, buf); y += 18;
        SetTextColor(dc, RGB(145,165,185));
        sprintf(buf, "pos=<%.2f %.2f> horizon=%.2f", bh->pos.x, bh->pos.y, bh->event_horizon);
        draw_text(dc, r.left+24, y, buf); y += 22;
    }

    SetTextColor(dc, RGB(226,234,242));
    draw_text(dc, r.left+14, y, "Hovered:"); y += 18;
    if (hov) {
        SetTextColor(dc, hov->kind == ENT_PIXEL ? mat_color(hov->material) : kind_color(hov->kind));
        sprintf(buf, "#%d %s %s", hov->id, kind_name(hov->kind), hov->name);
        draw_text(dc, r.left+24, y, buf); y += 18;
    } else {
        SetTextColor(dc, RGB(145,165,185));
        draw_text(dc, r.left+24, y, "none"); y += 18;
    }

    y += 8;
    SetTextColor(dc, RGB(226,234,242));
    draw_text(dc, r.left+14, y, "Selected:"); y += 18;

    if (sel) {
        SetTextColor(dc, sel->kind == ENT_PIXEL ? mat_color(sel->material) : kind_color(sel->kind));
        sprintf(buf, "#%d %s", sel->id, sel->name); draw_text(dc, r.left+24, y, buf); y += 18;

        SetTextColor(dc, RGB(145,165,185));
        sprintf(buf, "kind=%s particle=%s mat=%s mode=%s", kind_name(sel->kind), particle_name(sel->particle), mat_name(sel->material), mode_name(sel->mode));
        draw_text(dc, r.left+24, y, buf); y += 18;
        sprintf(buf, "pos=<%.2f %.2f> vel=<%.2f %.2f>", sel->pos.x, sel->pos.y, sel->vel.x, sel->vel.y);
        draw_text(dc, r.left+24, y, buf); y += 18;
        sprintf(buf, "mass=%.2f radius=%.2f children=%d body_id=%d parent_atom=%d", sel->mass, sel->radius, sel->child_count, sel->body_id, sel->parent_atom_id);
        draw_text(dc, r.left+24, y, buf); y += 18;
        if (sel->kind == ENT_ATOM) { sprintf(buf, "atom Z=%d A=%d p=%d n=%d e=%d asset=%d", sel->atomic_number, sel->mass_number, sel->protons, sel->neutrons, sel->electrons, sel->reusable_asset_id); draw_text(dc, r.left+24, y, buf); y += 18; }
        sprintf(buf, "density=%.2f stiff=%.2f fracture=%.2f meta_v=<%.2f %.2f>", sel->density, sel->stiffness, sel->fracture_limit, sel->meta_vx, sel->meta_vy);
        draw_text(dc, r.left+24, y, buf); y += 18;
        if (sel->kind == ENT_BLACKHOLE) {
            sprintf(buf, "BH force=%.1f radius=%.1f horizon=%.1f mass=%.1f", sel->gravity_strength, sel->gravity_radius, sel->event_horizon, sel->mass);
            draw_text(dc, r.left+24, y, buf); y += 18;
        }
        sprintf(buf, "origin=%s", sel->origin); draw_text(dc, r.left+24, y, buf); y += 18;
        sprintf(buf, "definition=%s", sel->definition); draw_text(dc, r.left+24, y, buf); y += 18;
        sprintf(buf, "storage=%s", sel->storage); draw_text(dc, r.left+24, y, buf); y += 18;
    }

    y = r.bottom - 126;
    SetTextColor(dc, RGB(120,255,150));
    draw_text(dc, r.left+14, y, "QoL:"); y += 18;
    SetTextColor(dc, RGB(145,165,185));
    draw_text(dc, r.left+24, y, "LMB paint | RMB blackhole | F forge | M preset"); y += 16;
    draw_text(dc, r.left+24, y, "Y atom view | S save asset | J feeder | E burst"); y += 16;
    draw_text(dc, r.left+24, y, "9/0 feeder rate | G gravity | H horizon | O cohesion"); y += 16;
    draw_text(dc, r.left+24, y, "F1 controls | F9 events | F10 windows | F11 wiring | INS self-studio"); y += 16;
}

static void render_trace(HDC dc, RECT r) {
    int y, i, shown=0;
    char buf[512];
    panel_frame(dc, r, "TRACE");
    y = r.top + 30;

    for (i = MAX_TRACE-1; i >= 0 && y < r.bottom - 10; --i) {
        Trace *t = &g.trace[i];
        if (!t->alive) continue;
        SetTextColor(dc, shown == 0 ? RGB(255,255,255) : RGB(145,165,185));
        sprintf(buf, "t=%6.2f #%d %s target=%d %s", t->t, t->id, t->action, t->target_id, t->note);
        draw_text(dc, r.left+14, y, buf);
        y += 16;
        shown++;
    }
}


static void render_controls_panel(HDC dc, RECT r) {
    int y = r.top + 36;
    int i, count = 0;
    char buf[512];

    panel_frame(dc, r, "CONTROLS SETTINGS / REMAP");

    SetTextColor(dc, RGB(255,220,90));
    sprintf(buf, "F1 controls | F9 events | F10 windows | F11 wiring | INS self-studio | F4 remap | conflicts=%d", g.controls_conflict_count);
    draw_text(dc, r.left+14, y, buf); y += 20;

    if (g.controls_capture) {
        SetTextColor(dc, RGB(255,96,96));
        draw_text(dc, r.left+14, y, "CAPTURE MODE: press new key for selected action, or ESC to cancel");
        y += 22;
    }

    for (i = 0; i < MAX_CONTROL_BINDINGS && y < r.bottom - 16; ++i) {
        ControlBinding *c = &g.controls[i];
        int conflict;
        if (!c->alive) continue;
        conflict = controls_key_is_used(c->key, c->action);

        if (count == g.controls_selected) SetTextColor(dc, RGB(255,255,255));
        else if (conflict) SetTextColor(dc, RGB(255,96,96));
        else SetTextColor(dc, RGB(145,165,185));

        sprintf(buf, "%s%-22s key=%-10s default=%-10s %s",
                count == g.controls_selected ? "> " : "  ",
                c->name,
                key_name_simple(c->key),
                key_name_simple(c->default_key),
                conflict ? "CONFLICT" : "");
        draw_text(dc, r.left+18, y, buf);
        y += 16;
        count++;
    }
}


static void render_event_panel(HDC dc, RECT r) {
    int y = r.top + 36;
    int i, shown = 0;
    char buf[512];

    panel_frame(dc, r, "EVENT REGISTRY / CONTEXT RESOLVER");

    SetTextColor(dc, RGB(255,220,90));
    sprintf(buf, "resolver=%s last_event=%d last_action=%s ctx=0x%08X conflicts=%d",
            g.event_resolver_on ? "on" : "off",
            g.last_event_id,
            action_name((ActionId)g.last_resolved_action),
            (unsigned int)g.last_context_mask,
            g.event_conflict_count);
    draw_text(dc, r.left+14, y, buf); y += 22;

    SetTextColor(dc, RGB(145,165,185));
    draw_text(dc, r.left+14, y, "Principle: Event + Context + Binding -> Action");
    y += 22;

    for (i = MAX_EVENT_RECORDS - 1; i >= 0 && y < r.bottom - 16; --i) {
        EventRecord *ev = &g.events[i];
        if (!ev->alive) continue;
        SetTextColor(dc, shown == 0 ? RGB(255,255,255) : RGB(145,165,185));
        sprintf(buf, "#%d t=%.2f %-12s code=%s mx=%d my=%d ctx=0x%08X target=%d %s",
                ev->id,
                ev->time,
                event_type_name(ev->type),
                ev->type == EVT_KEY_DOWN ? key_name_simple(ev->code) : key_name_simple(ev->code),
                ev->mouse_x,
                ev->mouse_y,
                ev->context_mask,
                ev->target_entity,
                ev->note);
        draw_text(dc, r.left+14, y, buf);
        y += 16;
        shown++;
    }
}


static void render_window_registry_panel(HDC dc, RECT r) {
    int y = r.top + 36;
    int i;
    int list_right = r.right - 372;
    int relation_y;
    RECT edit;
    WindowRecord *sel;
    const WindowDecorator *deco;
    char buf[512];

    window_sync_runtime();
    if (list_right < r.left + 340) list_right = r.right - 18;
    sel = window_selected_or_active();
    deco = window_decorator(sel);
    panel_frame(dc, r, "WINDOW / ACTION CENTRAL REGISTRY");

    SetTextColor(dc, RGB(255,220,90));
    sprintf(buf, "F10 toggle | drag title | corner resize | click row | arrows move | +/- size | D decorator | C cascade");
    draw_text(dc, r.left+14, y, buf); y += 22;

    SetTextColor(dc, RGB(226,234,242));
    draw_text(dc, r.left+14, y, "Windows:");
    y += 18;

    for (i = 0; i < MAX_WINDOW_RECORDS && y < r.bottom - 160; ++i) {
        WindowRecord *w = &g.windows[i];
        RECT row;
        if (!w->alive) continue;
        row.left = r.left + 18; row.top = y - 2; row.right = list_right - 10; row.bottom = y + 14;
        if (w->id == (WindowId)g.window_registry_selected) {
            fill_rect_c(dc, row, RGB(45, 30, 8));
            rect_outline(dc, row, window_decorator(w)->accent, 1);
        }
        SetTextColor(dc, w->id == g.window_registry_selected ? RGB(255,220,90) : (w->open ? RGB(120,255,150) : RGB(145,165,185)));
        sprintf(buf, "WIN %-14s open=%d z=%03d rc=%ld,%ld %ldx%ld deco=%s",
                w->name, w->open, w->z_order,
                w->rc.left, w->rc.top, w->rc.right - w->rc.left, w->rc.bottom - w->rc.top,
                window_decorator(w)->name);
        draw_text(dc, r.left+24, y, buf);
        y += 16;
    }

    relation_y = y;
    if (list_right < r.right - 40) {
        int ey;
        edit.left = list_right + 8; edit.top = r.top + 58; edit.right = r.right - 16; edit.bottom = r.bottom - 18;
        fill_rect_c(dc, edit, RGB(6, 8, 12));
        rect_outline(dc, edit, sel ? deco->accent : RGB(56,74,92), 1);
        ey = edit.top + 12;
        SetTextColor(dc, RGB(255,220,90));
        draw_text(dc, edit.left + 10, ey, "SELECTED WINDOW EDITOR"); ey += 22;
        if (sel) {
            SetTextColor(dc, deco->text);
            sprintf(buf, "%s  role=%s", sel->name, sel->role); draw_text(dc, edit.left + 10, ey, buf); ey += 18;
            sprintf(buf, "open=%d z=%d modal=%d touched=%.2f", sel->open, sel->z_order, sel->modal, g.time - sel->last_touched); draw_text(dc, edit.left + 10, ey, buf); ey += 18;
            sprintf(buf, "position left/top=%ld,%ld", sel->rc.left, sel->rc.top); draw_text(dc, edit.left + 10, ey, buf); ey += 18;
            sprintf(buf, "size width/height=%ldx%ld", sel->rc.right - sel->rc.left, sel->rc.bottom - sel->rc.top); draw_text(dc, edit.left + 10, ey, buf); ey += 18;
            sprintf(buf, "caps=0x%08lX decorator=%s", (unsigned long)sel->caps, deco->name); draw_text(dc, edit.left + 10, ey, buf); ey += 22;
            SetTextColor(dc, RGB(145,165,185));
            draw_text(dc, edit.left + 10, ey, "Direct edit while this panel is open:"); ey += 18;
            draw_text(dc, edit.left + 18, ey, "TAB select next | ENTER open/close"); ey += 16;
            draw_text(dc, edit.left + 18, ey, "ARROWS move | SHIFT+ARROWS fast"); ey += 16;
            draw_text(dc, edit.left + 18, ey, "+/- resize | D style | C cascade"); ey += 18;
            SetTextColor(dc, deco->accent);
            draw_text(dc, edit.left + 10, ey, "Decorator = action + presentation layer around the object.");
        } else {
            SetTextColor(dc, RGB(145,165,185));
            draw_text(dc, edit.left + 10, ey, "No window selected.");
        }
    }

    y = relation_y;
    y += 12;
    SetTextColor(dc, RGB(226,234,242));
    draw_text(dc, r.left+14, y, "Window -> Action relations:");
    y += 18;

    for (i = 0; i < MAX_WINDOW_ACTION_BINDINGS && y < r.bottom - 16; ++i) {
        WindowActionBinding *b = &g.win_actions[i];
        if (!b->alive) continue;
        SetTextColor(dc, RGB(145,165,185));
        sprintf(buf, "%-16s %-14s action=%-22s note=%s",
                window_name(b->window_id), b->relation, action_name(b->action), b->note);
        draw_text(dc, r.left+24, y, buf);
        y += 16;
    }
}


static void render_wiring_panel(HDC dc, RECT r) {
    int y = r.top + 36;
    int i, shown = 0;
    char buf[512];

    window_sync_runtime();
    panel_frame(dc, r, "WIRING / EVENT CONTEXT ACTION GRAPH");

    SetTextColor(dc, RGB(255,220,90));
    sprintf(buf, "F11 toggle | last_event=%d | context=0x%08X | action=%s",
            g.last_event_id,
            (unsigned int)g.last_context_mask,
            action_name((ActionId)g.last_resolved_action));
    draw_text(dc, r.left + 14, y, buf); y += 24;

    SetTextColor(dc, RGB(226,234,242));
    draw_text(dc, r.left + 14, y, "Runtime windows:"); y += 18;
    for (i = 0; i < MAX_WINDOW_RECORDS && y < r.bottom - 170; ++i) {
        WindowRecord *w = &g.windows[i];
        if (!w->alive) continue;
        SetTextColor(dc, w->open ? RGB(120,255,150) : RGB(145,165,185));
        sprintf(buf, "[%s] open=%d z=%d toggle=%s role=%s",
                window_name(w->id), w->open, w->z_order,
                action_name(w->toggle_action), w->role);
        draw_text(dc, r.left + 24, y, buf); y += 16;
    }

    y += 12;
    SetTextColor(dc, RGB(226,234,242));
    draw_text(dc, r.left + 14, y, "Action bindings:"); y += 18;
    for (i = 0; i < MAX_WINDOW_ACTION_BINDINGS && y < r.bottom - 20; ++i) {
        WindowActionBinding *b = &g.win_actions[i];
        if (!b->alive) continue;
        SetTextColor(dc, RGB(145,165,185));
        sprintf(buf, "%02d %-14s -> %-22s via %-14s | %s",
                shown,
                window_name(b->window_id),
                action_name(b->action),
                b->relation,
                b->note);
        draw_text(dc, r.left + 24, y, buf); y += 16;
        shown++;
    }
}
static void render_wiring_strip(HDC dc, RECT full) {
    RECT r;
    char buf[512];
    if (!g.wiring_strip_on) return;

    r.left = full.left + 14;
    r.top = full.top + 38;
    r.right = full.right - 360;
    r.bottom = r.top + 22;

    fill_rect_c(dc, r, RGB(12, 4, 6));
    rect_outline(dc, r, RGB(170, 0, 0), 1);

    SetTextColor(dc, RGB(255, 80, 80));
    sprintf(buf, "WIRE: Event#%d -> Context 0x%08X -> Resolver -> Action:%s -> Window/Object/Trace | F11 full wiring | F12 strip",
            g.last_event_id,
            (unsigned int)g.last_context_mask,
            action_name((ActionId)g.last_resolved_action));
    draw_text(dc, r.left + 8, r.top + 5, buf);
}


/* ---------- self studio / universal node kernel ---------- */

static BHBNode *node_by_id(int id) {
    int i;
    for (i = 0; i < MAX_NODES; ++i)
        if (g.nodes[i].alive && g.nodes[i].id == id) return &g.nodes[i];
    return 0;
}

static BHBNode *node_by_index(int visible_index) {
    int i, c = 0;
    for (i = 0; i < MAX_NODES; ++i) {
        if (!g.nodes[i].alive) continue;
        if (c == visible_index) return &g.nodes[i];
        c++;
    }
    return 0;
}

static BHBNode *node_selected(void) {
    return node_by_index(g.node_selected_index);
}

static int node_count_alive(void) {
    int i, c = 0;
    for (i = 0; i < MAX_NODES; ++i) if (g.nodes[i].alive) c++;
    return c;
}

static const char *roles_text(unsigned int roles) {
    static char buf[192];
    buf[0] = 0;
    if (roles & ROLE_WINDOW) lstrcatA(buf, "WINDOW|");
    if (roles & ROLE_PANEL) lstrcatA(buf, "PANEL|");
    if (roles & ROLE_BUTTON) lstrcatA(buf, "BUTTON|");
    if (roles & ROLE_CONTROL) lstrcatA(buf, "CONTROL|");
    if (roles & ROLE_EDIT) lstrcatA(buf, "EDIT|");
    if (roles & ROLE_CONTENT) lstrcatA(buf, "CONTENT|");
    if (roles & ROLE_ACTION) lstrcatA(buf, "ACTION|");
    if (roles & ROLE_TOOL) lstrcatA(buf, "TOOL|");
    if (roles & ROLE_ENTITY) lstrcatA(buf, "ENTITY|");
    if (roles & ROLE_MENU) lstrcatA(buf, "MENU|");
    if (roles & ROLE_WORKFLOW) lstrcatA(buf, "WORKFLOW|");
    if (roles & ROLE_PREFAB) lstrcatA(buf, "PREFAB|");
    if (!buf[0]) lstrcatA(buf, "NONE");
    return buf;
}

static const char *caps_text(unsigned int caps) {
    static char buf[192];
    buf[0] = 0;
    if (caps & CAP_DRAG) lstrcatA(buf, "DRAG|");
    if (caps & CAP_RESIZE) lstrcatA(buf, "RESIZE|");
    if (caps & CAP_EDIT) lstrcatA(buf, "EDIT|");
    if (caps & CAP_DELETE) lstrcatA(buf, "DELETE|");
    if (caps & CAP_DUPLICATE) lstrcatA(buf, "DUP|");
    if (caps & CAP_CONTAIN) lstrcatA(buf, "CONTAIN|");
    if (caps & CAP_BIND) lstrcatA(buf, "BIND|");
    if (caps & CAP_RUN) lstrcatA(buf, "RUN|");
    if (caps & CAP_SAVE) lstrcatA(buf, "SAVE|");
    if (caps & CAP_DEFINE) lstrcatA(buf, "DEFINE|");
    if (!buf[0]) lstrcatA(buf, "NONE");
    return buf;
}

static int node_add(int parent_id, unsigned int roles, unsigned int caps, const char *kind, const char *name, const char *label, WindowId win, ActionId action) {
    int i;
    for (i = 0; i < MAX_NODES; ++i) {
        if (!g.nodes[i].alive) {
            BHBNode *n = &g.nodes[i];
            BHBNode *p;
            memset(n, 0, sizeof(*n));
            n->alive = 1;
            n->id = g.next_node_id++;
            n->parent_id = parent_id;
            n->roles = roles;
            n->caps = caps;
            n->window_id = win;
            n->primary_action = action;
            n->visible = 1;
            n->open = 1;
            n->editable = (caps & CAP_EDIT) ? 1 : 0;
            n->x = 40 + (i % 6) * 18;
            n->y = 80 + (i % 8) * 18;
            n->w = 160;
            n->h = 40;
            copy_s(n->kind, sizeof(n->kind), kind);
            copy_s(n->name, sizeof(n->name), name);
            copy_s(n->label, sizeof(n->label), label);
            copy_s(n->workflow, sizeof(n->workflow), "blank -> define -> bind -> use -> save");
            p = node_by_id(parent_id);
            if (p) p->child_count++;
            return n->id;
        }
    }
    return 0;
}

static void node_prop_add(int owner_id, PropType type, const char *key, const char *value) {
    int i;
    for (i = 0; i < MAX_NODE_PROPS; ++i) {
        if (!g.props[i].alive) {
            BHBProperty *p = &g.props[i];
            memset(p, 0, sizeof(*p));
            p->alive = 1;
            p->id = g.next_prop_id++;
            p->owner_node_id = owner_id;
            p->type = type;
            copy_s(p->key, sizeof(p->key), key);
            copy_s(p->value, sizeof(p->value), value);
            return;
        }
    }
}

static void self_studio_init(void) {
    int app, menu, opts, controls, forge, blank, button, workflow, windows, wiring;
    BHBNode *n;
    memset(g.nodes, 0, sizeof(g.nodes));
    memset(g.props, 0, sizeof(g.props));
    g.next_node_id = 1;
    g.next_prop_id = 1;
    g.node_selected_index = 0;
    g.node_dragging = 0;
    g.node_drag_id = 0;
    SetRect(&g.self_studio_rc, 0, 0, 0, 0);
    SetRect(&g.self_tree_rc, 0, 0, 0, 0);
    SetRect(&g.self_canvas_rc, 0, 0, 0, 0);
    SetRect(&g.self_editor_rc, 0, 0, 0, 0);

    app = node_add(0, ROLE_WINDOW|ROLE_PANEL|ROLE_CONTENT|ROLE_CONTROL, CAP_CONTAIN|CAP_EDIT|CAP_DEFINE|CAP_SAVE, "app", "BHB_SELF", "the application as editable object", WIN_SELF_STUDIO, ACT_NONE);
    node_prop_add(app, PROP_STRING, "principle", "the config of the app is the demo of what can be built");
    node_prop_add(app, PROP_STRING, "mode", "self-hosted editor/workbench");

    menu = node_add(app, ROLE_MENU|ROLE_PANEL|ROLE_CONTROL, CAP_CONTAIN|CAP_EDIT|CAP_DRAG, "menu", "main_menu", "Godot/Blender/Gimp/OneNote-like root menu", WIN_SELF_STUDIO, ACT_NONE);
    node_prop_add(menu, PROP_STRING, "tabs", "Scene, Assets, Controls, Windows, Workflows, Options");

    opts = node_add(menu, ROLE_WINDOW|ROLE_PANEL|ROLE_EDIT|ROLE_CONTENT, CAP_DRAG|CAP_RESIZE|CAP_EDIT|CAP_CONTAIN|CAP_SAVE, "window", "options_window", "editable options menu as node tree", WIN_SELF_STUDIO, ACT_SELF_STUDIO_TOGGLE);
    node_prop_add(opts, PROP_BOOL, "draggable", "true");
    node_prop_add(opts, PROP_BOOL, "resizable", "true");

    controls = node_add(opts, ROLE_PANEL|ROLE_CONTROL|ROLE_EDIT, CAP_EDIT|CAP_BIND|CAP_CONTAIN, "panel", "controls_page", "control bindings are editable content", WIN_CONTROLS, ACT_CONTROLS_TOGGLE);
    node_prop_add(controls, PROP_REF, "registry", "ControlBinding[]");

    windows = node_add(opts, ROLE_PANEL|ROLE_EDIT|ROLE_CONTENT, CAP_EDIT|CAP_BIND|CAP_CONTAIN, "panel", "windows_page", "windows are registered configurable nodes", WIN_WINDOW_REGISTRY, ACT_WINDOW_REGISTRY_TOGGLE);
    node_prop_add(windows, PROP_REF, "registry", "WindowRecord[]");

    forge = node_add(opts, ROLE_PANEL|ROLE_TOOL|ROLE_ACTION|ROLE_CONTENT, CAP_RUN|CAP_EDIT|CAP_DEFINE|CAP_SAVE, "tool", "asset_forge_page", "blank forms can define atoms/assets/tools", WIN_SELF_STUDIO, ACT_SPAWN_ATOM);
    node_prop_add(forge, PROP_STRING, "blank_form", "node + properties + bindings + workflow");

    blank = node_add(app, ROLE_PREFAB|ROLE_CONTENT|ROLE_EDIT|ROLE_ACTION, CAP_DEFINE|CAP_DUPLICATE|CAP_EDIT|CAP_BIND|CAP_SAVE, "prefab", "blank_node_form", "empty object that can become window/button/tool/asset", WIN_SELF_STUDIO, ACT_NODE_DUPLICATE_SELECTED);
    node_prop_add(blank, PROP_STRING, "roles", "choose roles to manifest behavior");
    node_prop_add(blank, PROP_STRING, "capabilities", "choose capabilities to allow actions");

    button = node_add(blank, ROLE_BUTTON|ROLE_CONTROL|ROLE_ACTION|ROLE_EDIT, CAP_EDIT|CAP_BIND|CAP_DRAG|CAP_DUPLICATE, "button", "blank_button", "editable button: label + event + action", WIN_SELF_STUDIO, ACT_NONE);
    node_prop_add(button, PROP_STRING, "on_click", "bind any ActionId");
    node_prop_add(button, PROP_STRING, "style", "black/red default");

    workflow = node_add(blank, ROLE_WORKFLOW|ROLE_ACTION|ROLE_CONTENT, CAP_RUN|CAP_EDIT|CAP_SAVE|CAP_DEFINE, "workflow", "blank_workflow", "chain of actions: defineable and reusable", WIN_SELF_STUDIO, ACT_NONE);
    node_prop_add(workflow, PROP_STRING, "steps", "select -> edit -> bind -> run -> save");

    wiring = node_add(app, ROLE_PANEL|ROLE_CONTENT|ROLE_ACTION, CAP_RUN|CAP_EDIT, "panel", "wiring_view", "live wiring is part of the editable app", WIN_WIRING, ACT_WIRING_PANEL_TOGGLE);
    node_prop_add(wiring, PROP_REF, "source", "EventRecord + ContextBinding + WindowRecord");

    n = node_by_id(app); if (n) { n->x = 110; n->y = 70; n->w = 170; n->h = 50; }
    n = node_by_id(menu); if (n) { n->x = 150; n->y = 165; n->w = 180; n->h = 50; }
    n = node_by_id(opts); if (n) { n->x = 170; n->y = 260; n->w = 190; n->h = 56; }
    n = node_by_id(controls); if (n) { n->x = 430; n->y = 185; n->w = 180; n->h = 46; }
    n = node_by_id(windows); if (n) { n->x = 430; n->y = 245; n->w = 180; n->h = 46; }
    n = node_by_id(forge); if (n) { n->x = 430; n->y = 305; n->w = 180; n->h = 46; }
    n = node_by_id(blank); if (n) { n->x = 150; n->y = 395; n->w = 210; n->h = 54; }
    n = node_by_id(button); if (n) { n->x = 430; n->y = 385; n->w = 180; n->h = 44; }
    n = node_by_id(workflow); if (n) { n->x = 430; n->y = 440; n->w = 180; n->h = 44; }
    n = node_by_id(wiring); if (n) { n->x = 170; n->y = 505; n->w = 190; n->h = 48; }
}

static void node_select_delta(int delta) {
    int c = node_count_alive();
    if (c <= 0) return;
    g.node_selected_index += delta;
    while (g.node_selected_index < 0) g.node_selected_index += c;
    g.node_selected_index %= c;
}

static void node_duplicate_selected(void) {
    BHBNode *s = node_selected();
    int id;
    char name[64];
    if (!s) return;
    sprintf(name, "%s_copy", s->name);
    id = node_add(s->parent_id, s->roles, s->caps, s->kind, name, s->label, s->window_id, s->primary_action);
    if (id) {
        node_prop_add(id, PROP_STRING, "duplicated_from", s->name);
        trace_add("node", g.probe_id, 0, "selected node duplicated as blank editable form");
    }
}


static void node_set_selected_id(int id) {
    int i, idx = 0;
    for (i = 0; i < MAX_NODES; ++i) {
        if (!g.nodes[i].alive) continue;
        if (g.nodes[i].id == id) {
            g.node_selected_index = idx;
            return;
        }
        idx++;
    }
}

static RECT self_studio_node_rect(BHBNode *n) {
    RECT rc;
    rc.left = g.self_canvas_rc.left + (int)n->x;
    rc.top = g.self_canvas_rc.top + (int)n->y;
    rc.right = rc.left + (int)n->w;
    rc.bottom = rc.top + (int)n->h;
    return rc;
}

static int self_studio_pick_node(int x, int y) {
    int i;
    for (i = MAX_NODES - 1; i >= 0; --i) {
        BHBNode *n = &g.nodes[i];
        RECT rc;
        if (!n->alive || !n->visible) continue;
        rc = self_studio_node_rect(n);
        if (rect_contains(rc, x, y)) return n->id;
    }
    return 0;
}

static int self_studio_pick_tree_index(int x, int y) {
    int line_h = 16;
    int header_y = g.self_tree_rc.top + 30;
    int rel = y - header_y;
    int idx = rel / line_h;
    if (!rect_contains(g.self_tree_rc, x, y) || rel < 0) return -1;
    return idx;
}

static void self_studio_begin_interaction(int x, int y) {
    int id = 0;
    int idx = -1;
    BHBNode *n;

    if (!g.self_studio_on) return;

    idx = self_studio_pick_tree_index(x, y);
    if (idx >= 0) {
        int i, c = 0;
        for (i = 0; i < MAX_NODES; ++i) {
            if (!g.nodes[i].alive) continue;
            if (c == idx) {
                g.node_selected_index = idx;
                trace_add("node", g.probe_id, 0, "selected node from tree");
                return;
            }
            c++;
        }
    }

    id = self_studio_pick_node(x, y);
    if (!id) return;
    node_set_selected_id(id);
    n = node_by_id(id);
    if (n && (n->caps & CAP_DRAG)) {
        RECT rc = self_studio_node_rect(n);
        g.node_dragging = 1;
        g.node_drag_id = id;
        g.node_drag_dx = x - rc.left;
        g.node_drag_dy = y - rc.top;
        trace_add("node", g.probe_id, id, "node drag begin");
    } else {
        trace_add("node", g.probe_id, id, "selected node on visual mirror");
    }
}

static void self_studio_drag_move(int x, int y) {
    BHBNode *n;
    if (!g.node_dragging) return;
    n = node_by_id(g.node_drag_id);
    if (!n) return;
    n->x = (double)(x - g.self_canvas_rc.left) - g.node_drag_dx;
    n->y = (double)(y - g.self_canvas_rc.top) - g.node_drag_dy;
    if (n->x < 8) n->x = 8;
    if (n->y < 8) n->y = 8;
    if (n->x + n->w > (g.self_canvas_rc.right - g.self_canvas_rc.left) - 8)
        n->x = (g.self_canvas_rc.right - g.self_canvas_rc.left) - n->w - 8;
    if (n->y + n->h > (g.self_canvas_rc.bottom - g.self_canvas_rc.top) - 8)
        n->y = (g.self_canvas_rc.bottom - g.self_canvas_rc.top) - n->h - 8;
}

static void self_studio_end_interaction(void) {
    if (g.node_dragging)
        trace_add("node", g.probe_id, g.node_drag_id, "node drag end");
    g.node_dragging = 0;
    g.node_drag_id = 0;
}

static void render_node_props(HDC dc, RECT r, int owner_id, int *py) {
    int i;
    char buf[256];
    for (i = 0; i < MAX_NODE_PROPS && *py < r.bottom - 18; ++i) {
        BHBProperty *p = &g.props[i];
        if (!p->alive || p->owner_node_id != owner_id) continue;
        SetTextColor(dc, RGB(175,175,175));
        sprintf(buf, "  prop %-18s = %s", p->key, p->value);
        draw_text(dc, r.left + 20, *py, buf);
        *py += 16;
    }
}

static void render_self_studio_panel(HDC dc, RECT r) {
    int y, i, idx = 0;
    char buf[512];
    BHBNode *sel;
    RECT tree, canvas, editor;

    g.self_studio_rc = r;
    tree.left = r.left + 10; tree.top = r.top + 28; tree.right = r.left + 310; tree.bottom = r.bottom - 10;
    canvas.left = tree.right + 10; canvas.top = r.top + 28; canvas.right = r.right - 280; canvas.bottom = r.bottom - 10;
    editor.left = canvas.right + 10; editor.top = r.top + 28; editor.right = r.right - 10; editor.bottom = r.bottom - 10;
    g.self_tree_rc = tree;
    g.self_canvas_rc = canvas;
    g.self_editor_rc = editor;

    panel_frame(dc, r, "SELF STUDIO / VISUAL MIRROR OF INTERNAL NODES");

    fill_rect_c(dc, tree, RGB(6,8,12));
    fill_rect_c(dc, canvas, RGB(6,8,12));
    fill_rect_c(dc, editor, RGB(6,8,12));
    rect_outline(dc, tree, RGB(110, 18, 18), 1);
    rect_outline(dc, canvas, RGB(140, 22, 22), 1);
    rect_outline(dc, editor, RGB(110, 18, 18), 1);

    SetTextColor(dc, RGB(255,80,80));
    draw_text(dc, tree.left + 10, tree.top + 8, "NODE TREE");
    draw_text(dc, canvas.left + 10, canvas.top + 8, "VISUAL CANVAS (drag nodes)");
    draw_text(dc, editor.left + 10, editor.top + 8, "GENERIC EDITOR");
    SetTextColor(dc, RGB(190,190,190));
    draw_text(dc, r.left + 16, r.top + 8, "INSERT toggle | PGUP/PGDN select | ENTER edit/open | F8 duplicate | mouse selects/drags");

    y = tree.top + 30;
    for (i = 0; i < MAX_NODES && y < tree.bottom - 18; ++i) {
        BHBNode *n = &g.nodes[i];
        int depth = 0, p = n->parent_id;
        if (!n->alive) continue;
        while (p > 0) {
            BHBNode *pn = node_by_id(p);
            if (!pn) break;
            depth++;
            p = pn->parent_id;
        }
        if (idx == g.node_selected_index) {
            RECT hi = {tree.left + 6, y - 1, tree.right - 6, y + 15};
            fill_rect_c(dc, hi, RGB(80, 8, 12));
            SetTextColor(dc, RGB(255,255,255));
        } else {
            SetTextColor(dc, RGB(160,160,160));
        }
        sprintf(buf, "%*s#%d %s", depth * 2, "", n->id, n->name);
        draw_text(dc, tree.left + 10, y, buf);
        y += 16;
        idx++;
    }

    for (i = 0; i < MAX_NODES; ++i) {
        BHBNode *n = &g.nodes[i];
        BHBNode *p;
        RECT nr, pr;
        if (!n->alive || !n->visible) continue;
        p = node_by_id(n->parent_id);
        if (!p) continue;
        nr = self_studio_node_rect(n);
        pr = self_studio_node_rect(p);
        line_c(dc, (pr.left + pr.right) / 2, pr.bottom, (nr.left + nr.right) / 2, nr.top, RGB(100, 18, 18), 1);
    }

    for (i = 0; i < MAX_NODES; ++i) {
        BHBNode *n = &g.nodes[i];
        RECT nr;
        if (!n->alive || !n->visible) continue;
        nr = self_studio_node_rect(n);
        fill_rect_c(dc, nr, n == node_selected() ? RGB(58, 12, 14) : RGB(12, 14, 20));
        rect_outline(dc, nr, n == node_selected() ? RGB(255, 70, 70) : RGB(130, 20, 20), 1);
        SetTextColor(dc, RGB(240,240,240));
        draw_text(dc, nr.left + 6, nr.top + 6, n->name);
        SetTextColor(dc, RGB(180,180,180));
        draw_text(dc, nr.left + 6, nr.top + 22, n->kind);
        if (n->caps & CAP_DRAG) {
            SetTextColor(dc, RGB(255, 90, 90));
            draw_text(dc, nr.right - 34, nr.top + 6, "DRAG");
        }
    }

    sel = node_selected();
    y = editor.top + 30;
    if (sel) {
        SetTextColor(dc, RGB(255,255,255));
        sprintf(buf, "selected: #%d %s", sel->id, sel->name);
        draw_text(dc, editor.left + 10, y, buf); y += 18;
        SetTextColor(dc, RGB(180,180,180));
        sprintf(buf, "kind=%s", sel->kind);
        draw_text(dc, editor.left + 10, y, buf); y += 16;
        sprintf(buf, "label=%s", sel->label);
        draw_text(dc, editor.left + 10, y, buf); y += 16;
        sprintf(buf, "roles=%s", roles_text(sel->roles));
        draw_text(dc, editor.left + 10, y, buf); y += 16;
        sprintf(buf, "caps=%s", caps_text(sel->caps));
        draw_text(dc, editor.left + 10, y, buf); y += 16;
        sprintf(buf, "window=%s  action=%s", window_name(sel->window_id), action_name(sel->primary_action));
        draw_text(dc, editor.left + 10, y, buf); y += 16;
        sprintf(buf, "rect=(%.0f,%.0f,%.0f,%.0f) editable=%d open=%d", sel->x, sel->y, sel->w, sel->h, sel->editable, sel->open);
        draw_text(dc, editor.left + 10, y, buf); y += 16;
        sprintf(buf, "workflow=%s", sel->workflow);
        draw_text(dc, editor.left + 10, y, buf); y += 20;
        SetTextColor(dc, RGB(255,80,80));
        draw_text(dc, editor.left + 10, y, "Properties:"); y += 18;
        render_node_props(dc, editor, sel->id, &y);
        y += 10;
        SetTextColor(dc, RGB(160,160,160));
        draw_text(dc, editor.left + 10, y, "This panel is the generic schema target: roles/caps/props define behavior.");
    }
}

static void render_frame(HWND hwnd, HDC target) {
    RECT cr;
    WindowRecord *w;
    HDC dc;
    HBRUSH bg;
    int drawn[MAX_WINDOW_RECORDS];
    int pass;
    double t0 = clock_s();

    GetClientRect(hwnd, &cr);
    update_field_rect(cr.right, cr.bottom);

    if (!g.memdc || g.back_w != cr.right || g.back_h != cr.bottom) {
        if (g.memdc) {
            SelectObject(g.memdc, g.oldbmp);
            DeleteObject(g.membmp);
            DeleteDC(g.memdc);
        }
        g.memdc = CreateCompatibleDC(target);
        g.membmp = CreateCompatibleBitmap(target, cr.right, cr.bottom);
        g.oldbmp = (HBITMAP)SelectObject(g.memdc, g.membmp);
        g.back_w = cr.right;
        g.back_h = cr.bottom;
    }

    dc = g.memdc;
    bg = brush(RGB(4,8,14));
    FillRect(dc, &cr, bg);
    DeleteObject(bg);
    SetBkMode(dc, TRANSPARENT);

    camera_apply_target();
    draw_header(dc);
    render_field(dc);
    render_wiring_strip(dc, cr);

    window_sync_runtime();

    memset(drawn, 0, sizeof(drawn));
    for (pass = 0; pass < MAX_WINDOW_RECORDS; ++pass) {
        int i, best = -1, best_z = 2147483647;
        RECT rc;
        for (i = 0; i < MAX_WINDOW_RECORDS; ++i) {
            WindowRecord *cand = &g.windows[i];
            if (!cand->alive || !cand->open || cand->id == WIN_FIELD || drawn[i]) continue;
            if (cand->z_order < best_z) {
                best = i;
                best_z = cand->z_order;
            }
        }
        if (best < 0) break;
        drawn[best] = 1;
        w = &g.windows[best];
        rc = window_resolve_rect(w->id, cr);
        switch (w->id) {
            case WIN_INSPECTOR: render_inspector(dc, rc); break;
            case WIN_TRACE: render_trace(dc, rc); break;
            case WIN_CONTROLS: render_controls_panel(dc, rc); break;
            case WIN_EVENTS: render_event_panel(dc, rc); break;
            case WIN_WINDOW_REGISTRY: render_window_registry_panel(dc, rc); break;
            case WIN_WIRING: render_wiring_panel(dc, rc); break;
            case WIN_SELF_STUDIO: render_self_studio_panel(dc, rc); break;
            default: break;
        }
        window_render_chrome(dc, w);
    }

    {
        WindowRecord *registry = window_by_id(WIN_WINDOW_REGISTRY);
        WindowRecord *selected = window_by_id((WindowId)g.window_registry_selected);
        if (registry && selected && registry != selected && registry->open && selected->open) {
            int ax = (registry->rc.left + registry->rc.right) / 2;
            int ay = (registry->rc.top + registry->rc.bottom) / 2;
            int bx = (selected->rc.left + selected->rc.right) / 2;
            int by = (selected->rc.top + selected->rc.bottom) / 2;
            int pulse = (int)(80.0 + 90.0 * (0.5 + 0.5 * sin(g.time * 5.0)));
            line_c(dc, ax, ay, bx, by, RGB(80 + pulse / 3, 120 + pulse / 2, 80 + pulse), 2);
        }
    }
    g.frame_ms = (clock_s() - t0) * 1000.0;
    BitBlt(target, 0, 0, cr.right, cr.bottom, dc, 0, 0, SRCCOPY);
}


/* ---------- controls registry / remap settings ---------- */

static ControlBinding *control_by_action(ActionId action) {
    int i;
    for (i = 0; i < MAX_CONTROL_BINDINGS; ++i)
        if (g.controls[i].alive && g.controls[i].action == action) return &g.controls[i];
    return 0;
}

static void control_add(ActionId action, int key, const char *name, const char *desc) {
    int i;
    for (i = 0; i < MAX_CONTROL_BINDINGS; ++i) {
        if (!g.controls[i].alive) {
            ControlBinding *c = &g.controls[i];
            memset(c, 0, sizeof(*c));
            c->alive = 1;
            c->action = action;
            c->key = key;
            c->default_key = key;
            copy_s(c->name, sizeof(c->name), name);
            copy_s(c->description, sizeof(c->description), desc);
            return;
        }
    }
}

static const char *key_name_simple(int key) {
    static char buf[32];
    if (key >= 'A' && key <= 'Z') { buf[0] = (char)key; buf[1] = 0; return buf; }
    if (key >= '0' && key <= '9') { buf[0] = (char)key; buf[1] = 0; return buf; }
    switch (key) {
        case VK_SPACE: return "SPACE";
        case VK_ESCAPE: return "ESC";
        case VK_TAB: return "TAB";
        case VK_BACK: return "BACKSPACE";
        case VK_HOME: return "HOME";
        case VK_UP: return "UP";
        case VK_DOWN: return "DOWN";
        case VK_LEFT: return "LEFT";
        case VK_RIGHT: return "RIGHT";
        case VK_F1: return "F1";
        case VK_F2: return "F2";
        case VK_F3: return "F3";
        case VK_F4: return "F4";
        case VK_F5: return "F5";
        case VK_F6: return "F6";
        case VK_F7: return "F7";
        case VK_F8: return "F8";
        case VK_INSERT: return "INSERT";
        case VK_PRIOR: return "PGUP";
        case VK_NEXT: return "PGDN";
        case VK_RETURN: return "ENTER";
        case VK_OEM_PLUS: return "+";
        case VK_OEM_MINUS: return "-";
        case VK_OEM_4: return "[";
        case VK_OEM_6: return "]";
        case VK_OEM_1: return ";";
        case VK_OEM_7: return "'";
        case VK_OEM_COMMA: return ",";
        case VK_OEM_PERIOD: return ".";
        default:
            sprintf(buf, "VK_%d", key);
            return buf;
    }
}

static int controls_key_is_used(int key, ActionId except_action) {
    int i;
    if (key <= 0) return 0;
    for (i = 0; i < MAX_CONTROL_BINDINGS; ++i) {
        ControlBinding *c = &g.controls[i];
        if (!c->alive || c->action == except_action) continue;
        if (c->key == key) return 1;
    }
    return 0;
}

static void controls_recount_conflicts(void) {
    int i;
    g.controls_conflict_count = 0;
    for (i = 0; i < MAX_CONTROL_BINDINGS; ++i) {
        ControlBinding *c = &g.controls[i];
        if (!c->alive) continue;
        if (controls_key_is_used(c->key, c->action)) g.controls_conflict_count++;
    }
}

static void controls_init(void) {
    memset(g.controls, 0, sizeof(g.controls));
    g.controls_selected = 0;
    g.controls_capture = 0;
    g.controls_panel_on = 0;

    control_add(ACT_PAN_UP, 'W', "pan_up", "camera pan up");
    control_add(ACT_PAN_DOWN, 'S', "pan_down", "camera pan down");
    control_add(ACT_PAN_LEFT, 'A', "pan_left", "camera pan left");
    control_add(ACT_PAN_RIGHT, 'D', "pan_right", "camera pan right");
    control_add(ACT_ZOOM_IN, VK_OEM_PLUS, "zoom_in", "zoom at mouse in");
    control_add(ACT_ZOOM_OUT, VK_OEM_MINUS, "zoom_out", "zoom at mouse out");
    control_add(ACT_CAMERA_HOME, VK_HOME, "camera_home", "camera home");
    control_add(ACT_CAMERA_FOCUS, VK_BACK, "camera_focus", "focus selected");

    control_add(ACT_PAUSE, VK_SPACE, "pause", "pause or resume simulation");
    control_add(ACT_STEP, 'N', "single_step", "single simulation step");
    control_add(ACT_RESET, 'R', "reset", "reset field");
    control_add(ACT_QUIT, 'Q', "quit", "quit");

    control_add(ACT_MAT_DUST, '1', "mat_dust", "select dust material");
    control_add(ACT_MAT_METAL, '2', "mat_metal", "select metal material");
    control_add(ACT_MAT_LIGHT, '3', "mat_light", "select light material");
    control_add(ACT_MAT_STONE, '4', "mat_stone", "select stone material");

    control_add(ACT_BLACKHOLE_AT_MOUSE, 'B', "blackhole_at_mouse", "spawn or move blackhole at mouse");
    control_add(ACT_FEEDER_TOGGLE, 'J', "feeder_toggle", "toggle blackhole feeder");
    control_add(ACT_FEEDER_BURST, 'E', "feeder_burst", "emit one feeder burst");
    control_add(ACT_FEEDER_RATE_DOWN, '9', "feeder_rate_down", "decrease feeder rate");
    control_add(ACT_FEEDER_RATE_UP, '0', "feeder_rate_up", "increase feeder rate");

    control_add(ACT_BH_FORCE_DOWN, VK_OEM_4, "bh_force_down", "blackhole force down");
    control_add(ACT_BH_FORCE_UP, VK_OEM_6, "bh_force_up", "blackhole force up");
    control_add(ACT_BH_RADIUS_DOWN, VK_OEM_1, "bh_radius_down", "blackhole radius down");
    control_add(ACT_BH_RADIUS_UP, VK_OEM_7, "bh_radius_up", "blackhole radius up");
    control_add(ACT_BH_HORIZON_DOWN, VK_OEM_COMMA, "bh_horizon_down", "event horizon down");
    control_add(ACT_BH_HORIZON_UP, VK_OEM_PERIOD, "bh_horizon_up", "event horizon up");
    control_add(ACT_FORCE_RINGS_TOGGLE, 'P', "force_rings", "toggle force rings");
    control_add(ACT_KICK_SELECTED, 'Z', "kick_selected", "kick selected from blackhole");

    control_add(ACT_FORGE_BODY, 'F', "forge_body", "forge body from pixel cluster");
    control_add(ACT_SPAWN_ATOM, 'X', "spawn_atom", "spawn current element atom");
    control_add(ACT_ELEMENT_PREV, VK_F2, "element_prev", "previous element preset");
    control_add(ACT_ELEMENT_NEXT, VK_F3, "element_next", "next element preset");
    control_add(ACT_ATOM_VIEW_TOGGLE, 'Y', "atom_view", "toggle atom components");
    control_add(ACT_SAVE_ASSET, VK_F8, "save_asset", "save selected as reusable asset");

    control_add(ACT_GRAVITY_TOGGLE, 'G', "gravity", "toggle gravity");
    control_add(ACT_COHESION_TOGGLE, 'O', "cohesion", "toggle cohesion");
    control_add(ACT_HORIZON_TOGGLE, 'H', "horizon", "toggle horizon absorption");
    control_add(ACT_TRAILS_TOGGLE, 'T', "trails", "toggle trails");
    control_add(ACT_INSPECTOR_TOGGLE, 'I', "inspector", "toggle inspector");
    control_add(ACT_LABELS_TOGGLE, 'L', "labels", "toggle labels");
    control_add(ACT_MULTISCALE_TOGGLE, 'M', "multiscale", "toggle multiscale render");
    control_add(ACT_VECTORS_TOGGLE, 'V', "vectors", "toggle vectors");
    control_add(ACT_SMOOTH_CAMERA_TOGGLE, 'U', "smooth_camera", "toggle smooth camera");

    control_add(ACT_SELECT_NEXT, VK_TAB, "select_next", "cycle selected entity");
    control_add(ACT_DELETE_SELECTED, 'K', "delete_selected", "delete selected");
    control_add(ACT_CLEAR_PIXELS, 'C', "clear_pixels", "clear pixels");
    control_add(ACT_AUTO_FORGE_TOGGLE, VK_F7, "auto_forge", "toggle auto forge");

    control_add(ACT_CONTROLS_TOGGLE, VK_F1, "controls_panel", "toggle controls panel");
    control_add(ACT_REMAP_SELECTED, VK_F4, "remap_selected", "capture new key for selected control");
    control_add(ACT_REMAP_PREV, VK_F5, "remap_prev", "select previous control binding");
    control_add(ACT_REMAP_NEXT, VK_F6, "remap_next", "select next control binding");
    control_add(ACT_EVENT_PANEL_TOGGLE, VK_F9, "event_panel", "toggle event registry panel");
    control_add(ACT_WINDOW_REGISTRY_TOGGLE, VK_F10, "window_registry", "toggle central window/action registry");
    control_add(ACT_WIRING_PANEL_TOGGLE, VK_F11, "wiring_panel", "toggle wiring visualization panel");
    control_add(ACT_WIRING_STRIP_TOGGLE, VK_F12, "wiring_strip", "toggle compact wiring strip");
    control_add(ACT_SELF_STUDIO_TOGGLE, VK_INSERT, "self_studio", "toggle self-studio node builder");
    control_add(ACT_NODE_SELECT_PREV, VK_PRIOR, "node_prev", "select previous studio node");
    control_add(ACT_NODE_SELECT_NEXT, VK_NEXT, "node_next", "select next studio node");
    control_add(ACT_NODE_TOGGLE_EDIT, VK_RETURN, "node_toggle_edit", "toggle selected node editable/open state");
    control_add(ACT_NODE_DUPLICATE_SELECTED, VK_F8, "node_duplicate", "duplicate selected studio node");

    control_add(ACT_WINDOW_SELECT_PREV, 0, "window_prev", "window editor: select previous window");
    control_add(ACT_WINDOW_SELECT_NEXT, 0, "window_next", "window editor: select next window");
    control_add(ACT_WINDOW_TOGGLE_SELECTED, 0, "window_toggle", "window editor: open/close selected window");
    control_add(ACT_WINDOW_MOVE_LEFT, 0, "window_left", "window editor: move selected left");
    control_add(ACT_WINDOW_MOVE_RIGHT, 0, "window_right", "window editor: move selected right");
    control_add(ACT_WINDOW_MOVE_UP, 0, "window_up", "window editor: move selected up");
    control_add(ACT_WINDOW_MOVE_DOWN, 0, "window_down", "window editor: move selected down");
    control_add(ACT_WINDOW_GROW, 0, "window_grow", "window editor: grow selected window");
    control_add(ACT_WINDOW_SHRINK, 0, "window_shrink", "window editor: shrink selected window");
    control_add(ACT_WINDOW_DECORATOR_NEXT, 0, "window_decorator", "window editor: cycle selected decorator");
    control_add(ACT_WINDOW_LAYOUT_CASCADE, 0, "window_cascade", "window editor: organize windows as cascade");

    controls_recount_conflicts();
}

static ActionId controls_action_for_key(WPARAM key) {
    int i;
    for (i = 0; i < MAX_CONTROL_BINDINGS; ++i) {
        ControlBinding *c = &g.controls[i];
        if (!c->alive) continue;
        if (c->key <= 0) continue;
        if (c->key == (int)key) return c->action;
    }
    return ACT_NONE;
}

static void controls_select_delta(int delta) {
    int count = 0, i;
    for (i = 0; i < MAX_CONTROL_BINDINGS; ++i) if (g.controls[i].alive) count++;
    if (count <= 0) return;
    g.controls_selected += delta;
    while (g.controls_selected < 0) g.controls_selected += count;
    g.controls_selected %= count;
}

static ControlBinding *controls_selected_binding(void) {
    int count = 0, i;
    for (i = 0; i < MAX_CONTROL_BINDINGS; ++i) {
        if (!g.controls[i].alive) continue;
        if (count == g.controls_selected) return &g.controls[i];
        count++;
    }
    return 0;
}

static void controls_begin_capture(void) {
    if (!controls_selected_binding()) return;
    g.controls_capture = 1;
    trace_add("controls", g.probe_id, 0, "waiting for new key for selected action");
}

static void controls_capture_key(WPARAM key) {
    ControlBinding *c = controls_selected_binding();
    char msg[128];
    if (!c) return;
    if (key == VK_ESCAPE) {
        g.controls_capture = 0;
        trace_add("controls", g.probe_id, 0, "remap cancelled");
        return;
    }
    c->key = (int)key;
    g.controls_capture = 0;
    controls_recount_conflicts();
    context_bindings_init();
    sprintf(msg, "remapped %s to %s", c->name, key_name_simple(c->key));
    trace_add("controls", g.probe_id, 0, msg);
}

static void controls_execute(ActionId action, WPARAM raw_key) {
    double pan = zoom_pan_amount();
    if (GetKeyState(VK_SHIFT) & 0x8000) pan *= CAMERA_FAST_MULT;
    if (GetKeyState(VK_CONTROL) & 0x8000) pan *= CAMERA_SLOW_MULT;

    switch (action) {
        case ACT_PAN_UP: camera_pan(0, -pan); break;
        case ACT_PAN_DOWN: camera_pan(0, pan); break;
        case ACT_PAN_LEFT: camera_pan(-pan, 0); break;
        case ACT_PAN_RIGHT: camera_pan(pan, 0); break;
        case ACT_ZOOM_IN: camera_zoom_at_mouse((GetKeyState(VK_SHIFT)&0x8000) ? CAMERA_ZOOM_FAST_STEP : CAMERA_ZOOM_STEP); break;
        case ACT_ZOOM_OUT: camera_zoom_at_mouse((GetKeyState(VK_SHIFT)&0x8000) ? (1.0 / CAMERA_ZOOM_FAST_STEP) : (1.0 / CAMERA_ZOOM_STEP)); break;
        case ACT_CAMERA_HOME: camera_home(); break;
        case ACT_CAMERA_FOCUS: camera_focus_selected(); break;
        case ACT_PAUSE: g.paused = !g.paused; trace_add("pause", g.probe_id, 0, g.paused ? "paused" : "running"); break;
        case ACT_STEP: g.step_once = 1; g.paused = 1; trace_add("step", g.probe_id, 0, "single simulation step"); break;
        case ACT_RESET: reset_world(); break;
        case ACT_QUIT: PostQuitMessage(0); break;
        case ACT_MAT_DUST: g.mat = MAT_DUST; trace_add("material", g.probe_id, 0, "DUST"); break;
        case ACT_MAT_METAL: g.mat = MAT_METAL; trace_add("material", g.probe_id, 0, "METAL"); break;
        case ACT_MAT_LIGHT: g.mat = MAT_LIGHT; trace_add("material", g.probe_id, 0, "LIGHT"); break;
        case ACT_MAT_STONE: g.mat = MAT_STONE; trace_add("material", g.probe_id, 0, "STONE"); break;
        case ACT_BLACKHOLE_AT_MOUSE: { double wx, wy; screen_to_world(g.mouse_x, g.mouse_y, &wx, &wy); spawn_blackhole(wx, wy); } break;
        case ACT_FEEDER_TOGGLE: g.feeder_on = !g.feeder_on; trace_add("feeder", g.probe_id, g.blackhole_id, g.feeder_on ? "feeder on" : "feeder off"); break;
        case ACT_FEEDER_BURST: feeder_emit(g.feeder_rate); break;
        case ACT_FEEDER_RATE_DOWN: g.feeder_rate -= 6; if (g.feeder_rate < 1) g.feeder_rate = 1; trace_add("feeder_rate", g.probe_id, 0, "feeder rate decreased"); break;
        case ACT_FEEDER_RATE_UP: g.feeder_rate += 6; if (g.feeder_rate > FEEDER_MAX_RATE) g.feeder_rate = FEEDER_MAX_RATE; trace_add("feeder_rate", g.probe_id, 0, "feeder rate increased"); break;
        case ACT_BH_FORCE_DOWN: blackhole_scale_force(1.0 / FORCE_STEP); break;
        case ACT_BH_FORCE_UP: blackhole_scale_force(FORCE_STEP); break;
        case ACT_BH_RADIUS_DOWN: blackhole_scale_radius(1.0 / BH_RADIUS_STEP); break;
        case ACT_BH_RADIUS_UP: blackhole_scale_radius(BH_RADIUS_STEP); break;
        case ACT_BH_HORIZON_DOWN: blackhole_scale_horizon(1.0 / BH_HORIZON_STEP); break;
        case ACT_BH_HORIZON_UP: blackhole_scale_horizon(BH_HORIZON_STEP); break;
        case ACT_FORCE_RINGS_TOGGLE: g.show_force_field = !g.show_force_field; trace_add("force_field", g.probe_id, g.blackhole_id, g.show_force_field ? "visible" : "hidden"); break;
        case ACT_KICK_SELECTED: blackhole_kick_selected(); break;
        case ACT_FORGE_BODY: forge_bodies(); break;
        case ACT_SPAWN_ATOM: { double wx, wy; screen_to_world(g.mouse_x, g.mouse_y, &wx, &wy); spawn_element_atom(wx, wy, g.forge_element_index); } break;
        case ACT_ELEMENT_PREV: cycle_element_preset(-1); break;
        case ACT_ELEMENT_NEXT: cycle_element_preset(1); break;
        case ACT_ATOM_VIEW_TOGGLE: g.atom_view_on = !g.atom_view_on; trace_add("atom_view", g.probe_id, g.selected_id, g.atom_view_on ? "atom components visible" : "atom shell only"); break;
        case ACT_SAVE_ASSET: save_selected_as_asset(); break;
        case ACT_GRAVITY_TOGGLE: g.gravity_on = !g.gravity_on; trace_add("gravity", g.probe_id, g.blackhole_id, g.gravity_on ? "on" : "off"); break;
        case ACT_COHESION_TOGGLE: g.cohesion_on = !g.cohesion_on; trace_add("cohesion", g.probe_id, 0, g.cohesion_on ? "on" : "off"); break;
        case ACT_HORIZON_TOGGLE: g.absorb_on = !g.absorb_on; trace_add("horizon", g.probe_id, g.blackhole_id, g.absorb_on ? "on" : "off"); break;
        case ACT_TRAILS_TOGGLE: g.trails_on = !g.trails_on; trace_add("trails", g.probe_id, 0, g.trails_on ? "on" : "off"); break;
        case ACT_INSPECTOR_TOGGLE: window_toggle(WIN_INSPECTOR); break;
        case ACT_LABELS_TOGGLE: g.labels_on = !g.labels_on; break;
        case ACT_MULTISCALE_TOGGLE: g.multiscale_mode = !g.multiscale_mode; trace_add("multiscale", g.probe_id, 0, g.multiscale_mode ? "multiscale render on" : "multiscale render off"); break;
        case ACT_VECTORS_TOGGLE: g.show_vectors = !g.show_vectors; trace_add("vectors", g.probe_id, g.selected_id, g.show_vectors ? "vectors on" : "vectors off"); break;
        case ACT_SMOOTH_CAMERA_TOGGLE: g.camera_smooth = !g.camera_smooth; trace_add("camera", g.probe_id, 0, g.camera_smooth ? "smooth camera on" : "smooth camera off"); break;
        case ACT_SELECT_NEXT: cycle_selected(); break;
        case ACT_DELETE_SELECTED: entity_delete(g.selected_id); break;
        case ACT_CLEAR_PIXELS: clear_pixels(); break;
        case ACT_AUTO_FORGE_TOGGLE: g.auto_forge = !g.auto_forge; trace_add("auto_forge", g.probe_id, 0, g.auto_forge ? "on" : "off"); break;
        case ACT_CONTROLS_TOGGLE: window_toggle(WIN_CONTROLS); break;
        case ACT_REMAP_SELECTED: controls_begin_capture(); break;
        case ACT_REMAP_PREV: controls_select_delta(-1); break;
        case ACT_REMAP_NEXT: controls_select_delta(1); break;
        case ACT_EVENT_PANEL_TOGGLE: window_toggle(WIN_EVENTS); break;
        case ACT_WINDOW_REGISTRY_TOGGLE: window_toggle(WIN_WINDOW_REGISTRY); break;
        case ACT_WIRING_PANEL_TOGGLE: window_toggle(WIN_WIRING); break;
        case ACT_WIRING_STRIP_TOGGLE: g.wiring_strip_on = !g.wiring_strip_on; trace_add("wiring", g.probe_id, 0, g.wiring_strip_on ? "wiring strip on" : "wiring strip off"); break;
        case ACT_SELF_STUDIO_TOGGLE: window_toggle(WIN_SELF_STUDIO); break;
        case ACT_NODE_SELECT_NEXT: node_select_delta(1); break;
        case ACT_NODE_SELECT_PREV: node_select_delta(-1); break;
        case ACT_NODE_TOGGLE_EDIT: { BHBNode *n = node_selected(); if (n) { n->editable = !n->editable; n->open = !n->open; trace_add("node", g.probe_id, 0, "selected node edit/open toggled"); } } break;
        case ACT_NODE_DUPLICATE_SELECTED: node_duplicate_selected(); break;
        case ACT_WINDOW_SELECT_NEXT:
        case ACT_WINDOW_SELECT_PREV:
        case ACT_WINDOW_TOGGLE_SELECTED:
        case ACT_WINDOW_MOVE_LEFT:
        case ACT_WINDOW_MOVE_RIGHT:
        case ACT_WINDOW_MOVE_UP:
        case ACT_WINDOW_MOVE_DOWN:
        case ACT_WINDOW_GROW:
        case ACT_WINDOW_SHRINK:
        case ACT_WINDOW_DECORATOR_NEXT:
        case ACT_WINDOW_LAYOUT_CASCADE:
            window_edit_selected(action);
            break;
        default: break;
    }
    (void)raw_key;
}


/* ---------- event registry / context resolver ---------- */

static const char *event_type_name(EventType type) {
    switch (type) {
        case EVT_KEY_DOWN: return "KEY_DOWN";
        case EVT_MOUSE_MOVE: return "MOUSE_MOVE";
        case EVT_MOUSE_DOWN: return "MOUSE_DOWN";
        case EVT_MOUSE_UP: return "MOUSE_UP";
        case EVT_MOUSE_WHEEL: return "MOUSE_WHEEL";
        case EVT_TIMER: return "TIMER";
        default: return "NONE";
    }
}

static const char *action_name(ActionId action) {
    ControlBinding *c = control_by_action(action);
    if (c) return c->name;
    switch (action) {
        case ACT_NONE: return "none";
        default: return "unknown_action";
    }
}

static void context_binding_add(EventType type, int code, unsigned int req, unsigned int forbid, int priority, ActionId action, const char *name) {
    int i;
    for (i = 0; i < MAX_CONTEXT_BINDINGS; ++i) {
        if (!g.ctx_bind[i].alive) {
            ContextBinding *b = &g.ctx_bind[i];
            memset(b, 0, sizeof(*b));
            b->alive = 1;
            b->event_type = type;
            b->event_code = code;
            b->required_mask = req;
            b->forbidden_mask = forbid;
            b->priority = priority;
            b->action = action;
            copy_s(b->name, sizeof(b->name), name);
            return;
        }
    }
}

static void context_bindings_init(void) {
    int i;
    memset(g.ctx_bind, 0, sizeof(g.ctx_bind));

    /* Every existing control binding becomes a contextual binding.
       The difference: action is resolved through Event + Context + priority. */
    for (i = 0; i < MAX_CONTROL_BINDINGS; ++i) {
        ControlBinding *c = &g.controls[i];
        if (!c->alive) continue;
        if (c->key <= 0) continue;
        context_binding_add(EVT_KEY_DOWN, c->key, CTX_ANY, CTX_CAPTURE, 10, c->action, c->name);
    }

    /* Capture context overrides normal meaning.
       A key in capture-mode is not a command; it becomes "assign this key". */
    context_binding_add(EVT_KEY_DOWN, -1, CTX_CAPTURE, CTX_ANY, 1000, ACT_REMAP_SELECTED, "capture_key_to_selected_binding");

    /* Controls panel context gets its own priority for navigation/remap.
       These are still registered bindings, not hardcoded command branches. */
    context_binding_add(EVT_KEY_DOWN, VK_F4, CTX_CONTROLS_PANEL, CTX_ANY, 80, ACT_REMAP_SELECTED, "controls_remap_selected");
    context_binding_add(EVT_KEY_DOWN, VK_F5, CTX_CONTROLS_PANEL, CTX_ANY, 80, ACT_REMAP_PREV, "controls_prev_binding");
    context_binding_add(EVT_KEY_DOWN, VK_F6, CTX_CONTROLS_PANEL, CTX_ANY, 80, ACT_REMAP_NEXT, "controls_next_binding");

    context_binding_add(EVT_KEY_DOWN, VK_UP, CTX_WINDOW_REGISTRY, CTX_CAPTURE, 90, ACT_WINDOW_MOVE_UP, "window_move_up");
    context_binding_add(EVT_KEY_DOWN, VK_DOWN, CTX_WINDOW_REGISTRY, CTX_CAPTURE, 90, ACT_WINDOW_MOVE_DOWN, "window_move_down");
    context_binding_add(EVT_KEY_DOWN, VK_LEFT, CTX_WINDOW_REGISTRY, CTX_CAPTURE, 90, ACT_WINDOW_MOVE_LEFT, "window_move_left");
    context_binding_add(EVT_KEY_DOWN, VK_RIGHT, CTX_WINDOW_REGISTRY, CTX_CAPTURE, 90, ACT_WINDOW_MOVE_RIGHT, "window_move_right");
    context_binding_add(EVT_KEY_DOWN, VK_TAB, CTX_WINDOW_REGISTRY, CTX_CAPTURE, 95, ACT_WINDOW_SELECT_NEXT, "window_select_next");
    context_binding_add(EVT_KEY_DOWN, VK_RETURN, CTX_WINDOW_REGISTRY, CTX_CAPTURE, 95, ACT_WINDOW_TOGGLE_SELECTED, "window_toggle_selected");
    context_binding_add(EVT_KEY_DOWN, VK_OEM_PLUS, CTX_WINDOW_REGISTRY, CTX_CAPTURE, 95, ACT_WINDOW_GROW, "window_grow");
    context_binding_add(EVT_KEY_DOWN, VK_OEM_MINUS, CTX_WINDOW_REGISTRY, CTX_CAPTURE, 95, ACT_WINDOW_SHRINK, "window_shrink");
    context_binding_add(EVT_KEY_DOWN, 'D', CTX_WINDOW_REGISTRY, CTX_CAPTURE, 95, ACT_WINDOW_DECORATOR_NEXT, "window_decorator_next");
    context_binding_add(EVT_KEY_DOWN, 'C', CTX_WINDOW_REGISTRY, CTX_CAPTURE, 95, ACT_WINDOW_LAYOUT_CASCADE, "window_layout_cascade");

    /* Context examples: same physical key can mean a more local action when context matches.
       They are intentionally conservative so defaults remain stable. */
    context_binding_add(EVT_KEY_DOWN, 'S', CTX_ATOM_SELECTED, CTX_CAPTURE, 60, ACT_SAVE_ASSET, "atom_context_save_asset");
    context_binding_add(EVT_KEY_DOWN, 'Z', CTX_BLACKHOLE_SEL, CTX_CAPTURE, 60, ACT_BH_FORCE_UP, "blackhole_context_z_force_up");

    g.event_conflict_count = 0;
}

static EventContext collect_context(void) {
    EventContext c;
    Entity *sel;
    memset(&c, 0, sizeof(c));

    c.focused_entity = g.selected_id;
    c.hovered_entity = g.hovered_id;
    c.selected_entity = g.selected_id;
    c.active_panel = g.controls_panel_on ? 1 : 0;
    c.scale_level = current_scale_level();
    c.capture_mode = g.controls_capture;
    c.mouse_over_field = rect_contains(g.field_rc, g.mouse_x, g.mouse_y);

    c.mask = 0;
    c.mask |= CTX_WORLD;
    if (g.controls_panel_on) c.mask |= CTX_CONTROLS_PANEL;
    if (g.window_registry_panel_on) c.mask |= CTX_WINDOW_REGISTRY;
    if (g.controls_capture) c.mask |= CTX_CAPTURE;
    if (c.mouse_over_field) c.mask |= CTX_MOUSE_OVER_FIELD;

    if (c.scale_level == 0) c.mask |= CTX_SCALE_PIXEL;
    else if (c.scale_level == 1) c.mask |= CTX_SCALE_BODY;
    else if (c.scale_level == 2) c.mask |= CTX_SCALE_META;
    else c.mask |= CTX_SCALE_MAP;

    sel = entity_by_id(g.selected_id);
    if (sel) {
        if (sel->kind == ENT_ATOM || sel->parent_atom_id > 0) c.mask |= CTX_ATOM_SELECTED;
        if (sel->kind == ENT_BLACKHOLE) c.mask |= CTX_BLACKHOLE_SEL;
        if (sel->kind == ENT_BODY) c.mask |= CTX_BODY_SELECTED;
    }

    return c;
}

static EventRecord *event_register(EventType type, int code, int mx, int my, int wheel, const char *note) {
    int slot = (g.next_event_id - 1) % MAX_EVENT_RECORDS;
    EventRecord *ev = &g.events[slot];
    EventContext ctx = collect_context();

    memset(ev, 0, sizeof(*ev));
    ev->alive = 1;
    ev->id = g.next_event_id++;
    ev->type = type;
    ev->code = code;
    ev->mouse_x = mx;
    ev->mouse_y = my;
    ev->wheel_delta = wheel;
    ev->source_entity = g.probe_id;
    ev->target_entity = g.hovered_id ? g.hovered_id : g.selected_id;
    ev->context_mask = ctx.mask;
    ev->time = g.time;
    copy_s(ev->note, sizeof(ev->note), note);
    g.last_event_id = ev->id;
    g.last_context_mask = (int)ctx.mask;
    return ev;
}

static int binding_matches(ContextBinding *b, EventRecord *ev, EventContext *ctx) {
    if (!b || !b->alive || !ev) return 0;
    if (b->event_type != ev->type) return 0;
    if (b->event_code != -1 && b->event_code != ev->code) return 0;
    if ((ctx->mask & b->required_mask) != b->required_mask) return 0;
    if ((ctx->mask & b->forbidden_mask) != 0) return 0;
    return 1;
}

static ActionId resolve_event(EventRecord *ev, EventContext *ctx, int *conflict_count) {
    int i;
    int best_pri = -2147483647;
    ActionId best = ACT_NONE;
    *conflict_count = 0;

    for (i = 0; i < MAX_CONTEXT_BINDINGS; ++i) {
        ContextBinding *b = &g.ctx_bind[i];
        if (!binding_matches(b, ev, ctx)) continue;

        if (b->priority > best_pri) {
            best_pri = b->priority;
            best = b->action;
            *conflict_count = 0;
        } else if (b->priority == best_pri) {
            (*conflict_count)++;
        }
    }

    g.last_resolved_action = best;
    g.event_conflict_count = *conflict_count;
    return best;
}

static void event_dispatch(EventType type, int code, int mx, int my, int wheel, const char *note) {
    EventContext ctx;
    EventRecord *ev;
    ActionId action;
    int conflicts = 0;

    ev = event_register(type, code, mx, my, wheel, note);
    ctx = collect_context();

    action = resolve_event(ev, &ctx, &conflicts);

    if (g.controls_capture && type == EVT_KEY_DOWN) {
        /* In capture mode the raw key is data, not command. */
        controls_capture_key((WPARAM)code);
        return;
    }

    if (action == ACT_NONE) {
        trace_add("event", g.probe_id, ev ? ev->target_entity : 0, "event registered but no action resolved");
        return;
    }

    if (conflicts > 0) {
        trace_add("event_conflict", g.probe_id, ev ? ev->target_entity : 0, "multiple bindings matched same priority; first action used");
    }

    controls_execute(action, (WPARAM)code);
}


/* ---------- central window/action registry ---------- */

static const char *window_name(WindowId id) {
    switch (id) {
        case WIN_INSPECTOR: return "INSPECTOR";
        case WIN_TRACE: return "TRACE";
        case WIN_CONTROLS: return "CONTROLS";
        case WIN_EVENTS: return "EVENTS";
        case WIN_WINDOW_REGISTRY: return "WINDOW_REGISTRY";
        case WIN_WIRING: return "WIRING";
        case WIN_SELF_STUDIO: return "SELF_STUDIO";
        case WIN_FIELD: return "FIELD";
        default: return "NONE";
    }
}

static const WindowDecorator WINDOW_DECORATORS[WINDOW_DECORATOR_COUNT] = {
    { "oxide", RGB(9,16,24), RGB(18,7,9), RGB(120,45,45), RGB(255,78,58), RGB(255,220,190) },
    { "amber", RGB(12,11,5), RGB(28,18,4), RGB(176,122,42), RGB(255,190,80), RGB(255,232,176) },
    { "cyan", RGB(5,12,16), RGB(4,20,26), RGB(42,130,160), RGB(80,220,255), RGB(205,245,255) },
    { "bone", RGB(18,16,13), RGB(30,26,20), RGB(150,136,112), RGB(255,238,204), RGB(244,232,210) },
    { "void", RGB(6,5,10), RGB(12,8,22), RGB(82,62,122), RGB(174,122,255), RGB(226,214,255) }
};

static const WindowDecorator *window_decorator(WindowRecord *w) {
    if (!w) return &WINDOW_DECORATORS[0];
    if (w->decorator < 0 || w->decorator >= WINDOW_DECORATOR_COUNT) w->decorator = 0;
    return &WINDOW_DECORATORS[w->decorator];
}

static WindowRecord *window_by_id(WindowId id) {
    int i;
    for (i = 0; i < MAX_WINDOW_RECORDS; ++i)
        if (g.windows[i].alive && g.windows[i].id == id) return &g.windows[i];
    return 0;
}

static int rect_empty(RECT r) {
    return r.left == 0 && r.top == 0 && r.right == 0 && r.bottom == 0;
}

static RECT window_default_rect(WindowId id, RECT cr) {
    RECT r;
    switch (id) {
        case WIN_INSPECTOR:
            r.left = cr.right - 330; r.top = 54; r.right = cr.right - 14; r.bottom = cr.top + 350;
            if (r.bottom > cr.bottom - 128) r.bottom = cr.bottom - 128;
            break;
        case WIN_TRACE:
            r.left = 14; r.top = cr.bottom - 112; r.right = cr.right - 14; r.bottom = cr.bottom - 14;
            break;
        case WIN_CONTROLS:
            r.left = 44; r.top = 82; r.right = cr.right - 44; r.bottom = cr.bottom - 84;
            break;
        case WIN_EVENTS:
            r.left = 56; r.top = 96; r.right = cr.right - 56; r.bottom = cr.bottom - 96;
            break;
        case WIN_WINDOW_REGISTRY:
            r.left = 66; r.top = 110; r.right = cr.right - 66; r.bottom = cr.bottom - 110;
            break;
        case WIN_WIRING:
            r.left = 76; r.top = 124; r.right = cr.right - 76; r.bottom = cr.bottom - 124;
            break;
        case WIN_SELF_STUDIO:
            r.left = 36; r.top = 76; r.right = cr.right - 36; r.bottom = cr.bottom - 52;
            break;
        default:
            r.left = 0; r.top = 0; r.right = cr.right; r.bottom = cr.bottom;
            break;
    }
    if (r.right - r.left < 220) r.right = r.left + 220;
    if (r.bottom - r.top < 96) r.bottom = r.top + 96;
    return r;
}

static void window_clamp_rect(WindowRecord *w, RECT cr) {
    int width, height, max_w, max_h;
    if (!w) return;
    width = w->rc.right - w->rc.left;
    height = w->rc.bottom - w->rc.top;
    max_w = cr.right - cr.left - 16;
    max_h = cr.bottom - cr.top - 36;
    if (width < 180) width = 180;
    if (height < 64) height = 64;
    if (width > max_w) width = max_w;
    if (height > max_h) height = max_h;
    if (w->rc.left < cr.left + 8) w->rc.left = cr.left + 8;
    if (w->rc.top < cr.top + 28) w->rc.top = cr.top + 28;
    if (w->rc.left + width > cr.right - 8) w->rc.left = cr.right - width - 8;
    if (w->rc.top + height > cr.bottom - 8) w->rc.top = cr.bottom - height - 8;
    if (w->rc.left < cr.left + 8) w->rc.left = cr.left + 8;
    if (w->rc.top < cr.top + 28) w->rc.top = cr.top + 28;
    w->rc.right = w->rc.left + width;
    w->rc.bottom = w->rc.top + height;
}

static RECT window_resolve_rect(WindowId id, RECT client) {
    WindowRecord *w = window_by_id(id);
    RECT r = window_default_rect(id, client);
    if (!w) return r;
    if (rect_empty(w->rc)) w->rc = r;
    window_clamp_rect(w, client);
    return w->rc;
}

static RECT window_title_rect(WindowRecord *w) {
    RECT r = w->rc;
    r.bottom = r.top + 24;
    return r;
}

static RECT window_close_rect(WindowRecord *w) {
    RECT r = w->rc;
    r.left = r.right - 26;
    r.bottom = r.top + 24;
    return r;
}

static RECT window_resize_rect(WindowRecord *w) {
    RECT r = w->rc;
    r.left = r.right - 18;
    r.top = r.bottom - 18;
    return r;
}

static void window_render_chrome(HDC dc, WindowRecord *w) {
    RECT title, close_r, resize_r;
    const WindowDecorator *deco;
    int active, pulse, stripe;
    char buf[128];
    if (!w || !w->open || w->id == WIN_FIELD) return;
    deco = window_decorator(w);
    active = (g.window_active_id == w->id || g.window_registry_selected == w->id || g.window_drag_id == w->id || g.window_resize_id == w->id);
    pulse = active ? (int)(40.0 + 35.0 * (0.5 + 0.5 * sin(g.time * 8.0))) : 0;
    title = window_title_rect(w);
    close_r = window_close_rect(w);
    resize_r = window_resize_rect(w);
    fill_rect_c(dc, title, deco->title);
    line_c(dc, w->rc.left + 1, w->rc.bottom + 4, w->rc.right + 4, w->rc.bottom + 4, RGB(2, 2, 2), 2);
    line_c(dc, w->rc.right + 4, w->rc.top + 4, w->rc.right + 4, w->rc.bottom + 4, RGB(2, 2, 2), 2);
    rect_outline(dc, w->rc, active ? RGB(180 + pulse, 80 + pulse / 2, 55 + pulse / 3) : deco->edge, active ? 2 : 1);
    line_c(dc, w->rc.left + 2, title.bottom, w->rc.right - 2, title.bottom, deco->accent, 1);
    for (stripe = title.left + 8 + ((int)(g.time * 28.0) % 28); stripe < title.right - 36; stripe += 28)
        line_c(dc, stripe, title.top + 3, stripe + 12, title.top + 3, deco->accent, 1);
    SetTextColor(dc, deco->text);
    sprintf(buf, "%s  z=%d  %s", window_name(w->id), w->z_order, deco->name);
    draw_text(dc, title.left + 8, title.top + 6, buf);
    if ((w->caps & WIN_CAP_CLOSABLE) && w->toggle_action != ACT_NONE) {
        fill_rect_c(dc, close_r, RGB(48, 10, 12));
        rect_outline(dc, close_r, RGB(210, 80, 80), 1);
        SetTextColor(dc, RGB(255, 210, 210));
        draw_text(dc, close_r.left + 8, close_r.top + 5, "X");
    } else {
        SetTextColor(dc, RGB(140, 130, 130));
        draw_text(dc, close_r.left + 4, close_r.top + 5, "MOVE");
    }
    if (w->caps & WIN_CAP_RESIZABLE) {
        MoveToEx(dc, resize_r.left + 5, resize_r.bottom - 4, 0);
        LineTo(dc, resize_r.right - 4, resize_r.top + 5);
        MoveToEx(dc, resize_r.left + 10, resize_r.bottom - 4, 0);
        LineTo(dc, resize_r.right - 4, resize_r.top + 10);
    }
}

static WindowRecord *window_hit_chrome(int x, int y, int *hit_kind) {
    int i, best_z = -2147483647;
    WindowRecord *best = 0;
    *hit_kind = 0;
    for (i = 0; i < MAX_WINDOW_RECORDS; ++i) {
        WindowRecord *w = &g.windows[i];
        if (!w->alive || !w->open || w->id == WIN_FIELD) continue;
        if ((w->caps & WIN_CAP_RESIZABLE) && rect_contains(window_resize_rect(w), x, y)) {
            if (w->z_order >= best_z) { best_z = w->z_order; best = w; *hit_kind = 3; }
        } else if ((w->caps & WIN_CAP_CLOSABLE) && rect_contains(window_close_rect(w), x, y) && w->toggle_action != ACT_NONE) {
            if (w->z_order >= best_z) { best_z = w->z_order; best = w; *hit_kind = 1; }
        } else if ((w->caps & WIN_CAP_MOVABLE) && rect_contains(window_title_rect(w), x, y)) {
            if (w->z_order >= best_z) { best_z = w->z_order; best = w; *hit_kind = 2; }
        }
    }
    return best;
}

static WindowRecord *window_hit_body(int x, int y) {
    int i, best_z = -2147483647;
    WindowRecord *best = 0;
    for (i = 0; i < MAX_WINDOW_RECORDS; ++i) {
        WindowRecord *w = &g.windows[i];
        if (!w->alive || !w->open || w->id == WIN_FIELD || !(w->caps & WIN_CAP_BLOCKS_FIELD)) continue;
        if (rect_contains(w->rc, x, y) && w->z_order >= best_z) {
            best_z = w->z_order;
            best = w;
        }
    }
    return best;
}

static WindowRecord *window_selected_or_active(void) {
    WindowRecord *w = window_by_id((WindowId)g.window_registry_selected);
    int i, best_z = -2147483647;
    if (w && w->alive && w->id != WIN_FIELD) return w;
    w = window_by_id(g.window_active_id);
    if (w && w->alive && w->id != WIN_FIELD) return w;
    w = 0;
    for (i = 0; i < MAX_WINDOW_RECORDS; ++i) {
        WindowRecord *cand = &g.windows[i];
        if (!cand->alive || cand->id == WIN_FIELD) continue;
        if (cand->z_order >= best_z) {
            best_z = cand->z_order;
            w = cand;
        }
    }
    return w;
}

static void window_select(WindowId id, int raise) {
    WindowRecord *w = window_by_id(id);
    if (!w || w->id == WIN_FIELD) return;
    g.window_registry_selected = (int)id;
    g.window_active_id = id;
    w->last_touched = g.time;
    if (raise) w->z_order = ++g.next_window_z;
}

static void window_select_delta(int delta) {
    int count = 0, selected_index = -1, i, target;
    for (i = 0; i < MAX_WINDOW_RECORDS; ++i) {
        WindowRecord *w = &g.windows[i];
        if (!w->alive || w->id == WIN_FIELD) continue;
        if (w->id == (WindowId)g.window_registry_selected) selected_index = count;
        count++;
    }
    if (count <= 0) return;
    if (selected_index < 0) selected_index = 0;
    target = selected_index + delta;
    while (target < 0) target += count;
    target %= count;
    count = 0;
    for (i = 0; i < MAX_WINDOW_RECORDS; ++i) {
        WindowRecord *w = &g.windows[i];
        if (!w->alive || w->id == WIN_FIELD) continue;
        if (count == target) {
            window_select(w->id, 1);
            trace_add("window", g.probe_id, 0, "selected window changed");
            return;
        }
        count++;
    }
}

static void window_layout_cascade(void) {
    RECT client;
    HWND hwnd = GetActiveWindow();
    int i, n = 0;
    if (!hwnd) return;
    GetClientRect(hwnd, &client);
    for (i = 0; i < MAX_WINDOW_RECORDS; ++i) {
        WindowRecord *w = &g.windows[i];
        if (!w->alive || w->id == WIN_FIELD) continue;
        w->rc.left = 28 + n * 28;
        w->rc.top = 54 + n * 24;
        w->rc.right = w->rc.left + 360 + (n % 3) * 70;
        w->rc.bottom = w->rc.top + 190 + (n % 2) * 60;
        w->user_placed = 1;
        w->z_order = ++g.next_window_z;
        w->last_touched = g.time;
        window_clamp_rect(w, client);
        n++;
    }
    trace_add("window", g.probe_id, 0, "window layout cascaded");
}

static void window_edit_selected(ActionId action) {
    RECT client;
    HWND hwnd = GetActiveWindow();
    WindowRecord *w = window_selected_or_active();
    int step = (GetKeyState(VK_SHIFT) & 0x8000) ? 36 : 12;
    if (!w || w->id == WIN_FIELD) return;
    if (!hwnd) return;
    GetClientRect(hwnd, &client);

    if (action == ACT_WINDOW_SELECT_NEXT) { window_select_delta(1); return; }
    if (action == ACT_WINDOW_SELECT_PREV) { window_select_delta(-1); return; }
    if (action == ACT_WINDOW_LAYOUT_CASCADE) { window_layout_cascade(); return; }

    window_select(w->id, 1);
    if (action == ACT_WINDOW_TOGGLE_SELECTED && w->toggle_action != ACT_NONE) {
        window_set_open(w->id, !w->open);
    } else if ((w->caps & WIN_CAP_MOVABLE) && action == ACT_WINDOW_MOVE_LEFT) {
        OffsetRect(&w->rc, -step, 0);
    } else if ((w->caps & WIN_CAP_MOVABLE) && action == ACT_WINDOW_MOVE_RIGHT) {
        OffsetRect(&w->rc, step, 0);
    } else if ((w->caps & WIN_CAP_MOVABLE) && action == ACT_WINDOW_MOVE_UP) {
        OffsetRect(&w->rc, 0, -step);
    } else if ((w->caps & WIN_CAP_MOVABLE) && action == ACT_WINDOW_MOVE_DOWN) {
        OffsetRect(&w->rc, 0, step);
    } else if ((w->caps & WIN_CAP_RESIZABLE) && action == ACT_WINDOW_GROW) {
        w->rc.right += step;
        w->rc.bottom += step;
    } else if ((w->caps & WIN_CAP_RESIZABLE) && action == ACT_WINDOW_SHRINK) {
        w->rc.right -= step;
        w->rc.bottom -= step;
    } else if (action == ACT_WINDOW_DECORATOR_NEXT) {
        w->decorator = (w->decorator + 1) % WINDOW_DECORATOR_COUNT;
    }
    w->user_placed = 1;
    w->last_touched = g.time;
    window_clamp_rect(w, client);
}

static int window_registry_handle_click(WindowRecord *registry, int x, int y) {
    int i, row_y;
    (void)x;
    if (!registry) return 0;
    row_y = registry->rc.top + 76;
    for (i = 0; i < MAX_WINDOW_RECORDS && row_y < registry->rc.bottom - 160; ++i) {
        WindowRecord *w = &g.windows[i];
        if (!w->alive) continue;
        if (y >= row_y - 2 && y <= row_y + 14) {
            window_select(w->id, 1);
            if (w->toggle_action != ACT_NONE) window_set_open(w->id, !w->open);
            trace_add("window", g.probe_id, 0, "window registry row activated");
            return 1;
        }
        row_y += 16;
    }
    return 1;
}

static int window_begin_content_interaction(int x, int y) {
    WindowRecord *w = window_hit_body(x, y);
    if (!w) return 0;
    window_select(w->id, 1);
    if (w->id == WIN_WINDOW_REGISTRY) return window_registry_handle_click(w, x, y);
    return 1;
}

static int window_point_blocks_field(int x, int y) {
    return window_hit_body(x, y) != 0;
}

static int window_begin_chrome_interaction(int x, int y) {
    int hit_kind = 0;
    WindowRecord *w = window_hit_chrome(x, y, &hit_kind);
    if (!w) return 0;
    window_select(w->id, 1);
    if (hit_kind == 1) {
        window_set_open(w->id, 0);
        trace_add("window", g.probe_id, 0, "window closed from titlebar");
        return 1;
    }
    if (hit_kind == 3) {
        g.window_resize_id = w->id;
        g.window_resize_dx = w->rc.right - x;
        g.window_resize_dy = w->rc.bottom - y;
        w->user_placed = 1;
        trace_add("window", g.probe_id, 0, "window resize started");
        return 1;
    }
    g.window_drag_id = w->id;
    g.window_drag_dx = x - w->rc.left;
    g.window_drag_dy = y - w->rc.top;
    w->user_placed = 1;
    trace_add("window", g.probe_id, 0, "window drag started");
    return 1;
}

static int window_drag_active(void) {
    return g.window_drag_id != WIN_NONE || g.window_resize_id != WIN_NONE;
}

static void window_drag_move(int x, int y, RECT client) {
    WindowRecord *w;
    int width, height;
    if (g.window_resize_id != WIN_NONE) {
        w = window_by_id(g.window_resize_id);
        if (!w) return;
        w->rc.right = x + g.window_resize_dx;
        w->rc.bottom = y + g.window_resize_dy;
        w->user_placed = 1;
        w->last_touched = g.time;
        window_clamp_rect(w, client);
        return;
    }
    if (g.window_drag_id == WIN_NONE) return;
    w = window_by_id(g.window_drag_id);
    if (!w) return;
    width = w->rc.right - w->rc.left;
    height = w->rc.bottom - w->rc.top;
    w->rc.left = x - g.window_drag_dx;
    w->rc.top = y - g.window_drag_dy;
    w->rc.right = w->rc.left + width;
    w->rc.bottom = w->rc.top + height;
    w->user_placed = 1;
    w->last_touched = g.time;
    window_clamp_rect(w, client);
}

static void window_drag_end(void) {
    if (g.window_drag_id != WIN_NONE || g.window_resize_id != WIN_NONE) trace_add("window", g.probe_id, 0, "window edit ended");
    g.window_drag_id = WIN_NONE;
    g.window_resize_id = WIN_NONE;
}
static void window_add(WindowId id, const char *name, const char *role, ActionId toggle_action, int open, int modal) {
    int i;
    for (i = 0; i < MAX_WINDOW_RECORDS; ++i) {
        if (!g.windows[i].alive) {
            WindowRecord *w = &g.windows[i];
            memset(w, 0, sizeof(*w));
            w->alive = 1;
            w->id = id;
            w->open = open;
            w->modal = modal;
            w->z_order = ++g.next_window_z;
            w->toggle_action = toggle_action;
            w->caps = WIN_CAP_BLOCKS_FIELD | WIN_CAP_DECORATED;
            if (id != WIN_FIELD) w->caps |= WIN_CAP_MOVABLE | WIN_CAP_RESIZABLE;
            if (toggle_action != ACT_NONE) w->caps |= WIN_CAP_CLOSABLE;
            if (id == WIN_FIELD) w->caps = 0;
            w->decorator = ((int)id - 1) % WINDOW_DECORATOR_COUNT;
            if (w->decorator < 0) w->decorator = 0;
            w->last_touched = g.time;
            copy_s(w->name, sizeof(w->name), name);
            copy_s(w->role, sizeof(w->role), role);
            return;
        }
    }
}

static void window_action_bind(WindowId id, ActionId action, const char *relation, const char *note) {
    int i;
    for (i = 0; i < MAX_WINDOW_ACTION_BINDINGS; ++i) {
        if (!g.win_actions[i].alive) {
            WindowActionBinding *b = &g.win_actions[i];
            memset(b, 0, sizeof(*b));
            b->alive = 1;
            b->window_id = id;
            b->action = action;
            copy_s(b->relation, sizeof(b->relation), relation);
            copy_s(b->note, sizeof(b->note), note);
            return;
        }
    }
}

static void window_registry_init(void) {
    memset(g.windows, 0, sizeof(g.windows));
    memset(g.win_actions, 0, sizeof(g.win_actions));
    g.window_registry_selected = 0;
    g.next_window_z = 0;
    g.window_active_id = WIN_NONE;
    g.window_drag_id = WIN_NONE;
    g.window_resize_id = WIN_NONE;

    window_add(WIN_FIELD, "field_view", "main world/space projection", ACT_NONE, 1, 0);
    window_add(WIN_INSPECTOR, "inspector", "selected/hovered object state", ACT_INSPECTOR_TOGGLE, g.inspector_on, 0);
    window_add(WIN_TRACE, "trace", "provenance/action log", ACT_NONE, 1, 0);
    window_add(WIN_CONTROLS, "controls", "controls/remap settings", ACT_CONTROLS_TOGGLE, g.controls_panel_on, 1);
    window_add(WIN_EVENTS, "events", "event registry/context resolver", ACT_EVENT_PANEL_TOGGLE, g.event_panel_on, 1);
    window_add(WIN_WINDOW_REGISTRY, "window_registry", "central window/action registry", ACT_WINDOW_REGISTRY_TOGGLE, g.window_registry_panel_on, 1);
    window_add(WIN_WIRING, "wiring", "visual wiring of event/context/action/window flow", ACT_WIRING_PANEL_TOGGLE, g.wiring_panel_on, 1);
    window_add(WIN_SELF_STUDIO, "self_studio", "application config as editable node demo", ACT_SELF_STUDIO_TOGGLE, g.self_studio_on, 1);

    window_action_bind(WIN_INSPECTOR, ACT_INSPECTOR_TOGGLE, "toggles", "open/close inspector window");
    window_action_bind(WIN_CONTROLS, ACT_CONTROLS_TOGGLE, "toggles", "open/close controls window");
    window_action_bind(WIN_EVENTS, ACT_EVENT_PANEL_TOGGLE, "toggles", "open/close event resolver window");
    window_action_bind(WIN_WINDOW_REGISTRY, ACT_WINDOW_REGISTRY_TOGGLE, "toggles", "open/close window registry window");
    window_action_bind(WIN_WIRING, ACT_WIRING_PANEL_TOGGLE, "toggles", "open/close wiring visualization window");
    window_action_bind(WIN_WIRING, ACT_WIRING_STRIP_TOGGLE, "controls", "toggle always-on wiring strip");
    window_action_bind(WIN_SELF_STUDIO, ACT_SELF_STUDIO_TOGGLE, "toggles", "open/close self-studio node builder");
    window_action_bind(WIN_SELF_STUDIO, ACT_NODE_SELECT_NEXT, "contains_action", "select next node");
    window_action_bind(WIN_SELF_STUDIO, ACT_NODE_SELECT_PREV, "contains_action", "select previous node");
    window_action_bind(WIN_SELF_STUDIO, ACT_NODE_DUPLICATE_SELECTED, "contains_action", "duplicate selected node");
    window_action_bind(WIN_TRACE, ACT_NONE, "always_visible", "trace is currently always rendered");
    window_action_bind(WIN_FIELD, ACT_NONE, "root_projection", "field is the root projection window");

    window_action_bind(WIN_CONTROLS, ACT_REMAP_SELECTED, "contains_action", "controls window owns remap action");
    window_action_bind(WIN_CONTROLS, ACT_REMAP_NEXT, "contains_action", "controls window owns next-binding action");
    window_action_bind(WIN_CONTROLS, ACT_REMAP_PREV, "contains_action", "controls window owns previous-binding action");
    window_action_bind(WIN_WINDOW_REGISTRY, ACT_WINDOW_SELECT_NEXT, "contains_action", "select next editable window");
    window_action_bind(WIN_WINDOW_REGISTRY, ACT_WINDOW_TOGGLE_SELECTED, "contains_action", "open or close selected window");
    window_action_bind(WIN_WINDOW_REGISTRY, ACT_WINDOW_MOVE_LEFT, "contains_action", "move selected window");
    window_action_bind(WIN_WINDOW_REGISTRY, ACT_WINDOW_GROW, "contains_action", "resize selected window");
    window_action_bind(WIN_WINDOW_REGISTRY, ACT_WINDOW_DECORATOR_NEXT, "contains_action", "cycle selected window decorator");
    window_action_bind(WIN_WINDOW_REGISTRY, ACT_WINDOW_LAYOUT_CASCADE, "contains_action", "organize all windows");
}

static void window_sync_runtime(void) {
    WindowRecord *w;
    w = window_by_id(WIN_INSPECTOR); if (w) w->open = g.inspector_on;
    w = window_by_id(WIN_CONTROLS); if (w) w->open = g.controls_panel_on;
    w = window_by_id(WIN_EVENTS); if (w) w->open = g.event_panel_on;
    w = window_by_id(WIN_WINDOW_REGISTRY); if (w) w->open = g.window_registry_panel_on;
    w = window_by_id(WIN_WIRING); if (w) w->open = g.wiring_panel_on;
    w = window_by_id(WIN_SELF_STUDIO); if (w) w->open = g.self_studio_on;
    w = window_by_id(WIN_TRACE); if (w) w->open = 1;
    w = window_by_id(WIN_FIELD); if (w) w->open = 1;
}

static void window_set_open(WindowId id, int open) {
    WindowRecord *w = window_by_id(id);
    if (!w) return;
    w->open = open ? 1 : 0;
    w->z_order = ++g.next_window_z;

    if (id == WIN_INSPECTOR) g.inspector_on = w->open;
    else if (id == WIN_CONTROLS) g.controls_panel_on = w->open;
    else if (id == WIN_EVENTS) g.event_panel_on = w->open;
    else if (id == WIN_WINDOW_REGISTRY) g.window_registry_panel_on = w->open;
    else if (id == WIN_WIRING) g.wiring_panel_on = w->open;
    else if (id == WIN_SELF_STUDIO) g.self_studio_on = w->open;
}

static void window_toggle(WindowId id) {
    WindowRecord *w = window_by_id(id);
    char msg[128];
    if (!w) return;
    window_set_open(id, !w->open);
    sprintf(msg, "window %s %s", w->name, w->open ? "open" : "closed");
    trace_add("window", g.probe_id, 0, msg);
}

/* ---------- reset/input ---------- */

static void reset_world(void) {
    Entity *probe;
    memset(g.ent, 0, sizeof(g.ent));
    memset(g.trace, 0, sizeof(g.trace));

    g.next_ent_id = 1;
    g.next_trace_id = 1;
    g.selected_id = 0;
    g.hovered_id = 0;
    g.blackhole_id = 0;
    g.probe_id = 0;

    desktop_preset_init();
    g.desktop_preset_applied = 0;

    g.mat = MAT_DUST;
    g.tool = TOOL_EMIT;
    g.paused = 0;
    g.step_once = 0;
    g.gravity_on = 1;
    g.cohesion_on = 1;
    g.absorb_on = 1;
    g.trails_on = 1;
    g.inspector_on = 1;
    g.labels_on = 1;
    g.auto_forge = 0;
    g.feeder_on = 0;
    g.feeder_rate = FEEDER_DEFAULT_RATE;
    g.feeder_speed = FEEDER_DEFAULT_SPEED;
    g.feeder_spread = FEEDER_DEFAULT_SPREAD;
    g.feeder_accum = 0.0;
    g.feeder_emit_total = 0;
    g.show_force_field = 1;
    g.forge_element_index = 0;
    g.atom_view_on = 1;
    g.atom_component_count = 0;
    g.saved_asset_count = 0;
    init_element_presets();
    controls_init();
    memset(g.events, 0, sizeof(g.events));
    g.next_event_id = 1;
    g.event_resolver_on = 1;
    g.event_panel_on = 0;
    g.last_event_id = 0;
    g.last_resolved_action = ACT_NONE;
    g.last_context_mask = 0;
    g.event_conflict_count = 0;
    g.window_registry_panel_on = 0;
    g.wiring_panel_on = 0;
    g.wiring_strip_on = 0;
    g.self_studio_on = 0;
    g.window_active_id = WIN_NONE;
    g.window_drag_id = WIN_NONE;
    g.window_resize_id = WIN_NONE;
    context_bindings_init();
    window_registry_init();
    self_studio_init();

    g.brush_radius = 2;
    g.cam_x = 0.0;
    g.cam_y = 0.0;
    g.zoom = 1.0;
    g.target_cam_x = 0.0;
    g.target_cam_y = 0.0;
    g.target_zoom = 1.0;
    g.camera_smooth = 1;
    g.show_vectors = 1;
    g.multiscale_mode = 1;
    g.time = 0;
    g.accumulator = 0;
    g.absorbed_count = 0;
    g.forged_count = 0;
    g.auto_forge_timer = 0.0;
    g.last_clock = clock_s();

    probe = entity_new(ENT_PROBE, MAT_NONE, MODE_OBS, "MOUSE_PROBE", "editable input probe", 0, 0, 1.0, 1.0);
    if (probe) {
        g.probe_id = probe->id;
        copy_s(probe->origin, sizeof(probe->origin), "input.mouse");
        copy_s(probe->definition, sizeof(probe->definition), "mouse/probe is registered editable object");
        copy_s(probe->storage, sizeof(probe->storage), "entity-reg[probe]");
        select_entity(probe->id);
    }

    spawn_blackhole(0, 0);
    apply_desktop_blackhole_preset();
    trace_add("reset", 0, 0, "unbounded sparse field reset with micro-merged desktop BH preset");
}

static void handle_key(WPARAM wp) {
    event_dispatch(EVT_KEY_DOWN, (int)wp, g.mouse_x, g.mouse_y, 0, "key down");
}

static void handle_mouse_move(HWND hwnd, int x, int y) {
    Entity *probe = entity_by_id(g.probe_id);
    RECT client;
    double wx, wy;
    g.mouse_x = x;
    g.mouse_y = y;
    screen_to_world(x, y, &wx, &wy);

    if (probe) {
        probe->pos.x = wx;
        probe->pos.y = wy;
    }

    if (window_drag_active()) {
        GetClientRect(hwnd, &client);
        window_drag_move(x, y, client);
        return;
    }

    if (g.node_dragging) {
        self_studio_drag_move(x, y);
        return;
    }

    if (window_point_blocks_field(x, y)) {
        g.hovered_id = 0;
        return;
    }

    update_hover(x, y);

    if (g.mouse_l && rect_contains(g.field_rc, x, y))
        brush_spawn_at(x, y);

    if (g.mouse_r && rect_contains(g.field_rc, x, y))
        spawn_blackhole(wx, wy);
}

/* ---------- window ---------- */

static LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            SetTimer(hwnd, 1, 16, 0);
            return 0;

        case WM_TIMER:
            tick();
            InvalidateRect(hwnd, 0, FALSE);
            return 0;

        case WM_MOUSEMOVE:
            event_register(EVT_MOUSE_MOVE, 0, LOWORD(lp), HIWORD(lp), 0, "mouse move");
            handle_mouse_move(hwnd, LOWORD(lp), HIWORD(lp));
            return 0;

        case WM_LBUTTONDOWN:
            event_register(EVT_MOUSE_DOWN, 1, LOWORD(lp), HIWORD(lp), 0, "left mouse down");
            SetCapture(hwnd);
            if (window_begin_chrome_interaction(LOWORD(lp), HIWORD(lp)))
                return 0;
            if (g.self_studio_on && rect_contains(g.self_studio_rc, LOWORD(lp), HIWORD(lp))) {
                self_studio_begin_interaction(LOWORD(lp), HIWORD(lp));
                return 0;
            }
            if (window_begin_content_interaction(LOWORD(lp), HIWORD(lp)))
                return 0;
            g.mouse_l = 1;
            if (rect_contains(g.field_rc, LOWORD(lp), HIWORD(lp)))
                brush_spawn_at(LOWORD(lp), HIWORD(lp));
            return 0;

        case WM_LBUTTONUP:
            event_register(EVT_MOUSE_UP, 1, LOWORD(lp), HIWORD(lp), 0, "left mouse up");
            g.mouse_l = 0;
            window_drag_end();
            self_studio_end_interaction();
            ReleaseCapture();
            return 0;

        case WM_RBUTTONDOWN: {
            double wx, wy;
            event_register(EVT_MOUSE_DOWN, 2, LOWORD(lp), HIWORD(lp), 0, "right mouse down");
            if (window_point_blocks_field(LOWORD(lp), HIWORD(lp)))
                return 0;
            SetCapture(hwnd);
            g.mouse_r = 1;
            screen_to_world(LOWORD(lp), HIWORD(lp), &wx, &wy);
            spawn_blackhole(wx, wy);
            return 0;
        }

        case WM_RBUTTONUP:
            event_register(EVT_MOUSE_UP, 2, LOWORD(lp), HIWORD(lp), 0, "right mouse up");
            g.mouse_r = 0;
            ReleaseCapture();
            return 0;

        case WM_MBUTTONDOWN: {
            int id;
            event_register(EVT_MOUSE_DOWN, 3, LOWORD(lp), HIWORD(lp), 0, "middle mouse down");
            id = nearest_entity_screen(LOWORD(lp), HIWORD(lp), 26.0);
            if (id) select_entity(id);
            return 0;
        }

        case WM_MOUSEWHEEL: {
            int delta = GET_WHEEL_DELTA_WPARAM(wp);
            event_register(EVT_MOUSE_WHEEL, 0, g.mouse_x, g.mouse_y, delta, "mouse wheel");
            if (window_point_blocks_field(g.mouse_x, g.mouse_y))
                return 0;
            if (GetKeyState(VK_CONTROL) & 0x8000) {
                if (delta > 0) camera_zoom_at_mouse(CAMERA_ZOOM_STEP);
                else camera_zoom_at_mouse(1.0 / CAMERA_ZOOM_STEP);
            } else if (GetKeyState(VK_SHIFT) & 0x8000) {
                if (delta > 0) camera_zoom_at_mouse(CAMERA_ZOOM_FAST_STEP);
                else camera_zoom_at_mouse(1.0 / CAMERA_ZOOM_FAST_STEP);
            } else {
                if (delta > 0) g.brush_radius++;
                else g.brush_radius--;
                if (g.brush_radius < 1) g.brush_radius = 1;
                if (g.brush_radius > 18) g.brush_radius = 18;
            }
            return 0;
        }

        case WM_KEYDOWN:
            handle_key(wp);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC dc = BeginPaint(hwnd, &ps);
            render_frame(hwnd, dc);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_DESTROY:
            if (g.memdc) {
                SelectObject(g.memdc, g.oldbmp);
                DeleteObject(g.membmp);
                DeleteDC(g.memdc);
            }
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
    WNDCLASSA wc;
    HWND hwnd;
    MSG msg;

    (void)prev; (void)cmd;

    QueryPerformanceFrequency(&qpf);
    memset(&g, 0, sizeof(g));
    g.last_clock = clock_s();
    reset_world();

    memset(&wc, 0, sizeof(wc));
    wc.lpfnWndProc = wndproc;
    wc.hInstance = inst;
    wc.lpszClassName = "ZERO_0000_GRAPHFIELD";
    wc.hCursor = LoadCursorA(0, IDC_CROSS);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    if (!RegisterClassA(&wc)) return 1;

    hwnd = CreateWindowExA(
        0,
        "ZERO_0000_GRAPHFIELD",
        "ZERO 0000 - GraphField Visual Mirror",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, APP_W, APP_H,
        0, 0, inst, 0
    );

    if (!hwnd) return 1;

    ShowWindow(hwnd, show);
    UpdateWindow(hwnd);

    while (GetMessageA(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}
