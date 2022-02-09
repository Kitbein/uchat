#include "../inc/client.h"

static t_chat_list *chat_create_node(t_chat_data *chat) {
    t_chat_list *new_node = NULL;
    new_node = malloc(sizeof(t_chat_list));
    new_node->chat_id = chat->chat_id;
    new_node->username = strdup(chat->title);
    if (chat->user->id) {
        new_node->avatar = chat->user->avatar;
        new_node->status = chat->user->online;
        new_node->user_id = chat->user->id;
    }
    else {
        new_node->user_id = 0;
        new_node->avatar = 999;
        new_node->members = chat->members;
    }
    new_node->next = NULL;
    return new_node;
}

void chat_push_back(t_chat_list **list, t_chat_data *chat) {
    t_chat_list *back_list = chat_create_node(chat);
    t_chat_list *p = NULL;
    if (list == NULL || *list == NULL)
        *list = back_list;
    else {
        p = *list;
        while (p->next != NULL)
            p = p->next;
        p->next = back_list;
    }
}

void chat_clear_list(t_chat_list **list) {
    t_chat_list *p;
    while (*list) {
        p = NULL;
        if (list) {
            p = (*list)->next;
            free(*list);
            *list = p;
        }
    }
}

static void build_list(GtkWidget *main)
{
    GtkWidget *list_block = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(list_block), "list");                    // Имя
    gtk_widget_set_size_request(GTK_WIDGET(list_block), LIST_W, LIST_H);    // Размер
    gtk_fixed_put(GTK_FIXED(main), list_block, 0, 0);                       // Позиция
    //
    GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(search_block), "search_block");
    gtk_widget_set_size_request(GTK_WIDGET(search_block), 300, 40); //350, 40
    gtk_box_pack_start(GTK_BOX(list_block), search_block, FALSE, FALSE, 15);
    GtkWidget *search_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(search_field), "search_field");
    g_signal_connect(G_OBJECT(search_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Search for people");
    gtk_entry_set_max_length(GTK_ENTRY(search_field), MAX_USERNAME);
    gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0);
    GtkWidget *adduser = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(adduser), "adduser");
    gtk_widget_set_size_request(GTK_WIDGET(adduser), 30, 30);
    gtk_box_pack_end(GTK_BOX(search_block), adduser, FALSE, FALSE, 10);
    gtk_widget_set_halign(GTK_WIDGET(adduser), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(adduser), GTK_ALIGN_CENTER);
    tooltip("Add",adduser);
    //
    GtkWidget *dm_text = gtk_label_new("DIRECT MESSAGES");
    gtk_widget_set_name(GTK_WIDGET(dm_text), "dm_text");                 // Имя
    gtk_widget_set_halign(dm_text, GTK_ALIGN_START);                     // Позиция текста
    gtk_box_pack_start(GTK_BOX(list_block), dm_text, FALSE, FALSE, 0);
    //

    //GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, LIST_H-100, 100, 100, LIST_H-100);    // Параметры скролла
    GtkWidget *scrollable = gtk_scrolled_window_new(NULL, NULL);                 // Зона, доступная для бесконечного скролла
    gtk_widget_set_size_request(scrollable, LIST_W, LIST_H-200);
    gtk_widget_set_name(GTK_WIDGET(scrollable), "chatlist");

    t_msg.chatlist = create_chatlist();

    gtk_container_add(GTK_CONTAINER(scrollable), t_msg.chatlist);
    gtk_box_pack_start(GTK_BOX(list_block), scrollable, FALSE, FALSE, 0);              // Кладем скролл зону на главный экран
    gtk_widget_hide(gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(scrollable)));

    g_signal_connect(G_OBJECT(adduser), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(adduser), "button_press_event", G_CALLBACK(adduser_click), search_field);
    g_signal_connect(G_OBJECT(search_field), "activate", G_CALLBACK(adduser_click), search_field);

    GtkWidget *settings_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_name(GTK_WIDGET(settings_block), "settings_block");
    gtk_widget_set_size_request(GTK_WIDGET(settings_block), 300, 60);
    gtk_box_pack_end(GTK_BOX(list_block), settings_block, FALSE, FALSE, 10);
    
    GtkWidget *settings_button = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(settings_button), "settingsbutton");
    gtk_widget_set_size_request(GTK_WIDGET(settings_button), 45, 45);
    gtk_widget_set_halign(GTK_WIDGET(settings_button), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(settings_button), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(settings_block), settings_button, FALSE, FALSE, 10);
    tooltip("Settings", settings_button);

     GtkWidget *group = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(group), "msggroup");
    gtk_widget_set_size_request(GTK_WIDGET(group), 45, 45);
    //gtk_fixed_put(GTK_FIXED(main), group, LIST_W-50, LIST_H-50);
    gtk_box_pack_start(GTK_BOX(settings_block), group, FALSE, FALSE, 10);
    gtk_widget_set_halign(GTK_WIDGET(group), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(group), GTK_ALIGN_CENTER);
    tooltip("Create group",group);

    // GtkWidget *avatar_icon = gtk_event_box_new();
    // gtk_widget_set_name(GTK_WIDGET(avatar_icon), "avatarbutton");
    // gtk_widget_set_size_request(GTK_WIDGET(avatar_icon), 40, 40);
    // gtk_box_pack_end(GTK_BOX(settings_block), avatar_icon, FALSE, FALSE, 10);

    GtkWidget *avatar_icon = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(avatar_icon), "statusbutton");
    //gtk_widget_set_halign(GTK_WIDGET(avatar_icon), GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(GTK_WIDGET(avatar_icon), 47, 47);
    gtk_box_pack_end(GTK_BOX(settings_block), avatar_icon, FALSE, FALSE, 10);
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 47, 47);
    gtk_widget_set_halign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(avatar), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_event_avatar_account), (int*)47);
    gtk_event_box_set_above_child(GTK_EVENT_BOX(avatar_icon), TRUE);
    gtk_container_add(GTK_CONTAINER(avatar_icon), avatar);

    GtkWidget *username_part = gtk_label_new(t_account.username);
    gtk_widget_set_name(GTK_WIDGET(username_part), "nickname_part");
    gtk_widget_set_halign(GTK_WIDGET(username_part), GTK_ALIGN_CENTER);
    gtk_box_pack_end(GTK_BOX(settings_block), username_part, FALSE, FALSE, 10);

    g_signal_connect(G_OBJECT(settings_button), "enter-notify-event", G_CALLBACK(event_false_enter_notify), NULL);
    g_signal_connect(G_OBJECT(settings_button), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(settings_button), "button_press_event", G_CALLBACK(settings_click), NULL);

    g_signal_connect(G_OBJECT(group), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(group), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(group), "button_press_event", G_CALLBACK(msggroup_click), main);
}

