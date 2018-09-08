#include "snake.h"

GameInfo gameinfo={0};

Snake snake[MAXSIZE];
int16 front = 0;
int16 rear = 0;

Food food;

void AddLength( void );
void ShowSnake( uint8 sw );
void CreateFood( void );
void TestAddScore( void );
uint8 GameOver( void );
void ShowFood(void);


void BulidMap( uint16 x , uint16 y , uint8 size ){

	uint16 x_max = x + MAP_W;
	uint16 y_max = y + MAP_H;
	uint16 temp_x,temp_y;

	gameinfo.start_x = x + MAP_W/2;
	gameinfo.start_y = y + MAP_H/7*3;
	for( temp_x = x ; temp_x < x_max; temp_x++ ){
		
		if( temp_x == (x + size) ){

			gameinfo.LeftVal = temp_x;
			temp_x = x_max - size;
			gameinfo.RightVal = temp_x+1;

		}
		for(  temp_y = y ; temp_y < y_max; temp_y++  )
			ShowPoint( temp_x , temp_y , ON );
	
	}
	x = x + size;
	x_max = x_max - size;
	for( temp_y = y ; temp_y < y_max; temp_y++ ){
		
		if( temp_y == (y + size) ){

			gameinfo.UpVal = temp_y;
			temp_y = y_max - size;
			gameinfo.DownVal = temp_y+1;

		}
		for(  temp_x = x ; temp_x < x_max; temp_x++  )
			ShowPoint( temp_x , temp_y , ON );
	
	}
	temp_y = y + MAP_H/7*5;
	gameinfo.DownVal = temp_y+1;
	while( size-- ){
		for(  temp_x = x ; temp_x < x_max; temp_x++  )
			ShowPoint( temp_x , temp_y , ON );
		temp_y++;
	}
	ShowString( x + 2 , temp_y + 2 , "score : " );
	ShowString( x + 2 , temp_y + 32 , "speed : " );
	gameinfo.score_x = x + DIFFER;
	gameinfo.score_y = temp_y + 2;
	gameinfo.score = 0;
	ShowNum( gameinfo.score_x, gameinfo.score_y , gameinfo.score );

}

void AddLength( void ){

	switch( gameinfo.dir ){
	
		case SUP :{
			snake[rear].y = snake[rear-1].y-SNAKE_HW;
			snake[rear].x = snake[rear-1].x;
			rear++;
		}break;
		case SDOWN :{
			snake[rear].y = snake[rear-1].y+SNAKE_HW;
			snake[rear].x = snake[rear-1].x;
			rear++;
		}break;
		case SLEFT :{
			snake[rear].y = snake[rear-1].y;
			snake[rear].x = snake[rear-1].x-SNAKE_HW;
			rear++;
		}break;
		case SRIGHT :{
			snake[rear].y = snake[rear-1].y;
			snake[rear].x = snake[rear-1].x+SNAKE_HW;
			rear++;
		}break;
	
	}

}

void CreateFood(){

	do{
		food.x = (Snake_Random()%(gameinfo.RightVal-gameinfo.LeftVal))/SNAKE_HW*SNAKE_HW+gameinfo.LeftVal;
		food.y = (Snake_Random()%(gameinfo.DownVal-gameinfo.UpVal))/SNAKE_HW*SNAKE_HW+gameinfo.UpVal;
	}while(food.x<=gameinfo.LeftVal||food.x>=gameinfo.RightVal||food.y<=gameinfo.UpVal||food.y>=gameinfo.DownVal);
	

}

void ShowFood(){

	uint16 x,x_max;
	uint16 y,y_max;
	
	for( x=food.x,x_max=SNAKE_HW+x ; x<x_max ; x++ )
		for( y=food.y,y_max=SNAKE_HW+y ; y<y_max ; y++ ){
			ShowPoint( x-SNAKE_HW , y-SNAKE_HW , ON );
	}
	
}

void TestAddScore(){

	if( snake[front].x == food.x && snake[front].y == food.y ){
	
		AddLength();
		AddLength();
		gameinfo.score += 7-gameinfo.gamespeed/50;
		ShowNum( gameinfo.score_x, gameinfo.score_y , gameinfo.score );
		CreateFood();
		ShowFood();
	
	}

}

