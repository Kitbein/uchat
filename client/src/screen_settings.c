#include "../inc/client.h"

static void build_account_menu(GtkWidget *main)
{
    t_settings_screen.account_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(t_settings_screen.account_block), WINDOW_WIDTH-LEFTBAR_W, 0);
    gtk_widget_set_name(GTK_WIDGET(t_settings_screen.account_block), "menu_block");
    gtk_fixed_put(GTK_FIXED(main),t_settings_screen.account_block, 0, 0);

    GtkWidget *title1 = gtk_label_new("ACCOUNT INFORMATION");
    gtk_widget_set_name(GTK_WIDGET(title1), "title1");              // Имя
    gtk_widget_set_halign(title1, GTK_ALIGN_START);                  // Позиция текста
    gtk_box_pack_start(GTK_BOX(t_settings_screen.account_block), title1, FALSE, FALSE, 0);

    //--//
    GtkWidget *account_inf_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(account_inf_block), "account_block");
    gtk_box_pack_start(GTK_BOX(t_settings_screen.account_block), account_inf_block, FALSE, FALSE, 0);

    //--//
    GtkWidget *user_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(account_inf_block), user_box, FALSE, FALSE, 20);

    GtkWidget *avatar_container = gtk_fixed_new();
    gtk_widget_set_valign(GTK_WIDGET(avatar_container), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(user_box), avatar_container, FALSE, FALSE, 0);

    GtkWidget *avatar = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)100);
    gtk_fixed_put(GTK_FIXED(avatar_container), avatar, 0, 0);

    GtkWidget *add_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(add_button), "add_button");
    tooltip("Upload picture",add_button);
    gtk_fixed_put(GTK_FIXED(avatar_container), add_button, 70, 0);

    GtkWidget *gallery_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(gallery_button), "gallery_button");
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 100, 100);
    gtk_widget_set_size_request(GTK_WIDGET(add_button), 32, 32);
    gtk_widget_set_size_request(GTK_WIDGET(gallery_button), 32, 32);
    tooltip("Choose picture",gallery_button);
    gtk_fixed_put(GTK_FIXED(avatar_container), gallery_button, 84, 32);

    GtkWidget *names_account = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_valign(GTK_WIDGET(names_account), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(user_box), names_account, FALSE, FALSE, 20);

    // t_settings.username = gtk_label_new(t_account.username);
    // gtk_widget_set_name(GTK_WIDGET(t_settings.username), "nickname-s");
    // gtk_widget_set_halign(GTK_WIDGET(t_settings.username), GTK_ALIGN_START);
    // gtk_box_pack_start(GTK_BOX(names_account), t_settings.username, FALSE, FALSE, 0);
    // t_settings.name = gtk_label_new(t_account.name);
    // gtk_widget_set_name(GTK_WIDGET(t_settings.name), "nickname-n");
    // gtk_widget_set_halign(GTK_WIDGET(t_settings.name), GTK_ALIGN_START);
    // gtk_box_pack_start(GTK_BOX(names_account), t_settings.name, FALSE, FALSE, 10);

    t_settings.username = gtk_label_new(t_account.username);   ////////t_settings
    gtk_widget_set_name(GTK_WIDGET(t_settings.username), "nickname-s");
    gtk_widget_set_halign(GTK_WIDGET(t_settings.username), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(t_settings.username), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(user_box), t_settings.username, FALSE, FALSE, 0);

    // GtkWidget *exit_button = gtk_event_box_new();
    // gtk_widget_set_size_request(GTK_WIDGET(exit_button), 50, 50);
    // gtk_widget_set_name(GTK_WIDGET(exit_button), "exit_button");
    // gtk_widget_set_valign(GTK_WIDGET(exit_button), GTK_ALIGN_CENTER);
    // gtk_box_pack_end(GTK_BOX(user_box), exit_button, FALSE, FALSE, 0);
    // tooltip("Exit",exit_button);
    //
    GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(info_box), "info_box");
    gtk_box_pack_start(GTK_BOX(account_inf_block), info_box, FALSE, FALSE, 0);

    GtkWidget *username_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(username_field), "settings_fields");
    g_signal_connect(G_OBJECT(username_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "changed", G_CALLBACK(username_field_change_event), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_field), "Username");
    gtk_entry_set_max_length(GTK_ENTRY(username_field), MAX_USERNAME);
    gtk_entry_set_text(GTK_ENTRY(username_field), t_account.username);
    gtk_box_pack_start(GTK_BOX(info_box), username_field, TRUE, TRUE, 10);

    GtkWidget *password_field = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_field), FALSE);
    g_signal_connect(G_OBJECT(password_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(password_field), "changed", G_CALLBACK(pass_field_change_event), NULL);
    gtk_widget_set_name(GTK_WIDGET(password_field), "settings_fields");
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_field), "Password");
    gtk_entry_set_max_length(GTK_ENTRY(password_field), MAX_PASS);
    gtk_box_pack_start(GTK_BOX(info_box), password_field, TRUE, TRUE, 10);

    GtkWidget *repassword_field = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(repassword_field), FALSE);
    g_signal_connect(G_OBJECT(repassword_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(repassword_field), "changed", G_CALLBACK(repass_field_change_event), NULL);
    gtk_widget_set_name(GTK_WIDGET(repassword_field), "settings_fields");
    gtk_entry_set_placeholder_text(GTK_ENTRY(repassword_field), "Repeat password");
    gtk_entry_set_max_length(GTK_ENTRY(repassword_field), MAX_PASS);
    gtk_box_pack_start(GTK_BOX(info_box), repassword_field, TRUE, TRUE, 10);

    GtkWidget *apply_butt = gtk_button_new_with_label("Apply");
    gtk_widget_set_name(GTK_WIDGET(apply_butt), "apply_button");
    gtk_button_set_relief(GTK_BUTTON(apply_butt), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(apply_butt), 100, 10);
    gtk_box_pack_start(GTK_BOX(info_box), apply_butt, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(apply_butt), "clicked", G_CALLBACK(apply_butt_click), NULL);

    g_signal_connect(G_OBJECT(add_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(add_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(add_button), "button_press_event", G_CALLBACK(add_button_click), NULL);

    g_signal_connect(G_OBJECT(gallery_button), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(gallery_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(gallery_button), "button_press_event", G_CALLBACK(gallery_button_click), main);
}

static void build_appearance_menu(GtkWidget *main)
{
    t_settings_screen.theme_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(t_settings_screen.theme_block), WINDOW_WIDTH-LEFTBAR_W, 0);
    gtk_widget_set_name(GTK_WIDGET(t_settings_screen.theme_block), "menu_block");
    gtk_fixed_put(GTK_FIXED(main),t_settings_screen.theme_block, 0, 0);

    GtkWidget *title4 = gtk_label_new("THEME SELECTION");
    gtk_widget_set_name(GTK_WIDGET(title4), "title4");                // Имя
    gtk_widget_set_halign(title4, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(t_settings_screen.theme_block), title4, FALSE, FALSE, 0);

    GtkWidget *theme_select_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(theme_select_block), "appearance_block");
    gtk_box_pack_start(GTK_BOX(t_settings_screen.theme_block), theme_select_block, FALSE, FALSE, 0);

    GtkWidget *title5 = gtk_label_new("CHOOSE YOUR DESTINY!");
    gtk_widget_set_name(GTK_WIDGET(title5), "title5");                // Имя
    gtk_widget_set_halign(title5, GTK_ALIGN_START);                   // Позиция текста
    gtk_widget_set_halign(GTK_WIDGET(title5), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(theme_select_block), title5, FALSE, FALSE, 0);

    GtkWidget *appearance_menu = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(appearance_menu), "chat_bgs_box");
    gtk_box_pack_start(GTK_BOX(theme_select_block), appearance_menu, FALSE, FALSE, 0);

    GtkWidget *theme_marvel = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(theme_marvel), "theme_bgs");
    gtk_widget_set_size_request(GTK_WIDGET(theme_marvel), 260, 50);
    GtkWidget *marvel_label = gtk_label_new("MARVEL");
    gtk_widget_set_name(GTK_WIDGET(marvel_label), "theme_label");
    gtk_widget_set_halign(GTK_WIDGET(marvel_label), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(theme_marvel), marvel_label);
    gtk_box_pack_start(GTK_BOX(appearance_menu), theme_marvel, TRUE, FALSE, 0);

    GtkWidget *theme_anime = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(theme_anime), "theme_bgs");
    gtk_widget_set_size_request(GTK_WIDGET(theme_anime), 260, 50);
    GtkWidget *anime_label = gtk_label_new("ANIME");
    gtk_widget_set_name(GTK_WIDGET(anime_label), "theme_label");
    gtk_widget_set_halign(GTK_WIDGET(anime_label), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(theme_anime), anime_label);
    gtk_box_pack_start(GTK_BOX(appearance_menu), theme_anime, TRUE, FALSE, 0);

    GtkWidget *theme_game = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(theme_game), "theme_bgs");
    gtk_widget_set_size_request(GTK_WIDGET(theme_game), 260, 50);
    GtkWidget *game_label = gtk_label_new("GAME");
    gtk_widget_set_name(GTK_WIDGET(game_label), "theme_label");
    gtk_widget_set_halign(GTK_WIDGET(game_label), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(theme_game ), game_label);
    gtk_box_pack_start(GTK_BOX(appearance_menu), theme_game, TRUE, FALSE, 0);

    if(t_account.theme == 1)
        gtk_widget_set_state_flags(GTK_WIDGET(theme_marvel), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.theme == 2)
        gtk_widget_set_state_flags(GTK_WIDGET(theme_anime), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.theme == 3)
        gtk_widget_set_state_flags(GTK_WIDGET(theme_game), GTK_STATE_FLAG_LINK, TRUE);

    g_signal_connect(G_OBJECT(theme_marvel), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(theme_marvel), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(theme_marvel), "button_press_event", G_CALLBACK(theme_marvel_click), appearance_menu);

    g_signal_connect(G_OBJECT(theme_anime), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(theme_anime), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(theme_anime), "button_press_event", G_CALLBACK(theme_anime_click), appearance_menu);

    g_signal_connect(G_OBJECT(theme_game), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(theme_game), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(theme_game), "button_press_event", G_CALLBACK(theme_game_click), appearance_menu);


    GtkWidget *title3 = gtk_label_new("BACKGROUND SELECTION");
    gtk_widget_set_name(GTK_WIDGET(title3), "title3");
    gtk_widget_set_halign(title3, GTK_ALIGN_START);                     
    gtk_widget_set_halign(GTK_WIDGET(title3), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(theme_select_block), title3, FALSE, FALSE, 0);


    GtkWidget *previews_box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(previews_box1), "chat_bgs_box");
    gtk_box_pack_start(GTK_BOX(theme_select_block), previews_box1, FALSE, FALSE, 0);
    GtkWidget *bg1 = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(bg1), "chat_bg1");
    gtk_widget_set_size_request(GTK_WIDGET(bg1), 400, 200);
    gtk_box_pack_start(GTK_BOX(previews_box1), bg1, TRUE, FALSE, 10);
    GtkWidget *bg2 = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(bg2), "chat_bg2");
    gtk_widget_set_size_request(GTK_WIDGET(bg2), 400, 200);
    gtk_box_pack_start(GTK_BOX(previews_box1), bg2, TRUE, FALSE, 10);

    GtkWidget *previews_box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(GTK_WIDGET(previews_box2), "chat_bgs_box");
    gtk_box_pack_start(GTK_BOX(theme_select_block), previews_box2, FALSE, FALSE, 0);
    GtkWidget *bg3 = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(bg3), "chat_bg3");
    gtk_widget_set_size_request(GTK_WIDGET(bg3), 400, 200);
    gtk_box_pack_start(GTK_BOX(previews_box2), bg3, TRUE, FALSE, 10);
    GtkWidget *bg4 = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(bg4), "chat_bg4");
    gtk_widget_set_size_request(GTK_WIDGET(bg4), 400, 200);
    gtk_box_pack_start(GTK_BOX(previews_box2), bg4, TRUE, FALSE, 10);

    if(t_account.background == 1)
        gtk_widget_set_state_flags(GTK_WIDGET(bg1), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.background == 2)
        gtk_widget_set_state_flags(GTK_WIDGET(bg2), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.background == 3)
        gtk_widget_set_state_flags(GTK_WIDGET(bg3), GTK_STATE_FLAG_LINK, TRUE);
    else if(t_account.background == 4)
        gtk_widget_set_state_flags(GTK_WIDGET(bg4), GTK_STATE_FLAG_LINK, TRUE);

    g_signal_connect(G_OBJECT(bg1), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(bg1), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(bg1), "button_press_event", G_CALLBACK(bg1_preview_click), previews_box1);

    g_signal_connect(G_OBJECT(bg2), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(bg2), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(bg2), "button_press_event", G_CALLBACK(bg2_preview_click), previews_box1);

    g_signal_connect(G_OBJECT(bg3), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(bg3), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(bg3), "button_press_event", G_CALLBACK(bg3_preview_click), previews_box2);

    g_signal_connect(G_OBJECT(bg4), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(bg4), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(bg4), "button_press_event", G_CALLBACK(bg4_preview_click), previews_box2);
}


