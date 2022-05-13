// written by Joshua-8 2022-05
// testing code for combining relays with a high resolution (PWMed) "fine adjust" to reduce relay movement

import grafica.*;

import java.util.Collections;
int gi=0;
GPlot plot;
int numRelays=5;
int numCoarseSteps=int(pow(2, numRelays));
float minRelayResistance=2;
float maxResistance=pow(2, numRelays-1)*minRelayResistance;
float fineResistance=20;
int relayValue=0;

GPointsArray points = new GPointsArray(500);
GPointsArray points2 = new GPointsArray(500);
void setup() {
  size(1024, 800);
  background(150);
  plot = new GPlot(this, 0, 0, width, height);
  //plot.setXLim(0, 500);
  plot.setYLim(0, 1.3);
}

void draw() {
  plot = new GPlot(this, 0, 0, width, height);

  if (gi>1000) {
    points.remove(0);
    points2.remove(0);
  }
  setLoad(.5-.3*mouseY/height);
  gi++;
  // Add the points
  plot.setPoints(points);

  plot.addLayer("points", points2);
  plot.getLayer("points").setPointColor(color(0, 0, 255));
  plot.defaultDraw();
}
//returns the resistance it set, for the Arduino it will return void, the coarse/fine algorithm is here
float setLoad(float val) {  
  print(val);
  print(",");

  float relayStepsInFine=maxResistance/fineResistance;
  val=constrain(val, 0, 1)*(1+relayStepsInFine/(numCoarseSteps));
  float fractionalRelayValue=(float)val*(numCoarseSteps);

  while (relayValue>=fractionalRelayValue&&relayValue>0) {
    // the relays would be too much resistence
    relayValue--;
  }
  while (relayValue+relayStepsInFine<=fractionalRelayValue&&relayValue<numCoarseSteps-1) {
    //the fine control + the relays can't reach high enough
    relayValue++;
  }


  float leftover=fractionalRelayValue-relayValue;
  print(relayValue);
  print(",");
  print(leftover);
  print(",");
  print(leftover/relayStepsInFine);
  //print(",");
  //print(relayValue+leftover);
  print(",");
  print(fractionalRelayValue);
  print(",");
  print((float)relayValue / (numCoarseSteps-1) + 0.5 / numCoarseSteps);
  print(",");
  print(int((constrain(((float)relayValue / (numCoarseSteps-1) + 0.5 / numCoarseSteps), 0.0, 1.0) * ((1 << numRelays) - 1))));
  println();
  points.add(new GPoint(gi, fractionalRelayValue));
  points2.add(new GPoint(gi, relayValue));

  return calcResistance(relayValue, leftover/relayStepsInFine);
}

float calcResistance(int val, float fine) {
  val=(int)constrain(val, 0, numCoarseSteps-1);
  fine=constrain(fine, 0, 1);
  double resistance=0; 
  //parallel resistor additon
  //println();
  for (int i=0; i<numRelays; i++) {
    //16 8 4 2
    //print(pow(2, numRelays-i-1)*minRelayResistance);
    //print(" ");
    resistance+=1.0/(pow(2, numRelays-i-1)*minRelayResistance)*getBit(val, i);
  }
  //println();
  resistance+=1.0/fineResistance*fine;
  return (float) (1.0/resistance);
}

int getBit(int val, int position) {
  return (val >> position) & 1;
}
