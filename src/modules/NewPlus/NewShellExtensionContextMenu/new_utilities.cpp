#include "pch.h"
#include "new_utilities.h"

// HACK: Store number of templates when generating the menu entries to send later.
size_t saved_number_of_templates = -1;
size_t newplus::utilities::get_saved_number_of_templates()
{
    return saved_number_of_templates;
}
void newplus::utilities::set_saved_number_of_templates(size_t templates)
{
    saved_number_of_templates = templates;
}

POINT mouse_position_at_context_menu_right_click = { 0 };
POINT newplus::utilities::get_mouse_position_at_context_menu_right_click()
{
    return mouse_position_at_context_menu_right_click;
}

void newplus::utilities::set_mouse_position_at_context_menu_right_click_to_current_position()
{
    GetCursorPos(&mouse_position_at_context_menu_right_click);
}

void newplus::utilities::set_mouse_position(const POINT& mouse_location)
{
    mouse_position_at_context_menu_right_click = mouse_location;
}
