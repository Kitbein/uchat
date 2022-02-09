#include "../inc/client.h"

static void focus_switch(GtkWidget *widget, GtkWidget *target) {
    if(widget){
        gtk_widget_set_can_focus(GTK_WIDGET(target), TRUE);
        gtk_widget_grab_focus(GTK_WIDGET(target));
    }
}

void build_registration(GtkWidget **main_area)
{
    t_auth.registration_menu = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_auth.registration_menu), "auth_screen");
    gtk_widget_set_size_request(GTK_WIDGET(t_auth.registration_menu), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*main_area),t_auth.registration_menu, 0, 0);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "login_menu");
    gtk_widget_set_size_request(GTK_WIDGET(box), 430, 0);
    gtk_widget_set_halign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(t_auth.registration_menu), box);
    gtk_widget_set_can_focus(GTK_WIDGET(box), TRUE);
    gtk_widget_grab_focus(GTK_WIDGET(box));

    GtkWidget *title1 = gtk_label_new("Sign up");
    gtk_widget_set_name(GTK_WIDGET(title1), "login_title1");
    gtk_widget_set_halign(title1, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), title1, FALSE, FALSE, 0);

    GtkWidget *username_label = gtk_label_new("Username");
    gtk_widget_set_name(GTK_WIDGET(username_label), "login_label");
    gtk_widget_set_halign(username_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), username_label, FALSE, FALSE, 4);
    GtkWidget *username_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(username_field), "login_fields");
    g_signal_connect(G_OBJECT(username_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "changed", G_CALLBACK(username_field_change_event), NULL);
    gtk_entry_set_max_length(GTK_ENTRY(username_field), MAX_USERNAME);
    gtk_box_pack_start(GTK_BOX(box), username_field, TRUE, TRUE, 0);


    GtkWidget *pass_label = gtk_label_new("Password");
    gtk_widget_set_name(GTK_WIDGET(pass_label), "login_label");
    gtk_widget_set_halign(pass_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), pass_label, FALSE, FALSE, 4);
    GtkWidget *pass_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(pass_field), "login_fields");
    gtk_entry_set_visibility(GTK_ENTRY(pass_field), FALSE);
    g_signal_connect(G_OBJECT(pass_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(pass_field), "changed", G_CALLBACK(pass_field_change_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "activate", G_CALLBACK(focus_switch), pass_field);
    gtk_entry_set_max_length(GTK_ENTRY(pass_field), MAX_PASS);
    gtk_box_pack_start(GTK_BOX(box), pass_field, TRUE, TRUE, 0);

    GtkWidget *repass_label = gtk_label_new("Confirm Password");
    gtk_widget_set_name(GTK_WIDGET(repass_label), "login_label");
    gtk_widget_set_halign(repass_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), repass_label, FALSE, FALSE, 4);
    GtkWidget *repass_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(repass_field), "login_fields");
    gtk_entry_set_visibility(GTK_ENTRY(repass_field), FALSE);
    g_signal_connect(G_OBJECT(repass_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(repass_field), "changed", G_CALLBACK(repass_field_change_event), NULL);
    g_signal_connect(G_OBJECT(pass_field), "activate", G_CALLBACK(focus_switch), repass_field);
    gtk_entry_set_max_length(GTK_ENTRY(repass_field), MAX_PASS);
    gtk_box_pack_start(GTK_BOX(box), repass_field, TRUE, TRUE, 0);

    GtkWidget *next_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *event_cancel = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(event_cancel), "event_register");
    //КНОПКА CANCEL
    GtkWidget *cancel_label = gtk_button_new_with_label("Cancel");
    gtk_widget_set_name(GTK_WIDGET(cancel_label), "cancel_button");
    gtk_button_set_relief(GTK_BUTTON(cancel_label), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(cancel_label), 100, 30);
    gtk_container_add(GTK_CONTAINER(event_cancel), cancel_label);
    gtk_box_pack_start(GTK_BOX(next_buttons), event_cancel, TRUE, FALSE, 0);

    GtkWidget *event_next = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(event_next), "event_next");
    gtk_box_pack_start(GTK_BOX(box), next_buttons, FALSE, FALSE, 0);
    //КНОПКА Create account
    GtkWidget *next_label = gtk_button_new_with_label("Create account");
    gtk_widget_set_name(GTK_WIDGET(next_label), "login_button");
    gtk_button_set_relief(GTK_BUTTON(next_label), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(next_label), 100, 30);
    gtk_container_add(GTK_CONTAINER(event_next), next_label);
    gtk_box_pack_start(GTK_BOX(next_buttons), event_next, TRUE, FALSE, 0);

    g_signal_connect(G_OBJECT(next_label), "clicked", G_CALLBACK(reg_butt_click), NULL);


    gtk_widget_show_all(GTK_WIDGET(t_auth.registration_menu));

    g_signal_connect(G_OBJECT(cancel_label), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(cancel_label), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(cancel_label), "button_press_event", G_CALLBACK(login_button_click), main_area);

}

