#include <stdio.h>
#include <cstring>
#include <iostream>
#include <stdbool.h>
#include <list>
#include <typeinfo>


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
        bool CheckCollisions(Symulation S);
        bool Move(int mx,int my, Symulation S);
};

class Entity
{
    private:
        std::string n;
    public:
        Collider hb;
        Entity_Type et;
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
};

class Symulation
{
    private:
        int age;
    public:
        std::list<Entity> ents; 
        Symulation(){age=0;};
        void Step(){age++;};
        int GetAge(){return age;};
        int AddEntity(Entity e){
            if(ents.size()<ents.max_size())
            {
                ents.push_back(e);
                return ents.size();
            };return ents.size();
        };
};

bool Collider::CheckCollisions(Symulation S)
{
    std::list<Entity>::iterator iter;
    for(iter = S.ents.begin(); iter != S.ents.end(); iter++)
    {
        //int roll = iter->roll;
        //if(*this->pos==*iter->hb.pos){std::cout << "this is myself (" << iter->GetName() << ")" <<std::endl;
        //}else{std::cout << iter->GetName() <<std::endl;};
        if(!(*this->pos==*iter->hb.pos) && this->IsColliding(iter->hb))
        {
            //std:: cout << iter->GetName() << std::endl;
            return true;
        };
    };
    return false;
};

bool Collider::Move(int mx,int my, Symulation S)
{
    if(!this->CheckCollisions(S))
    {
        pos[0]=pos[0]+mx;
        pos[1]=pos[1]+my;
        //std::cout << this->pos[0] << "/" << this->pos[1] << std::endl;
        return true;
    };
    return false;
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
