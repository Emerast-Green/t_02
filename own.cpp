#include <stdio.h>
#include <cstring>
#include <iostream>
#include <stdbool.h>
//#include <list>
#include <typeinfo>
#include <cmath>

enum Entity_Type { Player, Storage, Item, NPC };
class Symulation;
//class Entity;

class Collider 
{
    public:
        int pos[2];
        int size[2];
        Collider(){};
        Collider(int px, int py, int sx, int sy)
        {
            pos[0]=px;pos[1]=py;
            size[0]=sx;size[1]=sy;
        };
        bool IsColliding(Collider other)
        {
            return IsColliding(other.pos,other.size);
        };
        bool IsColliding(int p[2], int s[2])
        {
            return (
                ((pos[0]<=p[0] && p[0]<=pos[0]+size[0]) || (p[0]<=pos[0] && pos[0]<=p[0]+s[0])) // Overlaping on OX 
                && 
                ((pos[1]<=p[1] && p[1]<=pos[1]+size[1]) || (p[1]<=pos[1] && pos[1]<=p[1]+s[1])) // Overlaping on OY
                );
        };
        bool CheckCollisions(Symulation& S);
        bool CheckCollisions(Symulation& S,int pos[2],int size[2]);
        bool Move(int mx,int my, Symulation& S);
        void MoveA(int mx,int my, Symulation& S);
};

class Entity
{
    private:
        std::string n;
    public:
        Collider hb;
        Collider* ptr_hb = &hb;
        Entity_Type et;
        Entity(){};
        Entity(int px,int py, int sx, int sy,std::string name,Entity_Type etype){
            n=name;
            et=etype;
          //  hitbox.pos[0] = px ; hitbox.pos[1] = py;
         //   hitbox.size[0] = sx; hitbox.size[1] = sy;
            hb.pos[0]=px; hb.pos[1]=py;
            hb.size[0]=sx;hb.size[1]=sy;
        };
        std::string GetName(){
            return n;
        };
        Entity& getThis()
        {
            return *this;
        }
};

class Symulation
{
    private:
        int age;
    public:
        //std::list<Entity> ents; 
        Entity* ents[16];
        int ents_size = 0;
        Symulation(){age=0;};
        void Step(){age++;};
        int GetAge(){return age;};
        int AddEntity(Entity& e){
            if(ents_size<16)
            {
                ents[ents_size]=&e;
                ents_size++;
                return ents_size;
            };return ents_size;
        };
        void FetchData()
        {
            for(int i=0;i<ents_size;i++)
            {
                std::cout << ents[i]->GetName() << " " << ents[i]->hb.pos[0] << " " << ents[i]->hb.pos[1] <<std::endl;
            };
        };
};

bool Collider::CheckCollisions(Symulation& S)
{
    //std::list<Entity>::iterator iter;
    //for(iter = S.ents.begin(); iter != S.ents.end(); iter++)
    for(int i=0;i<S.ents_size;i++)
    {
        //int roll = iter->roll;
        //if(*this->pos==*iter->hb.pos){std::cout << "this is myself (" << iter->GetName() << ")" <<std::endl;
        //}else{std::cout << iter->GetName() <<std::endl;};
        if(!(*this->pos==*S.ents[i]->hb.pos) && this->IsColliding(S.ents[i]->hb))
        {
            //std:: cout << iter->GetName() << std::endl;
            return true;
        };
    };
    return false;
};

bool Collider::CheckCollisions(Symulation& S,int p[2],int s[2])
{
   // std::list<Entity>::iterator iter;
    //for(iter = S.ents.begin(); iter != S.ents.end(); iter++)
    for(int i=0;i<S.ents_size;i++)
    {
        //int roll = iter->roll;
        //if(*this->pos==*iter->hb.pos){std::cout << "this is myself (" << iter->GetName() << ")" <<std::endl;
        //}else{std::cout << iter->GetName() <<std::endl;};
        if(!(*this->pos==*S.ents[i]->hb.pos) && S.ents[i]->hb.IsColliding(p,s))
        {
            //std:: cout << iter->GetName() << std::endl;
            return true;
        };
    };
    return false;
};

bool Collider::Move(int mx,int my, Symulation& S)
{
    int pos_[2];
    pos_[0] = pos[0]+mx;
    pos_[1] = pos[1]+my;
    if(!CheckCollisions(S,pos_,size))
    {
        pos[0]=pos[0]+mx;
        pos[1]=pos[1]+my;
        //std::cout << this->pos[0] << "/" << this->pos[1] << std::endl;
        return true;
    };
    return false;
};

void Collider::MoveA(int mx,int my,Symulation& S)
{
    float tmp[2];tmp[0]=0.0;tmp[1]=0.0;
    float dist;dist=sqrt(pow(mx,2)+pow(my,2));
    for(int i=0;i<(int)dist;i++)
    {
        tmp[0]=tmp[0]+mx/dist;tmp[1]=tmp[1]+my/dist;
        if(!this->Move((int)tmp[0],(int)tmp[1],S)){break;};
    };
};

// int main()
// {
//     Entity t1(0,0,10,10,"test",Player);
//     Entity t2(5,5,10,10,"name",Player);
//     //std::cout << t.GetName() <<std::endl;
//     Symulation S1;
//     std::cout << S1.AddEntity(t1) <<std::endl;
//     std::cout << S1.AddEntity(t2) <<std::endl;
//     //std::cout << S1.ents.front().GetName() <<std::endl;
//     for(int i=0;i<15;i++){S1.Step();};
//     //std::cout << S1.GetAge() <<std::endl;
//     Collider a1(0,0,10,10);
//     Collider a2(0,0,10,10);
//     //std::cout << a1.IsColliding(a2) <<std::endl;
//     //std::cout << a2.IsColliding(a1) <<std::endl;
//     std::cout << t1.hb.Move(5,0,S1) <<std::endl;
//     return 0;
// }