void build_authorization(GtkWidget **main_area)
{
    t_auth.login_menu = gtk_event_box_new();
    gtk_widget_set_name(GTK_WIDGET(t_auth.login_menu), "auth_screen");
    gtk_widget_set_size_request(GTK_WIDGET(t_auth.login_menu), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_fixed_put(GTK_FIXED(*main_area), t_auth.login_menu, 0, 0);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(GTK_WIDGET(box), "login_menu");
    gtk_widget_set_size_request(GTK_WIDGET(box), 430, 0);
    gtk_widget_set_halign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(t_auth.login_menu), box);

    GtkWidget *title1 = gtk_label_new("WELCOME!");
    gtk_widget_set_name(GTK_WIDGET(title1), "login_title1");
    gtk_widget_set_halign(title1, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), title1, FALSE, FALSE, 0);

    GtkWidget *login_label = gtk_label_new("Username");
    gtk_widget_set_name(GTK_WIDGET(login_label), "login_label");
    gtk_widget_set_halign(login_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), login_label, FALSE, FALSE, 4);
    GtkWidget *username_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(username_field), "login_fields");
    g_signal_connect(G_OBJECT(username_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "changed", G_CALLBACK(username_field_change_event), NULL);
    gtk_widget_set_can_focus(GTK_WIDGET(username_field), TRUE);
    gtk_widget_grab_focus(GTK_WIDGET(username_field));
    gtk_entry_set_max_length(GTK_ENTRY(username_field), MAX_USERNAME);
    gtk_box_pack_start(GTK_BOX(box), username_field, TRUE, TRUE, 0);

    GtkWidget *pass_label = gtk_label_new("Password");
    gtk_widget_set_name(GTK_WIDGET(pass_label), "login_label");
    gtk_widget_set_halign(pass_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(box), pass_label, FALSE, FALSE, 4);
    GtkWidget *pass_field = gtk_entry_new();
    gtk_widget_set_name(GTK_WIDGET(pass_field), "login_fields");
    g_signal_connect(G_OBJECT(pass_field), "insert-text", G_CALLBACK(all_input_event), NULL);
    g_signal_connect(G_OBJECT(pass_field), "changed", G_CALLBACK(pass_field_change_event), NULL);
    g_signal_connect(G_OBJECT(username_field), "activate", G_CALLBACK(focus_switch), pass_field);
    gtk_entry_set_max_length(GTK_ENTRY(pass_field), MAX_PASS);
    gtk_entry_set_visibility(GTK_ENTRY(pass_field), FALSE);
    gtk_box_pack_start(GTK_BOX(box), pass_field, TRUE, TRUE, 0);

    GtkWidget *login_butt = gtk_button_new_with_label("Login");
    gtk_widget_set_name(GTK_WIDGET(login_butt), "login_button");
    gtk_button_set_relief(GTK_BUTTON(login_butt), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(login_butt), 100, 20);
    gtk_box_pack_start(GTK_BOX(box), login_butt, TRUE, TRUE, 20);
    g_signal_connect(G_OBJECT(pass_field), "activate", G_CALLBACK(login_butt_click), pass_field);
    g_signal_connect(G_OBJECT(login_butt), "clicked", G_CALLBACK(login_butt_click), pass_field);

    GtkWidget *reg_label = gtk_button_new_with_label("Create account");
    gtk_button_set_relief(GTK_BUTTON(reg_label), GTK_RELIEF_NONE);
    gtk_widget_set_size_request(GTK_WIDGET(reg_label), 100, 20);
    gtk_widget_set_halign(reg_label, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), reg_label, TRUE, TRUE, 0);

    gtk_widget_show_all(GTK_WIDGET(t_auth.login_menu));
    g_signal_connect(G_OBJECT(reg_label), "enter-notify-event", G_CALLBACK(event_enter_notify), NULL);
    g_signal_connect(G_OBJECT(reg_label), "leave-notify-event", G_CALLBACK(event_leave_notify), NULL);
    g_signal_connect(G_OBJECT(reg_label), "button_press_event", G_CALLBACK(register_button_click), main_area);
}
