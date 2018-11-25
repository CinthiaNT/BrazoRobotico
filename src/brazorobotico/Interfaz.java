package brazorobotico;


/*
 *   Instituto Tecnologico de León
 *  Ingenieria en Sistemas Computacionales 
 *  Autores: Gonzalez Alcaraz Hernan Arturo
 *           Padilla Guerrero Paul Adrian
 *           Nava Torres Juana Cinthia Lizbeth
 *  Materia: Sistemas programables
 *  Semestre: Septimo
 *  Periodo: Agosto - Diciembre 2018
 *  Fecha de entrega: 23 de Noviembre 2018
*/

/*
    Se importan las librerias que haran la comunicacion
    con arduino
*/
import com.panamahitek.PanamaHitek_Arduino;
import com.panamahitek.ArduinoException;
import com.panamahitek.PanamaHitek_MultiMessage;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

/*
    Librerias utilizadas en interfaz grafica
*/
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.OutputStream;
import java.util.LinkedList;
import javax.swing.JButton;
import javax.swing.JFrame;
import static javax.swing.JFrame.EXIT_ON_CLOSE;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import java.awt.Font;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.ImageIcon;
import javax.swing.JLabel;


public class Interfaz extends JFrame {
    
    /*
    Se declaran los elementos a utilizar para la creacion de interfaz
    grafica.
    Los botones enviaran la informacion a arduino para generar 
    movimeinto en los motores.
    - 2 botones para la pinza: Abrir y cerrar.
    - 3 botones para muñeca: Izquierda, derecha y restablecer.
    - 2 botones para codo: subir y bajar.
    - 2 botones para hombro: subir y bajar.
    - 5 botones para motor: gira 90°,180°,360° y estos movimientos pueden ser
        izquierda y derecha.
    - 1 botones para generar secuencia.
    - 1 botones para realizar automatico.
    - 1 botones para borrar secuencia.
    ---------------------------------------------------------------------------
    Se declara una lista que sera la que guardara los valores de la secuencia
    a generar.
    
    Se declaran los objetos de PanamaHitek para realizar la conexion con
    arduino.
    */
    private JButton cerrar_pinza, abrir_pinza, derecha_muneca, izquierda_muneca,
            bajar_codo, subir_codo, bajar_hombro, subir_hombro,
            generar, automatico, borrar, restablecer, pasos_90, pasos_180, pasos_360,
            pasos_derecha, pasos_izquierda;
    private JPanel panel;
    private JLabel imagen,base,titulo;
    private String der, izq, cer, abri, abC, abH, arC, arH;
    private OutputStream ouput;
    private String puerto;
    private int time, dataRate;
    private Font fuente,fuente1;
    private boolean con, gem;
    String sec, alin_mun, giro;
    LinkedList<Lista> lista = new LinkedList<>();
    static PanamaHitek_Arduino arduino;
    static SerialPortEventListener listener;
    static PanamaHitek_MultiMessage multi;

