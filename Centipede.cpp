#include <iostream>
#include<cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.
// Don't edit unless required. Use functions on lines 43, 44, 45 for resizing the game window.
const int resolutionX = 960;
const int resolutionY = 960;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid=30
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid=30

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};

// The following exist purely for readability.
const int x = 0;
const int y = 1;
const int exists = 2;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


				/////To draw player on screen
void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite);

				/////To draw bullet on screen
void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite);

				/////To move bulllet upward
void moveBullet(float bullet[], sf::Clock& bulletClock,float mushroom[][4],int &mushrooms,float player[]);

				/////For moving the player
void movePlayer(float Player[],sf::RenderWindow& window);

				/////For drawing mushrooms
void drawmushroom(sf::RenderWindow& window,int &mushrooms,float mushroom[][4], sf::Sprite& mushroomSprite);

				/////For drawing white mushrooms
void drawpoismushroom(sf::RenderWindow& window,int &poismushrooms,float poismushroom[][4], sf::Sprite& poismushroomSprite);

				/////To give position to mushrooms
void posmushrooms(float mushroom[][4],int nums);                                                     

                                /////To check collision b/w bullet &mushroom
void dead(float bullet[],float mushroom[][4],int &mushrooms,float player[],int &count,sf::Sprite& mushroomSprite,bool &fire,int &score); 

				/////To To check collision b/w bullet & whitemushroom
void deadpois(float bullet[],float poismushroom[][4],int &poismushrooms,float player[],int &count,sf::Sprite& poismushroomSprite,bool &fire,int &score);

				/////For drawing centipede
void drawcentipede(sf::RenderWindow& window, float centipede[][3], sf::Sprite& centipedeSprite,sf::Clock& centipedeClock);

				/////To draw centipede head		
void drawhead(sf::RenderWindow& window, float centipedehead[][3], sf::Sprite& centipedeheadSprite,sf::Clock& centipedeheadClock,int &sz);

				/////To give position to centipede
void poscentipede(float centipede[][3],const int size,bool flag[],float centipedehead[][3],bool flag3[],bool flag1[], bool flag2[]);

				/////For moving centipede	
void movecentipede(sf::RenderWindow& window,sf::Sprite& mushroomSprite,float centipede[][3],sf::Clock& centipedeClock,bool flag[],float mushroom[][4],int &mushrooms ,float centipedehead[][3],sf::Clock& centipedeheadClock, bool flag1[] ,bool flag3[],bool falg2[],float bullet[],int &sz,int &poismushrooms,float poismushroom[][4],int &speed); 

				/////For centipede touch mushroom then it descend its level
void mushroomtouch(float centipede[][3], float mushroom[][4], int &mushrooms, bool flag[],bool flag1[], float centipedehead[][3],bool flag3[],bool flag2[],int &sz,int &poismushrooms,float poismushroom[][4],int &speed);
	
				/////For centipede collision with bullet
void centipedecollision(float centipede[][3],float centipedehead[][3],float bullet[],sf::Sprite& centipedeSprite,bool flag[],int &count1,int &count2,bool &fire,bool &earliar_level,int &speed,int &sz,bool flag1[],int &score,int &store1,int &store2,bool &check1,bool &check2);

				/////For checking is body of centipede is destroyed for head destroying
bool check(float centipede[][3]);
	
				/////To kill the fighter to end the game
void Killingfighter(float player[],float bullet[] , float centipede[][3],float centipedehead[][3],float poismushroom[][4],int &poismushrooms);

