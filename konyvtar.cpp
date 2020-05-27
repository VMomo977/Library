#include <map>
#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <iterator>
#include <sstream>

using namespace std;

class konyvtar{
    map<string,int> konyvek;
    map<string, set<string>> tagok;
public:
    konyvtar(){
    //beolvasas
        ifstream fin("book.txt");
       /* if(!fin.good()){
            cout<<"Nem jo a bemeneti fajl"<<endl;
        }else{
            cout<<"Jo a bemeneti fajl"<<endl;*/
            string cim;
            int konyv_db;
            while(getline(fin, cim,',')){
                fin>>konyv_db;
                konyvek[cim]=konyv_db;
                fin>>ws;
            }
            fin.close();
       /* }*/

        fin.open("member.txt");
       /* if(!fin.good()){
            cout<<"Nem jo a bemeneti fajl2"<<endl;
        }else{
            cout<<"Jo a bemeneti fajl2"<<endl;*/

            string tag;
            while(getline(fin,tag,',')){
                string tmp;
                int ki_db;
                string ki_cim;
                char kuka;
                set<string> seged;

                fin>>ki_db;
                fin>>kuka;


                for(int i=0; i<ki_db-1; i++){
                    getline(fin,ki_cim,',');
                    seged.insert(ki_cim);
                }
                getline(fin,ki_cim);
                seged.insert(ki_cim);

                tagok[tag]=seged;

            }

        //}
        fin.close();
    }

void adatbazis(){
    cout<<"Konyvek cimei: "<<endl;
    for(auto k : konyvek){
        cout<<k.first<<" "<<k.second<<endl;
    }
    cout<<endl;
    cout<<"Tagok nevei a kikolcsonzott konyvekkel: "<<endl;
    for(auto k: tagok){
        cout<<"Tag neve: "<<k.first<<endl<<" Konyvei: ";
            for(auto c : k.second){
                cout<<c<<",";
            }
        cout<<endl;
    }
    cout<<endl;
}

void uj_konyv(){
    cout<<endl;
    cout<<"Uj konyv felvetele. Kerlek ird be az uj konyv cimet!"<<endl;
    string cim;
    getline(cin, cim);

    if(konyvek.find(cim)!=konyvek.end()){
        cout<<"Van mar ilyen cimu konyv, tehat a db szama nott."<<endl;
        konyvek[cim]++;
    }else{
        cout<<"Nem volt meg ilyen konyv a konyvtarban, tehat tenyleg uj konyv lesz"<<endl;
        konyvek[cim]=1;
    }
    cout<<endl;
}

void kolcson(){
    cout<<"Adja meg a kolcsonozni kivano tag nevet!"<<endl;
    string tag;
    getline(cin,tag);
    cout <<"Ezutan beirhatja a kolcsonozni kivant konyv cimet!"<<endl;
    string cim;
    getline(cin, cim);

    if(tagok.find(tag)==tagok.end()){
        cout<<"Nincs ilyen tag a konyvtarban!"<<endl;
        return;
    }else{
        cout<<"Van ilyen nevu tag."<<endl;
        if(konyvek.find(cim)==konyvek.end() ){
            cout<<"Soha nem volt ilyen konyv a konyvtarban"<<endl;
            return;
        }else{
            if(konyvek[cim]==0){
                cout<<"Nincs egy peldany se a konyvtarban (Lehet mar kikolcsonozte azert)"<<endl;
                return;
            }else if(tagok[tag].find(cim)!=tagok[tag].end()){
                cout<<"Mar kikolcsonozte regebben"<<endl;
                return;
            }else{
                cout<<"Ki tudja kolcsonozni"<<endl;
                tagok[tag].insert(cim);
                konyvek[cim]--;

            }
        }
    }

    cout<<endl;
    cout<<"Tag kikolcsonzott konyvei:"<<endl;
    for(auto k : tagok[tag]){
        cout<<k<<",";
    }
    cout<<endl;
}

void holvannak(){

    cout<<"Hol vannak a konyvek?"<<endl;

    for(auto k : konyvek){
        for(auto t : tagok){
            if(t.second.count(k.first)!=0){
                cout<<"A "<< k.first<<" cimu konyvet "<<
                t.first<<" tag kolcsonozte ki."<<endl;
            }
        }
            cout<<"A "<<k.first<<" cimu konyv a konyvtarban van meg "<<
            k.second<<" db-szamban "<<endl;
    }

     cout<<endl;

}

void uj_tag(){
    cout<<"Uj tag felvetele. Kerlek add meg az uj tag nevet!"<<endl;
    string uj_tag;
    getline(cin, uj_tag);

    if(tagok.find(uj_tag)!=tagok.end()){
        cout<<"Van mar ilyen tagunk, nem lenne uj"<<endl;
        return;
    }else{
        cout<<"Nincs meg ilyen tagunk.Felvehetjuk"<<endl;
        tagok[uj_tag];
    }
    cout<<endl;
}

void visszahoz(){
    cout<<endl;
    cout<<"Konyv visszahozasa.Kerlek ird be a tag nevet es a konyv cimet"<<endl;
    string tag;
    string cim;
    getline(cin,tag);
    getline(cin,cim);

    if(tagok.find(tag)==tagok.end() || konyvek.find(cim)==konyvek.end()){
        cout<<"Vagy nincs ilyen tag vagy nincs ilyen konyv"<<endl;
        return;
    }else{
        if(tagok[tag].find(cim)!=tagok[tag].end()){
            cout<<"Kikolcsonozte tenyleg ezt a konyvet.Visszahozhatja"<<endl;
            konyvek[cim]++;
            tagok[tag].erase(cim);

        }else{
            cout<<"Nem vett ki ilyen konyvet"<<endl;
            return;
        }
    }
    cout<<endl;
}

void adottkonyv_hol(){
    cout<<"Hol van egy adott peldany? Kerlek add meg a peldany cimet!"<<endl;
    cout<<endl;
    string cim;
    getline(cin,cim);

    if(konyvek.find(cim)==konyvek.end()){
        cout<<"Nincs is ilyen konyv "<<endl;
    }else{
       cout<<konyvek[cim]<<" db peldany van a konyvtarban"<<endl;
       for( auto t : tagok){
            if(t.second.count(cim)==1){
                cout<<t.first<<" tagnal is van egy peldany"<<endl;
            }
       }
    }
}

};

