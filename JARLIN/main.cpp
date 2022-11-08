#include <iostream>
#include <list>
#include <string>
#include <array>
#include <map>

using namespace std;
void puestoMasFrecuente();
void distribucionPuesto();
void SolicitarDatosPersona();
class Puesto;
Puesto SolicitarDatosPuesto();
class Formacion;
Formacion SolicitarDatosFormacion();
void SolicitarDatosActividad();
void SolicitarDatosSubActividad();
void ImprimirPersona(bool imprimirActividades);
void ImprimirSubActividad();
void BorrarDatosUsuario();
void BorrarDatosTiempoSubActividad();
void Menu();
class Puesto;
class Persona;
Persona *buscarPersona(string basicString);
class Formacion;
class Actividad;
Actividad *nombreActividadExiste(string basicString);
class SubActividad;
SubActividad *getSubActividad(string basicString);
void datosQuemados();
void BorrarDatosUsuario();
void formacionMasFrecuente();
void mayorMenorTiempo();
void TiempoSubActividad();
void actividadesSinTiempo();
void distribucionTiempo();
void distribucionFormacion();
void distribucionInternet();
void imprimirListas();

struct Puesto {
    string nombre;
    double salario;
};

struct Formacion {
    string titulo;
    char band;
};

struct Tiempo {
    string subActividad = "";
    int mes;
    int dia;
    string hora;
    int horas = 0;
    int minutos = 0;
};

struct SubActividad {
    string nombre;
    Tiempo tiempo;
};
list<SubActividad> ListaSubActividad;

struct Actividad {
    string nombre;
    list<SubActividad> SubListaActividad = list<SubActividad>(); // SUBLISTA
};
list<Actividad> listaActividad;

struct Persona {
    string nombre;
    int cedula;
    int edad;
    string lugarResidencia;
    // RELACIONES CON OTRAS ESTRUCTURAS
    Puesto puesto;
    Formacion formacion;//SUBLISTA
    list<Actividad> listaActividad = list<Actividad>(); //SUBLISTA
    list<Tiempo> listaHoras = list<Tiempo>(); //SUBLISTA
};
list<Persona> listaPersona;

// ************************************ INSERCION Y ACTUALIZACION DE INFORMACION *******************************************

// FUNCION PARA ORDENAR LOS NOMBRES EN LA LISTA PERSONA
bool OrdenarNombre(Persona const &first, Persona const &second) {
    return (first.nombre < second.nombre);
}


// INSERTAR DATOS A LA LISTA PERSONA
void
InsertarDatosPersona(string nombre, int cedula, int edad, string lugarResidencia, Formacion formacion, Puesto puesto) {
    Persona p = {nombre, cedula, edad, lugarResidencia, puesto, formacion};
    listaPersona.push_front(p);
    listaPersona.sort(OrdenarNombre);
}

//  SOLICITAR DATOS A LA LISTA PERSONA
void SolicitarDatosPersona() {
    string nombre, lugarResidencia;
    int cedula, edad;
    cout << endl;
    cout << "\t.:UTILICE _ EN LUGAR DE ESPACIOS:.\n";
    cout << "\n\tINGRESE EL NOMBRE DEL USUARIO: ";
    cin >> nombre;
    cout << "\n\tINGRESE LA CEDULA: ";
    cin >> cedula;
    cout << "\n\tINGRESE LA EDAD: ";
    cin >> edad;
    cout << "\n\tINGRESE EL LUGAR DE RESIDENCIA: ";
    cin >> lugarResidencia;

    Formacion formacion = SolicitarDatosFormacion();
    Puesto puesto = SolicitarDatosPuesto();
    InsertarDatosPersona(nombre, cedula, edad, lugarResidencia, formacion, puesto);
}

//  SOLICITAR DATOS A LA LISTA PUESTO
Puesto SolicitarDatosPuesto() {
    string nombre;
    float salario;

    cout << "\n\tINGRESE EL NOMBRE DEL PUESTO: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "\n\tINGRESE EL SALARIO MENSUAL DEL USUARIO: ";
    cin >> salario;
    Puesto p = {nombre, salario};
    return p;
}

Formacion SolicitarDatosFormacion() {
    string nombre;
    char completo;

    cout << "\n\tINGRESE EL NOMBRE DE LA FORMACION: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "\n\tIngrese T si es una formacion completa, de lo contario ingrese F: ";
    cin >> completo;
    Formacion f = {nombre, completo};
    return f;
}

// INSERTAR DATOS A LA LISTA ACTIVIDAD
void InsertarDatosActividad(string nombre) {
    Actividad a = {nombre};
    listaActividad.push_back(a);
}

//  SOLICITAR DATOS A LA LISTA ACTIVIDAD
void SolicitarDatosActividad() {
    string nombre;
    cout << "\t\t\tINGRESE EL NOMBRE DE LA ACTIVIDAD: ";
    cin >> nombre;
    InsertarDatosActividad(nombre);
}

// INSERTAR DATOS A LA LISTA ACTIVIDAD
void InsertarDatosSubActividad(string nombre) {
    SubActividad sA = {nombre};
    ListaSubActividad.push_front(sA);
}

//  SOLICITAR DATOS A LA LISTA ACTIVIDAD
void SolicitarDatosSubActividad() {
    // solicitar datos de la actividad
    string nombre;
    cout << "\t\t\tINGRESE EL NOMBRE DE LA SUB-ACTIVIDAD : ";
    cin >> nombre;
    InsertarDatosSubActividad(nombre);
}

// ************************************ IMPRIMIR DATOS QUE CADA UNA DE LAS LISTAS Y SUBLISTAS *******************************************

// IMPRIMIR LISTA PERSONA
void ImprimirPersona(bool imprimirActividades) {//IMPRIME LOS DATOS DE LA LISTA PERSONA
    list<Persona>::iterator posP = listaPersona.begin();
    while (posP != listaPersona.end()) {//RECORRE LA LISTA PERSONA
        cout << "\nNombre: " << posP->nombre << "\nCedula:" << posP->cedula
             << "\nEdad: " << posP->edad << "\nLugar de Residencia: " << posP->lugarResidencia
             << "\nPuesto: " << posP->puesto.nombre << " Salario: " << posP->puesto.salario
             << "\nFormacion: " << posP->formacion.titulo << " Completo: " << to_string(posP->formacion.band) << endl;
        if (imprimirActividades) {//IMPRIME LOS DATOS DE LA LISTA ACTIVIDAD SI "imprimirActividades" ES VERDADERO
            cout << "\tActividades: \n";
            list<Actividad>::iterator posA = posP->listaActividad.begin();
            while (posA != posP->listaActividad.end()) {//RECORRE LA LISTA ACTIVIDAD
                cout << "\t\t--> Nombre Actividad: " << posA->nombre << " ";

                cout << "\t\tSub-Actividades: " << endl;
                list<SubActividad>::iterator posSA = posA->SubListaActividad.begin();
                while (posSA != posA->SubListaActividad.end()) {//RECORRE LA LISTA SUB-ACTIVIDAD
                    cout << "\t\t\tNombre: " << posSA->nombre << "   Horas: " << posSA->tiempo.horas << "   Minutos: "
                         << posSA->tiempo.minutos << endl;
                    posSA++;
                }
                posA++;
            }
            cout << endl;
        }
        posP++;
    }
}

// IMPRIMIR LISTA ACTIVIDAD
void ImprimirActividad(list<Actividad> lista) {
    // imprimir actividades
    list<Actividad>::iterator posA = lista.begin();
    while (posA != lista.end()) {
        cout << "Nombre: " << posA->nombre << endl;
        posA++;
    }
}

