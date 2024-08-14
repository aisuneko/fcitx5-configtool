/*
 * SPDX-FileCopyrightText: 2011~2011 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */
#ifndef _LAYOUT_DEADMAPDATA_H_
#define _LAYOUT_DEADMAPDATA_H_
#ifndef ENABLE_X11
#include <xkbcommon/xkbcommon-keysyms.h>
#endif
struct DeadMap {
    unsigned int dead;
    unsigned int nondead;
};
DeadMap deadMapData[] = {
#ifdef ENABLE_X11
    {XK_dead_grave, 0x0060},
    {XK_dead_acute, 0x00b4},
    {XK_dead_circumflex, 0x02c6},
    {XK_dead_tilde, 0x02dc},
    {XK_dead_macron, 0x00af},
    {XK_dead_breve, 0x02D8},
    {XK_dead_abovedot, 0x02D9},
    {XK_dead_diaeresis, 0x00A8},
    {XK_dead_abovering, 0x02DA},
    {XK_dead_doubleacute, 0x02DD},
    {XK_dead_caron, 0x02C7},
    {XK_dead_cedilla, 0x00B8},
    {XK_dead_ogonek, 0x02DB},
    {XK_dead_iota, 0x0269},
    {XK_dead_voiced_sound, 0x309B},
    {XK_dead_semivoiced_sound, 0x309A},
    {XK_dead_belowdot, 0x0323},
    {XK_dead_hook, 0x0309},
    {XK_dead_horn, 0x031b},
    {XK_dead_stroke, 0x0335},
    {XK_dead_abovecomma, 0x0312},
    {XK_dead_abovereversedcomma, 0x0314},
    {XK_dead_doublegrave, 0x030f},
    {XK_dead_belowring, 0x0325},
    {XK_dead_belowmacron, 0x0331},
    {XK_dead_belowcircumflex, 0x032D},
    {XK_dead_belowtilde, 0x0330},
    {XK_dead_belowbreve, 0x032e},
    {XK_dead_belowdiaeresis, 0x0324},
    {XK_dead_invertedbreve, 0x0311},
    {XK_dead_belowcomma, 0x0326},
    {XK_dead_currency, 0x00A4},

    /* dead vowels for universal syllable entry */
    {XK_dead_a, 0x0061},
    {XK_dead_A, 0x0041},
    {XK_dead_e, 0x0065},
    {XK_dead_E, 0x0045},
    {XK_dead_i, 0x0069},
    {XK_dead_I, 0x0049},
    {XK_dead_o, 0x006f},
    {XK_dead_O, 0x004f},
    {XK_dead_u, 0x0075},
    {XK_dead_U, 0x0055},
    {XK_dead_small_schwa, 0x0259},
    {XK_dead_capital_schwa, 0x018F},
#else
    // TODO: decide which hex value to use for libxkbcommon
    {XKB_KEY_dead_grave, 0x0060},
    {XKB_KEY_dead_acute, 0x00b4},
    {XKB_KEY_dead_circumflex, 0x02c6},
    {XKB_KEY_dead_tilde, 0x02dc},
    {XKB_KEY_dead_macron, 0x00af},
    {XKB_KEY_dead_breve, 0x02D8},
    {XKB_KEY_dead_abovedot, 0x02D9},
    {XKB_KEY_dead_diaeresis, 0x00A8},
    {XKB_KEY_dead_abovering, 0x02DA},
    {XKB_KEY_dead_doubleacute, 0x02DD},
    {XKB_KEY_dead_caron, 0x02C7},
    {XKB_KEY_dead_cedilla, 0x00B8},
    {XKB_KEY_dead_ogonek, 0x02DB},
    {XKB_KEY_dead_iota, 0x0269},
    {XKB_KEY_dead_voiced_sound, 0x309B},
    {XKB_KEY_dead_semivoiced_sound, 0x309A},
    {XKB_KEY_dead_belowdot, 0x0323},
    {XKB_KEY_dead_hook, 0x0309},
    {XKB_KEY_dead_horn, 0x031b},
    {XKB_KEY_dead_stroke, 0x0335},
    {XKB_KEY_dead_abovecomma, 0x0312},
    {XKB_KEY_dead_abovereversedcomma, 0x0314},
    {XKB_KEY_dead_doublegrave, 0x030f},
    {XKB_KEY_dead_belowring, 0x0325},
    {XKB_KEY_dead_belowmacron, 0x0331},
    {XKB_KEY_dead_belowcircumflex, 0x032D},
    {XKB_KEY_dead_belowtilde, 0x0330},
    {XKB_KEY_dead_belowbreve, 0x032e},
    {XKB_KEY_dead_belowdiaeresis, 0x0324},
    {XKB_KEY_dead_invertedbreve, 0x0311},
    {XKB_KEY_dead_belowcomma, 0x0326},
    {XKB_KEY_dead_currency, 0x00A4},

    /* dead vowels for universal syllable entry */
    {XKB_KEY_dead_a, 0x0061},
    {XKB_KEY_dead_A, 0x0041},
    {XKB_KEY_dead_e, 0x0065},
    {XKB_KEY_dead_E, 0x0045},
    {XKB_KEY_dead_i, 0x0069},
    {XKB_KEY_dead_I, 0x0049},
    {XKB_KEY_dead_o, 0x006f},
    {XKB_KEY_dead_O, 0x004f},
    {XKB_KEY_dead_u, 0x0075},
    {XKB_KEY_dead_U, 0x0055},
    {XKB_KEY_dead_small_schwa, 0x0259},
    {XKB_KEY_dead_capital_schwa, 0x018F},
#endif
};
#endif // _LAYOUT_DEADMAPDATA_H_
