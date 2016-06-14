//https://github.com/pathankhansalman/astart_maze_solver_team18_CS308_2012/blob/master/tremaux-code.c
#include <stdio.h>
#include <math.h>
#define maze_length 7
#define maze_width 7

#define THRESHOLD 60
//############################################################## Start of AVR code ############################################################

unsigned char data_received [4];
unsigned char ADC_Conversion(unsigned char);
unsigned char ADC_Value;
unsigned char flag = 0;
unsigned char Left_white_line = 0;
unsigned char Center_white_line = 0;
unsigned char Right_white_line = 0;

unsigned long int ShaftCountLeft = 0; //to keep track of left position encoder 
unsigned long int ShaftCountRight = 0; //to keep track of right position encoder
unsigned int Degrees; //to accept angle in degrees for turning

//Function to configure ports to enable robot's motion
void motion_pin_config (void) 
{
}

//Function to configure INT4 (PORTE 4) pin as input for the left position encoder
void left_encoder_pin_config (void)
{
}

//Function to configure INT5 (PORTE 5) pin as input for the right position encoder
void right_encoder_pin_config (void)
{
}

//Function to initialize ports

void left_position_encoder_interrupt_init (void) //Interrupt 4 enable
{
}

void right_position_encoder_interrupt_init (void) //Interrupt 5 enable
{
}

//ISR for right position encoder
//ISR(INT5_vect)
//{
// ShaftCountRight++;  //increment right shaft position count
//}


//ISR for left position encoder
//ISR(INT4_vect)
//{
// ShaftCountLeft++;  //increment left shaft position count
//}


//Function used for setting motor's direction
void motion_set (unsigned char Direction)
{
 //unsigned char PortARestore = 0;

}

void forward (void) //both wheels forward
{
}

void back (void) //both wheels backward
{
}

void left (void) //Left wheel backward, Right wheel forward
{
}

void right (void) //Left wheel forward, Right wheel backward
{
}

void soft_left (void) //Left wheel stationary, Right wheel forward
{
}

void soft_right (void) //Left wheel forward, Right wheel is stationary
{
}

void soft_left_2 (void) //Left wheel backward, right wheel stationary
{
 motion_set(0x01);
}

void soft_right_2 (void) //Left wheel stationary, Right wheel backward
{
}

void stop (void)
{
}


//Function used for turning robot by specified degrees
void angle_rotate(unsigned int Degrees)
{
 float ReqdShaftCount = 0;
 unsigned long int ReqdShaftCountInt = 0;

 ReqdShaftCount = (float) Degrees/ 4.090; // division by resolution to get shaft count
 ReqdShaftCountInt = (unsigned int) ReqdShaftCount;
 ShaftCountRight = 0; 
 ShaftCountLeft = 0; 

 while (1)
 {
  if((ShaftCountRight >= ReqdShaftCountInt) | (ShaftCountLeft >= ReqdShaftCountInt))
  break;
 }
 stop(); //Stop robot
}

//Function used for moving robot forward by specified distance

void linear_distance_mm(unsigned int DistanceInMM)
{
 float ReqdShaftCount = 0;
 unsigned long int ReqdShaftCountInt = 0;

 ReqdShaftCount = DistanceInMM / 5.338; // division by resolution to get shaft count
 ReqdShaftCountInt = (unsigned long int) ReqdShaftCount;
  
 ShaftCountRight = 0;
 while(1)
 {
  if(ShaftCountRight > ReqdShaftCountInt)
  {
  	break;
  }
 } 
 stop(); //Stop robot
}

void forward_mm(unsigned int DistanceInMM)
{
 forward();
 linear_distance_mm(DistanceInMM);
}

void back_mm(unsigned int DistanceInMM)
{
 back();
 linear_distance_mm(DistanceInMM);
}

void left_degrees(unsigned int Degrees) 
{
// 88 pulses for 360 degrees rotation 4.090 degrees per count
 left(); //Turn left
 angle_rotate(Degrees);
}



void right_degrees(unsigned int Degrees)
{
// 88 pulses for 360 degrees rotation 4.090 degrees per count
 right(); //Turn right
 angle_rotate(Degrees);
}


void soft_left_degrees(unsigned int Degrees)
{
 // 176 pulses for 360 degrees rotation 2.045 degrees per count
 soft_left(); //Turn soft left
 Degrees=Degrees*2;
 angle_rotate(Degrees);
}

void soft_right_degrees(unsigned int Degrees)
{
 // 176 pulses for 360 degrees rotation 2.045 degrees per count
 soft_right();  //Turn soft right
 Degrees=Degrees*2;
 angle_rotate(Degrees);
}