// IMPRIMIR LISTA SUB-ACTIVIDAD
void ImprimirSubActividad() {
    // imprime lista subactividades
    list<SubActividad>::iterator possA = ListaSubActividad.begin();
    while (possA != ListaSubActividad.end()) {
        cout << "\n\t\t\tNombre: " << possA->nombre << endl;
        possA++;
    }
}

// FUNCION PARA BORRAR DATOS DE LA INFORMACION PERSONAL DE UN USUARIO DADO
void BorrarDatosUsuario() {
    // validar que no hayan datos repetidos con la funcion unique (strings)
    string nombre;
    cout << "\n\tIngrese el nombre del usuario que desea eliminar: ";
    cin.ignore();
    getline(cin, nombre);
    // buscar la persona a borrar
    Persona *p = buscarPersona(nombre);
    if (p != NULL) {//se encontró persona
        list<Persona>::iterator posP = listaPersona.begin();
        while (posP != listaPersona.end()) {//recorrer lista
            if (posP->nombre == nombre) {
                listaPersona.erase(posP);//borrar persona
                break;
            }
            posP++;
        }
        cout << "\n\t.:Usuario borrado exitosamente:." << endl;
    } else {//no se encontró persona
        cout << "\n\t.:Usuario no encontrado:." << endl;
    }
    return;

}

// FUNCION PARA BORRAR DATOS DEL TIEMPO DE UNA SUBACTIVIDAD DE UN USUARIO DADO
void BorrarDatosTiempoSubActividad() {
    /*
     * 1. Buscar el usuario
     * 2. Buscar la subactividad
     * 3. Borrar el tiempo
     */
    ImprimirPersona(false);

    string nombre;
    string subActividad;
    bool borrado = false;
    cout << "\nIngrese el nombre del usuario: ";
    cin.ignore();
    getline(cin, nombre);
    Persona *p = buscarPersona(nombre);//buscar persona
    if (p != NULL) {//si la persona existe
        cout << "\n\tIngrese el nombre de la sub-Actividad: ";
        getline(cin, subActividad);
        list<Actividad>::iterator posA = p->listaActividad.begin();
        while (posA != p->listaActividad.end()) {//buscar actividad
            list<SubActividad>::iterator posSA = posA->SubListaActividad.begin();//buscar subactividad
            while (posSA != posA->SubListaActividad.end()) {
                if (posSA->nombre == subActividad) {//comparar subactividad
                    //se pone en ceros para indicar que está borrado
                    list<Tiempo>::iterator posT = p->listaHoras.begin();
                    while (posT != p->listaHoras.end()) {
                        if (posT->subActividad == subActividad) {
                            p->listaHoras.erase(posT);//borrar tiempo de lista hora
                            break;
                        }
                        posT++;
                    }
                    Tiempo tiempo = {"", 0, 0, "", 0, 0};//crear tiempo vacío
                    posSA->tiempo = tiempo;//asignar tiempo vacío
                    cout << "\n.:Sub-Actividad borrada exitosamente:." << endl;
                    borrado = true;//indicar que se borró
                    break;
                }
                posSA++;
            }
            if (borrado == true) {//si se borró, salir del while
                break;
            }
            posA++;
        }
        if (borrado == false) {//si no se borró, indicar que no se encontró
            cout << "\n.:Sub-Actividad no encontrada:." << endl;
        }
    } else {
        cout << "\n\t.:Usuario no encontrado:." << endl;//si no se encontró, indicar que no se encontró
    }

}

// *********************************************** MENU DE OPCIONES ***********************************************