int main()
{
	srand(time(0));

	// Declaring RenderWindow.
	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Centipede", sf::Style::Close | sf::Style::Titlebar);

	// Used to resize your window if it's too big or too small. Use according to your needs.
	window.setSize(sf::Vector2u(640, 640)); // Recommended for 1366x768 (768p) displays.
	//window.setSize(sf::Vector2u(1280, 1280)); // Recommended for 2560x1440 (1440p) displays.
	// window.setSize(sf::Vector2u(1920, 1920)); // Recommended for 3840x2160 (4k) displays.
	
	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(sf::Vector2i(100, 0));

	// Initializing Background Music.
	sf::Music bgMusic;
	bgMusic.openFromFile("Music/field_of_hopes.ogg");
	bgMusic.play();
	bgMusic.setVolume(50);
	
	
	// Initializing Background.
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/pngtree-gradient.png");
	backgroundSprite.setTexture(backgroundTexture);
	//backgroundSprite.setColor(sf::Color(0,0,255,255*0.20 )); // Reduces Opacity to 25%

	// Initializing Player and Player Sprites.
	float player[2] = {};
	player[x] = (resolutionX-boxPixelsX)/2;
	player[y] = resolutionY-boxPixelsY;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	playerTexture.loadFromFile("Textures/player.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(sf::IntRect(0,0, boxPixelsX, boxPixelsY));

	// Initializing Bullet and Bullet Sprites.
	bool fire=false;                                 //// Use to fire bullet
	float bullet[3] = {};
	bullet[x] = player[x];
	bullet[y] = player[y] - boxPixelsY/2;
	bullet[exists] = true;
	sf::Clock bulletClock;
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX+10, boxPixelsY+10));
	
	//Intializing Mushrooms and Mushrooms Sprites
	int num;
	do{
	num=rand()%30;
	}while(num<21); ////For no. of mushrooms between 20 and 30   
	int mushrooms=num;
	float mushroom[999][4]={};
	posmushrooms(mushroom,mushrooms); /////For declearing positions
	int count=0;
	sf::Clock mushroomClock;
	sf::Texture mushroomTexture;
	sf::Sprite mushroomSprite;
	mushroomTexture.loadFromFile("Textures/mushroom.png");
	mushroomSprite.setTexture(mushroomTexture);
	mushroomSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	
	
	// Initialize poisnous Mushroom and its Sprite
	int poismushrooms=1;           //////////nopm means no. of poisinous mushrooms
	float poismushroom[999][4]={};
	int counter=0;
	sf::Clock poismushroomClock;
	sf::Texture poismushroomTexture;
	sf::Sprite poismushroomSprite;
	poismushroomTexture.loadFromFile("Textures/mushroom.png");
	poismushroomSprite.setTexture(poismushroomTexture);
	poismushroomSprite.setTextureRect(sf::IntRect(0, 30, boxPixelsX, boxPixelsY));
	
	
	// Intializing Centipede and Centipede sprite
	const int size=11;
	bool flag[size] ={};
	bool flag3[size]={};
	bool fer=false;
	float centipede[size][3]={};
	sf::Clock centipedeClock;
	sf::Texture centipedeTexture;
	sf::Sprite centipedeSprite;
	centipedeTexture.loadFromFile("Textures/c_body_left_walk.png");
	centipedeSprite.setTexture(centipedeTexture);
	centipedeSprite.setTextureRect(sf::IntRect(0,0,32,32));
	
	
	 //Initializing centipede head 
        float centipedehead[2][3]={};
	bool flag1[2];
	bool flag2[2];
	sf::Clock centipedeheadClock;
	sf::Texture centipedeheadTexture;
	sf::Sprite centipedeheadSprite;
	centipedeheadTexture.loadFromFile("Textures/c_head_left_walk.png");
	centipedeheadSprite.setTexture(centipedeheadTexture);
	centipedeheadSprite.setTextureRect(sf::IntRect(0,0, 32, 32));
	int color=0;
	poscentipede(centipede,size,flag,centipedehead,flag3,flag1,flag2);
	
	
	//////////////// Some variables that is used for game
	int store1=0;
	int store2=10;
	bool check1=true;
	bool check2=true;
	bool earliar_level=true;                 ////// For if centipede is in earlier level and bullet kill it then centipede will vanish
	int sz=1;
	int count1=0;
	int count2=0;
	int speed=5;
	
	
	///////////For scoring at the end
	int score=0;
	sf::Text scoring;
	sf::Font scorefont;   
	scorefont.loadFromFile("Square.ttf");
	scoring.setFont(scorefont);
	scoring.setCharacterSize(40);
	scoring.setPosition(0,920);
	scoring.setString(to_string(score));
	
	
	
	
	while(window.isOpen()) {
		 
		///////////////////////////////////////////////////////////////
		//                                                           //
		// Call Your Functions Here. Some have been written for you. //
		// Be vary of the order you call them, SFML draws in order.  //
		//                                                           //
		///////////////////////////////////////////////////////////////
		
		window.draw(backgroundSprite);
		
		scoring.setString(to_string(score));   /////TO draw the score on screen
		window.draw(scoring);
		
		drawPlayer(window, player, playerSprite);
		movePlayer(player,window);
		
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
		fire=true;
		}
		if (bullet[exists] == true && fire) {
			drawBullet(window, bullet, bulletSprite);
			moveBullet(bullet, bulletClock,mushroom,mushrooms,player); 
			//drawBullet(window, bullet, bulletSprite);
			}	
		
		if(bullet[y]<0)                              //////////////For bullet shooting continously
		{
			fire=false;
			//bullet[y] = player[y] - boxPixelsY;                    //////This is for if you fire bullet without pressing space
			//bullet[x] = player[x];
			//drawBullet(window, bullet, bulletSprite);
			//moveBullet(bullet, bulletClock,mushroom,mushrooms,player); 
			//drawBullet(window, bullet, bulletSprite);
		}
		if(fire==false){
		bullet[y] = player[y] - boxPixelsY/2;
		bullet[x] = player[x];
		}
		
		drawmushroom(window,mushrooms,mushroom, mushroomSprite);
		dead(bullet,mushroom,mushrooms,player,count,mushroomSprite,fire,score); 
		drawpoismushroom(window,poismushrooms,poismushroom,poismushroomSprite);
		deadpois(bullet,poismushroom,poismushrooms,player,count,poismushroomSprite,fire,score);
		
		drawcentipede(window,centipede,centipedeSprite,centipedeClock);
		drawhead(window,centipedehead,centipedeheadSprite,centipedeheadClock,sz);
		
