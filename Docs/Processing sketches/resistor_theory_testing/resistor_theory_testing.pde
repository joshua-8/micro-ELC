// written by Joshua-8 2022-03


import grafica.*;

import java.util.Collections;

//simulate resistors being inaccurate
float[] scale={1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

void setup() {
  size(1024, 500);
  background(150);

  GPointsArray points = new GPointsArray();



  GPlot plot = new GPlot(this, 0, 0, width, height);

  // Set the plot title and the axis labels
  plot.setTitleText("series resistors");
  plot.getXAxis().setAxisLabelText("binary");
  plot.getYAxis().setAxisLabelText("current");

  //calculate for each value
  for (int i=0; i<256; i++) {
    points.add(i, new GPoint(i, 200/calcResistance(i)));
  }

  // Add the points
  plot.setPoints(points); 

  // Draw it!
  plot.setXLim(0, 255); 

  plot.setYLim(0, 200);

  plot.defaultDraw();
}

float calcResistance(int val) {
  double resistance=0; 
  ////parallel resistor additon
  //for (int i=0; i<8; i++) {
  //  resistance+=1.0/(pow(2, 7-i)*scale[i])*getBit(val, i);
  //}
  //return (float) (1.0/resistance);

  //series resistor addition
  for (int i=0; i<8; i++) {
    resistance+=(pow(2, i)*getBit(val, i));
  }
  return (float) (resistance);
}

int getBit(int val, int position) {
  return (val >> position) & 1;
}