void Menu() {
    int opc = 0; // GUARDAR DATO DE SELECCION EN MENU GENERAL
    int menu1 = 0, menu2 = 0, menu3 = 0, sub_menu1 = 0, sub_menu2 = 0; // GUARDAR DATO DE SELECCION EN SUB_MENUS
    while (true) {
        cout << "\n";
        cout << "\t\t\t----------------------------------------------------------------------" << endl;
        cout << "\t\t\t|                           MENU DE OPCIONES                         |" << endl;
        cout << "\t\t\t|                                                                    |" << endl;
        cout << "\t\t\t|                          1.INSERTAR DATOS                          |" << endl;
        cout << "\t\t\t|                          2.INSERTAR A USUARIO                      |" << endl;
        cout << "\t\t\t|                          3.MODIFICAR DATOS                         |" << endl;
        cout << "\t\t\t|                          4.ELIMINAR DATOS                          |" << endl;
        cout << "\t\t\t|                          5.CONSULTAS                               |" << endl;
        cout << "\t\t\t|                          6.REPORTES                                |" << endl;
        cout << "\t\t\t|                          7.SALIR                                   |" << endl;
        cout << "\t\t\t|                                                                    |" << endl;
        cout << "\t\t\t----------------------------------------------------------------------" << endl;
        cout << "\n\t\t\tDIGITE LA OPCION DESEADA: ";
        cin >> opc;

        // CONDICIONAL PARA LA INSERCION DE DATOS DE TODAS LAS LISTAS Y SUBLISTAS
        if (opc == 1) {
            cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 1>" << endl;
            cout << "\n\n";
            cout << "\t\t\t----------------------------------------------------------------------" << endl;
            cout << "\t\t\t|                                                                    |" << endl;
            cout << "\t\t\t|             1.INSERTAR DATOS EN LA LISTA PERSONA                   |" << endl;
            cout << "\t\t\t|             2.INSERTAR DATOS EN LA LISTA ACTIVIDAD                 |" << endl;
            cout << "\t\t\t|             3.INSERTAR DATOS EN LA LISTA SUB-ACTIVIDAD             |" << endl;
            cout << "\t\t\t|                                                                    |" << endl;
            cout << "\t\t\t----------------------------------------------------------------------" << endl;
            cout << "\n\t\t\t<<DIGITE LA OPCION DESEADA>> ";
            cin >> menu1;


            if (menu1 == 1) {
                cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 1>" << endl;
                SolicitarDatosPersona();
                cout << "\t\t\t<HA AGREGADO UNA PERSONA CON EXITO>" << endl;
                cout << "\n\n";
            } else if (menu1 == 2) {
                cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 4>" << endl;
                ImprimirActividad(listaActividad);
                SolicitarDatosActividad();

                Menu();
            } else if (menu1 == 3) {
                cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 5>" << endl;
                ImprimirSubActividad();
                SolicitarDatosSubActividad();

                cout << "\n\n";
            } else if (menu1 >= 4 || menu1 <= 0) {
                cout << "\t\t\t<USTED HA DIGITADO UNA OPCION FUERA DE RANGO>" << endl;
                cout << "\n\n";
            }

        }
        if (opc == 2) {
            cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 2>" << endl;
            ImprimirPersona(false);
            string nombre;
            cout << "INGRESE EL NOMBRE DE LA PERSONA POR FAVOR: \n";
            cin.ignore();
            getline(cin, nombre);
            Persona *p = buscarPersona(nombre);
            if (p == NULL) {
                cout << "\t\t\t<USTED HA DIGITADO UN NOMBRE NO EXISTENTE\n>" << endl;
                Menu();
            }
            cout << "\n\n";
            cout << "\t\t\t----------------------------------------------------------------------" << endl;
            cout << "\t\t\t|                                                                     |" << endl;
            cout << "\t\t\t|             1.INSERTAR FORMACION                                    |" << endl;
            cout << "\t\t\t|             2.INSERTAR PUESTO                                       |" << endl;
            cout << "\t\t\t|             3.INSERTAR ACTIVIDAD                                    |" << endl;
            cout << "\t\t\t|             4.INSERTAR SUB-ACTIVIDAD                                |" << endl;
            cout << "\t\t\t|                                                                     |" << endl;
            cout << "\t\t\t----------------------------------------------------------------------" << endl;
            cout << "\t\t<<DIGITE LA OPCION DESEADA: ";
            cin >> sub_menu1;
            if (sub_menu1 == 2) {
                cout << "\nPUESTO ACTUAL: " << p->puesto.nombre << " Salario: " << p->puesto.salario << endl;

                Puesto puesto = SolicitarDatosPuesto();
                p->puesto = puesto;
                cout << "\t\t\t<USTED HA MODIFICADO EL PUESTO DE LA PERSONA CON EXITO>" << endl;

                Menu();
            } else if (sub_menu1 == 1) {
                cout << "\nFORMACION ACTUAL: " << p->formacion.titulo << " COMPLETO: " << p->formacion.band << endl;
                Formacion formacion = SolicitarDatosFormacion();
                p->formacion = formacion;
                cout << "\t\t\t<USTED HA MODIFICADO EL PUESTO DE LA PERSONA CON EXITO>" << endl;

                Menu();
            } else if (sub_menu1 == 3) {
                cout << "ACTIVIDADES DISPONIBLES: " << endl;
                ImprimirActividad(listaActividad);
                cout << "\nACTIVIDADES ACTUALES: " << endl;
                ImprimirActividad(p->listaActividad);
                cout << "\nINGRESE EL NOMBRE DE LA NUEVA ACTIVIDAD: ";
                string nombreActividad;
                cin.ignore();
                getline(cin, nombreActividad);
                Actividad *existe = nombreActividadExiste(
                        nombreActividad);//BUSCA SI EXISTE LA ACTIVIDAD EN LA LISTA GRANDE
                if (existe == NULL) {
                    cout << "\t\t\t<USTED HA DIGITADO UNA ACTIVIDAD NO EXISTENTE\n>" << endl;
                    Menu();
                } else {
                    p->listaActividad.push_back(*existe);//SE CREA EL ENOACE
                    cout << "\t\t\t<USTED HA AGREGADO LA ACTIVIDAD A LA PERSONA>" << endl;

                }
                Menu();
            } else if (sub_menu1 == 4) {
                cout << "ACTIVIDADES DISPONIBLES: " << endl;
                ImprimirActividad(p->listaActividad);

                cout << "\nINGRESE EL NOMBRE DE LA ACTIVIDAD: ";
                string nombreActividad;
                cin.ignore();
                getline(cin, nombreActividad);
                Actividad *existe = nombreActividadExiste(nombreActividad);
                cout << "\nSUB-ACTIVIDADES DISPONIBLES: " << endl;
                ImprimirSubActividad();
                cout << "\nINGRESE EL NOMBRE DE LA SUB-ACTIVIDAD PARA AGREGAR: ";
                string nombreSubActividad;
                cin.clear();
                getline(cin, nombreSubActividad);


                SubActividad *existe2 = getSubActividad(nombreSubActividad);
                if (existe2 == NULL) {
                    cout << "\t\t\t<USTED HA DIGITADO UNA SUB-ACTIVIDAD NO EXISTENTE\n>" << endl;
                } else {
                    int mes = 0, dia = 0;
                    string hora = "";
                    int horas = 0;
                    int min = 0;
                    cout << "\nINGRESE EL MES (1 al 12): ";
                    cin >> mes;
                    cout << "\nINGRESE EL DIA (1-31): ";
                    cin >> dia;
                    cout << "\nINGRESE LA HORA DE INICIO (ejemplo 15:05): ";
                    cin >> hora;
                    cout << "\nINGRESE EL NUMERO DE HORAS: ";
                    cin >> horas;
                    cout << "\nINGRESE EL NUMERO DE MINUTOS: ";
                    cin >> min;
                    Tiempo t = Tiempo{nombreSubActividad, mes, dia, hora, horas, min};
                    SubActividad sub = SubActividad{nombreSubActividad, t};
                    p->listaHoras.push_back(t);//AGREGRE HORAS DE SUBACTIVIDAD

                    list<Actividad>::iterator it;
                    for (it = p->listaActividad.begin(); it != p->listaActividad.end(); it++) {
                        if (it->nombre == nombreActividad) {
                            it->SubListaActividad.push_front(sub);//AGREGUE SUBACTIVIDAD A LA ACTIVIDAD
                        }
                    }
                    cout << "SE AGREGO LA SUB-ACTIVIDAD CON EXITO" << endl;
                    list<Persona> prr = listaPersona;
                    ImprimirPersona(true);
                }
                Menu();
            }
            // CONDICIONAL PARA MODIFICAR DATOS DE LA PERSONA Y SU DEBIDO PUESTO
        }
        if (opc == 3) {
            cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 3>" << endl;
            cout << "\n\n";
            cout << "\t\t\t----------------------------------------------------------------------" << endl;
            cout << "\t\t\t|                                                                    |" << endl;
            cout << "\t\t\t|                 1.MODIFICAR DATOS EN LA LISTA PERSONA              |" << endl;
            cout << "\t\t\t|                 2.MODIFICAR DATOS EN LA LISTA PUESTO               |" << endl;
            cout << "\t\t\t|                                                                    |" << endl;
            cout << "\t\t\t----------------------------------------------------------------------" << endl;
            cout << "\t\t\t<<DIGITE LA OPCION DESEADA>> ";
            cin >> menu2;

            if (menu2 == 1) {
                bool encontrado = false;
                Persona *p;
                string nombre;
                while (true) {

                    if (encontrado == false) {
                        ImprimirPersona(false);
                        cout << "INGRESE EL NOMBRE DE LA PERSONA O DIGITE 0 PARA VOLVER AL MENU: \n";
                        cin.clear();
                        getline(cin, nombre);
                        if (nombre == "0") {
                            Menu();
                        }
                        p = buscarPersona(nombre);
                        if (p == NULL) {
                            cout << "\t\t\t<USTED HA DIGITADO UNA PERSONA NO EXISTENTE\n>" << endl;
                            continue;
                        } else {
                            encontrado = true;
                        }
                    }


                    cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 1>" << endl;
                    cout << "\n\n";
                    cout << "\t\t\t----------------------------------------------------------------------" << endl;
                    cout << "\t\t\t|                                                                    |" << endl;
                    cout << "\t\t\t|                 1.MODIFICAR NOMBRE DEL USUARIO                     |" << endl;
                    cout << "\t\t\t|                 2.MODIFICAR CEDULA DEL USUARIO                     |" << endl;
                    cout << "\t\t\t|                 3.MODIFICAR EDAD DEL USUARIO                       |" << endl;
                    cout << "\t\t\t|                 4.MODIFICAR LUGAR DE RESIDENCIA DEL USUARIO        |" << endl;
                    cout << "\t\t\t|                                                                    |" << endl;
                    cout << "\t\t\t|                 Cualquier otra tecla: Menu principal               |" << endl;
                    cout << "\t\t\t|                                                                    |" << endl;
                    cout << "\t\t\t----------------------------------------------------------------------" << endl;
                    cout << "\t\t\t<<DIGITE LA OPCION DESEADA>> ";
                    cin >> sub_menu1;
                    if (sub_menu1 == 1) {
                        cout << "Nombre actual: " << p->nombre << endl;
                        cout << "Ingrese el nuevo nombre de la persona: \n";
                        cin.ignore();
                        getline(cin, nombre);
                        p->nombre = nombre;
                        cout << "SE MODIFICO EL NOMBRE DE LA PERSONA" << endl;
                        ImprimirPersona(false);
                    } else if (sub_menu1 == 2) {
                        //
                        int cedula;
                        cout << "Cedula actual: " << p->cedula << endl;
                        cout << "\nIngrese la nueva cedula de la persona: ";
                        cin >> cedula;
                        p->cedula = cedula;
                    } else if (sub_menu1 == 3) {
                        //
                        int edad;
                        cout << "Edad actual: " << p->edad << endl;
                        cout << "\nIngrese la nueva edad de la persona: ";
                        cin >> edad;
                        p->edad = edad;
                    } else if (sub_menu1 == 4) {
                        //
                        string lugar;
                        cout << "Lugar de residencia actual: " << p->lugarResidencia << endl;
                        cout << "\nIngrese el nuevo lugar de residencia de la persona: ";
                        cin.ignore();
                        getline(cin, lugar);
                        p->lugarResidencia = lugar;

                        list<Persona> prr = listaPersona;

                        lugar = " ";

                    } else {
                        Menu();
                    }

                    cout << "\n\n";
                }
            } else if (menu2 == 2) {

                string menuConsultas = "1";
                while (menuConsultas >= "1" || menuConsultas <= "2") {
                    cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 2>" << endl;
                    cout << "\n\n";
                    cout << "\t\t\t------------------------------------------------------------" << endl;
                    cout << "\t\t\t|                                                          |" << endl;
                    cout << "\t\t\t|      1.MODIFICAR PUESTO                                  |" << endl;
                    cout << "\t\t\t|      2.MODIFICAR SALARIO DEL PUESTO                      |" << endl;
                    cout << "\t\t\t|                                                          |" << endl;
                    cout << "\t\t\t|      Cualquier otra tecla: Menu principal                |" << endl;
                    cout << "\t\t\t|                                                          |" << endl;
                    cout << "\t\t\t------------------------------------------------------------" << endl;
                    cout << "\t\t<<DIGITE LA OPCION DESEADA: ";
                    cin >> sub_menu2;
                    if (menuConsultas == "1") {


                    } else if (menuConsultas == "2") {
                        //
                    } else {
                        Menu();
                    }
                }

            }
        }
            // CONDICIONAL PARA ELIMINAR DATOS DE LA PERSONA Y EL TIEMPO DE UNA SUBACTIVIDAD DADA
        else if (opc == 4) {

            string menuConsultas = "1";
            while (menuConsultas >= "1" || menuConsultas <= "2") {

                cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 4>" << endl;
                cout << "\n\n";
                cout << "\t\t\t----------------------------------------------------------------------" << endl;
                cout << "\t\t\t|                                                                    |" << endl;
                cout << "\t\t\t|  1.ELIMINAR UN USUARIO                                             |" << endl;
                cout << "\t\t\t|  2.ELIMINAR TIEMPO EN UNA SUBACTIVIDAD REGISTRADA POR EL USUARIO   |" << endl;
                cout << "\t\t\t|                 *** OPCION 2: NO DISPONIBLE***                     |" << endl;
                cout << "\t\t\t|                                                                    |" << endl;
                cout << "\t\t\t|  Cualquier otra tecla: Menu principal                              |" << endl;
                cout << "\t\t\t|                                                                    |" << endl;
                cout << "\t\t\t----------------------------------------------------------------------" << endl;
                cout << "\t\t\t<<DIGITE LA OPCION DESEADA>> ";
                cin >> menuConsultas;

                if (menuConsultas == "1") {
                    cout << "\t\t\t<<USTED HA SELECCIONADO LA OPCION NUMERO 1>" << endl;
                    BorrarDatosUsuario();
                    cout << "\n\n";
                } else if (menuConsultas == "2") {
                    cout << "\t\t\t<<USTED HA SELECCIONADO LA OPCION NUMERO 2>" << endl;
                    BorrarDatosTiempoSubActividad();
                    cout << "\n\n";
                } else {
                    Menu();
                }

            };
        } else if (opc == 5) {

            string menuConsultas = "1";
            while (menuConsultas >= "1" || menuConsultas <= "5") {


                cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 5>" << endl;
                cout << "\n\n";
                cout << "\t\t\t----------------------------------------------------------------------" << endl;
                cout << "\t\t\t|                                                                    |" << endl;
                cout << "\t\t\t|               1.Cual es el puesto mas frecuente                    |" << endl;
                cout << "\t\t\t|               2.Cual es la formacion mas frecuente                 |" << endl;
                cout << "\t\t\t|               3.Sub-Actividad con mayor y menor consumo de tiempo  |" << endl;
                cout << "\t\t\t|               4.Actividades que no registran consumo de tiempo     |" << endl;
                cout << "\t\t\t|               5.Distribucion de tiempo persona X                   |" << endl;
                cout << "\t\t\t|                                                                    |" << endl;
                cout << "\t\t\t|               Cualquier otra tecla: Menu principal                 |" << endl;
                cout << "\t\t\t|                                                                    |" << endl;
                cout << "\t\t\t----------------------------------------------------------------------" << endl;
                cout << "\t\t\t<<DIGITE LA OPCION DESEADA: ";
                cin >> menuConsultas;
                if (menuConsultas == "1") {
                    puestoMasFrecuente();
                } else if (menuConsultas == "2") {
                    formacionMasFrecuente();

                } else if (menuConsultas == "3") {

                    mayorMenorTiempo();

                } else if (menuConsultas == "4") {
                    actividadesSinTiempo();

                } else if (menuConsultas == "5") {
                    distribucionTiempo();

                } else {
                    Menu();
                }

            }

        } else if (opc == 6) {
            string menuConsultas = "1";
            while (menuConsultas >= "1" || menuConsultas <= "5") {


                cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 6>" << endl;
                cout << "\n\n";
                cout
                        << "\t----------------------------------------------------------------------------------------------------------"
                        << endl;
                cout
                        << "\t|                                                                                                        |"
                        << endl;
                cout
                        << "\t|    1.Imprimir la informacion de todas las listas.                                                      |"
                        << endl;
                cout
                        << "\t|    2.Imprimir la informacion del total del tiempo registrado  por subactividad por persona en un dia X |"
                        << endl;
                cout
                        << "\t|    3.Imprimir la distribucion de los porcentajes segun la formacion del personal                       |"
                        << endl;
                cout
                        << "\t|    4.Imprimir la distribucion de los porcentajes segun los puestos.                                    |"
                        << endl;
                cout
                        << "\t|    5.Imprimir los porcentajes de las sub actividades de internet                                       |"
                        << endl;
                cout
                        << "\t|                                                                                                        |"
                        << endl;
                cout
                        << "\t|    Cualquier otra tecla: Menu principal                                                                |"
                        << endl;
                cout
                        << "\t|                                                                                                        |"
                        << endl;
                cout
                        << "\t----------------------------------------------------------------------------------------------------------"
                        << endl;
                cout << "\t<<DIGITE LA OPCION DESEADA: ";
                cin >> menuConsultas;
                if (menuConsultas == "1") {
                    imprimirListas();

                } else if (menuConsultas == "2") {
                    TiempoSubActividad();

                } else if (menuConsultas == "3") {
                    distribucionFormacion();

                } else if (menuConsultas == "4") {
                    distribucionPuesto();

                } else if (menuConsultas == "5") {
                    distribucionInternet();

                } else {
                    Menu();
                }

            };
        } else if (opc == 7) {
            cout << "\t\t\t<FIN DEL PROGRAMA>" << endl;
            break;
        }
    }
    Menu();
}