movecentipede(window,mushroomSprite,centipede,centipedeClock,flag,mushroom,mushrooms,centipedehead,centipedeheadClock, flag1,flag3,flag2,bullet,sz,poismushrooms,poismushroom,speed);
		
		Killingfighter(player,bullet ,centipede,centipedehead,poismushroom,poismushrooms);
		
		centipedecollision(centipede,centipedehead, bullet,centipedeSprite,flag,count1,count2,fire,earliar_level,speed,sz,flag1,score,store1,store2,check1,check2);
		
		if(count2+1>=14){
		
		if(color==0)								/////////////////////////////////////////////////
		{									//					       //
		centipedeheadSprite.setColor(sf::Color::Magenta);			//   Change color of head of different levels  //
		color+=1;								//					       //
		}									/////////////////////////////////////////////////
		else if(color==1)
		{
		centipedeheadSprite.setColor(sf::Color::Green);
		color+=1;
		}
		else if(color==2)
		{
		centipedeheadSprite.setColor(sf::Color::Red);
		color+=1;
		}
		else if(color==3)
		{
		centipedeheadSprite.setColor(sf::Color::Blue);
		color=0;
		}
			poscentipede(centipede,size,flag,centipedehead,flag3,flag1,flag2);
			drawcentipede(window,centipede,centipedeSprite,centipedeClock);
		count2=0;
		count1=0;
			earliar_level=true;
			speed=5;
		sz=1;
		fer=false;
			check1=true;
			check2=true;
		store1=0;
		store2=10;
		}
		
		if(player[x]<-100)
		{
		break;
		}
		
		
		
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				return 0;
			}
		}
		
		window.display();
		window.clear();
	}
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite) {
	playerSprite.setPosition(player[x], player[y]);
	window.draw(playerSprite);
	
}
void moveBullet(float bullet[], sf::Clock& bulletClock,float mushroom[][4],int &mushrooms,float player[]) {
	if (bulletClock.getElapsedTime().asMilliseconds() < 5)
		return;
	
	bulletClock.restart();
	bullet[y] -= 10;
		
	if (bullet[y] < -32)
		bullet[exists] = false;
				
}
void dead(float bullet[],float mushroom[][4],int &mushrooms,float player[],int &count, sf::Sprite& mushroomSprite,bool &fire,int &score)
{
	for(int i=0;i<mushrooms;i++)
	{
	if((bullet[x]+20>=mushroom[i][x]) && (bullet[x]<=mushroom[i][x]+20) && (bullet[y]+20>=mushroom[i][y]) && (bullet[y]<=mushroom[i][y]+20) && mushroom[i][exists])                 /////boxPixelsX-12=20 becoz if i take greater then 20 then it will destroy if bullet only pass by it
	{
					    /////////////////////////////////////////////////////////////
	mushroom[i][3]+=1;		    //							       //	
	if(mushroom[i][3]<2){               //	  For bullet hits two time then mushroom destroyed     //
	bullet[exists]=false;		    //                                                         //
	fire=false;			    /////////////////////////////////////////////////////////////
	}
	if(mushroom[i][3]>=2){
	score+=1;
	mushroom[i][exists]=false;
	bullet[exists]=false;
	fire=false;
	count++;
	break;
	}
	}
	}
	if (bullet[exists]==false){
	bullet[x] = player[x];
	bullet[y] = player[y] - boxPixelsY;
	bullet[exists]=true;
	}

}
void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite) {
	bulletSprite.setPosition(bullet[x], bullet[y]);
	window.draw(bulletSprite);
}

