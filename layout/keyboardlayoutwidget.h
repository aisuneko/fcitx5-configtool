/*
 * SPDX-FileCopyrightText: 2011~2011 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

/* this file is based on from libgnomekbd/libgnomekbd/gkbd-keyboard-drawing.c */

#ifndef KEYBOARDLAYOUTWIDGET_H
#define KEYBOARDLAYOUTWIDGET_H

#include <QAbstractNativeEventFilter>
#include <QMap>
#include <QWidget>
#include <QGuiApplication>

#ifndef ENABLE_X11
#include <xkbcommon/xkbcommon.h>
#endif

class QPainter;
struct Doodad;
struct _XkbDesc;
struct xkb_context;
struct _XkbShapeDoodad;
union _XkbDoodad;

#ifndef ENABLE_X11
struct _XkbGeometry;
struct _XkbIndicatorRec;
struct _XkbNamesRec;
struct _XkbDesc;
struct _clientState;
#endif

typedef enum {
    KEYBOARD_DRAWING_ITEM_TYPE_INVALID = 0,
    KEYBOARD_DRAWING_ITEM_TYPE_KEY,
    KEYBOARD_DRAWING_ITEM_TYPE_KEY_EXTRA,
    KEYBOARD_DRAWING_ITEM_TYPE_DOODAD
} KeyboardDrawingItemType;

typedef enum {
    KEYBOARD_DRAWING_POS_TOPLEFT,
    KEYBOARD_DRAWING_POS_TOPRIGHT,
    KEYBOARD_DRAWING_POS_BOTTOMLEFT,
    KEYBOARD_DRAWING_POS_BOTTOMRIGHT,
    KEYBOARD_DRAWING_POS_TOTAL,
    KEYBOARD_DRAWING_POS_FIRST = KEYBOARD_DRAWING_POS_TOPLEFT,
    KEYBOARD_DRAWING_POS_LAST = KEYBOARD_DRAWING_POS_BOTTOMRIGHT
} KeyboardDrawingGroupLevelPosition;

namespace fcitx {
namespace kcm {

struct DrawingItem {
    DrawingItem()
        : type(KEYBOARD_DRAWING_ITEM_TYPE_INVALID), originX(0), originY(0),
          angle(0), priority(0) {}

    virtual ~DrawingItem() {}
    KeyboardDrawingItemType type;
    int originX;
    int originY;
    int angle;
    unsigned int priority;
};

struct Doodad : public DrawingItem {
    Doodad() : doodad(0), on(0) {}
    union _XkbDoodad *doodad;
    int on;
};

#ifndef ENABLE_X11
#define XkbNumIndicators 32
typedef unsigned int Atom;
typedef struct _XkbGeometry{
    // Atom name;
    unsigned short width_mm;
    unsigned short height_mm;
    // char *label_font;
    // XkbColorPtr label_color;
    // XkbColorPtr base_color;
    // unsigned short sz_properties;
    // unsigned short sz_colors;
    // unsigned short sz_shapes;
    // unsigned short sz_sections;
    // unsigned short sz_doodads;
    // unsigned short sz_key_aliases;
    // unsigned short num_properties;
    unsigned short num_colors;
    unsigned short num_shapes;
    unsigned short num_sections;
    unsigned short num_doodads;
    // unsigned short num_key_aliases;
    // XkbPropertyPtr properties;
    XkbColorPtr colors;
    XkbShapePtr shapes;
    XkbSectionPtr sections;
    XkbDoodadPtr doodads;
    // XkbKeyAliasPtr key_aliases;
} *XkbGeometryPtr;

typedef struct _XkbIndicatorRec {
    unsigned long phys_indicators; // xkb_led_index_t?
} *XkbIndicatorPtr;

typedef struct _XkbNamesRec {
    // Atom keycodes;
    // Atom geometry;
    // Atom symbols;
    // Atom types;
    // Atom compat;
    // Atom vmods[XkbNumVirtualMods];
    Atom indicators[XkbNumIndicators];
    // Atom groups[XkbNumKbdGroups];
    // XkbKeyNamePtr keys;
    // XkbKeyAliasPtr key_aliases;
    // Atom *radio_groups;
    // Atom phys_symbols;

    // unsigned char num_keys;
    // unsigned char num_key_aliases;
    // unsigned short num_rg;
} *XkbNamesPtr;

struct _XkbDesc {
    // unsigned int defined;
    // unsigned short flags;
    // unsigned short device_spec;
    xkb_keycode_t min_key_code;
    xkb_keycode_t max_key_code;