void imprimirListas() {

    cout << "\nLista de Actividades: \n" << endl;
    list<Actividad>::iterator it;
    for (it = listaActividad.begin(); it != listaActividad.end(); it++) {
        cout << "\n\tACTIVIDAD: " << it->nombre << endl;
        cout << "\tLista de Sub-Actividades de la actividad: \n" << endl;
        list<SubActividad>::iterator it2;
        for (it2 = it->SubListaActividad.begin(); it2 != it->SubListaActividad.end(); it2++) {
            cout << "\t SUB ACTIVIDAD: " << it2->nombre << endl;
        }
    }
    cout << "\n------------------------------------------------------------------------" << endl;
    cout << "\nLista de Sub Actividades general: \n" << endl;
    list<SubActividad>::iterator it2;
    for (it2 = ListaSubActividad.begin(); it2 != ListaSubActividad.end(); it2++) {
        cout << "\tSUB-ACTIVIDAD: " << it2->nombre << endl;
    }
    cout << "\n------------------------------------------------------------------------" << endl;
    cout << "\tLista de Personas: \n" << endl;
    list<Persona>::iterator it3;
    for (it3 = listaPersona.begin(); it3 != listaPersona.end(); it3++) {
        cout << "\n->PERSONA: " << it3->nombre << endl;
        cout << "\n\tLista de Actividades de la persona: \n" << endl;
        list<Actividad>::iterator it4;
        for (it4 = it3->listaActividad.begin(); it4 != it3->listaActividad.end(); it4++) {
            cout << "\t ACTIVIDAD: " << it4->nombre << endl;
            cout << "\n\t Sub-Actividades de la actividad: \n" << endl;
            list<SubActividad>::iterator it2;
            for (it2 = it4->SubListaActividad.begin(); it2 != it4->SubListaActividad.end(); it2++) {
                cout << "\t\tSUB-ACTIVIDAD: " << it2->nombre << endl;
            }
        }
        cout << "\n\tLista de horas de cada persona: \n" << endl;
        list<Tiempo>::iterator it5;
        for (it5 = it3->listaHoras.begin(); it5 != it3->listaHoras.end(); it5++) {
            cout << "\t Sub-Actividad a la que pertenece: " << it5->subActividad << endl;
            cout << "\t Horas: " << it5->horas << "  Minutos: " << it5->minutos << endl;
            cout << "\t Fecha: " << it5->dia << "/" << it5->mes << "  Hora: " << it5->hora << endl;
        }
    }

}

