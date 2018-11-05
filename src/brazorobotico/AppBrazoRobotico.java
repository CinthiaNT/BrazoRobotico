package brazorobotico;

import com.panamahitek.PanamaHitek_Arduino;
import com.panamahitek.ArduinoException;
import com.panamahitek.PanamaHitek_MultiMessage;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ResourceBundle.Control;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.table.DefaultTableModel;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

public class AppBrazoRobotico extends JFrame {
    JPanel panel;
    JLabel motor1,motor2,motor3,motor4,motor5,X,Y,Z,imgBrazo;
    JTextField txtx1,txty1,txtz1,txtx2,txty2,txtz2,txtx3,txty3,txtz3,
               txtx4,txty4,txtz4,txtx5,txty5,txtz5;
    JScrollPane scrollTextArea;
    JButton ejecutar; 
    int contador;
    static PanamaHitek_Arduino arduino, arduinoSend;
    static SerialPortEventListener listener;
    static PanamaHitek_MultiMessage multi;
    static Scanner lector;
    static String entrada = "";
    FileWriter fichero = null;
    PrintWriter pw = null;

    public AppBrazoRobotico() {
        super("Brazo Robotico");
        this.setLayout(null);
        crear();
        try {
            arduino.arduinoTX("COM3", 9600);
        } catch (ArduinoException ex) {
            Logger.getLogger(Control.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            lector = new Scanner(new FileInputStream("src/texto/Cadena.txt"));
            while (lector.hasNext()) {
                entrada = lector.nextLine();
                contador++;
            }
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "Ha ocurrido un error al leer\nEl archivo indicado", "Analizador Lexico", JOptionPane.ERROR_MESSAGE);
        }
        armarPanelOeste();
        armarVentana();
        lanzar();
    }

    private void crear() {
        
        panel = new JPanel(null);
        motor1 = new JLabel("1. Gripper ");
        motor2 = new JLabel("2. Muñeca ");
        motor3 = new JLabel("3. Codo 1 ");
        motor4 = new JLabel("4. Hombro ");
        motor5 = new JLabel("5. Eje ");
        X = new JLabel("X");
        Y = new JLabel("Y");
        Z = new JLabel("Z");
        txtx1 = new JTextField();
        txty1 = new JTextField();
        txtz1 = new JTextField();
        txtx2 = new JTextField();
        txty2 = new JTextField();
        txtz2 = new JTextField();
        txtx3 = new JTextField();
        txty3 = new JTextField();
        txtz3 = new JTextField();
        txtx4 = new JTextField();
        txty4 = new JTextField();
        txtz4 = new JTextField();
        txtx5 = new JTextField();
        txty5 = new JTextField();
        txtz5 = new JTextField();
        imgBrazo = new JLabel();
        ejecutar = new JButton("Ejecutar Pasos");
        arduino = new PanamaHitek_Arduino();
        arduinoSend = new PanamaHitek_Arduino();
        multi = new PanamaHitek_MultiMessage(3, arduino);
    }
    
    void armarPanelOeste() {
        imgBrazo.setIcon(new ImageIcon ("src/imagenes/brazo.png"));
        imgBrazo.setBounds(400,48,395,270);
        motor1.setBounds(15, 40, 130, 50);
        motor2.setBounds(15, 100, 130, 50);
        motor3.setBounds(15, 160, 130, 50);
        motor4.setBounds(15, 220, 130, 50);
        motor5.setBounds(15, 280, 130, 50);
        txtx1.setBounds(135,52,50,23);
        txty1.setBounds(235,52,50,23);
        txtz1.setBounds(335,52,50,23);
        txtx2.setBounds(135,112,50,23);
        txty2.setBounds(235,112,50,23);
        txtz2.setBounds(335,112,50,23);
        txtx3.setBounds(135,172,50,23);
        txty3.setBounds(235,172,50,23);
        txtz3.setBounds(335,172,50,23);
        txtx4.setBounds(135,232,50,23);
        txty4.setBounds(235,232,50,23);
        txtz4.setBounds(335,232,50,23);
        txtx5.setBounds(135,292,50,23);
        txty5.setBounds(235,292,50,23);
        txtz5.setBounds(335,292,50,23);
        X.setBounds(150,0,90,50);
        Y.setBounds(250,0,90,50);
        Z.setBounds(350,0,90,50);
        ejecutar.setBounds(135,330,250,30);
        txtx1.setBackground(new Color(240, 240, 240));
        txty1.setBackground(new Color(240, 240, 240));
        txtz1.setBackground(new Color(240, 240, 240));
        txtx2.setBackground(new Color(240, 240, 240));
        txty2.setBackground(new Color(240, 240, 240));
        txtz2.setBackground(new Color(240, 240, 240));
        txtx3.setBackground(new Color(240, 240, 240));
        txty3.setBackground(new Color(240, 240, 240));
        txtz3.setBackground(new Color(240, 240, 240));
        txtx4.setBackground(new Color(240, 240, 240));
        txty4.setBackground(new Color(240, 240, 240));
        txtz4.setBackground(new Color(240, 240, 240));
        txtx5.setBackground(new Color(240, 240, 240));
        txty5.setBackground(new Color(240, 240, 240));
        txtz5.setBackground(new Color(240, 240, 240));
        ejecutar.setBackground(new Color(3,148,160));
        txtx1.setText("0");
        panel.add(motor1);
        panel.add(motor2);
        panel.add(motor3);
        panel.add(motor4);
        panel.add(motor5);
        panel.add(txtx1);
        panel.add(txty1);
        panel.add(txtz1);
        panel.add(txtx2);
        panel.add(txty2);
        panel.add(txtz2);
        panel.add(txtx3);
        panel.add(txty3);
        panel.add(txtz3);
        panel.add(txtx4);
        panel.add(txty4);
        panel.add(txtz4);
        panel.add(txtx5);
        panel.add(txty5);
        panel.add(txtz5);
        panel.add(X);
        panel.add(Y);
        panel.add(Z);
        panel.add(imgBrazo);
        panel.add(ejecutar);

}

    void armarVentana() {
        panel.setBounds(0, 0, 800, 400);
        panel.setBackground(Color.WHITE);
        add(panel);
    }

    void lanzar() {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(800, 400);
        this.setResizable(false);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }

}