    // XkbControlsPtr ctrls;
    // XkbServerMapPtr server;
    // XkbClientMapPtr map;
    XkbIndicatorPtr indicators;
    XkbNamesPtr names;
    // XkbCompatMapPtr compat;
    XkbGeometryPtr geom;
};
struct _clientState {
    struct xkb_state *XkbState = nullptr;
    struct xkb_context *XkbContext = nullptr;
    struct xkb_keymap *XkbKeymap = nullptr;
    // struct touch_event touch_event;
};
#endif

struct DrawingKey : public DrawingItem {
    DrawingKey() : xkbkey(0), pressed(false), keycode(0) {}
    struct _XkbKey *xkbkey;
    bool pressed;
    unsigned int keycode;
};

struct KeyboardDrawingGroupLevel {
    int group;
    int level;
};

class KeyboardLayoutWidget : public QWidget {
    Q_OBJECT
public:
    explicit KeyboardLayoutWidget(QWidget *parent = 0);
    virtual ~KeyboardLayoutWidget();
    void setGroup(int group);
    void setKeyboardLayout(const QString &layout, const QString &variant);
    void generatePixmap(bool force = false);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void init();
    void alloc();
    void release();
    void initInicatorDoodad(union _XkbDoodad *xkbdoodad, Doodad &doodad);
    unsigned int findKeycode(const char *keyName);
    void rotateRectangle(int origin_x, int origin_y, int x, int y, int angle,
                         int &rotated_x, int &rotated_y);
    bool parseXkbColorSpec(char *colorspec, QColor &color);
    void initColors();

    void focusOutEvent(QFocusEvent *event) override;

    void drawKey(QPainter *painter, DrawingKey *item);
    void drawDoodad(QPainter *painter, Doodad *doodad);
    void drawKeyLabel(QPainter *painter, unsigned int keycode, int angle,
                      int arg4, int originY, int x2, int y2, bool pressed);
    void drawKeyLabelHelper(QPainter *painter, const QString &text, int angle,
                            int glp, int end_glp, int x, int y, int width,
                            int height, int padding, bool is_pressed);

    void drawShapeDoodad(QPainter *painter, Doodad *doodad,
                         struct _XkbShapeDoodad *shapeDoodad);
    void drawTextDoodad(QPainter *painter, Doodad *doodad,
                        struct _XkbTextDoodad *textDoodad);
    void drawIndicatorDoodad(QPainter *painter, Doodad *doodad,
                             struct _XkbIndicatorDoodad *indicatorDoodad);

    int calcShapeOriginOffsetX(struct _XkbOutline *outline);
    void drawOutline(QPainter *painter, struct _XkbOutline *outline,
                     QColor color, int angle, int originX, int originY);
    void drawRectangle(QPainter *painter, QColor color, int angle, int xkb_x,
                       int xkb_y, int xkb_width, int xkb_height,
                       unsigned int radius);
    void drawPolygon(QPainter *painter, QColor color, int originX, int originY,
                     struct _XkbPoint *points, unsigned int num_points,
                     unsigned int radius);
    void rotateCoordinate(int originX, int originY, int x, int y, int angle,
                          int *rotated_x, int *rotated_y);
    int xkbToPixmapCoord(int n);
    double xkbToPixmapDouble(double d);
    void roundedPolygon(QPainter *painter, bool filled, double radius,
                        const std::vector<QPointF> &points);
    void drawCurveRectangle(QPainter *painter, bool filled, QColor color, int x,
                            int y, int width, int height, double radius);
    void roundedCorner(QPainterPath &path, QPointF b, QPointF c, double radius);
    void resizeEvent(QResizeEvent *event) override;
    void setKeyboard(struct _XkbComponentNames *xkbDesc);

private:
    void keyEvent(QKeyEvent *keyEvent);
    QString keySymToString(unsigned long keysym);

    QList<DrawingItem *> keyboardItems;
    std::vector<DrawingKey> keys;
    QList<Doodad *> physicalIndicators;
    struct _XkbDesc *xkb = nullptr;
    #ifndef ENABLE_X11
    struct _clientState *clientState;
    QPlatformNativeInterface *interface = nullptr;
    #endif
    unsigned int l3mod = 0;
    std::vector<QColor> colors;
    QPixmap image;
    double ratio = 1.0;
    KeyboardDrawingGroupLevel **groupLevels;
    bool trackModifiers = false;
    int mods;
    QMap<unsigned int, unsigned int> deadMap;
};

} // namespace kcm
} // namespace fcitx

#endif