void distribucionPuesto() {
    /*
     * imprime la distribucion de los puestos
     */

    //guarda el nombre del puesto en la clave y veces que aparece en el valor
    map<string, int> distribucion = {};

    //guarda total de formaciones
    int total = 0;

    list<Persona>::iterator it;
    for (it = listaPersona.begin(); it != listaPersona.end(); it++) {
        map<string, int>::iterator esta;
        esta = distribucion.find(it->puesto.nombre);
        if (esta == distribucion.end()) {
            //no existe el puesto en el diccionario por eso se agrega el nombre en la clave y el valor 1 por
            //que es la primera vez que se encuentra la formacion
            distribucion.insert(make_pair(it->puesto.nombre, 1));
            total += 1;
        } else {
            //ya existe el puesto en el diccionario por eso se suma 1
            esta->second += 1;
            total += 1;

        }
    }

    //imprime la distribucion del formaciones
    cout << "\nDistribucion de puestos: " << endl;
    map<string, int>::iterator it3;
    double total1 = 0;
    //imprime el nombre del puesto y la cantidad de veces que aparece, el porcentaje respecto al total de formaciones con una
    //simple regla de 3
    for (it3 = distribucion.begin(); it3 != distribucion.end(); it3++) {
        cout << "\n\t.:" << it3->first << ":.\t" << "Cantidad: " << it3->second << "\t" << "Porcentaje: "
             << double((it3->second * 100)) / double(total) << "%" << endl;
        total1 += double((it3->second * 100)) / double(total);
    }
    cout << "\n\tTotal: " << total1 << "%" << endl;

}

void distribucionFormacion() {
    /*
     * imprime la distribución de formaciones
     */

    //guarda el nombre de la formacion en la clave y veces que aparece en el valor
    map<string, int> distribucion = {};

    //guarda total de formaciones
    int total = 0;

    list<Persona>::iterator it;
    for (it = listaPersona.begin(); it != listaPersona.end(); it++) {
        map<string, int>::iterator esta;
        esta = distribucion.find(it->formacion.titulo);
        if (esta == distribucion.end()) {
            //no existe la formacion en el diccionario por eso se agrega el nombre en la clave y el valor 1 por
            //que es la primera vez que se encuentra la formacion
            distribucion.insert(make_pair(it->formacion.titulo, 1));
            total += 1;
        } else {
            //ya existe la foormacion en el diccionario por eso se suma 1
            esta->second += 1;
            total += 1;

        }
    }

    //imprime la distribucion del formaciones
    cout << "\nDistribucion de formaciones: " << endl;
    map<string, int>::iterator it3;
    double total1 = 0;
    //imprime la distribucion de formaciones, se hace con una simple regla de 3
    for (it3 = distribucion.begin(); it3 != distribucion.end(); it3++) {
        cout << "\n\t.:" << it3->first << ":.\t" << "Cantidad: " << it3->second << "\t" << "Porcentaje: "
             << double((it3->second * 100)) / double(total) << "%" << endl;
        total1 += double((it3->second * 100)) / double(total);
    }
    cout << "\n\tTotal: " << total1 << "%" << endl;// la suma debe ser 100%

}

void distribucionInternet() {
    /*
     *imprime la distrubicón de las sub actividades de internet
     */

    //guarda la actividad en clave y minitos sumados de las subactividades en valor
    map<string, int> distribucion = {};

    //guarda total de minutos que suman las actividades
    int total = 0;

    list<Persona>::iterator it;
    for (it = listaPersona.begin(); it != listaPersona.end(); it++) {
        list<Actividad>::iterator it2;
        for (it2 = it->listaActividad.begin(); it2 != it->listaActividad.end(); it2++) {
            if (it2->nombre == "Internet") {//si es la actividad internet
                list<SubActividad>::iterator it3;//iterador para recorrer las subactividades
                for (it3 = it2->SubListaActividad.begin();
                     it3 != it2->SubListaActividad.end(); it3++) {//recorre las subactividades
                    map<string, int>::iterator esta;
                    esta = distribucion.find(it3->nombre);
                    if (esta == distribucion.end()) {
                        //no existe la actividad en el diccionario por eso se agrega el nombre en la clave y el valor son los
                        //minutos que suman las sub actividades
                        distribucion.insert(make_pair(it3->nombre, 1));
                        total += 1;
                    } else {
                        //ya existe la actividad en el diccionario por eso se suma el valor de los minutos de las sub actividades
                        esta->second += 1;
                        total += 1;

                    }
                }
            }

        }
    }

    //imprime la distribucion del tiempo de las actividades
    cout << "\nDistribucion de sub-Actividades de la actividad Internet: " << endl;
    map<string, int>::iterator it3;
    double total1 = 0;

    //sacar el porcentaje de cada actividad, se hace con una simple regla de 3.
    for (it3 = distribucion.begin(); it3 != distribucion.end(); it3++) { //recorre el diccionario
        cout << "\n\t.:" << it3->first << ":.\t" << "Cantidad: " << it3->second << "\t" << "Porcentaje: "
             << double((it3->second * 100)) / double(total) << "%" << endl;
        total1 += double((it3->second * 100)) / double(total);
    }
    cout << "\n\tTotal: " << total1 << "%" << endl;

}

