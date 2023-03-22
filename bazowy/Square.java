import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

public class Square extends JFrame implements MouseListener{
    JLabel label;

    Square(JLabel rozgrywka) {
//        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        this.setSize(500, 500);
//        this.setLayout(null);

        label = rozgrywka;
        label.setBounds(0, 0, 100, 100);
        label.setBackground(Color.red);
        label.setOpaque(true);
        label.addMouseListener(this);
        this.add(label);
        this.setVisible(true);
    }

    @Override
    public void mouseClicked(MouseEvent e){
        System.out.println("You clicked");
    }
    @Override
    public void mousePressed(MouseEvent e) {
        System.out.println("You pressed mouse");

    }
    @Override
    public void mouseReleased(MouseEvent e)
    {
        System.out.println("Released");
    }
    public void mouseEntered(MouseEvent e)
    {
        System.out.println("entered");
    }
    @Override
    public void mouseExited(MouseEvent e)
    {
        System.out.println("exited");
    }

}
