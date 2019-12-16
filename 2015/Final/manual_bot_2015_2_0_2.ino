//Team Robocon 2015
//BITS Pilani

#include <PS2X_lib.h>  //for v1.6
#include<Servo.h>
PS2X ps2x; // create PS2 Controller Class
int error = 0; 
byte type = 0;
byte vibrate = 0;

bool proflag = false;
bool pwmflag = true;
//motor pins

          int lfront1=35  ; //front
          int lfront2=37  ; //front
          int rfront1=31  ; //front
          int rfront2=33  ; //front
          int lback1=39  ;//back
          int lback2=41  ;//back
          int rback1=43  ;//back
          int rback2=45  ;//back
          
          int dummy = 0;
//pwm pins          
          int pwmlf=5  ; //left-front  
          int pwmrf=4  ; //right-front    
          int pwmlb=6  ; //left-back
          int pwmrb=7  ; //right-back

//pwm constants
          float lf = 1;
          float rf = 1;
          float lb = 1;
          float rb = 1;
          
//Servo
 	  Servo finger;
          int pos=0;
	  int x_delay=45;
//Solenoids
         
         int srv = 25;
         int hit = 29;
	 int dsp = 27;
         bool srvstate = false;
         bool hitstate = false;
         
//timer
          unsigned long currenttime = 0;
          unsigned long srv_start_time = 0;
          unsigned long hit_start_time = 0;
         

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
	
	 pinMode(dsp,OUTPUT);
         pinMode(srv,OUTPUT);
         pinMode(hit,OUTPUT);
         
         finger.attach(2);
        
         error = ps2x.config_gamepad(11,9,10,8, true, true);   //GamePad(clock(blue), command(orange), attention(yellow), data(brown), Pressures?, Rumble?
         //10-blue
         //8-brown
         //11-orange
         //9-yellow
 
         if(error == 0)
        {
                 Serial.println("Found Controller, configured successful");
                 Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
                 Serial.println("holding L1 or R1 will print out the analog stick values.");
                 Serial.println("Go to www.billporter.info for updates and to report bugs.");
         }
           
          else if(error == 1)
          {
                 Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
                 return;         
          } 
          else if(error == 2)
                 Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
           
          else if(error == 3)
                 Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
 
           
           type = ps2x.readType();
	                          

}