//////>>>>>>>>>>>>>>>>>>>>> Move player in player area <<<<<<<<<<<<<<<<<<<<<//////

void movePlayer(float Player[],sf::RenderWindow& window)
{	

		//////////////////////////////////////////////////////////////////
		//								//
		//    The palying area of player is from 801 to 960 rows	//   
		//								//
		//////////////////////////////////////////////////////////////////

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)&&Player[y]>0&&Player[y]>800)
	{
	Player[y]-=0.7;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)&&Player[y]<resolutionY-boxPixelsY)
	{
	Player[y]+=0.7;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)&&Player[x]>0)
	{
	Player[x]-=0.7;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)&&Player[x]<resolutionX-boxPixelsX)
	{
	Player[x]+=0.7;
	}

}
void drawmushroom(sf::RenderWindow& window, int &mushrooms,float mushroom[][4], sf::Sprite& mushroomSprite)
{
	for(int a=0;a<mushrooms;a++){
	if(mushroom[a][exists]){
	mushroomSprite.setPosition(mushroom[a][x], mushroom[a][y]);
	window.draw(mushroomSprite);
}
}
}
void posmushrooms(float mushroom[][4] ,int nums)
{
	for(int a=0;a<nums;a++)         //////////////////For Drawing Mushrooms upto 30
	{
		mushroom[a][x]=rand()%(resolutionX-boxPixelsX);        /////mushroom along x-axis is upto 928
		mushroom[a][y]=rand()%(resolutionY-2*boxPixelsY); /////mushroom place along y-axis is from 0 upto 896 so that not in row of player
		mushroom[a][exists]=true;
		mushroom[a][3]=0;                   ///Reset all mushroom for bullet collision to 0
	}
}
void drawcentipede(sf::RenderWindow& window, float centipede[][3], sf::Sprite& centipedeSprite, sf::Clock& centipedeClock)
{
	for(int i=0;i<11;i++){
	centipedeSprite.setPosition(centipede[i][x],centipede[i][y]);
	window.draw(centipedeSprite);
}
}


