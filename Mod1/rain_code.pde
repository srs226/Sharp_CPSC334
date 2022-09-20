//Import necessary java libs for screen mapping
import java.awt.GraphicsEnvironment;
import java.awt.GraphicsDevice;

int[] cycle = {0,0,0,0,0,0};

//rightmost(bottom) x coord of section rounded
int full_width = 8160
int[] x_init = {full_width/2, round(full_width/3) - 10, round(full_width/6) - 10, round(2*full_width/3) - 10, round(5*full_width/6) - 10, full_width, 0};
int[] x = {full_width/2, round(full_width/3) - 10, round(full_width/6) - 10, round(2*full_width/3) - 10, round(5*full_width/6) - 10, full_width};
//background and rain colors of the six screens
color color1_1 = new_color();
color color1_2 = new_color();;

color color2_1 = new_color();
color color2_2 = new_color();

color color3_1 = new_color();
color color3_2 = new_color();

color color4_1 = new_color();
color color4_2 = new_color();

color color5_1 = new_color();
color color5_2 = new_color();

color color6_1 = new_color();
color color6_2 = new_color();

class rain_drops{
  float x_rain;
  float y;
  
  rain_drops(){
    y = random(400);
    x_rain = x[int(random(6))];
  }
  
  void rain(float speed){
    x_rain += speed;
  }
}
  

rain_drops drops[] = new rain_drops[200];

//place the display in the top left corner of the second display
void positionDisplay() {
  surface.setResizable(true);
  
  GraphicsEnvironment g = GraphicsEnvironment.getLocalGraphicsEnvironment();
  GraphicsDevice[] devices = g.getScreenDevices();
  
  int bigWidth = 0;
  int bigHeight = 0;
  
  int smallWidth = 0;
  int smallHeight = 0;
  
  for(int i = 0; i < devices.length; i++) {
    float currWidth = devices[i].getDisplayMode().getWidth();
    float currHeight = devices[i].getDisplayMode().getHeight();
    float ratio = currWidth / currHeight;
    if(ratio > 2.0) {
      bigWidth = Math.round(currWidth);
      bigHeight = Math.round(currHeight);
    } else {
      smallWidth = Math.round(currWidth);
      smallHeight = Math.round(currHeight);
    }
  }
  
  surface.setSize(bigWidth * 2, bigHeight);
  surface.setLocation(smallWidth, 0);
}

void setup() {
  positionDisplay();
  for(int i = 0; i < 200; i++){
    drops[i] = new rain_drops();
  }
}
  