int main(){
    konyvtar k;
    cout<<"Udvozlom, ez egy konyvtar rendszer."<<endl
    <<"Lehetseges opciok:"<<endl

    <<"\n 1 - uj konyv felvetele a konyvtarba"<<endl
    <<"\n 2 - kolcsonzes"<<endl
    <<"\n 3 - lekerdezi a konyvek helyet (konyvtar, kolcsonzo szemely)"<<endl
    <<"\n 4 - uj tag felvetele"<<endl
    <<"\n 5 - konyv visszahozasa"<<endl
    <<"\n 6 - egy adott konyv helyenek lekerdezese"<<endl
    <<"\n 7 - a konyvtar adatbazisa (konyvek listaja, tagok listaja)"<<endl
    <<"\n 8 - kilepes"<<endl
    <<endl<<"Kerem irja be az adott opcio szamat!"<<endl;

    int opcio;
    string o;
    getline(cin, o);
    stringstream ss;
    ss<<o;
    ss>>opcio;

    while(opcio != 8){
        switch (opcio)
            {
                case 1:
                   k.uj_konyv(); break;
                case 2:
                    k.kolcson(); break;
                case 3:
                    k.holvannak(); break;
                case 4:
                    k.uj_tag(); break;
                case 5:
                     k.visszahoz(); break;
                case 6:
                     k.adottkonyv_hol(); break;
                case 7:
                     k.adatbazis(); break;
            }
        cout<<endl;
        cout<<"Kovetkezo muvelet?"<<endl;

        getline(cin, o);
        stringstream ss;
        ss<<o;
        ss>>opcio;

    }

return 0;}
