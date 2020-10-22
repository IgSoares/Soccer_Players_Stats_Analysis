#ifndef SOB_H
#define SOB_H

#include "jogador.h"

std::istream& operator>>(std::istream &in,DateTime& d);

std::ostream& operator<<(std::ostream &out,const DateTime& d);

bool operator<=(const DateTime& a,const DateTime& b);

bool operator>=(const DateTime& a,const DateTime& b);

bool operator<(const DateTime& a,const DateTime& b);

bool operator>(const DateTime& a,const DateTime& b);


#endif

