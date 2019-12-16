#include <PS2X_lib.h>  //for v1.6
PS2X ps2x; // create PS2 Controller Class
int error = 0; 
byte type = 0;
byte vibrate = 0;

bool proflag = false;
//motor pins

          int lfront1=37  ; //front
          int lfront2=36  ; //front
          int rfront1=38  ; //front
          int rfront2=39  ; //front
          int lback1=41  ;//back
          int lback2=40  ;//back
          int rback1=42  ;//back
          int rback2=43  ;//back
          
          int dummy = 0;
//pwm pins          
          int pwmlf=2  ; //left-front  
          int pwmrf=3  ; //right-front    
          int pwmlb=4  ; //left-back
          int pwmrb=5  ; //right-back

//pwm constants
          float lf = 1;
          float rf = 1;
          float lb = 1;
          float rb = 1;

void setup(){
  
//serial on  
         Serial.begin(57600);
//define output
         
         pinMode(lfront1,OUTPUT);
         pinMode(lfront2,OUTPUT);
         pinMode(lback1,OUTPUT);
         pinMode(lback2,OUTPUT);
         pinMode(rfront1,OUTPUT);
         pinMode(rfront2,OUTPUT);
         pinMode(rback1,OUTPUT);
         pinMode(rback2,OUTPUT);
         
         pinMode(pwmlf,OUTPUT);
         pinMode(pwmlb,OUTPUT);
         pinMode(pwmrf,OUTPUT);
         pinMode(pwmrb,OUTPUT);
        
         error = ps2x.config_gamepad(13,11,10,12, true, true);   //GamePad(clock(blue), command(orange), attention(yellow), data(brown), Pressures?, Rumble?
         //23-blue
         //25-brown
         //29-orange
         //27-yellow
 
         if(error == 0)
{
                 Serial.println("Found Controller, configured successful");
                 Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
                 Serial.println("holding L1 or R1 will print out the analog stick values.");
                 Serial.println("Go to www.billporter.info for updates and to report bugs.");
         }
           
          else if(error == 1)
                 Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");          
          else if(error == 2)
                 Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
           
          else if(error == 3)
                 Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
 
           
           type = ps2x.readType();
                          

}