void distribucionTiempo() {
    string nombre;
    cout << "\nIngrese el nombre de la persona: ";
    cin.ignore();
    getline(cin, nombre);

    Persona *p = buscarPersona(nombre);
    if (p == NULL) {
        cout << "\nNo se encontro la persona";
        return;
    }
    int mes = 0, dia = 0;
    cout << "\nIngrese el mes: ";
    cin >> mes;
    cout << "\nIngrese el dia: ";
    cin >> dia;
    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        cout << "\n.:Mes o dia invalido:.";
        return;
    }

    //guarda la actividad en clave y minitos sumados de las subactividades en valor
    map<string, int> distribucion = {};

    //guarda total de minutos que suman las actividades
    int totalEnMinutos = 0;

    list<Actividad>::iterator it;
    for (it = p->listaActividad.begin(); it != p->listaActividad.end(); it++) {
        list<SubActividad>::iterator it2;
        for (it2 = it->SubListaActividad.begin(); it2 != it->SubListaActividad.end(); it2++) {
            if (it2->tiempo.mes == mes && it2->tiempo.dia == dia) {
                map<string, int>::iterator esta;
                esta = distribucion.find(it->nombre);
                if (esta == distribucion.end()) {
                    //no existe la actividad en el diccionario por eso se agrega el nombre en la clave y el valor son los
                    //minutos que suman las sub actividades
                    distribucion.insert(make_pair(it2->nombre, ((it2->tiempo.minutos) + ((it2->tiempo.horas) * 60))));
                    totalEnMinutos += ((it2->tiempo.minutos) + ((it2->tiempo.horas) * 60));
                } else {
                    //ya existe la actividad en el diccionario por eso se suma el valor de los minutos de las sub actividades
                    esta->second += it2->tiempo.minutos;
                    totalEnMinutos += ((it2->tiempo.minutos) + ((it2->tiempo.horas) * 60));
                }
            }
        }
    }

    //imprime la distribucion del tiempo de las actividades
    cout << "\nDistribucion de tiempo de las actividades: " << endl;
    map<string, int>::iterator it3;
    double total = 0;
    for (it3 = distribucion.begin(); it3 != distribucion.end(); it3++) {
        cout << "\n\t.:" << it3->first << ":.\t" << "Minutos: " << it3->second << "\t" << "Porcentaje: "
             << double((it3->second * 100)) / double(totalEnMinutos) << "%" << endl;
        total += double((it3->second * 100)) / double(totalEnMinutos);
    }
    cout << "\n\tTotal: " << total << "%" << endl;

}

void actividadesSinTiempo() {

    /*
     * Funcion que imprime las actividades que no tienen tiempo registrados
     * Recorre la lista de actividades y si no tiene tiempo registrado imprime la actividad
     *
     */
    bool tieneTiempo = false;
    list<Persona>::iterator persona;
    for (persona = listaPersona.begin(); persona != listaPersona.end(); persona++) {//recorre la lista de personas
        list<Actividad>::iterator actividad;
        for (actividad = persona->listaActividad.begin();
             actividad != persona->listaActividad.end(); actividad++) {//recorre la lista de actividades
            list<SubActividad>::iterator subActividad;
            for (subActividad = actividad->SubListaActividad.begin();
                 subActividad != actividad->SubListaActividad.end(); subActividad++) {
                if (subActividad->tiempo.horas != 0 || subActividad->tiempo.minutos != 0) {//si tiene tiempo
                    tieneTiempo = true;
                    break;//si tiene tiempo no se imprime y se salta la actividad
                }
            }
            if (tieneTiempo == false) {
                cout << "\t\t\tLa actividad " << actividad->nombre << " de " << persona->nombre
                     << ", no tiene tiempo registrado en ninguna sub-Actividad.\n" << endl;
            } else {
                tieneTiempo = false;//se reestablece el bool
            }
        }
    }

}

void TiempoSubActividad() {
    /*
     * Funcion que imprime el tiempo de las subactividades
     * Recorre la lista de actividades y si tiene tiempo registrado imprime el tiempo de la subactividad
     */
    int mes, dia;

    cout << "\t\t\t<USTED HA SELECCIONADO LA OPCION NUMERO 2>" << endl;
    cout << "\n\n";
    cout << "INGRESE EL MES A CONSULTAR (1-12): ";
    cin >> mes;
    cout << "INGRESE EL DIA A CONSULTAR (1-31): ";
    cin >> dia;
    int contador = 0;//contador de actividades que tienen tiempo registrado
    list<Persona>::iterator persona;
    for (persona = listaPersona.begin(); persona != listaPersona.end(); persona++) {//recorre la lista de personas
        list<Tiempo>::iterator tiempo;
        for (tiempo = persona->listaHoras.begin();
             tiempo != persona->listaHoras.end(); tiempo++) {//recorre la lista de tiempos
            if (tiempo->dia == dia && tiempo->mes == mes) {//si el tiempo es el que se quiere consultar
                cout << "Persona: " << persona->nombre << endl;
                cout << "Actividad: " << tiempo->subActividad << endl;
                cout << "Mes: " << tiempo->mes << endl;
                cout << "Dia: " << tiempo->dia << endl;
                cout << "Hora: " << tiempo->hora << endl;
                cout << "Horas dedicadas: " << tiempo->horas << endl;
                cout << "Minutos: " << tiempo->minutos << endl;
                cout << "\n";
                contador++;//se suma uno al contador
            }
        }
    }
    cout << "\n...Total de coincidencias... " << contador << endl;
}

string *buscarMayorMenor(map<string, int> formaciones) {
    /*
     * Funcion que busca el mayor y menor tiempo de las formaciones/puestos
     * Recorre el diccionario y busca el mayor y menor tiempo
     *
     */
    static string mayorMenorL[4];
    mayorMenorL[0] = "";//nombre de la subactividad con mayor tiempo
    mayorMenorL[1] = "";//tiempo en minutos de la subactividad con mayor tiempo
    mayorMenorL[2] = "";//nombre de la subactividad con menor tiempo
    mayorMenorL[3] = "";//tiempo en minutos de la subactividad con menor tiempo

    int max = 0;
    int min = 1000000;
    //recorre el diccionario y busca el mayor tiempo y el menor tiempo
    for (map<string, int>::iterator it = formaciones.begin(); it != formaciones.end(); ++it) {
        if (it->second > max) {//si el tiempo es mayor que el actual en la variable max
            max = it->second;//nuevo maximo
            mayorMenorL[0] = it->first;//nombre de la subactividad con mayor tiempo
            mayorMenorL[1] = to_string(max);//nuevo mayor timepo, se pasa a string porque esta en int
        }
        if (it->second < min) {//si el timepo es menor que el actual en la variable min
            min = it->second;//nuevo minimo
            mayorMenorL[2] = it->first;//nombre de la formacion/puesto con menor tiempo
            mayorMenorL[3] = to_string(min);//nuevo menor timepo, se pasa a string porque esta en int
        }
    }
    return mayorMenorL;
}