void drawhead(sf::RenderWindow& window, float centipedehead[][3], sf::Sprite& centipedeheadSprite,sf::Clock& centipedeheadClock,int &sz)
{
	for(int i=0;i<sz;i++){
	centipedeheadSprite.setPosition(centipedehead[i][x],centipedehead[i][y]);
	window.draw(centipedeheadSprite);
}
}
void poscentipede(float centipede[][3],const int size,bool flag[],float centipedehead[][3],bool flag3[],bool flag1[],bool flag2[])
{

	centipede[0][x]=960;					////////////////////////////////////////////////
	do{							//					      //
	centipede[0][y]=rand()%500;				//   For centipede come from random places    //
	}while(fmod(centipede[0][y],32)!=0);			//					      //
	centipede[0][exists]=true;				////////////////////////////////////////////////
	flag[0]=true;
	flag3[0]=true;
	
	for(int i=1;i<=size-1;i++)
	{
	centipede[i][x]=centipede[i-1][x]+30;
	centipede[i][y]=centipede[i-1][y];
	centipede[i][exists]=true;
	flag[i]=true;
	flag3[i]=true;
	}								/////////////////////////////////////
	centipedehead[0][x]=centipede[0][x]-30;                         //   For centipede head position   //
	centipedehead[0][y]=centipede[10][y];				/////////////////////////////////////
	centipedehead[0][exists] = true;
	flag1[0]=true;
	flag2[0]=true;
	flag1[1]=true;
	flag2[1]=true;
}
void movecentipede(sf::RenderWindow& window,sf::Sprite& mushroomSprite,float centipede[][3],sf::Clock& centipedeClock,bool flag[],float mushroom[][4],int &mushrooms ,float centipedehead[][3],sf::Clock& centipedeheadClock, bool flag1[] ,bool flag3[],bool flag2[],float bullet[],int &sz,int &poismushrooms,float poismushroom[][4],int &speed)
 {
	if (centipedeClock.getElapsedTime().asMilliseconds() < 20)
		return;
		
	centipedeClock.restart();
	
	//////////////////////////////////////////
	//					//	
	//          For Head of centipede	//
	//					//
	//////////////////////////////////////////
	
	//////////////////////This condition is used if centipede reach end of screen then it moves back and forth 
	for(int a=0;a<2;a++){
	if(centipedehead[a][exists]==false)
	{									
	if(centipedehead[a][y]>=0&&centipedehead[a][y]<800){                  
	mushroom[mushrooms][x]=centipedehead[a][x];
	mushroom[mushrooms][y]=centipedehead[a][y];
	mushroom[mushrooms][exists]=true;
	mushroom[mushrooms][3]=0;
	mushrooms++;
	}
	else if(centipedehead[a][y]>=800&&centipedehead[a][y]<=928)	//////If it is in player area then create poisnous mushrooms
	{
	poismushroom[poismushrooms][x]=centipedehead[a][x];
	poismushroom[poismushrooms][y]=centipedehead[a][y];
	poismushroom[poismushrooms][exists]=true;
	poismushroom[poismushrooms][3]=0;
	poismushrooms++;
	}
	centipedehead[a][y]=-102;
	}
	else if(flag2[a]==false){
	if(flag1[a]==true)
	{
	centipedehead[a][x]-=speed;
	if(centipedehead[a][x]<=0){
	centipedehead[a][y]-=32;
	flag1[a]=false;
	}
	}
	if(flag1[a]==false)
	{
	centipedehead[a][x]+=speed;
	if(centipedehead[a][x]>=928)
	{
	centipedehead[a][y]-=32;
	flag1[a]=true;
	}
	}
	if(centipedehead[a][y]<=800)
	flag2[a]=true;
	}
	
	////////This condition is for if it is 1st movement
	
	else if(flag2[a]==true){
	
	if(flag1[a]==true)
	{
	centipedehead[a][x]-=speed;
	if(centipedehead[a][x]<=0){
	centipedehead[a][y]+=32;
	flag1[a]=false;
	}
	}
	if(flag1[a]==false)
	{
	centipedehead[a][x]+=speed;
	if(centipedehead[a][x]>=928)
	{
	centipedehead[a][y]+=32;
	flag1[a]=true;
	}
	}
	if(centipedehead[a][y]>=928)
	flag2[a]=false;
	}
	}
		
	//////////////////////////////////////////////////
	//						//
	//             For body of centipede            //
	//						//
	//////////////////////////////////////////////////
	
	//////////////////////This condition is used if centipede reach end of screen then it moves back and forth
	for(int i=0;i<11;i++){
	if(centipede[i][exists]==false)
	{
	if(centipede[i][y]>=0&&centipede[i][y]<800){             
	mushroom[mushrooms][x]=centipede[i][x];
	mushroom[mushrooms][y]=centipede[i][y];
	mushroom[mushrooms][exists]=true;
	mushroom[mushrooms][3]=0;
	mushrooms++;
	}
	else if(centipede[i][y]>=800&&centipede[i][y]<=928)             //////If it is in player area then create poisnous mushroom
	{
	poismushroom[poismushrooms][x]=centipede[i][x];
	poismushroom[poismushrooms][y]=centipede[i][y];
	poismushroom[poismushrooms][exists]=true;
	poismushroom[poismushrooms][3]=0;
	poismushrooms++;
	}
	centipede[i][y]=-102;
	}
	else if(flag3[i]==false){
	if(flag[i]==true)
	{
	centipede[i][x]-=speed;
	if(centipede[i][x]<=0){
	centipede[i][y]-=32;
	flag[i]=false;
	}
	}
	if(flag[i]==false)
	{
	centipede[i][x]+=speed;
	if(centipede[i][x]>=928)
	{
	centipede[i][y]-=32;
	flag[i]=true;
	}
	}
	if(centipede[i][y]<=800)
	flag3[i]=true;
	}
	
	////////This condition is for if it is 1st movement
	
	else if(flag3[i]==true){
	if(flag[i]==true)
	{
	centipede[i][x]-=speed;
	if(centipede[i][x]<=0){
	centipede[i][y]+=32;
	flag[i]=false;
	}
	}
	if(flag[i]==false)
	{
	centipede[i][x]+=speed;
	if(centipede[i][x]>=928)
	{
	centipede[i][y]+=32;
	flag[i]=true;
	}
	}
	if(centipede[i][y]>=928)
	flag3[i]=false;
	}
	}

	mushroomtouch(centipede,mushroom,mushrooms,flag, flag1,centipedehead,flag3,flag2,sz,poismushrooms,poismushroom,speed);
	
}


