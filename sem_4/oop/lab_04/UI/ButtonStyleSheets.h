//
// Created by Dmitriy Dudurev on 11.05.2026.
//

#ifndef LAB_04_BUTTONSTYLESHEETS_H
#define LAB_04_BUTTONSTYLESHEETS_H

// Общий стиль окна
#define WINDOW_STYLE \
    "background-color: #f5f5f5;"

#define TITLE_LABEL_STYLE \
    "font-size: 16px; font-weight: bold; padding: 8px;"

#define GROUP_BOX_STYLE \
    "QGroupBox { font-weight: bold; border: 1px solid #bbb;" \
    "  border-radius: 6px; margin-top: 10px; padding: 8px;" \
    "  background-color: white; }" \
    "QGroupBox::title { subcontrol-origin: margin; left: 10px;" \
    "  padding: 0 6px; }"

// ============================================================================
// Кнопки этажа (вызов лифта)
// ============================================================================

#define INACTIVE_FLOOR_BUTTON \
    "QPushButton { min-width: 50px; min-height: 36px;" \
    "  border: 1px solid #aaa; border-radius: 4px;" \
    "  background-color: #fafafa; }" \
    "QPushButton:hover { background-color: #ececec; }"

#define ACTIVE_FLOOR_BUTTON \
    "QPushButton { min-width: 50px; min-height: 36px;" \
    "  border: 1px solid #5a4a82; border-radius: 4px;" \
    "  background-color: #4a3a6e; color: white; font-weight: bold; }"

// ============================================================================
// Кнопки внутри кабины
// ============================================================================
// current — кабина сейчас на этом этаже
// active  — кнопка нажата (есть задача)
// ============================================================================

#define INACTIVE_NOT_CURRENT_CABIN_BUTTON \
    "QPushButton { min-width: 44px; min-height: 30px;" \
    "  border: 1px solid #aaa; border-radius: 4px;" \
    "  background-color: #fafafa; }" \
    "QPushButton:hover { background-color: #ececec; }"

#define INACTIVE_CURRENT_CABIN_BUTTON \
    "QPushButton { min-width: 44px; min-height: 30px;" \
    "  border: 1px solid #b39ddb; border-radius: 4px;" \
    "  background-color: #ede1f7; font-weight: bold; }"

#define ACTIVE_NOT_CURRENT_CABIN_BUTTON \
    "QPushButton { min-width: 44px; min-height: 30px;" \
    "  border: 1px solid #5a4a82; border-radius: 4px;" \
    "  background-color: #4a3a6e; color: white; font-weight: bold; }"

#define ACTIVE_CURRENT_CABIN_BUTTON \
    "QPushButton { min-width: 44px; min-height: 30px;" \
    "  border: 1px solid #6a4ea8; border-radius: 4px;" \
    "  background-color: #8d6cd1; color: white; font-weight: bold; }"

// Маркер "активной" кнопки в setStyleSheet()
#define ACTIVE_BUTTON_MARKER "#4a3a6e"

#endif //LAB_04_BUTTONSTYLESHEETS_H
