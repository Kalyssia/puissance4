//---- controller.c ----
/**
 * @brief Implementation of the controller for the Connect 4
 */
struct controller_t{
   Model *mp;
   View *vp;
   GtkWidget **pGameButtons;
};

//---- controller.h ----

/**
 * @brief Declaration of the Controller (opaque type)
 */
typedef struct controller_t Controller;