void soft_left_2_degrees(unsigned int Degrees)
{
 // 176 pulses for 360 degrees rotation 2.045 degrees per count
 soft_left_2(); //Turn reverse soft left
 Degrees=Degrees*2;
 angle_rotate(Degrees);
}

void soft_right_2_degrees(unsigned int Degrees)
{
 // 176 pulses for 360 degrees rotation 2.045 degrees per count
 soft_right_2();  //Turn reverse soft right
 Degrees=Degrees*2;
 angle_rotate(Degrees);
}


//ADC pin configuration
void adc_pin_config (void)
{
}

void spi_pin_config (void)
{
}

void lcd_port_config (void)
{
}

//Initialization of ports
void port_init(void)
{
 adc_pin_config();
 spi_pin_config();
 lcd_port_config();
 motion_pin_config(); //robot motion pins config
 left_encoder_pin_config(); //left encoder pin config
 right_encoder_pin_config(); //right encoder pin config	
}
// Timer Frequency:225.000Hz
void timer5_init()
{
}

void adc_init()
{
}
unsigned char ADC_Conversion(unsigned char Ch) 
{

}
void velocity (unsigned char left_motor, unsigned char right_motor)
{

}

//Function To Initialize SPI bus
// clock rate: 921600hz
void spi_init(void)
{

}

//Function to send byte to the slave microcontroller and get ADC channel data from the slave microcontroller
unsigned char spi_master_tx_and_rx (unsigned char data)
{

}

//Function To Print Sesor Values At Desired Row And Coloumn Location on LCD
void print_sensor(char row, char coloumn,unsigned char channel)
{

	ADC_Value = ADC_Conversion(channel);
	lcd_print(row, coloumn, ADC_Value, 3);
}

//call this routine to initialize all peripherals
void init_devices(void)
{
 cli(); //disable all interrupts
 port_init();
 spi_init();
	adc_init();
	timer5_init();
 sei(); //re-enable interrupts
}

// checking values from the sensors
void check_sensors(){
	Left_white_line = ADC_Conversion(1);
	Right_white_line = spi_master_tx_and_rx(1);
	Center_white_line = spi_master_tx_and_rx(0);
}

//############################################################## Start of Tremaux code ##########################################################
// Declaration of variables
int is_at_end;
int path[maze_length][maze_width][maze_length][maze_width];
int parent_of[maze_length][maze_width];
int on_optimal_path[maze_length][maze_width];

// Initialization of variables
void init(){
	int i,j,k,l;
	init_devices();
	
	for(i=0;i<maze_length;i++){
	
		for(j=0;j<maze_width;j++){
		
			for(k=0;k<maze_length;k++){
			
				for(l=0;l<maze_width;l++){
					path[i][j][k][l] = 0;
				}
			}
		}
	}
	
	for(i=0;i<maze_length;i++){
	
		for(j=0;j<maze_width;j++){
			parent_of[i][j] = -1;
			on_optimal_path[i][j] = 0;
		}
		
	}
}

// Moves to given destination from given source point
void moveto(int arg1,int arg2,int arg3,int arg4){ // Should edit moveto function
	
	if(arg2 == arg4){
	
		if(arg3>arg1){
			forward();
			_delay_ms(1000);
			check_sensors();
			while(!(Left_white_line < THRESHOLD || Right_white_line < THRESHOLD) && Center_white_line < THRESHOLD){
				forward();
				check_sensors();
			}
		}
		
		else{
			back();
			_delay_ms(1000);
			check_sensors();
			while(!(Left_white_line < THRESHOLD || Right_white_line < THRESHOLD) && Center_white_line < THRESHOLD){
				back();
				check_sensors();
			}
		}
	}
	
	else if(arg1 == arg3){
	
		if(arg4>arg2){
			left_degrees(90);//turn left;
			forward();
			_delay_ms(1000);
			check_sensors();
			while(!(Left_white_line < THRESHOLD || Right_white_line < THRESHOLD) && Center_white_line < THRESHOLD){
				forward();
				check_sensors();
			}
			right_degrees(90);
		}
		
		else{
			right_degrees(90);//turn right;
			forward();
			_delay_ms(1000);
			check_sensors();
			while(!(Left_white_line < THRESHOLD || Right_white_line < THRESHOLD) && Center_white_line < THRESHOLD){
				forward();
				check_sensors();
			}
			left_degrees(90);
		}
	}
	
}

