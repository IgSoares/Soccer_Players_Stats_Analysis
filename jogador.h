#ifndef LEITURA_H
#define LEITURA_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <ctime>
#include <list>

class UserInfos;
class Stats;


//Estrutura definida para representar as datas e os horarios das atividades dos jogadores
struct DateTime{

     int day,month,year;
     int hour,minute,second;

     DateTime operator+(const DateTime& a);
     DateTime operator-(const DateTime& a);
     DateTime& operator=(const DateTime& a);

     std::time_t toTimestamp() const;
     void fromTimestamp(std::time_t time);

};


//Estrutura definida para representar as localizações dos jogadores durante a atividade
struct GlobalCoord{

     double latitude,longitude;
     char dirlat,dirlong;
};


//Estrutura definida para armazenar as informações dos jogadores
struct PlayerData{

     DateTime UTC;
     DateTime Local;
     int MS;
     GlobalCoord position;
     double speed;
     double altitude;
     double heading;
};


//Estrutura definida para o jogador,contendo um vetor de estruturas com as infos de cada jogador
struct Player{

     std::vector<PlayerData> data;
     Stats* s;
};

class Stats{

	DateTime time_1,time_2,tot_time; // tempo primeira atividade, segunda e tempo total
	DateTime faster_th18,faster_th20; // tepo a mais de 18 e 20 Km/h
	int speed_ft_18,speed_ft_20; // quantidade de corridas maior que 18 e 20 Km/h
	double max_speed_Kmh,max_speed_ms;// velocidade maxima
	double distance; // distancia percorrida

public:

	Stats();
	~Stats();
    void Calculate_first_time(UserInfos& us);//user infos -> struct ou classe responsavel pelos dados mandados pelo usuario
    void Calculate_sec_time(UserInfos& us);
    void Calculate_tot_time(UserInfos& us);
	void Calculate_speed_ft_18(Player& p);
	void Calculate_speed_ft_20(Player& p);
	void Calculate_max_speed(Player& p);
	void Calculate_total_distance(UserInfos& us,Player& p);
	DateTime get_first_time();
	DateTime get_sec_time();
	DateTime get_tot_time();
	DateTime get_time_ft_18();
	DateTime get_time_ft_20();
	int num_times_ft18();
	int num_times_ft20();
	double get_max_speed_Kmh();
	double get_max_speed_ms();
	double get_total_distance();

};

std::ostream& operator<<(std::ostream& out,const Player& p);

std::map<int,Player> readPlayerData(std::string name,UserInfos& us);

std::list<Player> lista_distancia(std::map<int,Player> m);

void destroi_stats(Player *p);

#endif // LEITURA_H