static void build_entryfield(GtkWidget *main)
{

    t_msg.entry_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_name(GTK_WIDGET(t_msg.entry_block), "entry_block");
    gtk_widget_set_size_request(GTK_WIDGET(t_msg.entry_block), ENTRY_W, ENTRY_H);
    gtk_fixed_put(GTK_FIXED(main),t_msg.entry_block, LIST_W, WINDOW_HEIGHT-ENTRY_H);

    GtkWidget *attach = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(attach), "attach");
    gtk_widget_set_size_request(GTK_WIDGET(attach), 40, 40);
    gtk_box_pack_start(GTK_BOX(t_msg.entry_block), attach, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(attach), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(attach), GTK_ALIGN_CENTER);
    tooltip("Attach image",attach);

    t_msg.entry = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(t_msg.entry), "entry_text");
    char* entry_placeholder_text = mx_strjoin("Message ", t_msg.current);
    gtk_entry_set_placeholder_text(GTK_ENTRY(t_msg.entry), entry_placeholder_text);
    g_signal_connect(G_OBJECT(t_msg.entry), "insert-text", G_CALLBACK(all_input_event), NULL);
    gtk_entry_set_max_length(GTK_ENTRY(t_msg.entry), MAX_MESSAGE);
    gtk_box_pack_start(GTK_BOX(t_msg.entry_block), t_msg.entry, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(t_msg.entry), "changed", G_CALLBACK(entry_text_change_event), NULL);

    GtkWidget *send = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(send), "send");
    gtk_widget_set_size_request(GTK_WIDGET(send), 40, 40);
    gtk_box_pack_end(GTK_BOX(t_msg.entry_block), send, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(send), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(send), GTK_ALIGN_CENTER);
    tooltip("Send",send);

    GtkWidget *sticker = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(sticker), "sticker");
    gtk_widget_set_size_request(GTK_WIDGET(sticker), 40, 40);
    gtk_box_pack_end(GTK_BOX(t_msg.entry_block), sticker, FALSE, FALSE, 0);
    gtk_widget_set_halign(GTK_WIDGET(sticker), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(sticker), GTK_ALIGN_CENTER);
    tooltip("Stickers",sticker);

    g_signal_connect(G_OBJECT(attach), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(attach), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(attach), "button_press_event", G_CALLBACK(attach_click), NULL);

    g_signal_connect(G_OBJECT(send), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(send), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(send), "button_press_event", G_CALLBACK(send_click), NULL);
    g_signal_connect(G_OBJECT(t_msg.entry), "activate", G_CALLBACK(send_press), NULL);

    g_signal_connect(G_OBJECT(sticker), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(sticker), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(sticker), "button_press_event", G_CALLBACK(sticker_click), main);

}

