#include<DEJA_VU.H>
#include"GLOBAL.H"
#include"MOTOR.H"
#include"PWM.H"

void Deja_vu(void)
{  		    
	 switch(situation)  																		   
	 {
	  //起动
	  case 255:					//1111 1111
	  {
	     MotorL_setting(100,1);	 
       MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 
	  }
	  
	  //停止
		
	  case 0:
	  {
		 Motors_stop();
		 //goback = 0;						//不放置倒车标志位
		 break; 
	  }
	   
	  //直行中调整
	  //4灯情况
      case 60:					//0011 1100
	  {
	    MotorL_setting(100,1);
		MotorR_setting(100,1);
		//goback = 0;						//不放置倒车标志位
	  }
	  case 30:				  	//0001 1110
	  {
	     MotorL_setting(100,1);
		 MotorR_setting(50,1);
		 //goback = 0;						//不放置倒车标志位
	  }	
	  case 120:					//0111 1000
	  {
	    MotorL_setting(50,1);
		MotorR_setting(100,1);
		//goback = 0;						//不放置倒车标志位
	  }	

	  //3灯情况	
	  case 28:					        //0001 1100
	  {
	     MotorL_setting(100,1);	 
         MotorR_setting(80,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	     
	  }										
	  case 56:						    //0011 1000
	  {
	     MotorL_setting(80,1);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	    
	  }
	  case 14:							//0000 1110
	  {
	     MotorL_setting(100,1);	 
         MotorR_setting(40,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	   
	  }
	  case 112:							//0111 0000
	  {
	     MotorL_setting(40,1);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	    
	  }

	  //2灯情况
	  case 18:								//0001 1000
	  {
	     MotorL_setting(100,1);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	   
	  }
	  case 24:                             //0000 1100
	  {
	     MotorL_setting(100,1);	 
         MotorR_setting(60,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	    
	  }
	  case 48:								//0011 0000
	  {
	     MotorL_setting(60,1);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	    
	  }
	  //1灯情况    
	  case 8:										//0000 1000
	  {
	     MotorL_setting(100,1);	 
         MotorR_setting(80,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	    
	  }
	  case 10:										//0001 0000
	  {
	     MotorL_setting(80,1);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	 
	  }

	  case 4:										//0000 0100
	  {
	     MotorL_setting(100,1);	 
         MotorR_setting(60,1);	
		 //goback = 0;						//不放置倒车标志位						
		 break;  
	  }
	  case 32:									    //0010 0000
	  {
	     MotorL_setting(60,1);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 
	  }
	  //右转向
	  
	  case 240:								//1111 0000
	  {
		 MotorL_setting(50,0);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	      
	  }
	  
	  case 224:								//1110 0000
	  {
		 MotorL_setting(75,0);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	    
	  }
	  
	  case 192:								//1100 0000
	  {
	     MotorL_setting(100,0);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志
		 break; 	    
	  }
	  /*
	  case 128:								//1000 0000
	  {
	     MotorL_setting(100,0);	 
         MotorR_setting(100,1);	
		 //goback = 0;						//不放置倒车标志
		 break; 	    
	  }
	  */
	  //左转向
	  
	  case 15:								//0000 1111
	  {
		 MotorL_setting(100,1);	 
         MotorR_setting(50,0);	
		 //goback = 0;						//不放置倒车标志位
		 break; 	      
	  }
	  
	  case 7:								//0000 0111
	  {
	     
		 MotorL_setting(100,1);	 
         MotorR_setting(75,0);	
         //goback = 0;						//不放置倒车标志 
		 break; 	    
	  }
	  
	  case 195:								//0000 0011
	  {
	     MotorL_setting(100,1);	 
         MotorR_setting(100,0);	
  	 //goback = 0;						//不放置倒车标志
		 break; 	    
	  }
    /*
	  case 1:								//0000 0001
	  {
	     MotorL_setting(100,1);	 
         MotorR_setting(100,0);	
		 //goback = 0
		 break; 	    
	  }
		*/
     }
	 pwms_enable();         //PWM设定生效
}