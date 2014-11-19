#include <gnome.h>


void
on_new1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_as1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_quit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_cut1_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_copy1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_paste1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_clear1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_properties1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_preferences1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_undo_move2_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_redo_move3_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_network1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_player1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_how_to_play1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_help2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_BT_UNDO_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_BT_FORCEMOVE_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_BT_AUTOFINISH_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_GamazonsMain_destroy                (GtkObject       *object,
                                        gpointer         user_data);

int
board_press_cb (GnomeCanvasItem *item, GdkEvent *event, gpointer data);

int arrow_fire_cb(GnomeCanvasItem *item, GdkEvent *event, gpointer data);