void mayorMenorTiempo() {
    /*
     * función que en un diccionario guarda las subactividades en clave y las cantidad de minutos en valor
     */
    map<string, int> formaciones = {};
    list<Persona>::iterator persona;

    //recorre la lista de personas
    for (persona = listaPersona.begin(); persona != listaPersona.end(); persona++) {
        list<Actividad>::iterator actividad;
        //recorre la lista de actividades de la persona
        for (actividad = persona->listaActividad.begin(); actividad != persona->listaActividad.end(); actividad++) {
            list<SubActividad>::iterator subActividad;
            //recorre la lista de subactividades de la actividad
            for (subActividad = actividad->SubListaActividad.begin();
                 subActividad != actividad->SubListaActividad.end(); subActividad++) {
                map<string, int>::iterator esta;//iterador para buscar en el diccionario
                esta = formaciones.find(subActividad->nombre);//busca la subactividad en el diccionario
                if (esta != formaciones.end()) {
                    //si la subactividad ya existe en el diccionario, suma los minutos
                    esta->second += (subActividad->tiempo.horas * 60) + subActividad->tiempo.minutos;
                } else {
                    //si la subactividad no existe en el diccionario, la agrega con el tiempo
                    formaciones.insert(pair<string, int>(subActividad->nombre, ((subActividad->tiempo.horas * 60) +
                                                                                subActividad->tiempo.minutos)));
                }
            }
        }
    }
    //se llama a la función que busca el mayor y menor tiempo
    string *r = buscarMayorMenor(formaciones);
    //se imprime el resultado,*r es una lista de strings que se trata como puntero
    cout << "\t\t\tLA SUB-ACTIVIDAD MAS FRECUENTE: " << *(r) << " Y TIENE " << *(r + 1) << " MINUTOS.\n" << endl;
    cout << "\t\t\tLA SUB-ACTIVIDAD MENOS FRECUENTE: " << *(r + 2) << " Y TIENE " << *(r + 3) << " MINUTOS.\n" << endl;
}

string* buscarFormacionMasFrecuente(map<string, int> formaciones) { //retorna el nombre de la formacion mas frecuente
    /*
     * Funcion que busca la formacion mas frecuente
     */
    static string masFrecuente[2];
    masFrecuente[0] = "";//Puesto-FORMACION
    masFrecuente[1] = "";//VECES QUE APARECE
    int max = 0;//variable que guarda la cantidad de veces que aparece la formacion mas frecuente
    map<string, int>::iterator it;
    for (it = formaciones.begin(); it != formaciones.end(); ++it) {
        if (it->second > max) {//si el tiempo es mayor que el actual en la variable max
            max = it->second;//nuevo maximo
            masFrecuente[0] = it->first;//nombre de la formacion/puesto con mayor tiempo
            masFrecuente[1] = to_string(max);//nuevo mayor timepo, se pasa a string porque esta en int
        }
    }
    return masFrecuente;
}

void formacionMasFrecuente() {
    /*
     * Funcion que busca la formacion mas frecuente
     */
    map<string, int> formaciones = {};
    list<Persona>::iterator it;
    for (it = listaPersona.begin(); it != listaPersona.end(); it++) {//recorre la lista de personas
        map<string, int>::iterator esta;//iterador para buscar en el diccionario
        esta = formaciones.find(it->formacion.titulo);//busca la formacion en el diccionario
        if (esta != formaciones.end()) {//si la formacion ya existe en el diccionario, suma 1
            esta->second++;//suma 1
        } else {
            if (it->formacion.titulo != "") {
                formaciones.insert(pair<string, int>(it->formacion.titulo,
                                                     1));//si la formacion no existe en el diccionario, la agrega con 1
            }
        }
    }
    string *f = buscarFormacionMasFrecuente(formaciones);

    cout << "\t\t\tLA FORMACION MAS FRECUENTE: " << *(f) << " Y APARECE " << *(f + 1) << " VECES.\n" << endl;

}

void puestoMasFrecuente() {
    /*
     * Funcion que busca el puesto mas frecuente
     *
     */
    map<string, int> puestos = {};//diccionario

    list<Persona>::iterator it;//iterador
    for (it = listaPersona.begin(); it != listaPersona.end(); it++) {//recorre la lista de personas
        map<string, int>::iterator esta;
        esta = puestos.find(it->puesto.nombre);
        if (esta != puestos.end()) {//si el puesto ya existe en el diccionario
            esta->second = esta->second + 1;//se incrementa el valor de la clave (contador)
        } else {//si el puesto no existe en el diccionario
            if (it->puesto.nombre != "") {//si el puesto no esta vacio
                puestos.insert(pair<string, int>(it->puesto.nombre, 1));//se agrega el puesto con un contador de 1
            }
        }
    }// puestos={"Administrador":3,"Analista":2,"Analista de Sistemas":1} ejemplo de diccionario
    string *f = buscarFormacionMasFrecuente(puestos);//TAMBIEN FUNCIONA CON PUESTOS

    //se imprime el resultado, *f es una lista de strings que se trata como puntero
    cout << "\t\t\tEL PUESTO MAS FRECUENTE: " << *(f) << " Y APARECE " << *(f + 1) << " VECES.\n" << endl;

}

SubActividad *getSubActividad(string nombreSubActividad) {
    /*
     * Funcion que retorna un puntero a una subactividad
     */
    SubActividad *existe = NULL;
    list<SubActividad>::iterator it;//iterador
    for (it = ListaSubActividad.begin(); it != ListaSubActividad.end(); it++) {
        if (it->nombre ==
            nombreSubActividad) {//si el nombre de la subactividad es igual al nombre de la subactividad que se busca
            existe = &(*it);//se retorna el puntero a la subactividad
            break;
        }
    }
    return existe;//retorna NULL si no existe
}

Actividad *nombreActividadExiste(string basicString) {
    /*
     * Funcion que busca si una actividad existe y la retorna como puntero
     */
    Actividad *existe = NULL;
    list<Actividad>::iterator it;
    for (it = listaActividad.begin(); it != listaActividad.end(); it++) {
        if (it->nombre == basicString) {
            existe = &(*it);//retorna la direccion de memoria de la actividad
            break;
        }
    }
    return existe;//retorna NULL si no existe
}

Persona *buscarPersona(string basicString) {
    /*
     * Funcion que busca una persona por su nombre
     */
    list<Persona>::iterator it = listaPersona.begin();
    while (it != listaPersona.end()) {
        if (it->nombre == basicString) {
            return &(*it);//retorna un puntero a la persona
        }
        it++;
    }
    return NULL;//si no encuentra la persona retorna NULL
}


// *********************************************** FUNCION PRINCIPAL **************************************************************
int main() {
    datosQuemados();
    Menu();
    return 0;
}

