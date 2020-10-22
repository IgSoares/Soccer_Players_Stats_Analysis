#include "sobrecargas_data.h"


std::istream& operator>>(std::istream &in,DateTime& d){

     in >> d.year;
     in.ignore();
     in >> d.month;
     in.ignore();
     in >> d.day;
     in.ignore();
     in >> d.hour;
     in.ignore();
     in >> d.minute;
     in.ignore();
     in >> d.second;

     return in;
}


std::ostream& operator<<(std::ostream &out,const DateTime& d){

     out << d.year << '/' << d.month << '/' << d.day << ',' << d.hour << ':' << std::setw(2) << std::setfill('0')<< d.minute << ':' << std::setw(2) << d.second;
     std::cout.fill(' ');

     return out;
}


bool operator<(const DateTime& a,const DateTime& b){

	return !(a >= b);
}


bool operator>(const DateTime& a,const DateTime& b){

    return !(a <= b);
}


bool operator<=(const DateTime& a,const DateTime& b){

    if(a.year != b.year){
        return a.year < b.year;
    }
    if(a.month != b.month){
        return a.year < b.year;
    }
    if(a.day != b.day){
        return a.day < b.day;
    }
    if(a.hour != b.hour){
        return a.hour < b.hour;
    }
    if(a.minute != b.minute){
        return a.minute < b.minute;
    }
    if(a.second != b.second){
        return a.second < b.second;
    }
    return true;
}


bool operator>=(const DateTime& a,const DateTime& b){

    if(a.year != b.year){
        return a.year > b.year;
    }
    if(a.month != b.month){
        return a.year > b.year;
    }
    if(a.day != b.day){
        return a.day > b.day;
    }
    if(a.hour != b.hour){
        return a.hour > b.hour;
    }
    if(a.minute != b.minute){
        return a.minute > b.minute;
    }
    if(a.second != b.second){
        return a.second > b.second;
    }
    return true;
}

DateTime DateTime::operator+(const DateTime& a){

    if(a > *this){
        this->day = a.day;
        this->month = a.month;
        this->year = a.year;
	}

	this->second += a.second;
	if(this->second >= 60){
        this->second -=60;
        this->minute++;
	}

	this->minute += a.minute;
	if(this->minute >= 60){
        this->minute -= 60;
        this->hour++;
	}

	this->hour += a.hour;

    return *this;
}


DateTime DateTime::operator-(const DateTime& a){ //corrigir (vazamento memoria) ->Errado

    std::time_t tempo_1 = this->toTimestamp();
    std::time_t tempo_2 = a.toTimestamp();
    std::time_t dif;

    if(tempo_1 >= tempo_2){
        dif = difftime(tempo_1,tempo_2);
    }
    else{
        dif = difftime(tempo_2,tempo_1);
    }
    if(a > *this){
        this->day = a.day;
        this->month = a.month;
        this->year = a.year;
	}

    this->fromTimestamp(dif);

    return *this;
}


DateTime& DateTime::operator=(const DateTime& a){

    this->year = a.year;
    this->month = a.month;
    this->day = a.day;
    this->hour = a.hour;
    this->minute = a.minute;
    this->second = a.second;
    return *this;
}
