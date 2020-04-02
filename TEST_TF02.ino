/**************************************
 * Author : Vahid Behtaji           ***
 * Description :                    ***
 *     rosserial connecting         ***
 *     three TF02(single Beam Lidar) **
 *     to Arduino with ROS          *** 
 *     Calculate:
 *     Distance, Gradient           ***
 */************************************
float dist1,dist2,dist3,GDT,angle,theta; //actual distance measurements of LiDAR
int check; //save check value
int i;
int uart[9]; //save data measured by LiDAR
const int HEADER=0x59; //frame header of data package
float threshold = 0.1; // the compensate value 
//long tn = 0;
//long tp = 0;
//float fr = 0;

void setup()
{
Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
Serial1.begin(9600); //set bit rate of serial port connecting LiDAR with Arduino
Serial2.begin(9600); //set bit rate of serial port connecting LiDAR with Arduino
Serial3.begin(9600); //set bit rate of serial port connecting LiDAR with Arduino
}
void loop()
{
  
//  fr = 1000.0/(millis() - tp);
////  Serial.print(millis());
////  Serial.print('\t'); 
//  Serial.print(fr);
//  Serial.print('\t'); 
//  tp = millis();
  
  //dist1 = 0; dist2 = 0; 
  Get_Reading_S1();
  Get_Reading_S2();
  Get_Reading_S3();
  Get_Angle();
  
//  Serial.print("val1 = ");
//  Serial.print(dist1);//output measure distance value of LiDAR
//  Serial.print('\t'); 
//  
//  Serial.print("val2 = ");
//  Serial.print(dist2);//output measure distance value of LiDAR
//  Serial.print('\t');
//
//  Serial.print("val3 = ");
//  Serial.print(dist3);//output measure distance value of LiDAR
//  Serial.print('\t');


  Serial.print("angle = ");
  Serial.print(angle);//output measure distance value of LiDAR
  Serial.print('\n');

  
  
  
}


void Get_Reading_S1(){ 
/*
 *****************************************************************************************************
                                TF02_1 Reading
 *****************************************************************************************************                               
*/

  if (Serial1.available()) //check if serial port has data input
  {
  if(Serial1.read()==HEADER) //assess data package frame header 0x59
    {
      uart[0]=HEADER;
      if( Serial1.read()==HEADER) //assess data package frame header 0x59
      {
         uart[1]=HEADER;
          for(i=2;i<9;i++) //save data in array
            {
                uart[i]=Serial1.read();
            }
                check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
                if(uart[8]==(check&0xff))//ver ify the received data as per protocol
          {
             
             dist1=(uart[2]+uart[3]*256.0)/100; //calculate distance value
             
             
             
      }
           
        }
    }
  }
 
/*
 ********************************************************************************************************
 *                            End-Of TF02-1 Reading
 ********************************************************************************************************
*/
}




void Get_Reading_S2(){ 
/*
 *****************************************************************************************************
                                TF02_2 Reading
 *****************************************************************************************************                               
*/

  if (Serial2.available()) //check if serial port has data input
  {
  if(Serial2.read()==HEADER) //assess data package frame header 0x59
    {
      uart[0]=HEADER;
      if( Serial2.read()==HEADER) //assess data package frame header 0x59
      {
         uart[1]=HEADER;
          for(i=2;i<9;i++) //save data in array
            {
                uart[i]=Serial2.read();
            }
                check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
                if(uart[8]==(check&0xff))//ver ify the received data as per protocol
          {
             
             dist2=(uart[2]+uart[3]*256.0)/100; //calculate distance value
             
             
             
      }
           
        }
    }
  }
 
/*
 ********************************************************************************************************
 *                            End-Of TF02-2 Reading
 ********************************************************************************************************
*/
}



void Get_Reading_S3(){ 
/*
 *****************************************************************************************************
                                TF02_3 Reading
 *****************************************************************************************************                               
*/

  if (Serial3.available()) //check if serial port has data input
  {
  if(Serial3.read()==HEADER) //assess data package frame header 0x59
    {
      uart[0]=HEADER;
      if( Serial3.read()==HEADER) //assess data package frame header 0x59
      {
         uart[1]=HEADER;
          for(i=2;i<9;i++) //save data in array
            {
                uart[i]=Serial3.read();
            }
                check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
                if(uart[8]==(check&0xff))//ver ify the received data as per protocol
          {
             
             dist3=(uart[2]+uart[3]*256.0)/100; //calculate distance value
             
             
             
      }
           
        }
    }
  }
 
/*
 ********************************************************************************************************
 *                            End-Of TF02-3 Reading
 ********************************************************************************************************
*/
}


void Get_Angle(){
    
/*
 *****************************************************************************************************
                                Calculate Gradiant between Two Sensors (TF02_1 & TF02_2)
 *****************************************************************************************************                               
*/
  if ( abs(dist1 - dist2) < threshold )
  {
    GDT = 0;
    theta = atan (GDT);
    angle = (theta * 180) / 3.14;       //degree
  }
  else
  {
    GDT = ((dist1-dist2)/0.14);
    theta = atan (GDT);
    angle = (theta * 180) / 3.14;       //degree
  }

/*
 ********************************************************************************************************
 *                            End-Of Calculating Angle
 ********************************************************************************************************
*/
}
