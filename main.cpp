#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
using namespace std;


         const   int N = 4, M = 4, O=5,P=5,K=6,H=6,
              TILESIZE = 64;
              int DIFFICULTY;
bool g_win = false;
int MAP[N][M], MAP1[O][P], MAP2[K][H];//Initial array to store value, position and space
int COP[N][M], COP1[O][P], COP2[K][H];//copy variable for undo

int WIDTH, HEIGHT,mode;

int HIGH=MAP[0][0],HIGH1=MAP1[0][0], HIGH2=MAP2[0][0]; // variables to store high score
void COP_Y(){//Copy values of MAP into COP function
   if(DIFFICULTY==1){
     for (int a=0; a<N; a++)
        {
            for (int b=0; b<M; b++)
                COP[a][b]=MAP[a][b];
        }
    }else if(DIFFICULTY==2){
     for (int a=0; a<O; a++)
        {
            for (int b=0; b<P; b++)
                COP1[a][b]=MAP1[a][b];
        }
    }else {
    for (int a=0; a<K; a++)
        {
            for (int b=0; b<H; b++)
                 COP2[a][b]=MAP2[a][b];
        }
    }




}

void undo(){//Change the values of MAP into COP for UNDO function

if(DIFFICULTY==1){
     for (int a=0; a<N; a++)
        {
            for (int b=0; b<M; b++)
                MAP[a][b]=COP[a][b];
        }
    }else if(DIFFICULTY==2){
     for (int a=0; a<O; a++)
        {
            for (int b=0; b<P; b++)
                MAP1[a][b]=COP1[a][b];
        }
    }else {
    for (int a=0; a<K; a++)
        {
            for (int b=0; b<H; b++)
                 MAP2[a][b]=COP2[a][b];
        }
    }




}

sf::Vector2i genPos(){//generate position for new values?

    sf::Vector2i v;
    if(DIFFICULTY==1){
    while(1)
    {
        v.x = rand()%N;
        v.y = rand()%N;
        if (MAP[v.y][v.x] == 0)
            break;
    }
    return v;
    }else if (DIFFICULTY==2){
         while(1)
    {
        v.x = rand()%O;
        v.y = rand()%O;
        if (MAP1[v.y][v.x] == 0)
            break;
    }
    return v;
    }else{
     while(1)
    {
        v.x = rand()%K;
        v.y = rand()%K;
        if (MAP2[v.y][v.x] == 0)
            break;
    }
    return v;
    }

}

enum class Direction
{
    Left,
    Right,
    Up,
    Down,
};

void coutMap()
{

    if(DIFFICULTY==1){
     for (int a=0; a<N; a++)
        {
            for (int b=0; b<M; b++)
                cout << MAP[a][b] << " ";
                cout << "\n";
        }
    }else if(DIFFICULTY==2){
     for (int a=0; a<O; a++)
        {
            for (int b=0; b<P; b++)
                cout << MAP1[a][b] << " ";
                cout << "\n";
        }
    }else {
    for (int a=0; a<K; a++)
        {
            for (int b=0; b<H; b++)
                cout << MAP1[a][b] << " ";
                cout << "\n";
        }
    }
    cout << "\n";
}

int genNewTile()
{
    int t = rand()%2;
    if (t==0)
        return 2;
    else
        return 4;
}

void placeNewTile()
{

    sf::Vector2i p = genPos();
    if(DIFFICULTY==1){
        MAP[p.y][p.x] = genNewTile();
    }else if(DIFFICULTY==2){
        MAP1[p.y][p.x] = genNewTile();
    }else{
        MAP2[p.y][p.x] = genNewTile();
    }
}

