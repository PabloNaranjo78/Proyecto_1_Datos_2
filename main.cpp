#include <gtkmm.h>

using namespace Gtk;

int main(int argc, char *argv[])
{
    // Inicialización GTK
    Main entorno(argc, argv);

    // Declaración de objetos
    Window ventana;
    Label etiqueta;

    // Características de la ventana
    ventana.set_title("Hola Mundo!");
    ventana.set_border_width(5);
    ventana.set_default_size(400, 200);

    // Etiqueta
    etiqueta.set_text("Hola Mundo!!");
    ventana.add(etiqueta);

    // Mostrar
    ventana.show_all_children();

    entorno.run(ventana);

    return 0;
}