static void build_chat(GtkWidget *main)
{
    GtkAdjustment *vadjustment = gtk_adjustment_new(0, 0, CHAT_H, 100, 100, CHAT_H); // Параметры скролла
    t_msg.scrolled_message = gtk_scrolled_window_new(NULL, vadjustment);             // Зона, доступная для бесконечного скролла
    gtk_widget_set_name(GTK_WIDGET(t_msg.scrolled_message), "scrollable_msg");                  // Имя 1
    gtk_widget_set_size_request(t_msg.scrolled_message, CHAT_W, CHAT_H);                        // Размер

    // g_signal_connect(G_OBJECT(t_msg.scrolled_message), "scroll_event", G_CALLBACK(scrolled), NULL);

    t_msg.chat_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);                 // Главный блок с сообщениями - вертикальный, все сообщения - горизонтальные
    gtk_widget_set_size_request(t_msg.chat_screen, CHAT_W, CHAT_H);               // Размер
    gtk_widget_set_name(GTK_WIDGET(t_msg.chat_screen), "messages_block");         // Имя 2

    gtk_container_add(GTK_CONTAINER(t_msg.scrolled_message), t_msg.chat_screen);              // Кладем чат в скролл зону
    gtk_fixed_put(GTK_FIXED(main),t_msg.scrolled_message, LIST_W, 0);                           // Кладем скролл зону на главный экран
    gtk_widget_hide(gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(t_msg.scrolled_message)));
}

static void build_theme_scr(GtkWidget *main)
{
    t_screen.theme_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(t_screen.theme_screen), "messages_block");
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.theme_screen), CHAT_W, CHAT_H);
    gtk_fixed_put(GTK_FIXED(main),t_screen.theme_screen, LIST_W, 0); 

    GtkWidget *theme_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(GTK_WIDGET(theme_box), 500, 400);
    gtk_box_pack_end(GTK_BOX(t_screen.theme_screen), theme_box, FALSE, FALSE, 0);
    gtk_widget_set_margin_bottom(GTK_WIDGET(theme_box), 120);

    GtkWidget *theme1 = gtk_event_box_new();
    GtkWidget *theme2 = gtk_event_box_new();
    GtkWidget *theme3 = gtk_event_box_new();

    gtk_widget_set_name(GTK_WIDGET(theme1), "theme1");
    gtk_widget_set_name(GTK_WIDGET(theme2), "theme2");
    gtk_widget_set_name(GTK_WIDGET(theme3), "theme3");
    gtk_widget_set_size_request(GTK_WIDGET(theme1), 220, 264);
    gtk_widget_set_size_request(GTK_WIDGET(theme2), 220, 264);
    gtk_widget_set_size_request(GTK_WIDGET(theme3), 220, 264);
    gtk_box_pack_start(GTK_BOX(theme_box), theme1, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(theme_box), theme2, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(theme_box), theme3, TRUE, FALSE, 0);

    gtk_widget_set_margin_start(GTK_WIDGET(theme1), 10);
    gtk_widget_set_margin_start(GTK_WIDGET(theme2), 10);
    gtk_widget_set_margin_start(GTK_WIDGET(theme3), 10);

}

void build_messanger_screen(GtkWidget **msgscreen)
{
    // Creating workspace
    t_screen.msg_scr = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_screen.msg_scr), "messanger");
    gtk_widget_set_size_request(GTK_WIDGET(t_screen.msg_scr), WINDOW_WIDTH, WINDOW_HEIGHT); //WINDOW_WIDTH-LEFTBAR_W
    gtk_fixed_put(GTK_FIXED(*msgscreen), t_screen.msg_scr, 0, 0);
    t_msg.main = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(t_screen.msg_scr), t_msg.main);
    //
    //
    build_list(t_msg.main);
    build_theme_scr(t_msg.main);
    build_chat(t_msg.main);
    build_entryfield(t_msg.main);
}