void shift(Direction d)
{

    if(DIFFICULTY==1){
    COP_Y();//SAVING before any change is made for undo
    bool didShift = 0;
    if (d == Direction::Up)
    {
        //COP_Y();//SAVING before any change is made for undo

        for (int j=0; j<M; j++) // Every row
        {
            for (int i=0; i<N-1; i++) // Search for every 0 (empty tile) and remove it
                if (MAP[i][j] == 0)
                {

                    bool change = 0;
                    for (int k=i; k<N-1; k++) // Shift everything up
                    {
                        MAP[k][j] = MAP[k+1][j];
                        if (MAP[k][j] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP[N-1][j] = 0;
                    if (change) i--; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int i=0; i<N-1; i++) // Merge the tiles with the same number
                if (MAP[i][j] == MAP[i+1][j] && MAP[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=i; k<N-1; k++)
                        MAP[k][j] = MAP[k+1][j];
                    MAP[N-1][j] = 0;
                    MAP[i][j] *= 2;
                }
        }
    }
    else if (d == Direction::Left)
    {
        //COP_Y();//SAVING before any change is made for undo
        for (int i=0; i<N; i++) // Every line
        {
            for (int j=0; j<M-1; j++) // Search for every 0 (empty tile) and remove it
                if (MAP[i][j] == 0)
                {

                    bool change = 0;
                    for (int k=j; k<M-1; k++) // Shift everything up
                    {
                        MAP[i][k] = MAP[i][k+1];
                        if (MAP[i][k] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP[i][M-1] = 0;
                    if (change) j--; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int j=0; j<N-1; j++) // Merge the tiles with the same number
                if (MAP[i][j] == MAP[i][j+1] && MAP[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=j; k<M-1; k++)
                        MAP[i][k] = MAP[i][k+1];
                    MAP[i][M-1] = 0;
                    MAP[i][j] *= 2;
                }
        }
    }
    else if (d == Direction::Down)
    {
        //COP_Y();//SAVING before any change is made for undo
        for (int j=0; j<M; j++) // Every row
        {
            for (int i=N-1; i>=0; i--) // Search for every 0 (empty tile) and remove it
                if (MAP[i][j] == 0)
                {

                    bool change = 0;
                    for (int k=i; k>0; k--) // Shift everything down
                    {
                        MAP[k][j] = MAP[k-1][j];
                        if (MAP[k][j] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP[0][j] = 0;
                    if (change) i++; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int i=N-1; i>0; i--) // Merge the tiles with the same number
                if (MAP[i][j] == MAP[i-1][j] && MAP[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=i; k>=0; k--)
                        MAP[k][j] = MAP[k-1][j];
                    MAP[0][j] = 0;
                    MAP[i][j] *= 2;
                }
        }
    }
    else if (d == Direction::Right)
    {
        //COP_Y();//SAVING before any change is made for undo
        for (int i=0; i<N; i++) // Every line
        {
            for (int j=M-1; j>=0; j--) // Search for every 0 (empty tile) and remove it
                if (MAP[i][j] == 0)
                {

                    bool change = 0;
                    for (int k=j; k>0; k--) // Shift everything to the right
                    {
                        MAP[i][k] = MAP[i][k-1];
                        if (MAP[i][k] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP[i][0] = 0;
                    if (change) j++; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int j=M-1; j>0; j--) // Merge the tiles with the same number
                if (MAP[i][j] == MAP[i][j-1] && MAP[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=j; k>0; k--)
                        MAP[i][k] = MAP[i][k-1];
                    MAP[i][0] = 0;
                    MAP[i][j] *= 2;
                }
        }
    }
        if (didShift)
        placeNewTile();


    }else if(DIFFICULTY==2){//IF DIFFICULTY IS 2



    COP_Y();//SAVING before any change is made for undo
    bool didShift = 0;
    if (d == Direction::Up)
    {
        //COP_Y();//SAVING before any change is made for undo

        for (int j=0; j<O; j++) // Every row
        {
            for (int i=0; i<P-1; i++) // Search for every 0 (empty tile) and remove it
                if (MAP1[i][j] == 0)
                {

                    bool change = 0;
                    for (int k=i; k<O-1; k++) // Shift everything up
                    {
                        MAP1[k][j] = MAP1[k+1][j];
                        if (MAP1[k][j] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP1[O-1][j] = 0;
                    if (change) i--; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int i=0; i<O-1; i++) // Merge the tiles with the same number
                if (MAP1[i][j] == MAP1[i+1][j] && MAP1[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=i; k<O-1; k++)
                        MAP1[k][j] = MAP1[k+1][j];
                    MAP1[O-1][j] = 0;
                    MAP1[i][j] *= 2;
                }
        }
    }
    else if (d == Direction::Left)
    {
        //COP_Y();//SAVING before any change is made for undo
        for (int i=0; i<O; i++) // Every line
        {
            for (int j=0; j<P-1; j++) // Search for every 0 (empty tile) and remove it
                if (MAP1[i][j] == 0)
                {
                    bool change = 0;
                    for (int k=j; k<P-1; k++) // Shift everything up
                    {
                        MAP1[i][k] = MAP1[i][k+1];
                        if (MAP1[i][k] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP1[i][P-1] = 0;
                    if (change) j--; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int j=0; j<O-1; j++) // Merge the tiles with the same number
                if (MAP1[i][j] == MAP1[i][j+1] && MAP1[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=j; k<P-1; k++)
                        MAP1[i][k] = MAP1[i][k+1];
                    MAP1[i][P-1] = 0;
                    MAP1[i][j] *= 2;
                }
        }
    }
    else if (d == Direction::Down)
    {
        //COP_Y();//SAVING before any change is made for undo
        for (int j=0; j<P; j++) // Every row
        {
            for (int i=O-1; i>=0; i--) // Search for every 0 (empty tile) and remove it
                if (MAP1[i][j] == 0)
                {
                    bool change = 0;
                    for (int k=i; k>0; k--) // Shift everything down
                    {
                        MAP1[k][j] = MAP1[k-1][j];
                        if (MAP1[k][j] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP1[0][j] = 0;
                    if (change) i++; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int i=O-1; i>0; i--) // Merge the tiles with the same number
                if (MAP1[i][j] == MAP1[i-1][j] && MAP1[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=i; k>=0; k--)
                        MAP1[k][j] = MAP1[k-1][j];
                    MAP1[0][j] = 0;
                    MAP1[i][j] *= 2;
                }
        }
    }
    else if (d == Direction::Right)
    {
        //COP_Y();//SAVING before any change is made for undo
        for (int i=0; i<O; i++) // Every line
        {
            for (int j=P-1; j>=0; j--) // Search for every 0 (empty tile) and remove it
                if (MAP1[i][j] == 0)
                {
                    bool change = 0;
                    for (int k=j; k>0; k--) // Shift everything to the right
                    {
                        MAP1[i][k] = MAP1[i][k-1];
                        if (MAP1[i][k] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP1[i][0] = 0;
                    if (change) j++; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int j=P-1; j>0; j--) // Merge the tiles with the same number
                if (MAP1[i][j] == MAP1[i][j-1] && MAP1[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=j; k>0; k--)
                        MAP1[i][k] = MAP1[i][k-1];
                    MAP1[i][0] = 0;
                    MAP1[i][j] *= 2;
                }
        }
    }
    if (didShift){
        //COP_Y();//SAVING before any change is made for undo
        placeNewTile();}



}else { //IF DIFFICULTY IS 3


    COP_Y();//SAVING before any change is made for undo
    bool didShift = 0;
    if (d == Direction::Up)
    {
       // COP_Y();//SAVING before any change is made for undo
        for (int j=0; j<H; j++) // Every row
        {
            for (int i=0; i<K-1; i++) // Search for every 0 (empty tile) and remove it
                if (MAP2[i][j] == 0)
                {
                    bool change = 0;
                    for (int k=i; k<K-1; k++) // Shift everything up
                    {
                        MAP2[k][j] = MAP2[k+1][j];
                        if (MAP2[k][j] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP2[K-1][j] = 0;
                    if (change) i--; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int i=0; i<K-1; i++) // Merge the tiles with the same number
                if (MAP2[i][j] == MAP2[i+1][j] && MAP2[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=i; k<K-1; k++)
                        MAP2[k][j] = MAP2[k+1][j];
                    MAP2[K-1][j] = 0;
                    MAP2[i][j] *= 2;
                }
        }
    }
    else if (d == Direction::Left)
    {
       // COP_Y();//SAVING before any change is made for undo
        for (int i=0; i<K; i++) // Every line
        {
            for (int j=0; j<H-1; j++) // Search for every 0 (empty tile) and remove it
                if (MAP2[i][j] == 0)
                {
                    bool change = 0;
                    for (int k=j; k<H-1; k++) // Shift everything up
                    {
                        MAP2[i][k] = MAP2[i][k+1];
                        if (MAP2[i][k] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP2[i][H-1] = 0;
                    if (change) j--; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int j=0; j<K-1; j++) // Merge the tiles with the same number
                if (MAP2[i][j] == MAP2[i][j+1] && MAP2[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=j; k<H-1; k++)
                        MAP2[i][k] = MAP2[i][k+1];
                    MAP2[i][H-1] = 0;
                    MAP2[i][j] *= 2;
                }
        }
    }
    else if (d == Direction::Down)
    {
        //COP_Y();//SAVING before any change is made for undo
        for (int j=0; j<H; j++) // Every row
        {
            for (int i=K-1; i>=0; i--) // Search for every 0 (empty tile) and remove it
                if (MAP2[i][j] == 0)
                {
                    bool change = 0;
                    for (int k=i; k>0; k--) // Shift everything down
                    {
                        MAP2[k][j] = MAP2[k-1][j];
                        if (MAP2[k][j] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP2[0][j] = 0;
                    if (change) i++; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int i=K-1; i>0; i--) // Merge the tiles with the same number
                if (MAP2[i][j] == MAP2[i-1][j] && MAP2[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=i; k>=0; k--)
                        MAP2[k][j] = MAP2[k-1][j];
                    MAP2[0][j] = 0;
                    MAP2[i][j] *= 2;
                }
        }
    }
    else if (d == Direction::Right)
    {
        //COP_Y();//SAVING before any change is made for undo
        for (int i=0; i<K; i++) // Every line
        {
            for (int j=H-1; j>=0; j--) // Search for every 0 (empty tile) and remove it
                if (MAP2[i][j] == 0)
                {
                    bool change = 0;
                    for (int k=j; k>0; k--) // Shift everything to the right
                    {
                        MAP2[i][k] = MAP2[i][k-1];
                        if (MAP2[i][k] != 0)
                        {
                            didShift = 1;
                            change = 1;
                        }
                    }
                    MAP2[i][0] = 0;
                    if (change) j++; // If something really changed (did not shift only 0s) check again the current position
                }
            for (int j=H-1; j>0; j--) // Merge the tiles with the same number
                if (MAP2[i][j] == MAP2[i][j-1] && MAP2[i][j] != 0)
                {
                    didShift = 1;
                    for (int k=j; k>0; k--)
                        MAP2[i][k] = MAP2[i][k-1];
                    MAP2[i][0] = 0;
                    MAP2[i][j] *= 2;
                }
        }
    }
    if (didShift){
        //COP_Y();//SAVING before any change is made for undo
        placeNewTile();}
}
}

void saveHIGHSCORE(int high, int high1, int high2){
    int temp, temp1, temp2;
    fstream easy("Save&load/easy high.txt",ios::in | ios::out);
    if(!easy.is_open())
            cout<<"error";
    else{easy>> temp2;
    if(temp2<=high2)
        easy<< high2;}
    easy.close();

        fstream normal("Save&load/normal high.txt",ios::in | ios::out);
        if(!normal.is_open())
            cout<<"error";
        else{normal>> temp1;
        if(temp1<=high1)
            normal<< high1;}
        normal.close();

            fstream hard("Save&load/hard high.txt",ios::in | ios::out);
            if(!hard.is_open())
                cout<<"error";
           else{ hard>> temp;
            if(temp<=high)
                hard<< high;}
            hard.close();



}

int * load(int n, int m){
     ifstream saving("Save&load/saved.bin",ios::binary | ios::in);
  if(!saving.is_open()){
    cout<<"error";
  }else{
      for(int i=0;i<n;i++){
        for(int j=0;j<m;i++){
            saving.read((char*)&MAP[i][j],sizeof(int));
            return *MAP;
        }
      }

                }
                saving.close();
}


int main()
{
    cout<< "1. New Game"<<endl<<"2. Load Game"<<endl;
    cin>>mode;
    cout<<"Enter Difficulty"<<endl<<"1. Hard"<<endl<<"2. Normal"<<endl<< "3. Easy"<<endl;
    cin>> DIFFICULTY;
   if(DIFFICULTY==1){
        WIDTH=TILESIZE*4;
        HEIGHT=TILESIZE*4;
   }else if(DIFFICULTY==2){
        WIDTH=TILESIZE*5;
        HEIGHT=TILESIZE*5;
   }else{
        WIDTH=TILESIZE*6;
        HEIGHT=TILESIZE*6;
   }
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(WIDTH-8, HEIGHT-8), "2048");

    sf::Texture tblank, t2, t4, t8, t16, t32, t64, t128, t256, t512, t1024, t2048, t4096, t8192;
    tblank.loadFromFile("images/blank.png");
    t2.loadFromFile("images/2.png");
    t4.loadFromFile("images/4.png");
    t8.loadFromFile("images/8.png");
    t16.loadFromFile("images/16.png");
    t32.loadFromFile("images/32.png");
    t64.loadFromFile("images/64.png");
    t128.loadFromFile("images/128.png");
    t256.loadFromFile("images/256.png");
    t512.loadFromFile("images/512.png");
    t1024.loadFromFile("images/1024.png");
    t2048.loadFromFile("images/2048.png");

    sf::Sprite sprite_blank(tblank);
    sf::Sprite sprite_2(t2);
    sf::Sprite sprite_4(t4);
    sf::Sprite sprite_8(t8);
    sf::Sprite sprite_16(t16);
    sf::Sprite sprite_32(t32);
    sf::Sprite sprite_64(t64);
    sf::Sprite sprite_128(t128);
    sf::Sprite sprite_256(t256);
    sf::Sprite sprite_512(t512);
    sf::Sprite sprite_1024(t1024);
    sf::Sprite sprite_2048(t2048);

    placeNewTile();
    placeNewTile();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && !g_win)
            {
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
                    shift(Direction::Left);
                else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
                    shift(Direction::Right);
                else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
                    shift(Direction::Up);
                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                    shift(Direction::Down);
                else if (event.key.code == sf::Keyboard::BackSpace ){
                    undo();
                }

            }
            else if (event.type == sf::Event::Closed)
                window.close();
        }

        ////////// CHECK IF USER WON THE GAME //////////
       if(DIFFICULTY==1){
        if (!g_win)
            for (int i=0; i<N; i++)
                for (int j=0; j<M; j++)
                    if (MAP[i][j] == 2049){
                        cout<<"you Won!!!!"<<endl;
                        g_win = 1;
                        break;
                    }
       }else if(DIFFICULTY==2){
         if (!g_win)
            for (int i=0; i<O; i++)
                for (int j=0; j<P; j++)
                    if (MAP1[i][j] == 2049){
                        cout<<"you Won!!!!"<<endl;
                        g_win = 1;
                        break;
                    }
       }else{
         if (!g_win)
            for (int i=0; i<K; i++)
                for (int j=0; j<H; j++)
                    if (MAP2[i][j] == 2049){
                        cout<<"you Won!!!!"<<endl;
                        g_win = 1;
                        break;
                    }
       }

{

                    }

        ////////// DRAW //////////
        window.clear();
 if(mode==1){
    if(DIFFICULTY==1){

        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
            {
                if (MAP[i][j] == 0)
                {
                    sprite_blank.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_blank);
                }
                else if (MAP[i][j] == 2)
                {
                    sprite_2.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2);
                }
                else if (MAP[i][j] == 4)
                {
                    sprite_4.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_4);
                }
                else if (MAP[i][j] == 8)
                {
                    sprite_8.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_8);
                }
                else if (MAP[i][j] == 16)
                {
                    sprite_16.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_16);
                }
                else if (MAP[i][j] == 32)
                {
                    sprite_32.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_32);
                }
                else if (MAP[i][j] == 64)
                {
                    sprite_64.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_64);
                }
                else if (MAP[i][j] == 128)
                {
                    sprite_128.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_128);
                }
                else if (MAP[i][j] == 256)
                {
                    sprite_256.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_256);
                }
                else if (MAP[i][j] == 512)
                {
                    sprite_512.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_512);
                }
                else if (MAP[i][j] == 1024)
                {
                    sprite_1024.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_1024);
                }
                else if (MAP[i][j] == 2048)
                {
                    sprite_2048.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2048);
                    cout<<"you won";
                }


            }

    }else if(DIFFICULTY==2){

         for (int i=0; i<P; i++)
            for (int j=0; j<O; j++)
            {
                if (MAP1[i][j] == 0)
                {
                    sprite_blank.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_blank);
                }
                else if (MAP1[i][j] == 2)
                {
                    sprite_2.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2);
                }
                else if (MAP1[i][j] == 4)
                {
                    sprite_4.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_4);
                }
                else if (MAP1[i][j] == 8)
                {
                    sprite_8.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_8);
                }
                else if (MAP1[i][j] == 16)
                {
                    sprite_16.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_16);
                }
                else if (MAP1[i][j] == 32)
                {
                    sprite_32.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_32);
                }
                else if (MAP1[i][j] == 64)
                {
                    sprite_64.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_64);
                }
                else if (MAP1[i][j] == 128)
                {
                    sprite_128.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_128);
                }
                else if (MAP1[i][j] == 256)
                {
                    sprite_256.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_256);
                }
                else if (MAP1[i][j] == 512)
                {
                    sprite_512.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_512);
                }
                else if (MAP1[i][j] == 1024)
                {
                    sprite_1024.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_1024);
                }
                else if (MAP1[i][j] == 2048)
                {
                    sprite_2048.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2048);
                    cout<<"you won";

                }

            }

    }else{

         for (int i=0; i<H; i++)
            for (int j=0; j<K; j++)
            {

                if (MAP2[i][j] == 0)
                {
                    sprite_blank.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_blank);
                }
                else if (MAP2[i][j] == 2)
                {
                    sprite_2.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2);
                }
                else if (MAP2[i][j] == 4)
                {
                    sprite_4.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_4);
                }
                else if (MAP2[i][j] == 8)
                {
                    sprite_8.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_8);
                }
                else if (MAP2[i][j] == 16)
                {
                    sprite_16.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_16);
                }
                else if (MAP2[i][j] == 32)
                {
                    sprite_32.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_32);
                }
                else if (MAP2[i][j] == 64)
                {
                    sprite_64.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_64);
                }
                else if (MAP2[i][j] == 128)
                {
                    sprite_128.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_128);
                }
                else if (MAP2[i][j] == 256)
                {
                    sprite_256.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_256);
                }
                else if (MAP2[i][j] == 512)
                {
                    sprite_512.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_512);
                }
                else if (MAP2[i][j] == 1024)
                {
                    sprite_1024.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_1024);
                }
                else if (MAP2[i][j] == 2048)
                {
                    sprite_2048.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2048);
                    cout<<"you won";
                }


            }


    }
 }else{
     if(DIFFICULTY==1)
        load(4,4);
    else if(DIFFICULTY==2)
        load(5,5);
    else
        load(6,6);
            if(DIFFICULTY==1){

        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++)
            {
                if (MAP[i][j] == 0)
                {
                    sprite_blank.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_blank);
                }
                else if (MAP[i][j] == 2)
                {
                    sprite_2.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2);
                }
                else if (MAP[i][j] == 4)
                {
                    sprite_4.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_4);
                }
                else if (MAP[i][j] == 8)
                {
                    sprite_8.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_8);
                }
                else if (MAP[i][j] == 16)
                {
                    sprite_16.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_16);
                }
                else if (MAP[i][j] == 32)
                {
                    sprite_32.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_32);
                }
                else if (MAP[i][j] == 64)
                {
                    sprite_64.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_64);
                }
                else if (MAP[i][j] == 128)
                {
                    sprite_128.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_128);
                }
                else if (MAP[i][j] == 256)
                {
                    sprite_256.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_256);
                }
                else if (MAP[i][j] == 512)
                {
                    sprite_512.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_512);
                }
                else if (MAP[i][j] == 1024)
                {
                    sprite_1024.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_1024);
                }
                else if (MAP[i][j] == 2048)
                {
                    sprite_2048.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2048);
                    cout<<"you won";
                }


            }

    }else if(DIFFICULTY==2){


         for (int i=0; i<P; i++)
            for (int j=0; j<O; j++)
            {
                if (MAP1[i][j] == 0)
                {
                    sprite_blank.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_blank);
                }
                else if (MAP1[i][j] == 2)
                {
                    sprite_2.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2);
                }
                else if (MAP1[i][j] == 4)
                {
                    sprite_4.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_4);
                }
                else if (MAP1[i][j] == 8)
                {
                    sprite_8.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_8);
                }
                else if (MAP1[i][j] == 16)
                {
                    sprite_16.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_16);
                }
                else if (MAP1[i][j] == 32)
                {
                    sprite_32.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_32);
                }
                else if (MAP1[i][j] == 64)
                {
                    sprite_64.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_64);
                }
                else if (MAP1[i][j] == 128)
                {
                    sprite_128.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_128);
                }
                else if (MAP1[i][j] == 256)
                {
                    sprite_256.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_256);
                }
                else if (MAP1[i][j] == 512)
                {
                    sprite_512.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_512);
                }
                else if (MAP1[i][j] == 1024)
                {
                    sprite_1024.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_1024);
                }
                else if (MAP1[i][j] == 2048)
                {
                    sprite_2048.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2048);
                    cout<<"you won";

                }

            }

    }else{


         for (int i=0; i<H; i++)
            for (int j=0; j<K; j++)
            {

                if (MAP2[i][j] == 0)
                {
                    sprite_blank.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_blank);
                }
                else if (MAP2[i][j] == 2)
                {
                    sprite_2.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2);
                }
                else if (MAP2[i][j] == 4)
                {
                    sprite_4.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_4);
                }
                else if (MAP2[i][j] == 8)
                {
                    sprite_8.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_8);
                }
                else if (MAP2[i][j] == 16)
                {
                    sprite_16.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_16);
                }
                else if (MAP2[i][j] == 32)
                {
                    sprite_32.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_32);
                }
                else if (MAP2[i][j] == 64)
                {
                    sprite_64.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_64);
                }
                else if (MAP2[i][j] == 128)
                {
                    sprite_128.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_128);
                }
                else if (MAP2[i][j] == 256)
                {
                    sprite_256.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_256);
                }
                else if (MAP2[i][j] == 512)
                {
                    sprite_512.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_512);
                }
                else if (MAP2[i][j] == 1024)
                {
                    sprite_1024.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_1024);
                }
                else if (MAP2[i][j] == 2048)
                {
                    sprite_2048.setPosition(j*TILESIZE, i*TILESIZE);
                    window.draw(sprite_2048);
                    cout<<"you won";
                }

            }


    }


 }
    window.display();

    }
    for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
    if(MAP[0][0]<MAP[i][j]){ //storing  high score
                    HIGH=MAP[i][j];}}}

    for (int i=0; i<O; i++){
            for (int j=0; j<P; j++){
                if(MAP1[0][0]<MAP1[i][j]){ //storing  high score
                    HIGH1=MAP1[i][j];}}}

       for (int i=0; i<K; i++){
            for (int j=0; j<H; j++){
    if(MAP2[0][0]<MAP2[i][j]){ //storing  high score
                    HIGH2=MAP2[i][j];}}}

    if(DIFFICULTY==1)
        cout<< "you score is "<< HIGH<<endl;
    else if (DIFFICULTY==2)
        cout<< "you score is "<< HIGH1<<endl;
    else
        cout<< "you score is "<< HIGH2<<endl;

    saveHIGHSCORE(HIGH,HIGH1,HIGH2);

    ofstream saving("Save&load/saved.bin",ios::binary | ios::out);
  if(!saving.is_open()){
    cout<<"error";
  }else{
      if(DIFFICULTY==1){
      for(int i=0;i<N;i++){
        for(int j=0;j<M;i++){
            saving.write((char*)&MAP[i][j],sizeof(int));
        }
      }

        }else if(DIFFICULTY==2){
             for(int i=0;i<O;i++){
        for(int j=0;j<P;i++){
            saving.write((char*)&MAP1[i][j],sizeof(int));
        }
      }
        }else{
             for(int i=0;i<K;i++){
        for(int j=0;j<H;i++){
            saving.write((char*)&MAP2[i][j],sizeof(int));
        }
      }
        }
                }

                saving.close();


    return 0;

    }




