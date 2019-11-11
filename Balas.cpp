
class Bala{
protected://atributos de la bala 
int danio;
bool Objetivo;
public:
virtual void Realizar_Danio(int,int,vector<Alien>);
virtual void Rebotar();
virtual void Danio()=0;
};
//Funciones de la bala 
void Bala::Realizar_Danio(int x,int y,vector<Alien> aliens){
    //lo que pasa cuando choca a un Alien
    //a->vida=a->vida - danio;//esto le pasaria al alien si lo tuviera como parametro
    Objetivo=false; 
    for(int i=0;i<aliens.size();i++){//hay un vector que contiene varios aliens entonces hago un for al tamaño de ese vector
        if(aliens[i].posicion_x==x){//si la posicion de la bala en la que fue lanzada es igual a la de algun alien  
            Objetivo=true;//el objetivo es por si le a llegado a caer la bala al alien
            aliens[i].vida=aliens[i].vida-danio;//si le callo bajale vida al alien lo que la bala hace efecto
            break;
        }
    }


}
void Bala::Rebotar(){
    if(!Objetivo){//si no encuentra objetivo
        //llenar 
    }
}

class Bala_Suave:public Bala{
    public:
    Bala_Suave(){}
    void Realizar_Danio(int,int,vector<Alien>) override;//hereda la funcion gracias al polimorfismo
    void Rebotar(){}//no hace nada
    void Danio() override{
        danio=10;
    } 
};


class Bala_Fuerte:public Bala{
    public:
    Bala_Fuerte(){}
    void Realizar_Danio(int x,int y,vector<Alien> aliens) override;//hereda la funcion gracias al polimorfismo
    void Rebotar(){}
    void Danio() override{
        danio=20;
    }
};
