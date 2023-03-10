// ---- view.c ----
/**
 * @brief Implementation of View for a Connect 4 program
 */
struct view_t{
   Model *mp;
   GtkWidget *table;
   GdkPixbuf *pixBClassic[IMAGES_NUMBER];
   GdkPixbuf *pixBToasts[IMAGES_NUMBER];
   GtkWidget *pHBoxGrid;
   GtkWidget *pLabelScore;
   GtkWidget *pLabelMessage;
};

// ---- view.h ----
/**
 * @brief Declaration of the opaque type View
 *
 */
typedef struct view_t View;
