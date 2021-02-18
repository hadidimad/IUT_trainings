#include <stdio.h>
long int _abs(long int a)
{

    return (a < 0) ? -a : a;
}

int main()
{
    long int k, boy_friend, date_place;
    long int boy_offset, girl_offset, time;
    scanf("%li %li %li", &k, &boy_friend, &date_place);
    int first_boy_place = boy_friend;
    int first_date_place = date_place;

    boy_offset = _abs(boy_friend) % k;
    if (boy_offset > k / 2)
    {
        boy_offset = k - boy_offset;
        // boy_friend += boy_offset;
        boy_friend = boy_friend + ((boy_friend >= 0) ? boy_offset : -boy_offset);
    }
    else
    {
        boy_friend = boy_friend + ((boy_friend >= 0) ? -boy_offset : boy_offset);
    }
    girl_offset = _abs(date_place) % k;

    if (girl_offset > k / 2)
    {
        girl_offset = k - girl_offset;
        date_place = date_place + ((date_place >= 0) ? girl_offset : -girl_offset);
    }
    else
    {
        date_place = date_place + ((date_place >= 0) ? -girl_offset : girl_offset);

        // date_place -= girl_offset;
    }
    time = (_abs(boy_friend - date_place) / k) + girl_offset + boy_offset;
    if (_abs((first_boy_place - first_date_place)) < time)
    {
        printf("%li", _abs(first_boy_place - first_date_place));
    }
    else
    {
        printf("%li", time);
    }

    return 0;
}