// Checks whether the node has paths to its children or not
int no_out_path_from(int arg1,int arg2){
	int child_x,child_y;
	int flag = 0;
	int turned_back = 0;
	
	child_x = arg1 + 1;
	child_y = arg2;
	
	if(child_x < maze_length && parent_of[arg1][arg2]!=10*child_x + child_y){
		// turn left
		// move forward
		if(!turned_back) flag++;
	}
	
	child_x = arg1 - 1;
	child_y = arg2;
	
	if(child_x > 0 && parent_of[arg1][arg2]!=10*child_x + child_y){
		// turn right
		// move forward
		if(!turned_back) flag++;
	}
	
	child_x = arg1;
	child_y = arg2 + 1;
	
	if(child_y < maze_width && parent_of[arg1][arg2]!=10*child_x + child_y){
		// move forward
		if(!turned_back) flag++;
	}
	
	child_x = arg1;
	child_y = arg2 - 1;
	
	if(child_y > 0 && parent_of[arg1][arg2]!=10*child_x + child_y){
		// turn back
		// move forward
		if(!turned_back) flag++;
	}
	
	if(flag>0) return 1;
	else return 0;
}

// Checks whether the children have outward paths or not
int no_child_with_outpath(int arg1,int arg2){
	int child_x,child_y;
	int flag = 0;
	
	child_x = arg1 + 1;
	child_y = arg2;
	
	if(child_x < maze_length && parent_of[arg1][arg2]!=10*child_x + child_y){
		// turn left
		// move forward
		if(path[arg1][arg2][child_x][child_y]!=2) flag++;
	}
	
	child_x = arg1 - 1;
	child_y = arg2;
	
	if(child_x > 0 && parent_of[arg1][arg2]!=10*child_x + child_y){
		// turn right
		// move forward
		if(path[arg1][arg2][child_x][child_y]!=2) flag++;
	}
	
	child_x = arg1;
	child_y = arg2 + 1;
	
	if(child_y < maze_width && parent_of[arg1][arg2]!=10*child_x + child_y){
		// move forward
		if(path[arg1][arg2][child_x][child_y]!=2) flag++;
	}
	
	child_x = arg1;
	child_y = arg2 - 1;
	
	if(child_y > 0 && parent_of[arg1][arg2]!=10*child_x + child_y){
		// turn back
		// move forward
		if(path[arg1][arg2][child_x][child_y]!=2) flag++;
	}
	
	if(flag>0) return 1;
	else return 0;
}

// Goto the parent of the given node
void goto_parent_of(int arg1,int arg2){
	int current_x,current_y;
	int parent_x,parent_y,parent;
	
	current_x = arg1;
	current_y = arg2;
	parent = parent_of[current_x][current_y];
	parent_x = parent/10;
	parent_y = parent%10;
	on_optimal_path[current_x][current_y] = 0;
	
	moveto(current_x,current_y,parent_x,parent_y);
}

// Go to one of the children at random
int goto_child_of(int arg1,int arg2){// Return an integer in this function to depict which child is the bot going to
	int current_x=arg1,current_y=arg2;
	int child_x,child_y,no_of_paths;
	int flag = 0,flagl = 0,flagr = 0,flags = 0,flagb = 0;
	int random_path_number;
	
	child_x = arg1 + 1;
	child_y = arg2;
	
	if(child_x < maze_length && parent_of[arg1][arg2]!=10*child_x + child_y && path[arg1][arg2][child_x][child_y]!=2){
		// turn left
		// move forward
		flag++;
		flagl++;
	}
	
	child_x = arg1 - 1;
	child_y = arg2;
	
	if(child_x > 0 && parent_of[arg1][arg2]!=10*child_x + child_y && path[arg1][arg2][child_x][child_y]!=2){
		// turn right
		// move forward
		flag++;
		flagr++;
	}
	
	child_x = arg1;
	child_y = arg2 + 1;
	
	if(child_y < maze_width && parent_of[arg1][arg2]!=10*child_x + child_y && path[arg1][arg2][child_x][child_y]!=2){
		// move forward
		flag++;
		flags++;
	}
	
	child_x = arg1;
	child_y = arg2 - 1;
	
	if(child_y > 0 && parent_of[arg1][arg2]!=10*child_x + child_y && path[arg1][arg2][child_x][child_y]!=2){
		// turn back
		// move forward
		flag++;
		flagb++;
	}
	
	no_of_paths = flag;
	random_path_number = rand(flag);
	
	if(random_path_number = 0){
		if(flagl > 0){
			// turn left
			// move forward
			return 0;
		}
		
		else if(flags > 0){
			// go forward
			return 1;
		}
		
		else if(flagr > 0){
			// turn right
			return 2;
		}
		
		else if(flagb > 0){
			// go backward
			return 3;
		}
	}
	
	if(random_path_number = 1){
		if(flags > 0){
			// turn left
			// move forward
			return 1;
		}
		
		else if(flagr > 0){
			// go forward
			return 2;
		}
		
		else if(flagb > 0){
			// turn right
			return 3;
		}
		
		else if(flagl > 0){
			// go backward
			return 0;
		}
	}
	
	if(random_path_number = 2){
		if(flagr > 0){
			// turn left
			// move forward
			return 2;
		}
		
		else if(flagb > 0){
			// go forward
			return 3;
		}
		
		else if(flagl > 0){
			// turn right
			return 0;
		}
		
		else if(flags > 0){
			// go backward
			return 1;
		}
	}
}