    public Interfaz() {
        super("Brazo Robotico");
        /*
        Se realiza la conexion con arduino
        */
        arduino = new PanamaHitek_Arduino();
        multi = new PanamaHitek_MultiMessage(3, arduino);
        listener = new SerialPortEventListener() {
            @Override
            public void serialEvent(SerialPortEvent spe) {
                try {
                    if (multi.dataReceptionCompleted()) {

                    }
                } catch (ArduinoException ex) {
                    Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                } catch (SerialPortException ex) {
                    Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        };
        try {
            //Inicia comunicacion con arduino
            arduino.arduinoRXTX("/dev/ttyACM0", 9600, listener);
        } catch (ArduinoException ex) {
            Logger.getLogger(ResourceBundle.Control.class.getName()).log(Level.SEVERE, null, ex);
        }
        /*
        Se delcarar los componentes necesarios para armar la interfaz grafica
        */
        gem = false;
        sec = "";
        fuente = new Font("Arial", Font.BOLD, 20);
        fuente1 = new Font("Arial", Font.BOLD, 15);
        setLayout(null);
        puerto = "/dev/ttyACM0";
        time = 2000;
        con = false;
        dataRate = 9600;
        ouput = null;
        panel = new JPanel(null);
        imagen = new JLabel(new ImageIcon("src/imagenes/brazo.png"));
        base = new JLabel("Base");
        titulo = new JLabel("Brazo Robotico");
        borrar = new JButton("Borrar secuencia");
        cerrar_pinza = new JButton("Cerrar Pinza");
        generar = new JButton("Generar secuencia");
        abrir_pinza = new JButton("Abrir pinza");
        izquierda_muneca = new JButton("Muñeca a la izquierda");
        subir_hombro = new JButton("Subir Hombro");
        bajar_hombro = new JButton("Bajar Hombro");
        derecha_muneca = new JButton("Muñeca a la derecha");
        restablecer = new JButton("Alinear Muñeca");
        bajar_codo = new JButton("Bajar Codo");
        subir_codo = new JButton("Subir Codo");
        automatico = new JButton("Automatico");
        pasos_90 = new JButton("Gira 90°");
        pasos_180 = new JButton("Gira 180°");
        pasos_360 = new JButton("Gira 360°");
        pasos_derecha = new JButton(">");
        pasos_izquierda = new JButton("<");
        this.getContentPane().setBackground(Color.WHITE);
        titulo.setFont(fuente);
        borrar.setBackground(Color.DARK_GRAY);
        borrar.setFont(fuente1);
        borrar.setForeground(Color.WHITE);
        cerrar_pinza.setBackground(Color.DARK_GRAY);
        cerrar_pinza.setFont(fuente1);
        cerrar_pinza.setForeground(Color.WHITE);
        abrir_pinza.setBackground(Color.DARK_GRAY);
        abrir_pinza.setFont(fuente1);
        abrir_pinza.setForeground(Color.WHITE);
        izquierda_muneca.setBackground(Color.DARK_GRAY);
        izquierda_muneca.setFont(fuente1);
        izquierda_muneca.setForeground(Color.WHITE);
        subir_hombro.setBackground(Color.DARK_GRAY);
        subir_hombro.setFont(fuente1);
        subir_hombro.setForeground(Color.WHITE);
        bajar_hombro.setBackground(Color.DARK_GRAY);
        bajar_hombro.setFont(fuente1);
        bajar_hombro.setForeground(Color.WHITE);
        derecha_muneca.setBackground(Color.DARK_GRAY);
        derecha_muneca.setFont(fuente1);
        derecha_muneca.setForeground(Color.WHITE);
        restablecer.setBackground(Color.DARK_GRAY);
        restablecer.setFont(fuente1);
        restablecer.setForeground(Color.WHITE);
        bajar_codo.setBackground(Color.DARK_GRAY);
        bajar_codo.setFont(fuente1);
        bajar_codo.setForeground(Color.WHITE);
        subir_codo.setBackground(Color.DARK_GRAY);
        subir_codo.setFont(fuente1);
        subir_codo.setForeground(Color.WHITE);
        pasos_90.setBackground(Color.DARK_GRAY);
        pasos_90.setFont(fuente1);
        pasos_90.setForeground(Color.WHITE);
        pasos_180.setBackground(Color.DARK_GRAY);
        pasos_180.setFont(fuente1);
        pasos_180.setForeground(Color.WHITE);
        pasos_360.setBackground(Color.DARK_GRAY);
        pasos_360.setFont(fuente1);
        pasos_360.setForeground(Color.WHITE);
        pasos_izquierda.setBackground(Color.DARK_GRAY);
        pasos_izquierda.setFont(fuente1);
        pasos_izquierda.setForeground(Color.WHITE);
        pasos_derecha.setBackground(Color.DARK_GRAY);
        pasos_derecha.setFont(fuente1);
        pasos_derecha.setForeground(Color.WHITE);
        automatico.setBackground(Color.DARK_GRAY);
        automatico.setFont(fuente1);
        automatico.setForeground(Color.WHITE);
        generar.setBackground(Color.DARK_GRAY);
        generar.setFont(fuente1);
        generar.setForeground(Color.WHITE);
        titulo.setBounds(50, 20, 200, 50);
        abrir_pinza.setBounds(50, 150, 210, 50);
        cerrar_pinza.setBounds(350, 150, 210, 50);
        izquierda_muneca.setBounds(50, 75, 210, 50);
        derecha_muneca.setBounds(350, 75, 210, 50);
        restablecer.setBounds(600, 75, 210, 50);
        subir_hombro.setBounds(50, 225, 210, 50); //hombro
        bajar_hombro.setBounds(350, 225, 210, 50);
        subir_codo.setBounds(50, 300, 210, 50);
        bajar_codo.setBounds(350, 300, 210, 50);
        automatico.setBounds(50, 450, 210, 50);
        generar.setBounds(350, 450, 210, 50);
        borrar.setBounds(600, 450, 210, 50);
        base.setBounds(50,350,100,30);
        base.setFont(fuente1);
        pasos_90.setBounds(100, 380, 110, 50);
        pasos_180.setBounds(250, 380, 110, 50);
        pasos_360.setBounds(400, 380, 110, 50);
        pasos_izquierda.setBounds(600, 380, 70, 50);
        pasos_derecha.setBounds(680, 380, 70, 50);
        imagen.setBounds(830, 130, 430, 266);
        add(titulo);
        add(pasos_derecha);
        add(base);
        add(pasos_izquierda);
        add(pasos_90);
        add(pasos_180);
        add(pasos_360);
        add(abrir_pinza);
        add(restablecer);
        add(cerrar_pinza);
        add(subir_hombro);
        add(izquierda_muneca);
        add(bajar_hombro);
        add(derecha_muneca);
        add(subir_codo);
        add(bajar_codo);
        add(panel);
        add(automatico);
        add(generar);
        add(borrar);
        add(imagen);
        /*
        Al dar clic en este boton se lanza un evento que enviara un
        identificador que correspondera a un valor para el servo motor 
        correspondiente a la muñeca. 
        */
        izquierda_muneca.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (gem == true) {
                    sec = "2";
                    alin_mun = "izquierda";
                    try {
                        arduino.sendData("2");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    lista.add(new Lista(sec));
                } else {
                    alin_mun = "izquierda";
                    try {
                        arduino.sendData("2");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });
        /*
        Al dar clic en este boton se lanza un evento que enviara un
        identificador que correspondera a un valor para el servo motor 
        correspondiente a la muñeca.
        */
        derecha_muneca.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (gem == true) {
                    sec = "1";
                    lista.add(new Lista(sec));
                    alin_mun = "derecha";
                    try {
                        arduino.sendData("1");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else {
                    alin_mun = "derecha";
                    try {
                        arduino.sendData("1");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }

            }
        });
        /*
        Al dar clic en este boton se lanza un evento que enviara un
        identificador que correspondera a un valor para el servo motor 
        correspondiente a la muñeca.Restablece el valor de la muñeca en su 
        estado inicial.
        */
        restablecer.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String variable_env = "";
                if (alin_mun.equals("izquierda")) {
                    variable_env = "B";
                } else if (alin_mun.equals("derecha")) {
                    variable_env = "A";
                }
                System.out.println(variable_env);
                if (gem == true) {
                    sec = variable_env;
                    lista.add(new Lista(sec));
                    try {
                        arduino.sendData(variable_env);
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else {
                    try {
                        arduino.sendData(variable_env);
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }

            }
        });
        /*
        Al dar clic en este boton se lanza un evento que enviara un
        identificador que correspondera a un valor para el servo motor 
        correspondiente a la pinza.
        */
        abrir_pinza.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (gem == true) {
                    sec = "4";
                    lista.add(new Lista(sec));
                    try {
                        arduino.sendData("4");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else {
                    try {
                        arduino.sendData("4");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });
        /*
        Al dar clic en este boton se lanza un evento que enviara un
        identificador que correspondera a un valor para el servo motor 
        correspondiente a la pinza. 
        */
        cerrar_pinza.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (gem == true) {
                    sec = "3";
                    lista.add(new Lista(sec));
                    try {
                        arduino.sendData("3");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else {
                    try {
                        arduino.sendData("3");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });
        /*
        Al dar clic en este boton se lanza un evento que enviara un
        identificador que correspondera a un valor para el servo motor 
        correspondiente al hombro.
        */
        subir_hombro.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (gem == true) {
                    sec = "5";
                    lista.add(new Lista(sec));
                    try {
                        arduino.sendData("5");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else {
                    try {
                        arduino.sendData("5");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });
        /*
        Al dar clic en este boton se lanza un evento que enviara un
        identificador que correspondera a un valor para el servo motor 
        correspondiente al hombro. 
        */
        bajar_hombro.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (gem == true) {
                    sec = "6";
                    lista.add(new Lista(sec));
                    try {
                        arduino.sendData("6");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else {
                    try {
                        arduino.sendData("6");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });
        /*
        Al dar clic en este boton se lanza un evento que enviara un
        identificador que correspondera a un valor para el servo motor 
        correspondiente al codo. 
        */
        subir_codo.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (gem == true) {
                    sec = "7";
                    lista.add(new Lista(sec));
                    try {
                        arduino.sendData("7");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else {
                    try {
                        arduino.sendData("7");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });
        /*
        Al dar clic en este boton se lanza un evento que enviara un
        identificador que correspondera a un valor para el servo motor 
        correspondiente al codo.
        */
        bajar_codo.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (gem == true) {
                    sec = "8";
                    lista.add(new Lista(sec));
                    try {
                        arduino.sendData("8");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else {
                    try {
                        arduino.sendData("8");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });
        /* 
        Al dar clic en este boton se lanza un evento que envia el identificar
        correspondiente a girar el motor a pasos en 90°.
        */
        pasos_90.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                giro = "noventa";
            }
        });
        /* 
        Al dar clic en este boton se lanza un evento que envia el identificar
        correspondiente a girar el motor a pasos en 180°.
        */
        pasos_180.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                giro = "ciento";
            }
        });
        /* 
        Al dar clic en este boton se lanza un evento que envia el identificar
        correspondiente a girar el motor a pasos en 360°.
        */
        pasos_360.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                giro = "trescientos";
            }
        });
        /* 
        Al dar clic en este boton se lanza un evento que envia el identificar
        correspondiente a girar el motor a pasos.
        El moviemto sera a la derecha además de los grados que seleccionaste
        con los botones anteriores.
        */
        pasos_derecha.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (giro != null) {
                    String var_grado = "";
                    if (giro.equals("noventa")) {
                        var_grado = "C";
                    } else if (giro.equals("ciento")) {
                        var_grado = "D";
                    } else if (giro.equals("trescientos")) {
                        var_grado = "E";
                    }
                    if (gem == true) {
                        sec = var_grado;
                        lista.add(new Lista(sec));
                        try {
                            arduino.sendData(var_grado);
                        } catch (ArduinoException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (SerialPortException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    } else {
                        try {
                            arduino.sendData(var_grado);
                        } catch (ArduinoException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (SerialPortException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                } else {
                    JOptionPane.showMessageDialog(null, "Elige el grado de giro a realizar");
                }
            }
        });
        /* 
        Al dar clic en este boton se lanza un evento que envia el identificar
        correspondiente a girar el motor a pasos.
        El moviemto sera a la derecha además de los grados que seleccionaste
        con los botones anteriores.
        */
        pasos_izquierda.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (giro != null) {
                    String var_grado = "";
                    if (giro.equals("noventa")) {
                        var_grado = "F";
                    } else if (giro.equals("ciento")) {
                        var_grado = "G";
                    } else if (giro.equals("trescientos")) {
                        var_grado = "H";
                    }
                    if (gem == true) {
                        sec = var_grado;
                        lista.add(new Lista(sec));
                        try {
                            arduino.sendData(var_grado);
                        } catch (ArduinoException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (SerialPortException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    } else {
                        try {
                            arduino.sendData(var_grado);
                        } catch (ArduinoException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (SerialPortException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                } else {
                    JOptionPane.showMessageDialog(null, "Elige el grado de giro a realizar");
                }
            }
        });
        /*
        Al dar clic en generar se cambia el estado de gem a true para ppoder
        realizar un automatico
        */
        generar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gem = true;
                JOptionPane.showMessageDialog(null, "Presione los botones para generar secuencia");
            }
        });
        /*
        Al dar clic en generar secuencia envia un identificar a arduino
        para que se ejecute el metodo correspondiente de "eliminar secuencia".
        Se limpia la lista.
        */
        borrar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    arduino.sendData("X");
                } catch (ArduinoException ex) {
                    Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                } catch (SerialPortException ex) {
                    Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                }
                lista.clear();
                gem = false;
            }
        });
        /*Al dar clic en generar secuencia envia un identificar a arduino
        para que se ejecute el metodo correspondiente de "automatico"
        */
        automatico.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (gem == true) {
                    try {
                        arduino.sendData("9");
                    } catch (ArduinoException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SerialPortException ex) {
                        Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                    }

                    for (int i = 0; i < lista.size(); i++) {
                        try {
                            arduino.sendData(lista.get(i).secuencia);
                        } catch (ArduinoException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (SerialPortException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        }
                        gem = false;
                    }
                } else {
                    JOptionPane.showMessageDialog(null, "Genera una secuencia");
                }
            }
        });
    }

    public static void main(String[] args) {
        Interfaz obj = new Interfaz();
        obj.setDefaultCloseOperation(EXIT_ON_CLOSE);
        obj.setSize(1250, 600);
        obj.setLocation(100, 50);
        obj.setResizable(false);
        obj.setVisible(true);
    }
}
