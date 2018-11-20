package brazorobotico;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileDescriptor;
import java.io.OutputStream;
import java.util.Enumeration;
import java.util.LinkedList;
import javax.swing.JButton;
import javax.swing.JFrame;
import static javax.swing.JFrame.EXIT_ON_CLOSE;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import com.panamahitek.PanamaHitek_Arduino;
import com.panamahitek.ArduinoException;
import com.panamahitek.PanamaHitek_MultiMessage;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;

import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

public class Interfaz extends JFrame {

    private JButton cerrar_pinza, abrir_pinza, derecha_muneca, izquierda_muneca,
            bajar_codo, cerrar_codo, bajar_hombro, subir_hombro,
            generar, automatico, borrar, restablecer,pasos_90,pasos_180,pasos_360,
            pasos_derecha,pasos_izquierda;
    private JPanel panel;
    private String der, izq, cer, abri, abC, abH, arC, arH;
    private OutputStream ouput;
    private String puerto;
    private int time, dataRate;
    private boolean con, gem;
    String sec, alin_mun, giro;
    LinkedList<Lista> lista = new LinkedList<>();
    static PanamaHitek_Arduino arduino;
    static SerialPortEventListener listener;
    static PanamaHitek_MultiMessage multi;

    public Interfaz() {
        super("Control");
        arduino = new PanamaHitek_Arduino();
        multi = new PanamaHitek_MultiMessage(3, arduino);
        listener = new SerialPortEventListener() {
            @Override
            public void serialEvent(SerialPortEvent spe) {
                try {
                    if (multi.dataReceptionCompleted()) {
//                        lblTemp.setText("Temperatura: " + multi.getMessage(0) + "°C");
//                        lblHumedad.setText("Humedad: " + multi.getMessage(1) + "%");
//                        lblLum.setText("Luminosidad: " + multi.getMessage(2) + "");
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
        gem = false;
        sec = "";
        setLayout(null);
        puerto = "/dev/ttyACM0";
        time = 2000;
        con = false;
        dataRate = 9600;
        ouput = null;
        panel = new JPanel(null);
        borrar = new JButton("Borrar secuencia");
        cerrar_pinza = new JButton("Cerrar Pinza");
        generar = new JButton("Generar secuencia");
        abrir_pinza = new JButton("Abrir pinza");
        izquierda_muneca = new JButton("MUñeca a la izquierda");
        subir_hombro = new JButton("Subir Hombro");
        bajar_hombro = new JButton("Bajar Hombro");
        derecha_muneca = new JButton("Muñeca a la derecha");
        restablecer = new JButton("Alinear Muñeca");
        bajar_codo = new JButton("Bajar Codo");
        cerrar_codo = new JButton("Subir Codo");
        automatico = new JButton("Automatico");
        pasos_90 = new JButton("Gira 90°");
        pasos_180 = new JButton("Gira 180°");
        pasos_360 = new JButton("Gira 360°");
        pasos_derecha = new JButton(">");
        pasos_izquierda = new JButton("<");
        borrar.setBackground(Color.lightGray);
        cerrar_pinza.setBackground(Color.lightGray);
        abrir_pinza.setBackground(Color.lightGray);
        izquierda_muneca.setBackground(Color.lightGray);
        subir_hombro.setBackground(Color.lightGray);
        bajar_hombro.setBackground(Color.lightGray);
        derecha_muneca.setBackground(Color.lightGray);
        restablecer.setBackground(Color.lightGray);
        bajar_codo.setBackground(Color.lightGray);
        cerrar_codo.setBackground(Color.lightGray);
        pasos_90.setBackground(Color.lightGray);
        pasos_180.setBackground(Color.lightGray);
        pasos_360.setBackground(Color.lightGray);
        pasos_izquierda.setBackground(Color.lightGray);
        pasos_derecha.setBackground(Color.lightGray);
        automatico.setBackground(Color.WHITE);
        generar.setBackground(Color.WHITE);
        abrir_pinza.setBounds(50, 150, 210, 50);
        cerrar_pinza.setBounds(350, 150, 210, 50);
        izquierda_muneca.setBounds(50, 75, 210, 50);
        derecha_muneca.setBounds(350, 75, 210, 50);
        restablecer.setBounds(600, 75, 210, 50);
        subir_hombro.setBounds(50, 225, 210, 50); //hombro
        bajar_hombro.setBounds(350, 225, 210, 50);
        cerrar_codo.setBounds(50, 300, 210, 50);
        bajar_codo.setBounds(350, 300, 210, 50);
        automatico.setBounds(50, 450, 210, 50);
        generar.setBounds(350, 450, 210, 50);
        borrar.setBounds(600, 450, 210, 50);
        pasos_90.setBounds(50,380,110,50);
        pasos_180.setBounds(200,380,110,50);
        pasos_360.setBounds(350, 380, 110, 50);
        pasos_izquierda.setBounds(600,380,70,50);
        pasos_derecha.setBounds(680,380,70,50);
        add(pasos_derecha);
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
        add(cerrar_codo);
        add(bajar_codo);
        add(panel);
        add(automatico);
        add(generar);
        add(borrar);
        //  Conection();
        izquierda_muneca.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("SUBIENDO HOMBRO");
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
        cerrar_codo.addActionListener(new ActionListener() {
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
        pasos_90.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                giro = "noventa";
            }
        });
         pasos_180.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                giro = "ciento";
            }
        });
          pasos_360.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                giro = "trescientos";
            }
        });
          
        pasos_derecha.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(giro!= null){
                    String var_grado = "";
                    if(giro.equals("noventa")){
                        var_grado = "C";
                    }else if(giro.equals("ciento")){
                        var_grado = "D";
                    }else if(giro.equals("trescientos")){
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
            }else{
                    JOptionPane.showMessageDialog(null, "Elige el grado de giro a realizar");
                }
            }
        });  
        
        pasos_izquierda.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(giro!= null){
                    String var_grado = "";
                    if(giro.equals("noventa")){
                        var_grado = "F";
                    }else if(giro.equals("ciento")){
                        var_grado = "G";
                    }else if(giro.equals("trescientos")){
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
            }else{
                    JOptionPane.showMessageDialog(null, "Elige el grado de giro a realizar");
                }
            }
        });
        
          
          
          
          
        generar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gem = true;
                JOptionPane.showMessageDialog(null, "Presione los botones para generar secuencia");
            }
        });
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
            }
        });
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
                        System.out.println(lista.get(i).secuencia);
                        //enviarDatos(lista.get(i).secuencia);
                        try {
                            arduino.sendData(lista.get(i).secuencia);
                        } catch (ArduinoException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (SerialPortException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        }
                        
                    }
                  
                } else {
                    try {
                            arduino.sendData("9");
                        } catch (ArduinoException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (SerialPortException ex) {
                            Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                        }
                }
            }
        });
    }
    

    public static void main(String[] args) {
        Interfaz obj = new Interfaz();
        obj.setDefaultCloseOperation(EXIT_ON_CLOSE);
        obj.setSize(950, 600);
        obj.setLocation(250, 50);
        obj.setResizable(false);
        obj.setVisible(true);
    }
}