void draw() {
  clear();
  setBackground(x);  //set background as starter colors
  
  //screen1 - rec3
  if(cycle[0] < 3){
    waves(x[0], color1_1, color1_2);
    if(cycle[0] == 0){
      x[0] -=30;
    }
    
    cycle[0]++;
  }
  else if(cycle[0] > 2 && cycle[0] < 5){
    waves2(x[0], color1_1, color1_2);
    if(cycle[0] == 3){
      x[0] -=30;
    }
    cycle[0]++;
  }
  else{
    cycle[0] = 0;
    waves2(x[0], color1_1, color1_2);
  }
  if(x[0] <= width/3 + 10){
    x[0] = x_init[0];
    color1_1 = color1_2;
    color1_2 = new_color();
  }
  
  
  //screen2 - rec2
  if(cycle[1] < 2){
    waves(x[1], color2_1, color2_2);
    if(cycle[1] == 0){
      x[1] -= 20;
    }
    cycle[1]++;    
  }
  else if(cycle[1] > 1 && cycle[1] < 3){
    waves2(x[1], color2_1, color2_2);
    if(cycle[1] == 2){
      x[1] -= 20;
    }
    cycle[1]++;
  }
  else{
    cycle[1] = 0;
    waves2(x[1], color2_1, color2_2);
  }
  if(x[1] <= width/6 + 10){
    x[1] = x_init[1];
    color2_1 = color2_2;
    color2_2 = new_color();
  }
  
  //screen3 - rec1
  if(cycle[2] < 5) {
    waves(x[2], color3_1, color3_2);
    if(cycle[2] == 0){
      x[2] -= 50;
    }
    cycle[2]++;
  }
  else if(cycle[2] > 4 && cycle[2] < 10){
    waves2(x[2], color3_1, color3_2);
    if(cycle[2] == 5){
      x[2] -= 50;
    }
    cycle[2]++;
  }
  else{
    cycle[2] = 0;
    waves2(x[2], color3_1, color3_2);
  }
  if(x[2] <= 0){
    x[2] = x_init[2];
    //choose new rain color, set prev color to background
    color3_1 = color3_2;
    color3_2 = new_color();
  }

  
  //screen4 - rec6
  if(cycle[5] == 0) {
    waves(x[5], color6_1, color6_2);
    x[5] -= 10;
    cycle[5]++;
  }
  else if(cycle[5] == 1) {
    waves2(x[5], color6_1, color6_2);
    x[5] -= 10;
    cycle[5]--;
  }
  if(x[5] <= width*.83333 +10) {
    x[5] = x_init[5];
    //choose new rain color, set prev color to background
    color6_1 = color6_2;
    color6_2 = new_color();
  }

  
  //screen5 - rec5
  if(cycle[4] < 6) {
    waves(x[4], color5_1, color5_2);
    if(cycle[4] == 0){
      x[4] -= 60;
    }
    cycle[4]++;
  }
  else if(cycle[4] > 5 && cycle[4] < 12) {
    waves2(x[4], color5_1, color5_2);
    if(cycle[4] == 6){
      x[4] -= 60;
    }
    cycle[4]++;
  }
  else{
    waves2(x[4], color5_1, color5_2);
    cycle[4] = 0;
  }
  if(x[4] <= (width*.66666 + 10)) {
    x[4] = x_init[4];
    //choose new rain color, set prev color to background
    color5_1 = color5_2;
    color5_2 = new_color();
  }
  
  //screen6 - rec4
  if(cycle[3] < 4) {
    waves(x[3], color4_1, color4_2);
    if(cycle[3] == 0){
      x[3] -= 40;
    }
    cycle[3]++;
  }
  else if(cycle[3] > 3 && cycle[3] < 8) {
    waves2(x[3], color4_1, color4_2);
    if(cycle[3] == 4){
      x[3] -= 40;
    }
    cycle[3]++;
  }
  else{
    waves2(x[3], color4_1, color4_2);
    cycle[3] = 0;
  }
  if(x[3] <= (width/2 + 10)) {
    x[3] = x_init[3];
    //choose new rain color, set prev color to background
    color4_1 = color4_2;
    color4_2 = new_color();
  }
  
  delay(500);
  
  rainfall();
  
  delay(500);
}

//before setup make struct and populate with a number of drops with random spots on the screen, make function to tell what color they should be
//draw them each time in the right color
void rainfall(){
   for(int i = 0; i < 200; i++){
     drops[i].rain(random(40));
     if(drops[i].x_rain > width){
       drops[i].x_rain = drops[i].x_rain - width;
     }
     if(drops[i].x_rain <= x_init[2]){
       fill(color3_2);
       stroke(color3_2);
       rect(drops[i].x_rain, drops[i].y, 2, 2);
     }
     else if(drops[i].x_rain <= x_init[1] && drops[i].x_rain > x_init[2]){
       fill(color2_2);
       stroke(color2_2);
       rect(drops[i].x_rain, drops[i].y, 2, 2);
     }
     else if(drops[i].x_rain <= x_init[0] && drops[i].x_rain > x_init[1]){
       fill(color1_2);
       stroke(color1_2);
       rect(drops[i].x_rain, drops[i].y, 2, 2);
     }
     else if(drops[i].x_rain <= x_init[3] && drops[i].x_rain > x_init[2]){
       fill(color4_2);
       stroke(color4_2);
       rect(drops[i].x_rain, drops[i].y, 2, 2);
     }
     else if(drops[i].x_rain <= x_init[4] && drops[i].x_rain > x_init[3]){
       fill(color5_2);
       stroke(color5_2);
       rect(drops[i].x_rain, drops[i].y, 2, 2);
     }
     else{
       fill(color6_2);
       stroke(color6_2);
       rect(drops[i].x_rain, drops[i].y, 2, 2);
     }
   }
}



color new_color(){
  color new_color = color(random(100, 255), random(55, 120), random(100, 255));
  return new_color;
}