void loop(){
  
           if(error == 1) //skip loop if no controller found
              return;

           ps2x.read_gamepad(false, vibrate); 
           
           //programmable
           
           if(ps2x.ButtonPressed(PSB_SELECT))
           {
               Serial.println("Programmable Mode :");
               Serial.println("Press the button corresponding to the wheel with wrong direction :(Press Start to EXIT)");
               while(true)
                 {
                    ps2x.read_gamepad(false, vibrate);
                    
                    //Reversing Motors Polarity
                    if(ps2x.ButtonPressed(PSB_GREEN)) 
                    {
                      Serial.print("lfront changed");
                      dummy = lfront1;
                      lfront1 = lfront2;
                      lfront2 = dummy;
                    }
                    else if(ps2x.ButtonPressed(PSB_RED)) 
                    {
                      Serial.print("rfront changed");
                      dummy = rfront1;
                      rfront1 = rfront2;
                      rfront2 = dummy;
                     }
                    else if(ps2x.ButtonPressed(PSB_PINK))
                    {
                      Serial.print("lback changed");
                      dummy = lback1;
                      lback1 = lback2;
                      lback2 = dummy;
                    }
                    else if(ps2x.ButtonPressed(PSB_BLUE)) 
                    {
                      Serial.print("rback changed");
                      dummy = rback1;
                      rback1 = rback2;
                      rback2 = dummy;
                    }
                    //end - Reversing Motors Polarity
                   
                    //Changing PWM 
                    else if(ps2x.ButtonPressed(PSB_L1))
                    {
                      if(pwmflag)
                        lf = lf-0.05;
                      else
                        lf = lf+0.05;
                      Serial.println(lf);
                    }
                    else if(ps2x.ButtonPressed(PSB_L2))
                    {
                      if(pwmflag)
                        lb = lb-0.05;
                      else
                        lb = lb+0.05;
                      Serial.println(lb);
                    }
                    else if(ps2x.ButtonPressed(PSB_R1))
                    {
                      if(pwmflag)
                        rf = rf-0.05;
                      else
                        rf = rf+0.05;
                      Serial.println(rf);
                    }
                    else if(ps2x.ButtonPressed(PSB_R2))
                    {
                      if(pwmflag)
                        rf = rf-0.05;
                      else
                        rf = rf+0.05;
                      Serial.println(rb);
                    }
                    //end-Changing PWM
                    
                    else if(ps2x.ButtonPressed(PSB_SELECT))
                    {
                      if(pwmflag)
                        pwmflag = false;
                      else
                        pwmflag = true;
                    }
                    
                    else if(ps2x.ButtonPressed(PSB_START))
                    {
                      Serial.println("Ready to run");
                      break;
                    }
                    
                  delay(50);
                 }//end of while
            }//end of programmable mode
            
            
           //navigation (Left)
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
                        
                    }//end backward
                    
                    //left
                    if(ps2x.Analog(PSS_LX)<100)
        
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
                                                      
                    }//end left
                    
                    //right
                    if(ps2x.Analog(PSS_LX)>150)
        
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
       
          }// end of navigation (Left)
          
          
	//navigation (Right)
           if((ps2x.Analog(PSS_RX)!=123)||(ps2x.Analog(PSS_RY)!=123))
           {
                  
                  if(ps2x.Analog(PSS_RY)<100)
                  {
                  
                            int x=map(ps2x.Analog(PSS_RY),100,0,50,255);
                            
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
                   if(ps2x.Analog(PSS_RY)>150)
                    {
                            int x=map(ps2x.Analog(PSS_RY),150,255,50,255);
                            
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
                        
                    }//end backward
                    
                    //left
                    if(ps2x.Analog(PSS_RX)<100)
        
                    {
                        
                            int x=map(ps2x.Analog(PSS_RX),100,0,50,255);
                            
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
                                                      
                    }//end left
                    
                    //right
                    if(ps2x.Analog(PSS_RX)>150)
        
                    {
                      
                            int x=map(ps2x.Analog(PSS_RX),150,255,50,255);
                              
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
       
          }// end of navigation (Right)
          

          //turn right
          if(ps2x.Button(PSB_RED))
          {
                            int x=ps2x.Analog(ps2x.Analog(PSAB_PAD_RIGHT));
                            
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
        if(ps2x.Button(PSB_PINK))
          {
                            int x=ps2x.Analog(ps2x.Analog(PSAB_PAD_LEFT));
                             
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
        
        
        //Service
        if(ps2x.Button(PSB_R1))
        {          
             Serial.println("R1 pressed");
             
             //Stop Motion
                            digitalWrite(lback1,LOW);
                            digitalWrite(lback2,LOW);
                            
                            digitalWrite(lfront1, LOW);
                            digitalWrite(lfront2, LOW);
                           
                            digitalWrite(rback1,LOW);
                            digitalWrite(rback2,LOW);
                            
                            digitalWrite(rfront1, LOW);
                            digitalWrite(rfront2, LOW);
                            
                            delay(100);
                            
            digitalWrite(dsp,HIGH);
            delay(400);
            
            for(pos = 100; pos<=145; pos+=5)     // goes from 180 degrees to 0 degrees 
            {                             
                finger.write(pos);              // tell servo to go to position in variable 'pos' 
                delay(10);                       // waits 15ms for the servo to reach the position 
            } 
            
            delay(400);
            
            digitalWrite(dsp,LOW);
            delay(400);
            
            for(pos = 145; pos >= 100; pos -= 5) // goes from 0 degrees to 180 degrees 
            {                                  // in steps of 1 degree 
              finger.write(pos);              // tell servo to go to position in variable 'pos' 
              delay(10);                       // waits 15ms for the servo to reach the position 
            }
            
            delay(x_delay);
            
            digitalWrite(srv,HIGH);
            delay(500);
            digitalWrite(srv,LOW);
            delay(500);
            
        }//end Service
	
          //Service delay	
	  if(ps2x.ButtonPressed(PSB_L1))
                  {
                    x_delay++;
                  }
          if(ps2x.ButtonPressed(PSB_L2))
                  {
                    x_delay--;
                  }
        
        //Service Racket
        if(ps2x.Button(PSB_CROSS))
        {
                digitalWrite(srv,HIGH);
                srvstate = true;
                srv_start_time = millis();
         }
            
         //Hitting Racket
         if(ps2x.Button(PSB_TRIANGLE))
         {
                digitalWrite(hit,HIGH);
                hitstate = true;
                hit_start_time = millis();
         }
        
         
        
         currenttime = millis();
         if(srvstate && currenttime - srv_start_time > 400)
         {
               digitalWrite(srv,LOW);
               srvstate = false;
         }
         if(hitstate && currenttime - hit_start_time > 400)
         {
               digitalWrite(hit,LOW);
               hitstate = false;
         }
         
         
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
                    
                    
                    
                    
                    