void build_settings_menu(GtkWidget **stgscreen)
{
    t_screen.settings_scr = gtk_fixed_new();
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.settings_scr), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*stgscreen), t_screen.settings_scr, 0, 0);

    GtkWidget *selection = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(selection), "leftbar");
    gtk_widget_set_size_request(GTK_WIDGET(selection), LEFTBAR_W, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(t_screen.settings_scr), selection, 0, 0);

    t_settings_screen.boxes[0] = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_settings_screen.boxes[0]), "accountbutton");
    gtk_widget_set_halign(GTK_WIDGET(t_settings_screen.boxes[0]), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_settings_screen.boxes[0]), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), t_settings_screen.boxes[0], FALSE, FALSE, 10);
    gtk_widget_set_state_flags(GTK_WIDGET(t_settings_screen.boxes[0]), GTK_STATE_FLAG_LINK, FALSE);

    t_settings_screen.boxes[1] = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_settings_screen.boxes[1]), "themebutton");
    gtk_widget_set_halign(GTK_WIDGET(t_settings_screen.boxes[1]), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_settings_screen.boxes[1]), 50, 50);
    gtk_box_pack_start(GTK_BOX(selection), t_settings_screen.boxes[1], FALSE, FALSE, 10);

    t_settings_screen.boxes[2] = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_settings_screen.boxes[2]), "exit_from_sett_button");
    gtk_widget_set_halign(GTK_WIDGET(t_settings_screen.boxes[2]), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(t_settings_screen.boxes[2]), 50, 50);
    gtk_box_pack_end(GTK_BOX(selection), t_settings_screen.boxes[2], FALSE, FALSE, 10);

    GtkWidget *settings_scr_main = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(GTK_WIDGET(settings_scr_main), "settings_scr");
    gtk_widget_set_size_request(GTK_WIDGET(settings_scr_main), WINDOW_WIDTH-67, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(t_screen.settings_scr), settings_scr_main, LEFTBAR_W, 0);
    GtkWidget *main = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(settings_scr_main), main);
    gtk_widget_hide(gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(settings_scr_main)));

    build_account_menu(main);
    build_appearance_menu(main);

    g_signal_connect(G_OBJECT(t_settings_screen.boxes[0]), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_settings_screen.boxes[0]), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_settings_screen.boxes[0]), "button_press_event", G_CALLBACK(account_inf_click), NULL);

    g_signal_connect(G_OBJECT(t_settings_screen.boxes[1]), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_settings_screen.boxes[1]), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_settings_screen.boxes[1]), "button_press_event", G_CALLBACK(theme_settings_click), NULL);

    g_signal_connect(G_OBJECT(t_settings_screen.boxes[2]), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(t_settings_screen.boxes[2]), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(t_settings_screen.boxes[2]), "button_press_event", G_CALLBACK(exit_fr_settings_click), NULL);
}