void mushroomtouch(float centipede[][3], float mushroom[][4], int &mushrooms, bool flag[],bool flag1[], float centipedehead[][3],bool flag3[],bool flag2[],int &sz,int &poismushrooms,float poismushroom[][4],int &speed)
{	
	//////////////////////////////////////////
	//					//	
	//          For Head of centipede	//
	//					//
	//////////////////////////////////////////
	
	/////If head of centipede touch poisnous mushroom
	for(int b=0;b<2;b++){
	for(int a=0;a<mushrooms;a++){
	if((centipedehead[b][x]+30>=mushroom[a][x]) && (centipedehead[b][x]<=mushroom[a][x]+30) && ((centipedehead[b][y]+30)>=mushroom[a][y]) && (centipedehead[b][y]<=mushroom[a][y]+30) && mushroom[a][exists])
	{
	if(flag2[b]==false){
	centipedehead[b][y]-=32;
	flag1[0]=!flag1[b];
	}
	else{
	centipedehead[b][y]+=32;
	flag1[b]=!flag1[b];
	}
	}
	}
	/////If head of centipede touch poisnous mushroom
	for(int c=0;c<poismushrooms;c++)
	{
	if((centipedehead[b][x]+30>=poismushroom[c][x]) && (centipedehead[b][x]<=poismushroom[c][x]+30) && (centipedehead[b][y]+30>=poismushroom[c][y]) && (centipedehead[b][y]<=poismushroom[c][y]+30) && poismushroom[c][exists])
	{
	if(flag2[b]==false){
	centipedehead[b][y]-=32;
	flag1[b]=!flag1[b];
	}
	else{
	centipedehead[b][y]+=32;
	flag1[b]=!flag1[b];
	}
	}
	}
	}
	
	//////////////////////////////////////////////////
	//						//
	//             For body of centipede            //
	//						//
	//////////////////////////////////////////////////
	
	/////If centipede touch mushroom
	for(int j=0;j<=10;j++){
	for(int d=0;d<mushrooms;d++){
	if((centipede[j][x]+30>=mushroom[d][x]) && (centipede[j][x]<=mushroom[d][x]+30) && ((centipede[j][y]+30)>=mushroom[d][y]) && (centipede[j][y]<=mushroom[d][y]+30) && mushroom[d][exists])
	{
	if(flag3[j]==false)
	{
	centipede[j][y]-=32;
	flag[j]=!flag[j];
	}
	else{
	centipede[j][y]+=32;
	flag[j]=!flag[j];
	}
	}
	}
	
	/////If centipede touch poisnous mushroom
		for(int d=0;d<poismushrooms;d++){
	if((centipede[j][x]+30>=poismushroom[d][x]) && (centipede[j][x]<=poismushroom[d][x]+30) && ((centipede[j][y]+30)>=poismushroom[d][y]) && (centipede[j][y]<=poismushroom[d][y]+30) && poismushroom[d][exists])
	{
	if(flag3[j]==false)
	{
	centipede[j][y]-=32;
	flag[j]=!flag[j];
	}
	else{
	centipede[j][y]+=32;
	flag[j]=!flag[j];
	}
	}
	}
	}
}	

