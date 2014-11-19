/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gnome.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  gtk_object_set_data_full (GTK_OBJECT (component), name, \
    gtk_widget_ref (widget), (GtkDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  gtk_object_set_data (GTK_OBJECT (component), name, widget)

static GnomeUIInfo file1_menu_uiinfo[] =
{
  GNOMEUIINFO_MENU_NEW_ITEM (N_("_New"), NULL, on_new1_activate, NULL),
  GNOMEUIINFO_SEPARATOR,
  GNOMEUIINFO_MENU_EXIT_ITEM (on_quit1_activate, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo preferences1_menu_uiinfo[] =
{
  {
    GNOME_APP_UI_ITEM, N_("_Network"),
    NULL,
    (gpointer) on_network1_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("_Player"),
    NULL,
    (gpointer) on_player1_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("_Theme"),
    NULL,
    (gpointer) on_theme1_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  GNOMEUIINFO_END
};

static GnomeUIInfo help1_menu_uiinfo[] =
{
  {
    GNOME_APP_UI_ITEM, N_("_How To Play"),
    NULL,
    (gpointer) on_how_to_play1_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-help",
    0, (GdkModifierType) 0, NULL
  },
  GNOMEUIINFO_MENU_ABOUT_ITEM (on_about1_activate, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo menubar1_uiinfo[] =
{
  GNOMEUIINFO_MENU_GAME_TREE (file1_menu_uiinfo),
  GNOMEUIINFO_MENU_SETTINGS_TREE (preferences1_menu_uiinfo),
  GNOMEUIINFO_MENU_HELP_TREE (help1_menu_uiinfo),
  GNOMEUIINFO_END
};

GtkWidget*
create_GamazonsMain (void)
{
  GtkWidget *GamazonsMain;
  GtkWidget *vbox1;
  GtkWidget *menubar1;
  GtkWidget *scrolledwindow1;
  GtkWidget *viewport1;
  GtkWidget *hbox1;
  GtkWidget *scrolledwindow2;
  GtkWidget *viewport2;
  GtkWidget *table1;
  GtkWidget *hbox9;
  GtkWidget *label30;
  GtkWidget *label31;
  GtkWidget *label32;
  GtkWidget *label33;
  GtkWidget *label34;
  GtkWidget *label35;
  GtkWidget *label36;
  GtkWidget *label37;
  GtkWidget *label38;
  GtkWidget *label39;
  GtkWidget *vbox7;
  GtkWidget *label29;
  GtkWidget *label28;
  GtkWidget *label27;
  GtkWidget *label26;
  GtkWidget *label25;
  GtkWidget *label24;
  GtkWidget *label23;
  GtkWidget *label22;
  GtkWidget *label21;
  GtkWidget *label20;
  GtkWidget *vbox8;
  GtkWidget *label40;
  GtkWidget *label41;
  GtkWidget *label42;
  GtkWidget *label43;
  GtkWidget *label44;
  GtkWidget *label45;
  GtkWidget *label46;
  GtkWidget *label47;
  GtkWidget *label48;
  GtkWidget *label49;
  GtkWidget *hbox10;
  GtkWidget *label10;
  GtkWidget *label11;
  GtkWidget *label12;
  GtkWidget *label13;
  GtkWidget *label14;
  GtkWidget *label15;
  GtkWidget *label16;
  GtkWidget *label17;
  GtkWidget *label18;
  GtkWidget *label19;
  GtkWidget *scrolledwindow4;
  GtkWidget *CNVS_GAMEBOARD;
  AtkObject *atko;
  GtkWidget *vbox2;
  GtkWidget *vbox3;
  GtkWidget *vbox4;
  GtkWidget *label1;
  GtkWidget *scrolledwindow3;
  GtkWidget *viewport3;
  GtkWidget *hbox11;
  GtkWidget *scrolledwindow5;
  GtkWidget *viewport4;
  GtkWidget *vbox9;
  GtkWidget *vbuttonbox1;
  GtkWidget *BT_UNDO;
  GtkWidget *BT_FORCEMOVE;
  GtkWidget *BT_AUTOFINISH;
  GtkWidget *hbox12;
  GtkWidget *scrolledwindow6;
  GtkWidget *textview1;
  GtkWidget *statusbar1;

  GamazonsMain = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_usize (GamazonsMain, 770, 510);
  gtk_window_set_title (GTK_WINDOW (GamazonsMain), _("Gamazons"));
  gtk_window_set_resizable (GTK_WINDOW (GamazonsMain), FALSE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (GamazonsMain), TRUE);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (GamazonsMain), vbox1);

  menubar1 = gtk_menu_bar_new ();
  gtk_widget_show (menubar1);
  gtk_box_pack_start (GTK_BOX (vbox1), menubar1, FALSE, FALSE, 0);
  gnome_app_fill_menu (GTK_MENU_SHELL (menubar1), menubar1_uiinfo,
                       NULL, FALSE, 0);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox1), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  viewport1 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), viewport1);

  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox1);
  gtk_container_add (GTK_CONTAINER (viewport1), hbox1);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow2);
  gtk_box_pack_start (GTK_BOX (hbox1), scrolledwindow2, TRUE, TRUE, 0);
  gtk_widget_set_usize (scrolledwindow2, 210, -2);
  GTK_WIDGET_SET_FLAGS (scrolledwindow2, GTK_CAN_DEFAULT);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  viewport2 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport2);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), viewport2);

  table1 = gtk_table_new (3, 3, FALSE);
  gtk_widget_show (table1);
  gtk_container_add (GTK_CONTAINER (viewport2), table1);

  hbox9 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox9);
  gtk_table_attach (GTK_TABLE (table1), hbox9, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  label30 = gtk_label_new (_("a"));
  gtk_widget_show (label30);
  gtk_box_pack_start (GTK_BOX (hbox9), label30, FALSE, FALSE, 0);
  gtk_widget_set_usize (label30, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label30), GTK_JUSTIFY_LEFT);

  label31 = gtk_label_new (_("b"));
  gtk_widget_show (label31);
  gtk_box_pack_start (GTK_BOX (hbox9), label31, FALSE, FALSE, 0);
  gtk_widget_set_usize (label31, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label31), GTK_JUSTIFY_LEFT);

  label32 = gtk_label_new (_("c"));
  gtk_widget_show (label32);
  gtk_box_pack_start (GTK_BOX (hbox9), label32, FALSE, FALSE, 0);
  gtk_widget_set_usize (label32, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label32), GTK_JUSTIFY_LEFT);

  label33 = gtk_label_new (_("d"));
  gtk_widget_show (label33);
  gtk_box_pack_start (GTK_BOX (hbox9), label33, FALSE, FALSE, 0);
  gtk_widget_set_usize (label33, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label33), GTK_JUSTIFY_LEFT);

  label34 = gtk_label_new (_("e"));
  gtk_widget_show (label34);
  gtk_box_pack_start (GTK_BOX (hbox9), label34, FALSE, FALSE, 0);
  gtk_widget_set_usize (label34, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label34), GTK_JUSTIFY_LEFT);

  label35 = gtk_label_new (_("f"));
  gtk_widget_show (label35);
  gtk_box_pack_start (GTK_BOX (hbox9), label35, FALSE, FALSE, 0);
  gtk_widget_set_usize (label35, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label35), GTK_JUSTIFY_LEFT);

  label36 = gtk_label_new (_("g"));
  gtk_widget_show (label36);
  gtk_box_pack_start (GTK_BOX (hbox9), label36, FALSE, FALSE, 0);
  gtk_widget_set_usize (label36, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label36), GTK_JUSTIFY_LEFT);

  label37 = gtk_label_new (_("h"));
  gtk_widget_show (label37);
  gtk_box_pack_start (GTK_BOX (hbox9), label37, FALSE, FALSE, 0);
  gtk_widget_set_usize (label37, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label37), GTK_JUSTIFY_LEFT);

  label38 = gtk_label_new (_("i"));
  gtk_widget_show (label38);
  gtk_box_pack_start (GTK_BOX (hbox9), label38, FALSE, FALSE, 0);
  gtk_widget_set_usize (label38, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label38), GTK_JUSTIFY_LEFT);

  label39 = gtk_label_new (_("j"));
  gtk_widget_show (label39);
  gtk_box_pack_start (GTK_BOX (hbox9), label39, FALSE, FALSE, 0);
  gtk_widget_set_usize (label39, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label39), GTK_JUSTIFY_LEFT);

  vbox7 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox7);
  gtk_table_attach (GTK_TABLE (table1), vbox7, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  label29 = gtk_label_new (_("10"));
  gtk_widget_show (label29);
  gtk_box_pack_start (GTK_BOX (vbox7), label29, FALSE, FALSE, 0);
  gtk_widget_set_usize (label29, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label29), GTK_JUSTIFY_LEFT);

  label28 = gtk_label_new (_("9"));
  gtk_widget_show (label28);
  gtk_box_pack_start (GTK_BOX (vbox7), label28, FALSE, FALSE, 0);
  gtk_widget_set_usize (label28, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label28), GTK_JUSTIFY_LEFT);

  label27 = gtk_label_new (_("8"));
  gtk_widget_show (label27);
  gtk_box_pack_start (GTK_BOX (vbox7), label27, FALSE, FALSE, 0);
  gtk_widget_set_usize (label27, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label27), GTK_JUSTIFY_LEFT);

  label26 = gtk_label_new (_("7"));
  gtk_widget_show (label26);
  gtk_box_pack_start (GTK_BOX (vbox7), label26, FALSE, FALSE, 0);
  gtk_widget_set_usize (label26, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label26), GTK_JUSTIFY_LEFT);

  label25 = gtk_label_new (_("6"));
  gtk_widget_show (label25);
  gtk_box_pack_start (GTK_BOX (vbox7), label25, FALSE, FALSE, 0);
  gtk_widget_set_usize (label25, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label25), GTK_JUSTIFY_LEFT);

  label24 = gtk_label_new (_("5"));
  gtk_widget_show (label24);
  gtk_box_pack_start (GTK_BOX (vbox7), label24, FALSE, FALSE, 0);
  gtk_widget_set_usize (label24, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label24), GTK_JUSTIFY_LEFT);

  label23 = gtk_label_new (_("4"));
  gtk_widget_show (label23);
  gtk_box_pack_start (GTK_BOX (vbox7), label23, FALSE, FALSE, 0);
  gtk_widget_set_usize (label23, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label23), GTK_JUSTIFY_LEFT);

  label22 = gtk_label_new (_("3"));
  gtk_widget_show (label22);
  gtk_box_pack_start (GTK_BOX (vbox7), label22, FALSE, FALSE, 0);
  gtk_widget_set_usize (label22, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label22), GTK_JUSTIFY_LEFT);

  label21 = gtk_label_new (_("2"));
  gtk_widget_show (label21);
  gtk_box_pack_start (GTK_BOX (vbox7), label21, FALSE, FALSE, 0);
  gtk_widget_set_usize (label21, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label21), GTK_JUSTIFY_LEFT);

  label20 = gtk_label_new (_("1"));
  gtk_widget_show (label20);
  gtk_box_pack_start (GTK_BOX (vbox7), label20, FALSE, FALSE, 0);
  gtk_widget_set_usize (label20, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label20), GTK_JUSTIFY_LEFT);

  vbox8 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox8);
  gtk_table_attach (GTK_TABLE (table1), vbox8, 2, 3, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  label40 = gtk_label_new (_("10"));
  gtk_widget_show (label40);
  gtk_box_pack_start (GTK_BOX (vbox8), label40, FALSE, FALSE, 0);
  gtk_widget_set_usize (label40, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label40), GTK_JUSTIFY_LEFT);

  label41 = gtk_label_new (_("9"));
  gtk_widget_show (label41);
  gtk_box_pack_start (GTK_BOX (vbox8), label41, FALSE, FALSE, 0);
  gtk_widget_set_usize (label41, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label41), GTK_JUSTIFY_LEFT);

  label42 = gtk_label_new (_("8"));
  gtk_widget_show (label42);
  gtk_box_pack_start (GTK_BOX (vbox8), label42, FALSE, FALSE, 0);
  gtk_widget_set_usize (label42, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label42), GTK_JUSTIFY_LEFT);

  label43 = gtk_label_new (_("7"));
  gtk_widget_show (label43);
  gtk_box_pack_start (GTK_BOX (vbox8), label43, FALSE, FALSE, 0);
  gtk_widget_set_usize (label43, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label43), GTK_JUSTIFY_LEFT);

  label44 = gtk_label_new (_("6"));
  gtk_widget_show (label44);
  gtk_box_pack_start (GTK_BOX (vbox8), label44, FALSE, FALSE, 0);
  gtk_widget_set_usize (label44, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label44), GTK_JUSTIFY_LEFT);

  label45 = gtk_label_new (_("5"));
  gtk_widget_show (label45);
  gtk_box_pack_start (GTK_BOX (vbox8), label45, FALSE, FALSE, 0);
  gtk_widget_set_usize (label45, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label45), GTK_JUSTIFY_LEFT);

  label46 = gtk_label_new (_("4"));
  gtk_widget_show (label46);
  gtk_box_pack_start (GTK_BOX (vbox8), label46, FALSE, FALSE, 0);
  gtk_widget_set_usize (label46, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label46), GTK_JUSTIFY_LEFT);

  label47 = gtk_label_new (_("3"));
  gtk_widget_show (label47);
  gtk_box_pack_start (GTK_BOX (vbox8), label47, FALSE, FALSE, 0);
  gtk_widget_set_usize (label47, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label47), GTK_JUSTIFY_LEFT);

  label48 = gtk_label_new (_("2"));
  gtk_widget_show (label48);
  gtk_box_pack_start (GTK_BOX (vbox8), label48, FALSE, FALSE, 0);
  gtk_widget_set_usize (label48, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label48), GTK_JUSTIFY_LEFT);

  label49 = gtk_label_new (_("1"));
  gtk_widget_show (label49);
  gtk_box_pack_start (GTK_BOX (vbox8), label49, FALSE, FALSE, 0);
  gtk_widget_set_usize (label49, 15, 40);
  gtk_label_set_justify (GTK_LABEL (label49), GTK_JUSTIFY_LEFT);

  hbox10 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox10);
  gtk_table_attach (GTK_TABLE (table1), hbox10, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  label10 = gtk_label_new (_("a"));
  gtk_widget_show (label10);
  gtk_box_pack_start (GTK_BOX (hbox10), label10, FALSE, FALSE, 0);
  gtk_widget_set_usize (label10, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label10), GTK_JUSTIFY_LEFT);

  label11 = gtk_label_new (_("b"));
  gtk_widget_show (label11);
  gtk_box_pack_start (GTK_BOX (hbox10), label11, FALSE, FALSE, 0);
  gtk_widget_set_usize (label11, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label11), GTK_JUSTIFY_LEFT);

  label12 = gtk_label_new (_("c"));
  gtk_widget_show (label12);
  gtk_box_pack_start (GTK_BOX (hbox10), label12, FALSE, FALSE, 0);
  gtk_widget_set_usize (label12, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label12), GTK_JUSTIFY_LEFT);

  label13 = gtk_label_new (_("d"));
  gtk_widget_show (label13);
  gtk_box_pack_start (GTK_BOX (hbox10), label13, FALSE, FALSE, 0);
  gtk_widget_set_usize (label13, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label13), GTK_JUSTIFY_LEFT);

  label14 = gtk_label_new (_("e"));
  gtk_widget_show (label14);
  gtk_box_pack_start (GTK_BOX (hbox10), label14, FALSE, FALSE, 0);
  gtk_widget_set_usize (label14, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label14), GTK_JUSTIFY_LEFT);

  label15 = gtk_label_new (_("f"));
  gtk_widget_show (label15);
  gtk_box_pack_start (GTK_BOX (hbox10), label15, FALSE, FALSE, 0);
  gtk_widget_set_usize (label15, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label15), GTK_JUSTIFY_LEFT);

  label16 = gtk_label_new (_("g"));
  gtk_widget_show (label16);
  gtk_box_pack_start (GTK_BOX (hbox10), label16, FALSE, FALSE, 0);
  gtk_widget_set_usize (label16, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label16), GTK_JUSTIFY_LEFT);

  label17 = gtk_label_new (_("h"));
  gtk_widget_show (label17);
  gtk_box_pack_start (GTK_BOX (hbox10), label17, FALSE, FALSE, 0);
  gtk_widget_set_usize (label17, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label17), GTK_JUSTIFY_LEFT);

  label18 = gtk_label_new (_("i"));
  gtk_widget_show (label18);
  gtk_box_pack_start (GTK_BOX (hbox10), label18, FALSE, FALSE, 0);
  gtk_widget_set_usize (label18, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label18), GTK_JUSTIFY_LEFT);

  label19 = gtk_label_new (_("j"));
  gtk_widget_show (label19);
  gtk_box_pack_start (GTK_BOX (hbox10), label19, FALSE, FALSE, 0);
  gtk_widget_set_usize (label19, 40, 15);
  gtk_label_set_justify (GTK_LABEL (label19), GTK_JUSTIFY_LEFT);

  scrolledwindow4 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow4);
  gtk_table_attach (GTK_TABLE (table1), scrolledwindow4, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow4), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

  CNVS_GAMEBOARD = gnome_canvas_new ();
  gtk_widget_show (CNVS_GAMEBOARD);
  gtk_container_add (GTK_CONTAINER (scrolledwindow4), CNVS_GAMEBOARD);
  gtk_widget_set_usize (CNVS_GAMEBOARD, 400, 400);
  gnome_canvas_set_scroll_region (GNOME_CANVAS (CNVS_GAMEBOARD), 0, 0, 100, 100);

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox2);
  gtk_box_pack_start (GTK_BOX (hbox1), vbox2, TRUE, TRUE, 0);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox3);
  gtk_box_pack_start (GTK_BOX (vbox2), vbox3, TRUE, TRUE, 0);

  vbox4 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox4);
  gtk_box_pack_start (GTK_BOX (vbox3), vbox4, TRUE, TRUE, 0);

  label1 = gtk_label_new (_("Moves Made:"));
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (vbox4), label1, FALSE, FALSE, 0);
  gtk_widget_set_usize (label1, 0, 40);
  gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label1), 0.59, 0.72);

  scrolledwindow3 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow3);
  gtk_box_pack_start (GTK_BOX (vbox4), scrolledwindow3, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow3), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  viewport3 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport3);
  gtk_container_add (GTK_CONTAINER (scrolledwindow3), viewport3);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport3), GTK_SHADOW_NONE);

  hbox11 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox11);
  gtk_container_add (GTK_CONTAINER (viewport3), hbox11);

  scrolledwindow5 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow5);
  gtk_box_pack_start (GTK_BOX (hbox11), scrolledwindow5, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow5), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  viewport4 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport4);
  gtk_container_add (GTK_CONTAINER (scrolledwindow5), viewport4);
  gtk_widget_set_usize (viewport4, -2, 17);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport4), GTK_SHADOW_NONE);

  vbox9 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox9);
  gtk_container_add (GTK_CONTAINER (viewport4), vbox9);

  vbuttonbox1 = gtk_vbutton_box_new ();
  gtk_widget_show (vbuttonbox1);
  gtk_box_pack_start (GTK_BOX (vbox9), vbuttonbox1, FALSE, TRUE, 0);
  gtk_widget_set_usize (vbuttonbox1, -2, 105);
  gtk_button_box_set_spacing (GTK_BUTTON_BOX (vbuttonbox1), 0);

  BT_UNDO = gtk_button_new_with_mnemonic (_("Undo"));
  gtk_widget_show (BT_UNDO);
  gtk_container_add (GTK_CONTAINER (vbuttonbox1), BT_UNDO);
  gtk_widget_set_usize (BT_UNDO, -2, 30);
  GTK_WIDGET_SET_FLAGS (BT_UNDO, GTK_CAN_DEFAULT);

  BT_FORCEMOVE = gtk_button_new_with_mnemonic (_("Force Move"));
  gtk_widget_show (BT_FORCEMOVE);
  gtk_container_add (GTK_CONTAINER (vbuttonbox1), BT_FORCEMOVE);
  gtk_widget_set_usize (BT_FORCEMOVE, 106, 30);
  GTK_WIDGET_SET_FLAGS (BT_FORCEMOVE, GTK_CAN_DEFAULT);

  BT_AUTOFINISH = gtk_button_new_with_mnemonic (_("Autofinish"));
  gtk_widget_show (BT_AUTOFINISH);
  gtk_container_add (GTK_CONTAINER (vbuttonbox1), BT_AUTOFINISH);
  gtk_widget_set_usize (BT_AUTOFINISH, -2, 30);
  GTK_WIDGET_SET_FLAGS (BT_AUTOFINISH, GTK_CAN_DEFAULT);

  hbox12 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox12);
  gtk_box_pack_start (GTK_BOX (vbox9), hbox12, TRUE, TRUE, 0);

  scrolledwindow6 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow6);
  gtk_box_pack_start (GTK_BOX (hbox11), scrolledwindow6, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow6), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  textview1 = gtk_text_view_new ();
  gtk_widget_show (textview1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow6), textview1);
  gtk_widget_set_usize (textview1, 120, -2);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (textview1), FALSE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textview1), FALSE);

  statusbar1 = gtk_statusbar_new ();
  gtk_widget_show (statusbar1);
  gtk_box_pack_start (GTK_BOX (vbox1), statusbar1, FALSE, FALSE, 0);

  gtk_signal_connect (GTK_OBJECT (GamazonsMain), "destroy",
                      GTK_SIGNAL_FUNC (on_GamazonsMain_destroy),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (BT_UNDO), "clicked",
                      GTK_SIGNAL_FUNC (on_BT_UNDO_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (BT_FORCEMOVE), "clicked",
                      GTK_SIGNAL_FUNC (on_BT_FORCEMOVE_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (BT_AUTOFINISH), "clicked",
                      GTK_SIGNAL_FUNC (on_BT_AUTOFINISH_clicked),
                      NULL);

  atko = gtk_widget_get_accessible (CNVS_GAMEBOARD);
  atk_object_set_name (atko, _("CNVS_GAMEBOARD"));


  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (GamazonsMain, GamazonsMain, "GamazonsMain");
  GLADE_HOOKUP_OBJECT (GamazonsMain, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, menubar1, "menubar1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, menubar1_uiinfo[0].widget, "file1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, file1_menu_uiinfo[0].widget, "new1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, file1_menu_uiinfo[1].widget, "separator1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, file1_menu_uiinfo[2].widget, "quit1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, menubar1_uiinfo[1].widget, "preferences1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, preferences1_menu_uiinfo[0].widget, "network1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, preferences1_menu_uiinfo[1].widget, "player1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, preferences1_menu_uiinfo[2].widget, "theme1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, menubar1_uiinfo[2].widget, "help1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, help1_menu_uiinfo[0].widget, "how_to_play1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, help1_menu_uiinfo[1].widget, "about1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, scrolledwindow1, "scrolledwindow1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, viewport1, "viewport1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, scrolledwindow2, "scrolledwindow2");
  GLADE_HOOKUP_OBJECT (GamazonsMain, viewport2, "viewport2");
  GLADE_HOOKUP_OBJECT (GamazonsMain, table1, "table1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, hbox9, "hbox9");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label30, "label30");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label31, "label31");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label32, "label32");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label33, "label33");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label34, "label34");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label35, "label35");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label36, "label36");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label37, "label37");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label38, "label38");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label39, "label39");
  GLADE_HOOKUP_OBJECT (GamazonsMain, vbox7, "vbox7");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label29, "label29");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label28, "label28");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label27, "label27");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label26, "label26");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label25, "label25");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label24, "label24");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label23, "label23");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label22, "label22");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label21, "label21");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label20, "label20");
  GLADE_HOOKUP_OBJECT (GamazonsMain, vbox8, "vbox8");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label40, "label40");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label41, "label41");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label42, "label42");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label43, "label43");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label44, "label44");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label45, "label45");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label46, "label46");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label47, "label47");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label48, "label48");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label49, "label49");
  GLADE_HOOKUP_OBJECT (GamazonsMain, hbox10, "hbox10");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label10, "label10");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label11, "label11");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label12, "label12");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label13, "label13");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label14, "label14");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label15, "label15");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label16, "label16");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label17, "label17");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label18, "label18");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label19, "label19");
  GLADE_HOOKUP_OBJECT (GamazonsMain, scrolledwindow4, "scrolledwindow4");
  GLADE_HOOKUP_OBJECT (GamazonsMain, CNVS_GAMEBOARD, "CNVS_GAMEBOARD");
  GLADE_HOOKUP_OBJECT (GamazonsMain, vbox2, "vbox2");
  GLADE_HOOKUP_OBJECT (GamazonsMain, vbox3, "vbox3");
  GLADE_HOOKUP_OBJECT (GamazonsMain, vbox4, "vbox4");
  GLADE_HOOKUP_OBJECT (GamazonsMain, label1, "label1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, scrolledwindow3, "scrolledwindow3");
  GLADE_HOOKUP_OBJECT (GamazonsMain, viewport3, "viewport3");
  GLADE_HOOKUP_OBJECT (GamazonsMain, hbox11, "hbox11");
  GLADE_HOOKUP_OBJECT (GamazonsMain, scrolledwindow5, "scrolledwindow5");
  GLADE_HOOKUP_OBJECT (GamazonsMain, viewport4, "viewport4");
  GLADE_HOOKUP_OBJECT (GamazonsMain, vbox9, "vbox9");
  GLADE_HOOKUP_OBJECT (GamazonsMain, vbuttonbox1, "vbuttonbox1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, BT_UNDO, "BT_UNDO");
  GLADE_HOOKUP_OBJECT (GamazonsMain, BT_FORCEMOVE, "BT_FORCEMOVE");
  GLADE_HOOKUP_OBJECT (GamazonsMain, BT_AUTOFINISH, "BT_AUTOFINISH");
  GLADE_HOOKUP_OBJECT (GamazonsMain, hbox12, "hbox12");
  GLADE_HOOKUP_OBJECT (GamazonsMain, scrolledwindow6, "scrolledwindow6");
  GLADE_HOOKUP_OBJECT (GamazonsMain, textview1, "textview1");
  GLADE_HOOKUP_OBJECT (GamazonsMain, statusbar1, "statusbar1");

  return GamazonsMain;
}

GtkWidget*
create_PlayerSettings (void)
{
  GtkWidget *PlayerSettings;
  GtkWidget *vbox5;
  GtkWidget *hbox3;
  GtkWidget *WhitePlayerLabel;
  GtkWidget *WhiteHumanRadio;
  GSList *WhiteHumanRadio_group = NULL;
  GtkWidget *WhiteAIRadio;
  GtkWidget *hbox4;
  GtkWidget *BlackPlayerLabel;
  GtkWidget *BlackHumanRadio;
  GSList *BlackHumanRadio_group = NULL;
  GtkWidget *BlackAIRadio;
  GtkWidget *hseparator1;
  GtkWidget *AISettings;
  GtkWidget *hbox5;
  GtkWidget *vbox6;
  GtkWidget *hbox6;
  GtkWidget *TimeLabel;
  GtkWidget *SearchDepthLabel;
  GtkWidget *SearchWidthLabel;
  GtkWidget *hbox7;
  GtkObject *TimeSpinner_adj;
  GtkWidget *TimeSpinner;
  GtkObject *DepthSpinner_adj;
  GtkWidget *DepthSpinner;
  GtkObject *WidthSpinner_adj;
  GtkWidget *WidthSpinner;
  GtkWidget *hbuttonbox3;
  GtkWidget *PlayerOKButton;
  GtkWidget *PlayerCancelButton;
  GtkWidget *alignment1;
  GtkWidget *hbox8;
  GtkWidget *image1;
  GtkWidget *label9;

  PlayerSettings = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_usize (PlayerSettings, 370, 185);
  gtk_window_set_title (GTK_WINDOW (PlayerSettings), _("Player Settings"));
  gtk_window_set_default_size (GTK_WINDOW (PlayerSettings), 300, 185);
  gtk_window_set_resizable (GTK_WINDOW (PlayerSettings), FALSE);

  vbox5 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox5);
  gtk_container_add (GTK_CONTAINER (PlayerSettings), vbox5);
  gtk_widget_set_usize (vbox5, -2, 70);

  hbox3 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox3);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox3, TRUE, TRUE, 0);
  gtk_widget_set_usize (hbox3, -2, 2);

  WhitePlayerLabel = gtk_label_new (_("White Player:"));
  gtk_widget_show (WhitePlayerLabel);
  gtk_box_pack_start (GTK_BOX (hbox3), WhitePlayerLabel, FALSE, FALSE, 0);
  gtk_widget_set_usize (WhitePlayerLabel, 100, -2);
  gtk_label_set_justify (GTK_LABEL (WhitePlayerLabel), GTK_JUSTIFY_LEFT);
  gtk_misc_set_alignment (GTK_MISC (WhitePlayerLabel), 0.3, 0.5);

  WhiteHumanRadio = gtk_radio_button_new_with_mnemonic (NULL, _("Human"));
  gtk_widget_show (WhiteHumanRadio);
  gtk_box_pack_start (GTK_BOX (hbox3), WhiteHumanRadio, FALSE, FALSE, 0);
  gtk_widget_set_usize (WhiteHumanRadio, 85, -2);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (WhiteHumanRadio), WhiteHumanRadio_group);
  WhiteHumanRadio_group = gtk_radio_button_group (GTK_RADIO_BUTTON (WhiteHumanRadio));

  WhiteAIRadio = gtk_radio_button_new_with_mnemonic (NULL, _("AI"));
  gtk_widget_show (WhiteAIRadio);
  gtk_box_pack_start (GTK_BOX (hbox3), WhiteAIRadio, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (WhiteAIRadio), WhiteHumanRadio_group);
  WhiteHumanRadio_group = gtk_radio_button_group (GTK_RADIO_BUTTON (WhiteAIRadio));

  hbox4 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox4);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox4, TRUE, TRUE, 0);
  gtk_widget_set_usize (hbox4, -2, 2);

  BlackPlayerLabel = gtk_label_new (_("Black Player: "));
  gtk_widget_show (BlackPlayerLabel);
  gtk_box_pack_start (GTK_BOX (hbox4), BlackPlayerLabel, FALSE, FALSE, 0);
  gtk_widget_set_usize (BlackPlayerLabel, 100, -2);
  gtk_label_set_justify (GTK_LABEL (BlackPlayerLabel), GTK_JUSTIFY_LEFT);

  BlackHumanRadio = gtk_radio_button_new_with_mnemonic (NULL, _("Human"));
  gtk_widget_show (BlackHumanRadio);
  gtk_box_pack_start (GTK_BOX (hbox4), BlackHumanRadio, FALSE, FALSE, 0);
  gtk_widget_set_usize (BlackHumanRadio, 85, -2);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (BlackHumanRadio), BlackHumanRadio_group);
  BlackHumanRadio_group = gtk_radio_button_group (GTK_RADIO_BUTTON (BlackHumanRadio));

  BlackAIRadio = gtk_radio_button_new_with_mnemonic (NULL, _("AI"));
  gtk_widget_show (BlackAIRadio);
  gtk_box_pack_start (GTK_BOX (hbox4), BlackAIRadio, FALSE, FALSE, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (BlackAIRadio), BlackHumanRadio_group);
  BlackHumanRadio_group = gtk_radio_button_group (GTK_RADIO_BUTTON (BlackAIRadio));

  hseparator1 = gtk_hseparator_new ();
  gtk_widget_show (hseparator1);
  gtk_box_pack_start (GTK_BOX (vbox5), hseparator1, TRUE, TRUE, 0);
  gtk_widget_set_usize (hseparator1, -2, 1);

  AISettings = gtk_label_new (_("AI Settings:"));
  gtk_widget_show (AISettings);
  gtk_box_pack_start (GTK_BOX (vbox5), AISettings, FALSE, FALSE, 0);
  gtk_widget_set_usize (AISettings, -2, 15);
  gtk_label_set_justify (GTK_LABEL (AISettings), GTK_JUSTIFY_LEFT);

  hbox5 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox5);
  gtk_box_pack_start (GTK_BOX (vbox5), hbox5, TRUE, TRUE, 0);

  vbox6 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox6);
  gtk_box_pack_start (GTK_BOX (hbox5), vbox6, TRUE, TRUE, 0);
  gtk_widget_set_usize (vbox6, -2, 28);

  hbox6 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox6);
  gtk_box_pack_start (GTK_BOX (vbox6), hbox6, TRUE, TRUE, 0);

  TimeLabel = gtk_label_new (_("Search Time: "));
  gtk_widget_show (TimeLabel);
  gtk_box_pack_start (GTK_BOX (hbox6), TimeLabel, FALSE, FALSE, 0);
  gtk_widget_set_usize (TimeLabel, 121, -2);
  gtk_label_set_justify (GTK_LABEL (TimeLabel), GTK_JUSTIFY_LEFT);

  SearchDepthLabel = gtk_label_new (_("Max Search Depth"));
  gtk_widget_show (SearchDepthLabel);
  gtk_box_pack_start (GTK_BOX (hbox6), SearchDepthLabel, FALSE, FALSE, 0);
  gtk_widget_set_usize (SearchDepthLabel, 127, -2);

  SearchWidthLabel = gtk_label_new (_("Max Search Width"));
  gtk_widget_show (SearchWidthLabel);
  gtk_box_pack_start (GTK_BOX (hbox6), SearchWidthLabel, FALSE, FALSE, 0);
  gtk_widget_set_usize (SearchWidthLabel, 112, -2);
  gtk_label_set_justify (GTK_LABEL (SearchWidthLabel), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (SearchWidthLabel), 1, 0.5);

  hbox7 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox7);
  gtk_box_pack_start (GTK_BOX (vbox6), hbox7, TRUE, TRUE, 0);

  TimeSpinner_adj = gtk_adjustment_new (5, 1, 100, 1, 10, 10);
  TimeSpinner = gtk_spin_button_new (GTK_ADJUSTMENT (TimeSpinner_adj), 1, 0);
  gtk_widget_show (TimeSpinner);
  gtk_box_pack_start (GTK_BOX (hbox7), TimeSpinner, TRUE, TRUE, 10);
  gtk_widget_set_usize (TimeSpinner, 10, -2);

  DepthSpinner_adj = gtk_adjustment_new (0, 0, 100, 1, 10, 10);
  DepthSpinner = gtk_spin_button_new (GTK_ADJUSTMENT (DepthSpinner_adj), 1, 0);
  gtk_widget_show (DepthSpinner);
  gtk_box_pack_start (GTK_BOX (hbox7), DepthSpinner, TRUE, TRUE, 10);
  gtk_widget_set_usize (DepthSpinner, 10, -2);

  WidthSpinner_adj = gtk_adjustment_new (0, 0, 3000, 1, 10, 10);
  WidthSpinner = gtk_spin_button_new (GTK_ADJUSTMENT (WidthSpinner_adj), 1, 0);
  gtk_widget_show (WidthSpinner);
  gtk_box_pack_start (GTK_BOX (hbox7), WidthSpinner, TRUE, TRUE, 10);
  gtk_widget_set_usize (WidthSpinner, 10, -2);

  hbuttonbox3 = gtk_hbutton_box_new ();
  gtk_widget_show (hbuttonbox3);
  gtk_box_pack_start (GTK_BOX (vbox5), hbuttonbox3, TRUE, TRUE, 0);
  gtk_widget_set_usize (hbuttonbox3, -2, 25);
  gtk_container_set_border_width (GTK_CONTAINER (hbuttonbox3), 39);
  gtk_button_box_set_spacing (GTK_BUTTON_BOX (hbuttonbox3), 0);

  PlayerOKButton = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (PlayerOKButton);
  gtk_container_add (GTK_CONTAINER (hbuttonbox3), PlayerOKButton);
  gtk_widget_set_usize (PlayerOKButton, 50, -2);
  gtk_container_set_border_width (GTK_CONTAINER (PlayerOKButton), 10);
  GTK_WIDGET_SET_FLAGS (PlayerOKButton, GTK_CAN_DEFAULT);

  PlayerCancelButton = gtk_button_new ();
  gtk_widget_show (PlayerCancelButton);
  gtk_container_add (GTK_CONTAINER (hbuttonbox3), PlayerCancelButton);
  gtk_container_set_border_width (GTK_CONTAINER (PlayerCancelButton), 10);
  GTK_WIDGET_SET_FLAGS (PlayerCancelButton, GTK_CAN_DEFAULT);

  alignment1 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment1);
  gtk_container_add (GTK_CONTAINER (PlayerCancelButton), alignment1);

  hbox8 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox8);
  gtk_container_add (GTK_CONTAINER (alignment1), hbox8);

  image1 = gtk_image_new_from_stock ("gtk-cancel", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image1);
  gtk_box_pack_start (GTK_BOX (hbox8), image1, FALSE, FALSE, 0);

  label9 = gtk_label_new_with_mnemonic (_("Cancel"));
  gtk_widget_show (label9);
  gtk_box_pack_start (GTK_BOX (hbox8), label9, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label9), GTK_JUSTIFY_LEFT);

  gtk_signal_connect (GTK_OBJECT (PlayerOKButton), "clicked",
                      GTK_SIGNAL_FUNC (on_PlayerOKButton_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (PlayerCancelButton), "clicked",
                      GTK_SIGNAL_FUNC (on_PlayerCancelButton_clicked),
                      NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (PlayerSettings, PlayerSettings, "PlayerSettings");
  GLADE_HOOKUP_OBJECT (PlayerSettings, vbox5, "vbox5");
  GLADE_HOOKUP_OBJECT (PlayerSettings, hbox3, "hbox3");
  GLADE_HOOKUP_OBJECT (PlayerSettings, WhitePlayerLabel, "WhitePlayerLabel");
  GLADE_HOOKUP_OBJECT (PlayerSettings, WhiteHumanRadio, "WhiteHumanRadio");
  GLADE_HOOKUP_OBJECT (PlayerSettings, WhiteAIRadio, "WhiteAIRadio");
  GLADE_HOOKUP_OBJECT (PlayerSettings, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT (PlayerSettings, BlackPlayerLabel, "BlackPlayerLabel");
  GLADE_HOOKUP_OBJECT (PlayerSettings, BlackHumanRadio, "BlackHumanRadio");
  GLADE_HOOKUP_OBJECT (PlayerSettings, BlackAIRadio, "BlackAIRadio");
  GLADE_HOOKUP_OBJECT (PlayerSettings, hseparator1, "hseparator1");
  GLADE_HOOKUP_OBJECT (PlayerSettings, AISettings, "AISettings");
  GLADE_HOOKUP_OBJECT (PlayerSettings, hbox5, "hbox5");
  GLADE_HOOKUP_OBJECT (PlayerSettings, vbox6, "vbox6");
  GLADE_HOOKUP_OBJECT (PlayerSettings, hbox6, "hbox6");
  GLADE_HOOKUP_OBJECT (PlayerSettings, TimeLabel, "TimeLabel");
  GLADE_HOOKUP_OBJECT (PlayerSettings, SearchDepthLabel, "SearchDepthLabel");
  GLADE_HOOKUP_OBJECT (PlayerSettings, SearchWidthLabel, "SearchWidthLabel");
  GLADE_HOOKUP_OBJECT (PlayerSettings, hbox7, "hbox7");
  GLADE_HOOKUP_OBJECT (PlayerSettings, TimeSpinner, "TimeSpinner");
  GLADE_HOOKUP_OBJECT (PlayerSettings, DepthSpinner, "DepthSpinner");
  GLADE_HOOKUP_OBJECT (PlayerSettings, WidthSpinner, "WidthSpinner");
  GLADE_HOOKUP_OBJECT (PlayerSettings, hbuttonbox3, "hbuttonbox3");
  GLADE_HOOKUP_OBJECT (PlayerSettings, PlayerOKButton, "PlayerOKButton");
  GLADE_HOOKUP_OBJECT (PlayerSettings, PlayerCancelButton, "PlayerCancelButton");
  GLADE_HOOKUP_OBJECT (PlayerSettings, alignment1, "alignment1");
  GLADE_HOOKUP_OBJECT (PlayerSettings, hbox8, "hbox8");
  GLADE_HOOKUP_OBJECT (PlayerSettings, image1, "image1");
  GLADE_HOOKUP_OBJECT (PlayerSettings, label9, "label9");

  return PlayerSettings;
}