// Get the coordinates of the child chosen by the random algorithm
int successor_value(int arg1,int arg2,int arg3){
	int rand = arg3;
	int retval;
	
	if(rand == 0) retval = 10*(arg1+1) + arg2;
	else if(rand == 1) retval = 10*(arg1-1) + arg2;
	else if(rand == 2) retval = 10*arg1 + arg2 + 1;
	else if(rand == 3) retval = 10*arg1 + arg2 + 1;
	
	return retval;
}

// Get the coordinates of the successor in the solution of the maze
int correct_successor_value(int arg1,int arg2){
	int child_x, child_y;
	
	child_x = arg1 + 1;
	child_y = arg2;
	
	if(child_x < maze_length && path[arg1][arg2][child_x][child_y]==1) return 10*child_x + child_y;
	
	child_x = arg1 - 1;
	child_y = arg2;
	
	if(child_x < maze_length && path[arg1][arg2][child_x][child_y]==1) return 10*child_x + child_y;
	
	child_x = arg1;
	child_y = arg2 + 1;
	
	if(child_x < maze_length && path[arg1][arg2][child_x][child_y]==1) return 10*child_x + child_y;
	
	child_x = arg1;
	child_y = arg2 - 1;
	
	if(child_x < maze_length && path[arg1][arg2][child_x][child_y]==1) return 10*child_x + child_y;
}

// Goes to the successor of the present node in the solution of the maze
void goto_successor_of(int arg1,int arg2){
	int child_x, child_y;
	
	child_x = arg1 + 1;
	child_y = arg2;
	
	if(child_x < maze_length && path[arg1][arg2][child_x][child_y]==1) moveto(arg1,arg2,child_x,child_y);
	
	child_x = arg1 - 1;
	child_y = arg2;
	
	if(child_x < maze_length && path[arg1][arg2][child_x][child_y]==1) moveto(arg1,arg2,child_x,child_y);
	
	child_x = arg1;
	child_y = arg2 + 1;
	
	if(child_x < maze_length && path[arg1][arg2][child_x][child_y]==1) moveto(arg1,arg2,child_x,child_y);
	
	child_x = arg1;
	child_y = arg2 - 1;
	
	if(child_x < maze_length && path[arg1][arg2][child_x][child_y]==1) moveto(arg1,arg2,child_x,child_y);
}

// Exploring the maze
void tremaux_exploring(int arg1,int arg2){
	int current_x=arg1,current_y=arg2;
	int successor_x,successor_y,parent_x,parent_y;
	int child_id;
	is_at_end = 0;
	init();
	
	if(!is_at_end){
		
		if(no_out_path_from(current_x,current_y) || no_child_with_outpath(current_x,current_y)){
			goto_parent_of(current_x,current_y);
			parent_x = parent_of[current_x][current_y]/10;
			parent_y = parent_of[current_x][current_y]%10;
			path[parent_x][parent_y][current_x][current_y]++;
			tremaux_exploring(parent_x,parent_y);
		}
		
		else{
			child_id = goto_child_of(current_x,current_y);
			successor_x = successor_value(current_x,current_y,child_id)/10;
			successor_y = successor_value(current_x,current_y,child_id)%10;
			path[current_x][current_y][successor_x][successor_y]++;
			tremaux_exploring(successor_x,successor_y);
		}
		
	}
}

// Back-tracing maze
void tremaux_solving(int arg1,int arg2){
	int current_x=arg1,current_y=arg2;
	int successor_x,successor_y;
	
	if(!(arg1==0 && arg2==0)){
		goto_successor_of(arg1,arg2);
		successor_x = correct_successor_value(current_x,current_y)/10;
		successor_y = correct_successor_value(current_x,current_y)%10;
		tremaux_solving(successor_x,successor_y);
	}
}

// Main function
int main_tactic(){
	int i=0,j=0;
	tremaux_exploring(i,j);
	//_delay_ms(5000)
	tremaux_solving(maze_length-1,maze_width-1);
	return 0;
}

