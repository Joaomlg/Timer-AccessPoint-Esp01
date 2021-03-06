/*
    Autor: João Marcos Lana Gomes
    Dezembro, 2018

    Ler header da biblioteca para demais explicações: 'time.h'
*/

#include "time.h"

Time::Time() {
    _hour = 0;
    _minute = 0;
    _second = 0;
}

Time::Time(byte hour, byte minute, byte second) {
    _hour = hour;
    _minute = minute;
    _second = second;
}

Time::Time(DateTime time) {
    _hour = time.hour();
    _minute = time.minute();
    _second = time.second();
}

byte Time::get_hour() {
    return _hour;
}

byte Time::get_minute() {
    return _minute;
}

byte Time::get_second() {
    return _second;
}

bool Time::cmp(byte hour, byte minute) {
    if(_hour == hour && _minute == minute)
        return true;
    return false;
}

bool Time::cmp(byte hour, byte minute, byte second) {
    if(_hour == hour && _minute == minute && _second == second)
        return true;
    return false;
}

bool Time::operator == (const Time& other) {
    if(_hour == other._hour && _minute == other._minute && _second == other._second)
        return true;
    return false;
}

bool Time::operator != (const Time& other) {
    Time self = Time(_hour, _minute, _second);
    if(!(self == other))
        return true;
    return false;
}

bool Time::operator > (const Time& other) {
    if(_hour != other._hour) {
        return (_hour > other._hour ? true : false);
    } else {
        if(_minute != other._minute) {
            return (_minute > other._minute ? true : false);
        } else {
            if(_second != other._second) {
                return (_second > other._second ? true : false);
            } else {
                return false;
            }
        }
    }
}

bool Time::operator < (const Time& other) {
    Time self = Time(_hour, _minute, _second);
    if(!(self > other))
        return true;
    return false;
}

bool Time::operator >= (const Time& other) {
    Time self = Time(_hour, _minute, _second);
    if(self > other || self == other)
        return true;
    return false;
}

bool Time::operator <= (const Time& other) {
    Time self = Time(_hour, _minute, _second);
    if(self < other || self == other)
        return true;
    return false;
}

Time Time::operator + (const Time& other) {
    byte hour = _hour + other._hour;
    byte minute = _minute + other._minute;
    byte second = _second + other._second;
    
    if(second > 59) {
        minute += second / 60;
        second = second % 60;
    }

    if(minute > 59) {
        hour += minute / 60;
        minute = minute % 60;
    }

    if(hour > 23) {
        hour = hour % 24;
    }

    return Time(hour, minute, second);
}

Time Time::operator - (const Time& other) {
    byte hour = _hour - other._hour;
    byte minute = _minute - other._minute;
    byte second = _second - other._second;
    
    if(second < 0) {
        minute -= (second / 60) + 1;
        second = second + 60;
    }

    if(minute < 0) {
        hour -= (minute / 60) + 1;
        minute = minute + 60;
    }

    if(hour < 0) {
        hour = hour + 24;
    }


    return Time(hour, minute, second);
}

unsigned long Time::toSeconds() {
    return _hour*3600 + _minute*60 + _second;
}

String Time::toStr(bool showSeconds) {
    String times_str[] = {String(_hour), String(_minute), String(_second)};

    for(int i=0; i<3; i++) {
        // Adiciona zeros se preciso (9:5 -> 09:05)
        if(times_str[i].length() < 2) {
        times_str[i] = '0' + times_str[i];
        }
    }

    if(showSeconds) {
        return (times_str[0] + ':' + times_str[1] + ':' + times_str[2]); 
    } else {
        return (times_str[0] + ':' + times_str[1]); 
    }
}