void datosQuemados() {
    // DATOS QUEMADOS LISTA SUBACTIVIDAD
    SubActividad sA1 = {"Ciclismo"};
    ListaSubActividad.push_front(sA1);

    SubActividad sA2 = {"Realiza un Examen"};
    ListaSubActividad.push_front(sA2);

    SubActividad sA3 = {"Atiende clientes"};
    ListaSubActividad.push_front(sA3);

    SubActividad sA4 = {"Hace cumplir la ley"};
    ListaSubActividad.push_front(sA4);

    SubActividad sA5 = {"Limpieza de patio"};
    ListaSubActividad.push_front(sA5);

    SubActividad sAn = {"YouTube"};
    ListaSubActividad.push_front(sAn);

    SubActividad sA6 = {"Descansar"};
    ListaSubActividad.push_front(sA6);

    SubActividad sA7 = {"Se peina"};
    ListaSubActividad.push_front(sA7);

    SubActividad sA8 = {"Sale a caminar"};
    ListaSubActividad.push_front(sA8);

    SubActividad sA9 = {"Ve noticias"};
    ListaSubActividad.push_front(sA9);

    SubActividad sA10 = {"Se baña"};
    ListaSubActividad.push_front(sA10);

    // DATOS QUEMADOS LISTA ACTIVIDAD
    Actividad a1 = {"Deporte"};
    listaActividad.push_front(a1);

    Actividad a2 = {"Estudia"};
    listaActividad.push_front(a2);

    Actividad a3 = {"Trabaja"};
    listaActividad.push_front(a3);

    Actividad a4 = {"Reza"};
    listaActividad.push_front(a4);

    Actividad a5 = {"Que hacer domestico"};
    listaActividad.push_front(a5);

    Actividad a6 = {"Dormir"};
    listaActividad.push_front(a6);

    Actividad a7 = {"Cuidado Personal"};
    listaActividad.push_front(a7);

    Actividad a8 = {"Deporte"};
    listaActividad.push_front(a8);

    Actividad a9 = {"Internet"};
    listaActividad.push_front(a9);

    Actividad a10 = {"Cuidado Personal"};
    listaActividad.push_front(a10);


    // DATOS QUEMADOS LISTA FORMACION
    Formacion f1 = {"Egresado", true};

    Formacion f2 = {"Universitaria incompleta", false};

    Formacion f3 = {"Primaria", true};

    Formacion f4 = {"Secundaria", true};

    Formacion f5 = {"Bachillerato", true};

    Formacion f6 = {"Licenciatura", false};

    Formacion f7 = {"Ms", false};

    Formacion f8 = {"Egresado", true};

    Formacion f9 = {"Activo", true};

    Formacion f10 = {"Tecnico", false};

    // DATOS QUEMADOS LISTA PUESTO
    Puesto k1 = {"Doctor", 1.200000};

    Puesto k2 = {"Enfermera ", 550.000};

    Puesto k3 = {"Cajera", 230.000};

    Puesto k4 = {"Policia", 972.000};

    Puesto k5 = {"Doctor", 1200.00000};

    Puesto k6 = {"Estudiante", 115.000};

    Puesto k7 = {"Estilista", 155.000};

    Puesto k8 = {"Ing.Electronico", 2200.00000};

    Puesto k9 = {"Cirujano", 1205.00000};

    Puesto k10 = {"Estilista", 130.000};
// --------------------------------------------------------------

    Persona p1 = {"Carlos Vasquez", 208760987, 18, "Naranjo"};
    p1.formacion = f1;
    p1.puesto = k1;
    sA1.tiempo = Tiempo{sA1.nombre, 12, 15, "15:00", 1, 0};
    sA8.tiempo = Tiempo{sA8.nombre, 12, 15, "18:00", 5, 20};
    a1.SubListaActividad.push_front(sA1);
    a2.SubListaActividad.push_front(sA8);
    p1.listaHoras.push_front(sA1.tiempo);
    p1.listaHoras.push_front(sA8.tiempo);
    p1.listaActividad.push_back(a1);
    p1.listaActividad.push_back(a2);
    listaPersona.push_front(p1);

    Persona p2 = {"Maria Hernandez", 508460167, 22, "Alajuela"};
    p2.puesto = k2;
    SubActividad sA22 = SubActividad{sA2.nombre, Tiempo{sA2.nombre, 12, 15, "15:00", 0, 0}};
    a2.SubListaActividad.push_front(sA22);
    p2.listaActividad.push_back(a2);
    p2.listaHoras.push_front(sA22.tiempo);
    p2.formacion = f2;
    listaPersona.push_front(p2);

    Persona p3 = {"Patricia Cordero", 301720427, 15, "San Ramon"};
    SubActividad sA33 = SubActividad{sA3.nombre, Tiempo{sA3.nombre, 11, 15, "10:00", 3, 0}};
    a3.SubListaActividad.push_front(sA33);
    p3.listaActividad.push_back(a3);
    p3.listaHoras.push_front(sA33.tiempo);
    p3.formacion = f4;
    p3.puesto = k3;
    listaPersona.push_front(p3);

    Persona p4 = {"Daniel Salazar", 103770841, 11, "La Tigra"};
    SubActividad sA44 = SubActividad{sA4.nombre, Tiempo{sA4.nombre, 11, 15, "20:00", 0, 0}};
    a4.SubListaActividad.push_front(sA44);
    p4.listaActividad.push_back(a4);
    p4.listaHoras.push_front(sA44.tiempo);
    p4.formacion = f4;
    p4.puesto = k4;
    listaPersona.push_front(p4);

    Persona p5 = {"Sofia Viales", 209840991, 19, "Guapiles"};
    SubActividad sA55 = SubActividad{sA5.nombre, Tiempo{sA5.nombre, 12, 15, "12:00", 3, 0}};
    a5.SubListaActividad.push_front(sA55);
    p5.listaActividad.push_back(a5);
    p5.listaHoras.push_front(sA55.tiempo);
    p5.formacion = f5;
    p5.puesto = k5;
    listaPersona.push_front(p5);

    Persona p6 = {"Tatiana Uribe", 702310732, 25, "Upala"};
    SubActividad sA66 = SubActividad{sA6.nombre, Tiempo{sA6.nombre, 12, 15, "18:00", 3, 0}};
    a6.SubListaActividad.push_front(sA66);
    p6.listaActividad.push_back(a6);
    p6.listaHoras.push_front(sA66.tiempo);
    p6.formacion = f6;
    p6.puesto = k6;
    listaPersona.push_front(p6);

    Persona p7 = {"Carmen Oreamuno", 107650227, 30, "Palmares"};
    SubActividad sA77 = SubActividad{sA7.nombre, Tiempo{sA7.nombre, 12, 15, "8:00", 3, 0}};
    a7.SubListaActividad.push_front(sA77);
    p7.listaActividad.push_back(a7);
    p7.listaHoras.push_front(sA77.tiempo);
    p7.formacion = f7;
    p7.puesto = k7;
    listaPersona.push_front(p7);

    Persona p8 = {"Enrique Garcia", 203310957, 42, "San Carlos"};
    SubActividad sA88 = SubActividad{sA8.nombre, Tiempo{sA8.nombre, 12, 15, "11:00", 3, 0}};
    a8.SubListaActividad.push_front(sA88);
    p8.listaActividad.push_back(a8);
    p8.listaHoras.push_front(sA88.tiempo);
    p8.formacion = f8;
    p8.puesto = k8;
    listaPersona.push_front(p8);

    Persona p9 = {"Pablo Morales", 203550983, 65, "Liberia"};
    SubActividad sA99 = SubActividad{sA9.nombre, Tiempo{sA9.nombre, 12, 15, "7:40", 3, 0}};
    a9.SubListaActividad.push_front(sA99);
    a9.SubListaActividad.push_front(sAn);
    p9.listaActividad.push_back(a9);
    p9.listaHoras.push_front(sA99.tiempo);
    p9.formacion = f9;
    p9.puesto = k9;
    listaPersona.push_front(p9);

    Persona p10 = {"Dylan Rojas", 204560934, 26, "Santa Clara"};
    SubActividad sA100 = SubActividad{sA10.nombre, Tiempo{sA100.nombre, 12, 15, "15:00", 1, 0}};
    a10.SubListaActividad.push_front(sA100);
    p10.listaActividad.push_back(a10);
    p10.listaHoras.push_front(sA100.tiempo);
    p10.formacion = f10;
    p10.puesto = k10;
    listaPersona.push_front(p10);
}