void centipedecollision(float centipede[][3],float centipedehead[][3],float bullet[],sf::Sprite& centipedeSprite,bool flag[],int &count1,int &count2,bool &fire,bool &earliar_level,int &speed,int &sz,bool flag1[],int &score,int &store1,int &store2,bool &check1,bool &check2)
{
		
		
		//////////////////////////////////////////////////
		//						//
		//	   Check for Centipede body		//
		//						//
		//////////////////////////////////////////////////
	
		for(int k=0;k<=10;k++)
		{
		if((bullet[x]+20>=centipede[k][x]) && (bullet[x] <= (centipede[k][x]+20)) && (bullet[y]+20 >= centipede[k][y]) && (bullet[y] <= (centipede[k][y]+20)) && centipede[k][exists]){
		centipede[k][exists]=false;
		bullet[exists]=false;
		fire=false;
		if(sz==1)
		{
		if(flag1[0]){
		centipedehead[1][x]=centipede[10][x]+30;
		flag1[1]=false;
		
		}
		else
		{
		centipedehead[1][x]=centipede[10][x]-30;
		flag1[1]=!flag[10];
		}
		centipedehead[1][y]=centipede[10][y];
		centipedehead[1][exists]=true;
		sz++;
		}
		earliar_level=false;
		count2++;
		if(count1==0){
		for(int i=k;i<=10;i++){
		if(count1==0)
		flag[i]=!flag[i];
		}
		}
		count1++;
		score+=10;
		//speed=speed+2;
		}
		}
		
		//////////////////////////////////////////////////
		//						//
		//	   Check for Centipedehead		//
		//						//
		//////////////////////////////////////////////////
	
		for(int i=0;i<sz;i++){
		if((bullet[x]+25>=centipedehead[i][x]) && (bullet[x] <= (centipedehead[i][x]+25)) && (bullet[y]+25 >= centipedehead[i][y]) && (bullet[y] <= (centipedehead[i][y]+25)) && centipedehead[i][exists])
		{
		if(earliar_level==true){
			bullet[exists]=false;
			fire=false;
		for(int j=0;j<11;j++){
			centipede[j][exists]=false;
			count2++;
			score+=10;
				}
			centipedehead[i][exists]=false;
			count2++;
			score+=20;
		}
		else
		{
		if(i==0){
		 if(check1==true)
		{
			if(centipede[store1][exists]==true)
			{
			if(flag[store1])
			centipedehead[0][x]=centipede[store1][x]-58;
			else
			centipedehead[0][x]=centipede[store1][x]+58;
			centipedehead[0][y]=centipede[store1][y];
			centipede[store1][exists]=false;
			store1=store1+1;
			count2++;
			score+=20;
			}
			else
			{
			check1=false;
			}	
		}
		}
		else if(i==1){
		 if(check2==true)
		{
			if(centipede[store2][exists]==true)
			{
			if(flag[store2])
			centipedehead[1][x]=centipede[store2][x]-58;
			else
			centipedehead[1][x]=centipede[store2][x]+58;
			centipedehead[1][y]=centipede[store2][y];
			centipede[store2][exists]=false;
			store2=store2-1;
			count2++;
			score+=20;
			}
			else
			{
			check2=false;
			}	
		}
		}
		}
		bool fere=check(centipede);     /////// Call  function to check if body destroyed then head will destroyed 
		if(fere==true){
			count2++;
			centipedehead[i][exists]=false;
			score+=20;
			}
			//speed=speed+2;
		}
		}
		
		
		
		
}