void loop(){

           ps2x.read_gamepad(false, vibrate); 
           
           //programmable
           
           if(ps2x.ButtonPressed(PSB_SELECT))
           {
             Serial.println("Programmable Mode :");
             Serial.println("Press the button corresponding to the wheel with wrong direction :(Press Start to EXIT)");
             while(true)
             {
                ps2x.read_gamepad(false, vibrate);
                if(ps2x.ButtonPressed(PSB_GREEN)) {
                   Serial.print("lfront changed");
                   dummy = lfront1;
                   lfront1 = lfront2;
                   lfront2 = dummy;
                  }
                 if(ps2x.ButtonPressed(PSB_RED)) {
                   Serial.print("rfront changed");
                   dummy = rfront1;
                   rfront1 = rfront2;
                   rfront2 = dummy;
                  }
                  if(ps2x.ButtonPressed(PSB_PINK)) {
                   Serial.print("lback changed");
                   dummy = lback1;
                   lback1 = lback2;
                   lback2 = dummy;
                  }
                  if(ps2x.ButtonPressed(PSB_BLUE)) {
                   Serial.print("rback changed");
                   dummy = rback1;
                   rback1 = rback2;
                   rback2 = dummy;
                  }
                  if(ps2x.ButtonPressed(PSB_START))
                  {
                    Serial.println("Ready to run");
                    break;
                  }
                  if(ps2x.ButtonPressed(PSB_L1))
                  {
                    lf = lf-0.05;
                    Serial.println(lf);
                  }
                  if(ps2x.ButtonPressed(PSB_L2))
                  {
                    lb = lb-0.05;
                    Serial.println(lb);
                  }
                  if(ps2x.ButtonPressed(PSB_R1))
                  {
                    rf = rf-0.05;
                    Serial.println(rf);
                  }
                  if(ps2x.ButtonPressed(PSB_R2))
                  {
                    rb = rb-0.05;
                    Serial.println(rb);
                  }
                  delay(50);
             }
            }
           //navigation
                  
           if((ps2x.Analog(PSS_LX)!=123)||(ps2x.Analog(PSS_LY)!=123))
           {
                  
                  if(ps2x.Analog(PSS_LY)<100)
                  {
                  
                            int x=map(ps2x.Analog(PSS_LY),100,0,50,255);
                            
                            digitalWrite(lback1,HIGH);
                            digitalWrite(lback2,LOW);
                            
                            digitalWrite(lfront1, HIGH);
                            digitalWrite(lfront2, LOW);
                           
                            digitalWrite(rback1,HIGH);
                            digitalWrite(rback2,LOW);
                            
                            digitalWrite(rfront1, HIGH);
                            digitalWrite(rfront2, LOW);
                           
                            analogWrite(pwmlf,lf*x);
                            analogWrite(pwmlb,lb*x);
                            analogWrite(pwmrf,rf*x);
                            analogWrite(pwmrb,rb*x);
                            
                            Serial.print("forward @ ");
                            Serial.println(x);
                           
                    
                   }//end forward
                    
                    //backward
                    if(ps2x.Analog(PSS_LY)>150)
        
                    {
                            int x=map(ps2x.Analog(PSS_LY),150,255,50,255);
                            
                            digitalWrite(lback1,LOW);
                            digitalWrite(lback2,HIGH);
                            
                            digitalWrite(lfront1, LOW);
                            digitalWrite(lfront2, HIGH);
                           
                            digitalWrite(rback1,LOW);
                            digitalWrite(rback2,HIGH);
                            
                            digitalWrite(rfront1, LOW);
                            digitalWrite(rfront2, HIGH);
                           
                            analogWrite(pwmlf,lf*x);
                            analogWrite(pwmlb,lb*x);
                            analogWrite(pwmrf,rf*x);
                            analogWrite(pwmrb,rb*x);
                
                            
                            Serial.print("backward @ ");
                            Serial.println(x);
                        
                    }//end forward
                    
                    //left(motors on front and back)
                    else if(ps2x.Analog(PSS_LX)<100)
        
                    {
                        
                            int x=map(ps2x.Analog(PSS_LX),100,0,50,255);
                            
                            digitalWrite(lback1,HIGH);
                            digitalWrite(lback2,LOW);
                            
                            digitalWrite(lfront1, LOW);
                            digitalWrite(lfront2, HIGH);
                           
                            digitalWrite(rback1,LOW);
                            digitalWrite(rback2,HIGH);
                            
                            digitalWrite(rfront1, HIGH);
                            digitalWrite(rfront2, LOW);
                           
                            analogWrite(pwmlf,lf*x);
                            analogWrite(pwmlb,lb*x);
                            analogWrite(pwmrf,rf*x);
                            analogWrite(pwmrb,rb*x);
                            
                            Serial.print("left @ ");
                            Serial.println(x);
                                                      
                    }//emd left
                  
                    else if(ps2x.Analog(PSS_LX)>150)
        
                    {
                      
                            int x=map(ps2x.Analog(PSS_LX),150,255,50,255);
                              
                            digitalWrite(lback1,LOW);
                            digitalWrite(lback2,HIGH);
                            
                            digitalWrite(lfront1, HIGH);
                            digitalWrite(lfront2, LOW);
                           
                            digitalWrite(rback1,HIGH);
                            digitalWrite(rback2,LOW);
                            
                            digitalWrite(rfront1, LOW);
                            digitalWrite(rfront2, HIGH);
                           
                            analogWrite(pwmlf,lf*x);
                            analogWrite(pwmlb,lb*x);
                            analogWrite(pwmrf,rf*x);
                            analogWrite(pwmrb,rb*x);         
                              
                              Serial.print("right @ ");
                              Serial.println(x);                              
        
                    }//end of right
       
          }// end of navigation
          
          //turn right
          if(ps2x.Button(PSB_PINK))
          {
                            digitalWrite(lback1,HIGH);
                            digitalWrite(lback2,LOW);
                            
                            digitalWrite(lfront1, HIGH);
                            digitalWrite(lfront2, LOW);
                           
                            digitalWrite(rback1,LOW);
                            digitalWrite(rback2,HIGH);
                            
                            digitalWrite(rfront1, LOW);
                            digitalWrite(rfront2, HIGH);
                           
                            analogWrite(pwmlf,255);
                            analogWrite(pwmlb,255);
                            analogWrite(pwmrf,255);
                            analogWrite(pwmrb,255);
                    
                    Serial.println("turning right");        
        }//end of turn right
        
        
        //turn left
        if(ps2x.Button(PSB_RED))
          {
                            digitalWrite(lback1,LOW);
                            digitalWrite(lback2,HIGH);
                            
                            digitalWrite(lfront1, LOW);
                            digitalWrite(lfront2, HIGH);
                           
                            digitalWrite(rback1,HIGH);
                            digitalWrite(rback2,LOW);
                            
                            digitalWrite(rfront1, HIGH);
                            digitalWrite(rfront2, LOW);
                           
                            analogWrite(pwmlf,255);
                            analogWrite(pwmlb,255);
                            analogWrite(pwmrf,255);
                            analogWrite(pwmrb,255);
                    
                    Serial.println("turning left");         
        }//end of turn left
          
          
          delay(100);
          
                            digitalWrite(lback1,LOW);
                            digitalWrite(lback2,LOW);
                            
                            digitalWrite(lfront1, LOW);
                            digitalWrite(lfront2, LOW);
                           
                            digitalWrite(rback1,LOW);
                            digitalWrite(rback2,LOW);
                            
                            digitalWrite(rfront1, LOW);
                            digitalWrite(rfront2, LOW);
                            
                            
        
}    
                    
                    
                    
                    
                    
