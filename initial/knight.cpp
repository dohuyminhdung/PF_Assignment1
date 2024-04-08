#include "knight.h"
class Hiiro {
    public:
    int MaxHP, HP,
    level,
    remedy,
    maidenkiss, 
    phoenixdown, 
    rescue;
    bool merlin_meet = false, asclepius_meet = false, arthur = false, lancelot = false, thua_bowser = false, event0 = false; 
};
int levelO (int i){
    int b; 
    int levelO;
    b = i%10 ; 
    levelO = i > 6?(b > 5?b : 5) : b   ; 
    return levelO;
    }
bool snt (int n){
    bool snt = true;
    if (n==2) snt = true;
    else for (int i = 2; i<n/2; i++) if (n%i==0) snt = false;
    return snt;
    }   
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}
void HPcheck (int &HP, int &MaxHP){
if (HP>MaxHP) HP = MaxHP;
}

void itemcheck (int &item){
    if (item>99) item = 99;
}
void getmario (int &HP, int &lvl, int &pd){
    int n, mario, s=0;
    n = ((lvl + pd)%5 + 1) * 3;
    for ( int i = 0; i<n; i++) 
        s = s + (99-i*2);
    HP = HP + (s%100);
    while (snt(HP)==false) HP = HP + 1;
}
int fib (int n){
    if (n==1 || n==2) return 1;
    else return fib(n-2) + fib(n-1);
    // hàm về dãy số fibo
}
bool fibocheck (int HP){
    bool check = false;
    int i = 1;
    while (fib(i)<=HP){
        if (fib(i) == HP) {
            check = true; 
            break; 
            }
        else i = i+1; 
    }
    return check;
}
void meet_asclepius (string path, int &rmd, int &mdk, int &pd) {
    ifstream input(path);
    int r1, c1, medicine, count = 0;
    string s;
    input>>r1; 
    getline(input, s); 
    input>>c1; 
    for (int p = 0; p < r1; p++) {
        getline(input, s); 
         count = 0;
         for (int i = 0; i<c1 ; i++){
            input>>medicine; 
             if (count == 3) continue; 
             if (medicine == 16) {
                 rmd = rmd + 1;
                 itemcheck(rmd);
                 count = count + 1;
             }
             if (medicine == 17) {
                 mdk = mdk + 1;
                 itemcheck(mdk);
                 count = count + 1;
                
             }
             if (medicine == 18) {
                 pd = pd + 1;
                 itemcheck(pd);
                 count = count + 1;
                
             }
         } //small for
    } //big for
    input.close();
}
void meet_merlin (string path, int &HP){
    ifstream input(path);
    int n9;
    string s, ml, Ml;
    ml = "merlin";
    Ml = "Merlin";
    input>>n9;
    getline(input, s);
    while (getline(input, s)){
        if (s.find(ml) != string::npos || s.find(Ml) != string::npos) 
            HP = HP + 3; 
        else if ((s.find('M') != string::npos || s.find('m') != string::npos) && (s.find('E') != string::npos || s.find('e') != string::npos) && (s.find('R') != string::npos || s.find('r') != string::npos ) && (s.find('L') != string::npos || s.find('l') != string::npos ) && (s.find('I') != string::npos || s.find('i') != string::npos) && (s.find('N') != string::npos || s.find('n') != string::npos))
            HP = HP + 2;
        else continue;    
    }
    input.close();
}
void teemo (string path, int &HP, int &MaxHP, int &num2str, int &debuff1, int &debuff2, int &frogdb, int &level, int &phoenixdown){
    // convert num2str, the mushrooms will affect us:
    string str;
    ostringstream convert;   
    convert << num2str;      
    str = convert.str();
    int mushnum = str.length(); //mushroom in event
    // handle the file, call the string that detail mushroom effects:
    ifstream input(path);
    int n2;
    string in;
    input>>n2; //number of variable in array
    getline (input,in);
    getline (input,in);
    // convert the string in file to array:
    int arr[100];
    for (int i = 0; i < in.length() ; i++){
        if (in[i] == ',') { in[i] = ' '; }
    }
    stringstream intel(in);
    for (int m=0; m<n2; m++){
        intel>>arr[m];
    }
    /* tasks for mushroom type 2:*/
    //testing the array is mountain form or not:
    //calling mtx and mti also
    bool dinh, nui;
    int dinhnui = 0, vitri = 0;
    int mtx = 0, mti = 0;
    dinh = false;
    nui = false;
    arr[n2] = -999;
    for (int k = 0; k<n2; k++) {
    if (arr[k]==arr[k+1]) {
        nui = false; 
        break; 
        }   
    if (dinh == false && arr[k]<arr[k+1]) 
        continue;
    if (dinh == false && arr[k]>arr[k+1]) {
        dinh = true; 
        nui = true;
        dinhnui = arr[k];
        vitri = k;
    }
    if (dinh == true && arr[k]<=arr[k+1]){
        nui = false; 
        break;
    }
   }
    if (nui == true) {
        mtx = dinhnui; 
        mti = vitri;
    }
    if (nui != true) {
        mtx = -2;
        mti = -3;
    }

    /*tasks for mushroom type 1:*/
    //caculating maxi and mini 
    int max = arr[0];
    int min = arr[0];
    int maxi, mini;
    for (int n = 0; n < n2; n++){
        if (arr[n]>=max) {
            max = arr[n];
            maxi = n;
        }
    }
    for (int l = 0; l < n2; l++){
        if (arr[l]<=min) {
            min = arr[l];
            mini = l;
        }
    }
    /*create array for type 3 and 4*/
    int arr2[100];
    for (int g = 0; g < n2; g++) {
        if (arr[g] < 0) arr2[g] = 0 - arr[g];
        else arr2[g] = arr[g];
        arr2[g] =  (17 * arr2[g] + 9)%257;
        
    }
    //tasks for mushroom type 3:
    //calling maxi2, mini2
    int max2 = arr2[0];
    int min2 = arr2[0];
    int maxi2 = 0, mini2 = 0;
    for (int x = 0; x < n2; x++){
        if (arr2[x]>max2) {
            max2 = arr2[x];
            maxi2 = x;
        }
    }
    for (int y = 0; y < n2; y++){
        if (arr2[y]<min2) {
            min2 = arr2[y];
            mini2 = y;
        }
    }
    //tasks for mushroom type 4:
    //calling max2_3x, max2_3i:
    int max2_3x = 0;
    int max2_3i = 0;
    int save1 = 0, save2 = 0;
    if (arr2[0]==arr2[1] && arr[1]==arr2[2]) {
        max2_3x = -5; 
        max2_3i = -7;
    } 
    else {
        for (int h = 0; h < 3; h++){
            if (arr2[h]>max2_3x) {
                max2_3x = arr2[h];
                save1 = arr2[h];
                max2_3i = h;
                save2 = h;
            }
        }
        arr2[max2_3i] = 0;
        max2_3x = 0;
        for (int j = 0; j < 3; j++){
            if (arr2[j]>max2_3x) {
                max2_3x = arr2[j];
                max2_3i = j;
            }
        }
        arr2[save2] = save1;
    }
    // if (max2_3i != 0 && max2_3i != 1 && max2_3i != 2) {
    //     max2_3x = -5; 
    //     max2_3i = -7;
    // }
    //handle the mushroom will meet 
    //string of event 13<ms> is str
    //the length of str is mushnum
    for (int b = 2; b < mushnum; b++) {
    //case 1:
    if (str[b] == '1') {
        HP = HP - (maxi + mini); 
    //HPcheck
        HPcheck (HP, MaxHP);
        if (HP<=0){
            if (phoenixdown>0) {
                phoenixdown = phoenixdown - 1;
                HP = MaxHP;
                if (debuff2 != 0) {
                    debuff2 = 0;
                    level = frogdb;
                    }
                if (debuff1 != 0) { 
                    debuff1 = 0;
                    HP = HP * 5;
                    HPcheck (HP, MaxHP); 
                }    
                } // pd > 0
            else break; //pd<0; keep HP < 0, break for            
        }//HP<0
    }//end case 1
    //case 2:
    if (str[b] == '2') {
        HP =  HP - (mtx + mti); 
        HPcheck (HP, MaxHP);
        if (HP<=0){
            if (phoenixdown>0) {
                phoenixdown = phoenixdown - 1;
                HP = MaxHP;
                if (debuff2 != 0) {
                    debuff2 = 0;
                    level = frogdb;
                    }
                if (debuff1 != 0) { 
                    debuff1 = 0;
                    HP = HP * 5;
                    HPcheck (HP, MaxHP); 
                }    
                } // pd > 0
            else break; //pd<0; keep HP < 0, break for            
        }//HP<0

    }//end case 2
    //case 3 
    if (str[b] == '3') {
        HP = HP - (maxi2 + mini2); 
        if (HP<=0){
            if (phoenixdown>0) {
                phoenixdown = phoenixdown - 1;
                HP = MaxHP;
                if (debuff2 != 0) {
                    debuff2 = 0;
                    level = frogdb;
                    }
                if (debuff1 != 0) { 
                    debuff1 = 0;
                    HP = HP * 5;
                    HPcheck (HP, MaxHP); 
                }    
                } // pd > 0
            else break; //pd<0; keep HP < 0, break for            
        }
    }//end case 3
    //case 4
    if (str[b] == '4') {
        HP = HP - (max2_3x + max2_3i); 
        if (HP<=0){
            if (phoenixdown>0) {
                phoenixdown = phoenixdown - 1;
                HP = MaxHP;
                if (debuff2 != 0) {
                    debuff2 = 0;
                    level = frogdb;
                    }
                if (debuff1 != 0) { 
                    debuff1 = 0;
                    HP = HP * 5;
                    HPcheck (HP, MaxHP); 
                }    
                } // pd > 0
            else break; //pd<0; keep HP < 0, break for            
        }
    }//end case 4
    } //for
    input.close();
    
} //after this void if still get HP<0 we will turn to another pd check, ofc will no pd left and turn to rescue = 0
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    ifstream input(file_input);
    Hiiro hiiro;
    input>>hiiro.MaxHP;
    input>>hiiro.level;
    input>>hiiro.remedy;
    input>>hiiro.maidenkiss;
    input>>hiiro.phoenixdown;
    hiiro.HP = hiiro.MaxHP;
    if (hiiro.HP==999) hiiro.arthur = true;
    if (snt(hiiro.HP)==true) hiiro.lancelot == true;
    string s;
    getline (input, s);
    getline (input, s);
    string packs;
    getline (input, packs); 
    string mushghost, merlin, asclepius;
    mushghost = "";
    merlin = "";
    asclepius = "";
    mushghost = packs.substr(0, packs.find(",")); 
    asclepius = packs.substr(packs.find(",") + 1, packs.find(",",packs.find(",") + 1) - packs.find(",") - 1); 
    merlin = packs.substr(packs.find( ",", packs.find(",") + 1) + 1); 
    hiiro.rescue = -1;
    int i = 1, event = 0, k = 0;
    int frogdb = 0 , debuff1 = 0, debuff2 = 0 ;
    s += " ";
    for ( ; k<s.length(); k++) {
        if (s[k] != ' ') { event = event*10 + (s[k]-'0'); }
        else { 
            switch(event){
                   case 0:
                   hiiro.event0 = true;
                   break;
                   case 1:
                   if (hiiro.level>levelO(i) || hiiro.arthur || hiiro.lancelot) {
                        if (hiiro.level != 10)  
                        hiiro.level += 1;
                   }
                   else if (hiiro.level<levelO(i)) 
                   hiiro.HP = hiiro.HP - levelO(i)*10; 
                   break;
                   case 2:
                   if (hiiro.level>levelO(i) || hiiro.arthur || hiiro.lancelot) {
                        if (hiiro.level!=10) 
                        hiiro.level = hiiro.level + 1;
                        }
                   if (hiiro.level<levelO(i)) 
                   hiiro.HP = hiiro.HP - 1.5*levelO(i)*10; 
                   break;
                   case 3:
                   if (hiiro.level>levelO(i) || hiiro.arthur || hiiro.lancelot) {
                        if (hiiro.level!=10) 
                        hiiro.level = hiiro.level + 1;
                    }
                   else if (hiiro.level<levelO(i)) hiiro.HP = hiiro.HP - 4.5*levelO(i)*10; 
                   
                   break;
                   case 4:
                   if (hiiro.level>levelO(i) || hiiro.arthur || hiiro.lancelot) {
                        if (hiiro.level!=10) 
                        hiiro.level = hiiro.level + 1;
                    }
                   else if (hiiro.level<levelO(i)) hiiro.HP = hiiro.HP - 7.5*levelO(i)*10; 
                   
                   break;
                   case 5:
                   if (hiiro.level>levelO(i) || hiiro.arthur || hiiro.lancelot) {
                        if (hiiro.level!=10) 
                        hiiro.level = hiiro.level + 1;
                    }
                   else if (hiiro.level<levelO(i)) hiiro.HP = hiiro.HP - 9.5*levelO(i)*10; 
                   
                   break;
                   case 6:
                   if (debuff1!=0 || debuff2!=0) break;
                   if (hiiro.level>levelO(i) || hiiro.arthur || hiiro.lancelot) {
                        if (hiiro.level!=10) hiiro.level = hiiro.level + 2;
                    }
                   else if (hiiro.level<levelO(i)) {
                       if (hiiro.remedy != 0) hiiro.remedy = hiiro.remedy - 1;
                       else {
                            debuff1 = 5;
                            if (hiiro.HP<5) hiiro.HP = 1;
                            else hiiro.HP = hiiro.HP/5;    
                       }
                       }
                   
                   break;
                   case 7:
                   if (debuff1!=0 || debuff2!=0) break;
                   else if (hiiro.level>levelO(i) || hiiro.arthur || hiiro.lancelot) 
                   {if (hiiro.level!=10) hiiro.level = hiiro.level + 2;}
                   else if (hiiro.level<levelO(i)) {
                        if (hiiro.maidenkiss!=0) hiiro.maidenkiss = hiiro.maidenkiss - 1;
                        else { frogdb = hiiro.level; hiiro.level = 1; debuff2 = 5;} 
                   }
                   break;
                   case 11:
                   getmario (hiiro.HP, hiiro.level, hiiro.phoenixdown);
                   HPcheck (hiiro.HP, hiiro.MaxHP);
                   break;
                   case 12:
                   if (fibocheck(hiiro.HP)==true) hiiro.HP = hiiro.HP - 1;
                   while (fibocheck(hiiro.HP)==false) hiiro.HP = hiiro.HP - 1;
                   break;
                   case 15:
                   hiiro.remedy = hiiro.remedy + 1;
                   itemcheck (hiiro.remedy);
                   break;
                   case 16:
                   hiiro.maidenkiss = hiiro.maidenkiss + 1;
                   itemcheck (hiiro.maidenkiss);
                   break;
                   case 17:
                   hiiro.phoenixdown = hiiro.phoenixdown + 1;
                   itemcheck (hiiro.phoenixdown);
                   break;
                   case 99:
                   if (hiiro.arthur) hiiro.level = 10;
                   else if (hiiro.lancelot) {
                    if (hiiro.level >=8) hiiro.level = 10; 
                    else hiiro.thua_bowser = true;
                   }
                   else if (hiiro.level == 10) hiiro.level = 10;
                   else hiiro.thua_bowser = true;
                   break;
                   // thua, xuat cac chi so ra man hinh 
                   case 19:
                   if (hiiro.asclepius_meet==true) break;
                   else {
                        hiiro.asclepius_meet = true;
                        meet_asclepius (asclepius, hiiro.remedy, hiiro.maidenkiss, hiiro.phoenixdown);
                        break;
                        }
                    case 18:
                    if (hiiro.merlin_meet == true) break;
                    else {
                        hiiro.merlin_meet = true;
                        meet_merlin (merlin, hiiro.HP);
                        HPcheck (hiiro.HP, hiiro.MaxHP);
                            break;
                        }
                    default: 
                            teemo (mushghost, hiiro.HP, hiiro.MaxHP, event , debuff1, debuff2, frogdb, hiiro.level, hiiro.phoenixdown);
                            break;
            } //switch case trong else của for, cần break khi win hoặc lose trong for 
            if (hiiro.level > 10) hiiro.level = 10;
            if (hiiro.event0) {
                hiiro.rescue = 1;
                break;
            } 
            //trong trường hợp ngủm củ tỏi
            if (hiiro.thua_bowser){
                hiiro.rescue = 0;
                break;
                } 
            if (hiiro.HP<=0){
                if (hiiro.phoenixdown>0) {
                    hiiro.phoenixdown = hiiro.phoenixdown - 1;
                    hiiro.HP = hiiro.MaxHP;
                    if (debuff2 != 0) {
                        debuff2 = 0;
                        hiiro.level = frogdb;
                        }
                    if (debuff1 != 0) { 
                        debuff1 = 0;
                        hiiro.HP = hiiro.HP * 5;
                        HPcheck (hiiro.HP, hiiro.MaxHP); 
                    }    
                    }
            else {
                hiiro.rescue = 0;
                break;
                }
            }
                if (debuff1!=0) {
                    if (hiiro.remedy!=0) {
                        hiiro.remedy = hiiro.remedy - 1; 
                        hiiro.HP = hiiro.HP*5; 
                        HPcheck(hiiro.HP, hiiro.MaxHP); 
                        debuff1 = 0; 
                        }
                    else { 
                        debuff1 = debuff1 - 1;
                        if (debuff1==1) { 
                            hiiro.HP = hiiro.HP*5; 
                            HPcheck(hiiro.HP, hiiro.MaxHP); 
                            debuff1 = 0; 
                        }
                    } 
                }  
                if (debuff2!=0) {
                    if (hiiro.maidenkiss!=0) {
                    hiiro.maidenkiss = hiiro.maidenkiss - 1; 
                    hiiro.level = frogdb; 
                    debuff2 = 0;
                    }
                    else {
                        debuff2 = debuff2 - 1;
                        if (debuff2==1) {
                            hiiro.level = frogdb; 
                            debuff2 = 0;
                        }
                    }
                }
            event = 0; 
            i = i + 1;
            if (s[k+1] == '\0') break;
            display(hiiro.HP, hiiro.level, hiiro.remedy, hiiro.maidenkiss, hiiro.phoenixdown, hiiro.rescue);
        } //else switch 
    } //for
if (event == 0) hiiro.rescue = 1;
display(hiiro.HP, hiiro.level, hiiro.remedy, hiiro.maidenkiss, hiiro.phoenixdown, hiiro.rescue);
input.close();
} //void