void GameInit(){

	front = 0;
	rear = 1;

	gameinfo.dir = SUP;
	gameinfo.gamespeed = 200;
	gameinfo.score = 0;	
	ShowNum( gameinfo.score_x, gameinfo.score_y+32 , gameinfo.gamespeed );

	snake[front].x = gameinfo.start_x;
	snake[front].y = gameinfo.start_y;

	AddLength();
	AddLength();
	AddLength();
	ShowSnake( ON );
	CreateFood();
	ShowFood();

}

void ShowSnake( uint8 sw ){
	
	uint16 x,x_max;
	uint16 y,y_max;
	uint16 i;
	for(i=0;i<rear;i++){
	
		for( x=snake[i].x,x_max=SNAKE_HW+x ; x<x_max ; x++ )
			for( y=snake[i].y,y_max=SNAKE_HW+y ; y<y_max ; y++ ){
				ShowPoint( x-SNAKE_HW , y-SNAKE_HW , sw );
			}
	
	}

}


void MoveSnake(){

	Snake snake_t1={0},snake_t2={0};
	uint16 i;
	
	snake_t1.x = snake[front].x;
	snake_t1.y = snake[front].y;
	switch( gameinfo.dir ){
	
		case SUP :{
			snake[front].y = snake[front].y-SNAKE_HW;
			snake[front].x = snake[front].x;
		}break;
		case SDOWN :{
			snake[front].y = snake[front].y+SNAKE_HW;
			snake[front].x = snake[front].x;
		}break;
		case SLEFT :{
			snake[front].y = snake[front].y;
			snake[front].x = snake[front].x-SNAKE_HW;
		}break;
		case SRIGHT :{
			snake[front].y = snake[front].y;
			snake[front].x = snake[front].x+SNAKE_HW;
		}break;
	
	}
	for(i=1;i<rear;i++){

		snake_t2.x = snake[i].x;
		snake_t2.y = snake[i].y;
		snake[i].x = snake_t1.x;
		snake[i].y = snake_t1.y;
		snake_t1.x = snake_t2.x;
		snake_t1.y = snake_t2.y;

	}

}

//¼ì²âÓÎÏ·ÊÇ·ñÊ§°Ü
//0 Õý³£ÓÎÏ·
//1 Ò§µ½×Ô¼º£¬ÓÎÏ·Ê§°Ü
//2 ÅöÇ½£¬ÓÎÏ·Ê§°Ü
uint8 GameOver(){

	uint16 i;
	for(i=3;i<rear;i++){
	
		if( (snake[i].x == snake[front].x) && (snake[i].y == snake[front].y) )
			return 0;

	}
	if( snake[front].x <= gameinfo.LeftVal || snake[front].x >= gameinfo.RightVal )
		return 2;
	else if( snake[front].y <= gameinfo.UpVal || snake[front].y >= gameinfo.DownVal )
		return 2;
	else
		return 0;

}

void GameIng(){
	
	uint8 flag = SUP;

	while( GetInstruction() );
	while(1){

		
		if( GameOver() ){
		
			ShowSnake(  OFF );
			//BulidMap( 10 , 1 , WALL_W );
			ShowString( (gameinfo.LeftVal+gameinfo.RightVal)/2-30 , (gameinfo.UpVal+gameinfo.DownVal)/2 , "GameOver!" );
			while(1);
		
		}
	
		if( flag != SPAUSE && flag != SENDGAME ){
			if( gameinfo.dir == SUP && flag != SDOWN )
				gameinfo.dir = flag;
			else if( gameinfo.dir == SDOWN && flag != SUP )
				gameinfo.dir = flag;
			else if( gameinfo.dir == SLEFT && flag != SRIGHT )
				gameinfo.dir = flag;
			else if( gameinfo.dir == SRIGHT && flag != SLEFT )
				gameinfo.dir = flag;
		}
		else if( !flag )
			while( !GetInstruction() );
		else{
			gameinfo.gamespeed+=50;
			if( gameinfo.gamespeed > 300 )
				gameinfo.gamespeed=50;
			ShowNum( gameinfo.score_x, gameinfo.score_y+32 , gameinfo.gamespeed );
		}
		SnakeDelayMs(gameinfo.gamespeed);
		TestAddScore();
		ShowSnake( OFF );
		MoveSnake();
		ShowSnake( ON );
		ShowFood();
		flag = GetInstruction();

	}

}