void waves(int x_coord, color col1, color col2){
  
    //convex?? who knows
    fill(col2);
    stroke(col2);
    beginShape();
    vertex(x_coord, 0);
    bezierVertex(x_coord+1-10, 0, x_coord-10, height*.1, x_coord, height*.1);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.2);
    bezierVertex(x_coord-10, height*.2, x_coord-10, height*.3, x_coord, height*.3);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.4);
    bezierVertex(x_coord-10, height*.4, x_coord-10, height*.5, x_coord, height*.5);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.6);
    bezierVertex(x_coord-10, height*.6, x_coord-10, height*.7, x_coord, height*.7);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.8);
    bezierVertex(x_coord-10, height*.8, x_coord-10, height*.9, x_coord, height*.9);
    endShape();
    
    
    //concave??
    fill(col1);
    stroke(col1);
    beginShape();
    vertex(x_coord, height*.1);
    bezierVertex(x_coord+10, height*.1, x_coord+10, height*.2, x_coord, height*.2);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.3);
    bezierVertex(x_coord+10, height*.3, x_coord+10, height*.4, x_coord, height*.4);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.5);
    bezierVertex(x_coord+10, height*.5, x_coord+10, height*.6, x_coord, height*.6);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.7);
    bezierVertex(x_coord+10, height*.7, x_coord+10, height*.8, x_coord, height*.8);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.9);
    bezierVertex(x_coord+10, height*.9, x_coord+10, height, x_coord, height);
    endShape();
}

void waves2(int x_coord, color col1, color col2){
  //reorganize them so only two fill statements, add color to args
    fill(col1);
    stroke(col2);
    
    //concave
    beginShape();
    vertex(x_coord, 0);
    bezierVertex(x_coord+10, 0, x_coord+10, height*.1, x_coord, height*.1);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.2);
    bezierVertex(x_coord+10, height*.2, x_coord+10, height*.3, x_coord, height*.3);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.4);
    bezierVertex(x_coord+10, height*.4, x_coord+10, height*.5, x_coord, height*.5);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.6);
    bezierVertex(x_coord+10, height*.6, x_coord+10, height*.7, x_coord, height*.7);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.8);
    bezierVertex(x_coord+10, height*.8, x_coord+10, height*.9, x_coord, height*.9);
    endShape();
    
    fill(col2);
    stroke(col2);
    //convex
    beginShape();
    vertex(x_coord, height*.1);
    bezierVertex(x_coord-10, height*.1, x_coord-10, height*.2, x_coord, height*.2);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.3);
    bezierVertex(x_coord-10, height*.3, x_coord-10, height*.4, x_coord, height*.4);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.5);
    bezierVertex(x_coord-10, height*.5, x_coord-10, height*.6, x_coord, height*.6);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.7);
    bezierVertex(x_coord-10, height*.7, x_coord-10, height*.8, x_coord, height*.8);
    endShape();
    
    beginShape();
    vertex(x_coord, height*.9);
    bezierVertex(x_coord-10, height*.9, x_coord-10, height, x_coord, height);
    endShape();
    
    //x_coord += 10;
}

//set background
void setBackground(int[] x){
  //screen3 - rec1
  fill(color3_1);
  stroke(color3_2);
  rect(0, 0, x[2], height);
  
  fill(color3_2);
  rect(x[2], 0, width/6 - x[2], height);
  
  //screen2 - rec2
  fill(color2_1);
  stroke(color2_2);
  rect(width/6, 0, x[1] - width/6, height);
  
  fill(color2_2);
  rect(x[1], 0, width/3 - x[1], height);
  
  //screen1 - rec3
  fill(color1_1);
  stroke(color1_2);
  rect(width/3, 0, x[0] - width/3, height);
  
  fill(color1_2);
  rect(x[0], 0, width/2 - x[0], height);
  
  //screen4
  fill(color4_1);
  stroke(color4_2);
  rect(width/2, 0, x[3] - width/2, height);
  
  fill(color4_2);
  rect(x[3], 0, width*(.6666) - x[3], height);
  
  //screen5
  fill(color5_1);
  stroke(color5_2);
  rect(width*.6666, 0, x[4] - width*.6666, height);
  
  fill(color5_2);
  rect(x[4], 0, width*.833333 - x[4], height);
  
  //screen6
  fill(color6_1);
  stroke(color6_2);
  rect(width*.833333, 0, x[5] - width*.833333, height);
  
  fill(color6_2);
  rect(x[5], 0, width - x[5], height);
}
