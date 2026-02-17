import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.animation.AnimationTimer;


class LineVertex {
  public double X1;
  public double Y1;
  public double Z1;
  public double X2;
  public double Y2;
  public double Z2;
  public static double d;

  public LineVertex(double X1, double Y1, double Z1, double X2, double Y2, double Z2) {
    this.X1 = X1;
    this.Y1 = Y1;
    this.Z1 = Z1;
    this.X2 = X2;
    this.Y2 = Y2;
    this.Z2 = Z2;
  }

  public static void setDistance(double distance) {
    d = distance;
  }

  public void project(GraphicsContext gc) {
    gc.strokeLine(d*X1/Z1, d*Y1/Z1, d*X2/Z2, d*Y2/Z2);
  }

  public void rotateY(double angle) {
    Z1 -= 300/2;
    Z2 -= 300/2;

    double oldX1 = X1;
    double oldZ1 = Z1;
    double oldX2 = X2;
    double oldZ2 = Z2;

    X1 = oldX1 * Math.cos(angle) + oldZ1 * Math.sin(angle);
    Z1 = -oldX1 * Math.sin(angle) + oldZ1 * Math.cos(angle);
    X2 = oldX2 * Math.cos(angle) + oldZ2 * Math.sin(angle);
    Z2 = -oldX2 * Math.sin(angle) + oldZ2 * Math.cos(angle);

    Z1 += 300/2;
    Z2 += 300/2;
  }
}



public class Main extends Application {
  public double d = 195;
  // public int ScreenW = 1920;
  // public int ScreenH = 1080;
  public int ScreenW = 400;
  public int ScreenH = 300;


  public static void main(String[] args) {
    launch(args);
  }



  @Override
  public void start(Stage primaryStage) {
    Canvas canvas = new Canvas(ScreenW, ScreenH);
    GraphicsContext gc = canvas.getGraphicsContext2D();
    gc.setFill(Color.BLACK);
    gc.translate(ScreenW/2, ScreenH/2);

    LineVertex.setDistance(d);


    new AnimationTimer() {
      double Z = 400;
      double deltaZ = 1.0;
      double angle = 0.0;
      double deltaAngle = +0.001;

      public void handle(long currentNanoTime) {
        gc.clearRect(-ScreenW/2, -ScreenH/2, ScreenW, ScreenH);

        // Z += deltaZ;
        double X = ScreenH/2;
        double Y = ScreenH/2;
        double depth = ScreenH/2;
        angle += deltaAngle;
        // Z += deltaZ;


        // double oldX = X;
        // double oldY = Y;
        // double oldZ = Z;

        // Rz
        // X = X * Math.cos(angle) - Y * Math.sin(angle);
        // Y = X * Math.sin(angle) + Y * Math.cos(angle);

        // Ry
        // X = oldX * Math.cos(angle) - oldZ * Math.sin(angle);
        // Z = -oldX * Math.sin(angle) + oldZ * Math.cos(angle);

        // Rx
        // Y = Y * Math.cos(angle) - Z * Math.cos(angle);
        // Z = Y * Math.sin(angle) + Z * Math.cos(angle);

        LineVertex[] vertices = new LineVertex[]{
          new LineVertex(-X, Y, Z, X, Y, Z),
          new LineVertex(X, Y, Z, X, -Y, Z),
          new LineVertex(-X, -Y, Z, X, -Y, Z),
          new LineVertex(-X, Y, Z, -X, -Y, Z),

          new LineVertex(-X, Y, Z+depth, X, Y, Z+depth),
          new LineVertex(X, Y, Z+depth, X, -Y, Z+depth),
          new LineVertex(-X, -Y, Z+depth, X, -Y, Z+depth),
          new LineVertex(-X, Y, Z+depth, -X, -Y, Z+depth),

          new LineVertex(-X, Y, Z, -X, Y, Z+depth),
          new LineVertex(X, Y, Z, X, Y, Z+depth),
          new LineVertex(-X, -Y, Z, -X, -Y, Z+depth),
          new LineVertex(X, -Y, Z, X, -Y, Z+depth)
        };

        for(int i = 0; i < vertices.length; i++) {
          vertices[i].rotateY(angle);
          vertices[i].project(gc);
        }

      }
    }.start();


    VBox vbox = new VBox(canvas);
    Scene scene = new Scene(vbox);
    primaryStage.setTitle("Cube");
    primaryStage.setScene(scene);
    primaryStage.show();
  }
}

