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


class Cube {
  public double width, height, depth;
  public double posX, posY, posZ;
  public double rotX, rotY, rotZ;
  public double[] vertices = {
     -0.5, -0.5,  0.5, 
      0.5, -0.5,  0.5, 
      0.5,  0.5,  0.5, 
     -0.5,  0.5,  0.5, 
     -0.5, -0.5, -0.5, 
      0.5, -0.5, -0.5, 
      0.5,  0.5, -0.5, 
     -0.5,  0.5, -0.5, 
  };
  public int[] edges = {
    0, 1,  1, 2,  2, 3,  3, 0,  // front
    4, 5,  5, 6,  6, 7,  7, 4,  // back
    0, 4,  1, 5,  2, 6,  3, 7   // connect
  };

  Cube() {
    this.width = 100;
    this.height = 100;
    this.depth = 100;
    this.posX = 0;
    this.posY = 0;
    this.posZ = 0;
    this.rotX = 0;
    this.rotY = 0;
    this.rotZ = 0;
  }
  Cube(double width, double height, double depth) {
    this.width = width;
    this.height = height;
    this.depth = depth;
    this.posX = 0;
    this.posY = 0;
    this.posZ = 0;
    this.rotX = 0;
    this.rotY = 0;
    this.rotZ = 0;
  }
  Cube(double width, double height, double depth, double posX, double posY, double posZ) {
    this.width = width;
    this.height = height;
    this.depth = depth;
    this.posX = posX;
    this.posY = posY;
    this.posZ = posZ;
    this.rotX = 0;
    this.rotY = 0;
    this.rotZ = 0;
  }
  Cube(double width, double height, double depth, double posX, double posY, double posZ, double rotX, double rotY, double rotZ) {
    this.width = width;
    this.height = height;
    this.depth = depth;
    this.posX = posX;
    this.posY = posY;
    this.posZ = posZ;
    this.rotX = rotX;
    this.rotY = rotY;
    this.rotZ = rotZ;
  }

  // scale -> rotate -> translate -> project -> draw
  public void draw(GraphicsContext gc, double d) {
    for(int e = 0; e < 12*2; e += 2) {
      double X1 = vertices[edges[e]*3 + 0];
      double Y1 = vertices[edges[e]*3 + 1];
      double Z1 = vertices[edges[e]*3 + 2];
      double X2 = vertices[edges[e+1]*3 + 0];
      double Y2 = vertices[edges[e+1]*3 + 1];
      double Z2 = vertices[edges[e+1]*3 + 2];

      // scale
      X1 *= width;
      Y1 *= height;
      Z1 *= depth;
      X2 *= width;
      Y2 *= height;
      Z2 *= depth;

      // rotate
      double oldX1 = X1;
      double oldY1 = Y1;
      double oldZ1 = Z1;
      double oldX2 = X2;
      double oldY2 = Y2;
      double oldZ2 = Z2;

      // Rx
      Y1 = Y1 * Math.cos(rotX) - Z1 * Math.sin(rotX);
      Z1 = Y1 * Math.sin(rotX) + Z1 * Math.cos(rotX);
      Y2 = Y2 * Math.cos(rotX) - Z2 * Math.sin(rotX);
      Z2 = Y2 * Math.sin(rotX) + Z2 * Math.cos(rotX);

      // Ry
      X1 = oldX1 * Math.cos(rotY) + oldZ1 * Math.sin(rotY);
      Z1 = -oldX1 * Math.sin(rotY) + oldZ1 * Math.cos(rotY);
      X2 = oldX2 * Math.cos(rotY) + oldZ2 * Math.sin(rotY);
      Z2 = -oldX2 * Math.sin(rotY) + oldZ2 * Math.cos(rotY);

      // TODO: implement Z rotation
      // Rz
      // X = X * Math.cos(angle) - Y * Math.sin(angle);
      // Y = X * Math.sin(angle) + Y * Math.cos(angle);


      // translate
      X1 += posX;
      Y1 += posY;
      Z1 += posZ;
      X2 += posX;
      Y2 += posY;
      Z2 += posZ;

      // project
      double projX1 = d * X1/Z1;
      double projY1 = d * Y1/Z1;
      double projX2 = d * X2/Z2;
      double projY2 = d * Y2/Z2;

      // draw
      gc.strokeLine(projX1, projY1, projX2, projY2);
    }
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
      double X = 0;
      double Y = 0;
      double Z = 150;
      double delta = 1.0;
      double angleX = 0.0;
      double angleY = 0.0;
      double angleZ = 0.0;
      double deltaAngle = +0.010;

      public void handle(long currentNanoTime) {
        gc.clearRect(-ScreenW/2, -ScreenH/2, ScreenW, ScreenH);
        // gc.clearRect(0, 0, ScreenW, ScreenH);

        // X+=delta;
        // Y+=delta;
        // Z+=delta;
        // angleX+=deltaAngle;
        // angleY+=deltaAngle;
        angleZ+=deltaAngle;

        Cube c1 = new Cube(100, 100, 100, X, Y, Z, angleX, angleY, angleZ);
        c1.draw(gc, d);


        // Z += deltaZ;
        // double X = ScreenH/2;
        // double Y = ScreenH/2;
        // double depth = ScreenH/2;
        // angle += deltaAngle;
        // Z += deltaZ;
        // LineVertex[] vertices = new LineVertex[]{
        //   new LineVertex(-X, Y, Z, X, Y, Z),
        //   new LineVertex(X, Y, Z, X, -Y, Z),
        //   new LineVertex(-X, -Y, Z, X, -Y, Z),
        //   new LineVertex(-X, Y, Z, -X, -Y, Z),
        //
        //   new LineVertex(-X, Y, Z+depth, X, Y, Z+depth),
        //   new LineVertex(X, Y, Z+depth, X, -Y, Z+depth),
        //   new LineVertex(-X, -Y, Z+depth, X, -Y, Z+depth),
        //   new LineVertex(-X, Y, Z+depth, -X, -Y, Z+depth),
        //
        //   new LineVertex(-X, Y, Z, -X, Y, Z+depth),
        //   new LineVertex(X, Y, Z, X, Y, Z+depth),
        //   new LineVertex(-X, -Y, Z, -X, -Y, Z+depth),
        //   new LineVertex(X, -Y, Z, X, -Y, Z+depth)
        // };
        //
        // for(int i = 0; i < vertices.length; i++) {
        //   vertices[i].rotateY(angle);
        //   vertices[i].project(gc);
        // }

      }
    }.start();


    VBox vbox = new VBox(canvas);
    Scene scene = new Scene(vbox);
    primaryStage.setTitle("Cube");
    primaryStage.setScene(scene);
    primaryStage.show();
  }
}

