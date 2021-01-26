//
// Created by sergiy on 1/25/21.
//

void strcopy(char *s, char *t){
    int i;
    i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}

void strcopy2(char *s, char *t){
    while ((*s = *t) != '\0'){
        s++;
        t++;
    }
}

void strcopy3(char *s, char *t){
    while ((*s++ = *t++) != '\0')
        ;
}

void strcopy4(char *s, char *t){
    while (*s++ = *t++)
        ;
}