void drawpoismushroom(sf::RenderWindow& window,int &poismushrooms,float poismushroom[][4], sf::Sprite& poismushroomSprite)
{
	for(int a=0;a<poismushrooms;a++){
		if(poismushroom[a][exists]){
		poismushroomSprite.setPosition(poismushroom[a][x], poismushroom[a][y]);
		window.draw(poismushroomSprite);
					}
				}
}


void deadpois(float bullet[],float poismushroom[][4],int &poismushrooms,float player[],int &count,sf::Sprite& poismushroomSprite,bool &fire,int &score){
for(int i=0;i<poismushrooms;i++)
	{
	if((bullet[x]+20>=poismushroom[i][x]) && (bullet[x]<=poismushroom[i][x]+20) && ((bullet[y]+20)>=poismushroom[i][y]) && (bullet[y]<=poismushroom[i][y]+20) && poismushroom[i][exists])
	{
	
	poismushroom[i][3]+=1;			//////////////////////////////////////////////////////////////////////
	if(poismushroom[i][3]<2){               //								    //
	bullet[exists]=false;			//     For bullet hits two time then poisnous mushroom destroyed    //
	fire=false;				//								    //
	}					//////////////////////////////////////////////////////////////////////
	if(poismushroom[i][3]>=2){
	score+=1;
	poismushroom[i][exists]=false;
	bullet[exists]=false;
	fire=false;
	count++;
	break;
	}
	}
	}
	if (bullet[exists]==false){
	bullet[x] = player[x];
	bullet[y] = player[y] - boxPixelsY;
	bullet[exists]=true;
	}
}

bool check(float centipede[][3])
{
	for(int i=0;i<11;i++){
		if(centipede[i][exists]==true)
		return false;
	}
	return true;
}

void Killingfighter(float player[],float bullet[] , float centipede[][3],float centipedehead[][3],float poismushroom[][4],int &poismushrooms)
{

	//////////////////////////////////////////////////
	//						//
	//	   Check for poisnous mushroom		//
	//						//
	//////////////////////////////////////////////////
	for(int i=0;i<poismushrooms;i++){
	if((player[x]+25>=poismushroom[i][x]) && (player[x]<=poismushroom[i][x]+25) && ((player[y]+25)>=poismushroom[i][y]) && (player[y]<=poismushroom[i][y]+25) && poismushroom[i][exists])
	{
	player[x]=-10000;
	bullet[exists]=false;
	}
	}
	
	//////////////////////////////////////////////////
	//						//
	//	   Check for Centipedehead		//
	//						//
	//////////////////////////////////////////////////
	
	for(int j=0;j<2;j++)
	{
	if((player[x]+25>=centipedehead[j][x]) && (player[x]<=centipedehead[j][x]+25) && ((player[y]+25)>=centipedehead[j][y]) && (player[y]<=centipedehead[j][y]+25) && centipedehead[j][exists])
	{
	player[x]=-10000;
	bullet[exists]=false;
	}
	}
	
	//////////////////////////////////////////////////
	//						//
	//	   Check for Centipede body		//
	//						//
	//////////////////////////////////////////////////
	
	for(int k=0;k<11;k++)
	{
	if((player[x]+25>=centipede[k][x]) && (player[x]<=centipede[k][x]+25) && ((player[y]+25)>=centipede[k][y]) && (player[y]<=centipede[k][y]+25) && centipede[k][exists])          /////I use 25 becoz if i take greater then 20 then it will destroy if plyaer only pass by it       
	{
	player[x]=-10000;
	bullet[exists]=false;
	}
	}
}
