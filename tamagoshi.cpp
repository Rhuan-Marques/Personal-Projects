#include<bits/stdc++.h>
#include<fstream>
#include<Windows.h>
#include <time.h>
using namespace std;
#define DEBUG printf("\n-----------DEBUG-----BOLADO-----------\n"); //Define uma forma fácil de printar coisas pra debugar

time_t Tt; //Cria variável de tempo
#define timer time(&Tt) //Define Timer

map<string, pair<int, int> > coordenadas; //Cria Mapa que terá as coordenadas, no sprite do BixIn, aonde terá os olhos, boca, etc
map<string, string> colecao;  //Colecao de BixIns
vector<bool> upgrades; //Upgrades comprados
vector<string> Bixin; //Cria a imagem LOCAL do BixIn
string nome, raca;  //Variável LOCAL do nome e raça do atual BixIn
long int happy, comida, agua, banho, sum, last_time, sono, moedas; //Variáveis LOCAIS dos status do atual BixIn
bool Forced_State=false; //Cria booleano usado para forçar estados emocionais do BixIn pra debuggar
bool dormindo;  //Bool que dirá se o BixIn está dormindo ou não
ifstream infile;
ofstream outfile;

void LimparTela(){ //Limpa a tela
    system("cls");
}
long int random(long int num_inicial, long int num_final){  //Função que randomiza um valor entre dois numeros
    return num_inicial + rand()%num_final;
}

string lower(string s){
    for(int i=0; i<s.size(); i++){
        if(s[i]>='A' && s[i]<= 'Z'){
            s[i]-= ('A' - 'a');
        }
    }
    return s;
}

void Colecao(map<string, string> mapa, string modo){  //Prita a coleção dos Bixin que você tem
    if(modo == "Print"){
        for(map<string, string>::const_iterator it=mapa.begin(); it!=mapa.end(); ++it){
            if(it->second=="???") cout << "CRIE UM " << it->first << endl;
            else if(it->second!="000" && it->second!="") cout << it->second  << '(' << it->first << ")\n";
        }
    }
    else if(modo == "Change"){
        outfile.open("Databases/ColecaoBixIn.txt");
        for(map<string, string>::const_iterator it=mapa.begin(); it!=mapa.end(); ++it){
            if(it->first == raca) outfile << raca << " " << nome << endl;
            else outfile << it->first << ' ' << it->second << endl;
        }
        outfile.close();
    }
}
string DiretCol(string arquivo){ //Função que retorna o diretório certo do arquivo desejado.
    return "Databases/Colecao/"+raca+"/"+arquivo+".txt";
}

void GetBixInPadrao(){  //Função usada pra ler resetar a imagem local do BixIN pra a emoção padrão
    string aux;
    Bixin.clear();
    infile.open(DiretCol("Bixin"));
    while(getline(infile, aux)){
        Bixin.push_back(aux);
    }
    infile.close();
}

void readBixin(){   //Função que Lê o BixIn das Databases e inputa nas variáveis LOCAIS, Inicialização.
    string aux;
    string aux_b;
    infile.open("Databases/BixInAtual.txt");
        infile >> raca;
    infile.close();
    GetBixInPadrao(); //Pega o Bixin das Databases
    infile.open(DiretCol("Status")); //Pega os status da Database
        infile >> aux >> nome;
        infile >> aux >> raca;
        infile >> aux >> happy;
        infile >> aux >> comida;
        infile >> aux >> agua;
        infile >> aux >> banho;
        infile >> aux >> sono >> dormindo;
    infile.close();
    infile.open(DiretCol("HiddenS"));  //Pega tempo e coordenadas
        infile >> aux >> last_time;
        int cordX, cordY;
        while(infile >> aux >> cordY >> cordX){
            coordenadas[aux] = make_pair(cordY, cordX);
        }
    infile.close();
    colecao.clear();
    infile.open("Databases/ColecaoBixIn.txt");  //Pega a coleção de BixIns
        while(infile >> aux >> aux_b){
            colecao[aux] = aux_b;
        }
    infile.close();
    infile.open("Databases/Moedas.txt");
        infile >> aux >> moedas;
    infile.close();
}

vector<string> sprite(string s){  //Função que carrega os sprites locais, listados acima.
    vector<string> r;
    if(s == "Mao"){
        r.push_back("    ______________");
        r.push_back("   (______        |");
        r.push_back("  (________       |");
        r.push_back(" (_________       |");
        r.push_back("   (_______      /");
        r.push_back("        (_______/");
    }
    else if(s == "Banho"){
        r.push_back(" ___________________|");
        r.push_back("|         __________|");
        r.push_back("|________/          |");
        r.push_back("                    |");
        r.push_back("                    |");
        r.push_back("                    |");
        r.push_back("                    |");
        r.push_back("                    |");
        r.push_back("                    |");
        r.push_back("                    |");
        r.push_back("                    |");
        r.push_back("                    |");
        r.push_back("                    |");
    }
    else if(s == "Loja"){
        r.push_back("   _________________________   ");
        r.push_back("  /                        /|  ");
        r.push_back(" /                        /||  ");
        r.push_back("/______________________  / ||  ");
        r.push_back("|| ||       ___        ||  ||  ");
        r.push_back("|| ||      / ..\\       ||  ||  ");
        r.push_back("|| ||      \\ - /       ||  ||  ");
        r.push_back("|| ||       | |        ||  ||  ");
        r.push_back("|| ||___ ___/ \\___ ____||__||  ");
        r.push_back("|| /    /         \\    ||  /|  ");
        r.push_back("||/    | |     @ | |   || / |  ");
        r.push_back("||_____|_|_______|_|___||/  |  ");
        r.push_back("|                       |   |  ");
        r.push_back("|                       |  /   ");
        r.push_back("|                       | /    ");
        r.push_back("|_______________________|/     ");
    }

    return r;
}

void printBixin(){   //Printa a imagem do BixIn usando a matriz de char LOCAL
    for(long int i=0; i<Bixin.size(); i++){
        cout << Bixin[i] << endl;
    }
}
void TrocarMembro(string name,int alteracaoY, int alteracaoX, char newMember){
    Bixin[coordenadas[name].first+alteracaoY][coordenadas[name].second+alteracaoX] = newMember;
}
                                      //Função usada regularmente para trocar os caracteres do BixIn e fazer suas emoções estado

void Acareciar(){   //Função que contem o efeito da opção "acareciar"
    int n=9;
    vector<string> Mao = sprite("Mao");
    for(int frame=0; frame<10; frame++){
        for(int i=0; i<6; i++){
            for(int ii=0; ii<n; ii++) cout << "    ";
            cout << Mao[i] << endl;
        }
        printBixin();
        Sleep(100);
        LimparTela();
        if(n>0) n-=3;
        else n+=3;
    }
    happy+=20;
}

void DarBanho(){    //Função que contem o efeito da opção "banho"
    vector<string> Chuveiro = sprite("Banho");
    for(int frame=0; frame<30; frame++){
        Chuveiro[3][random(0, 9)] = '|';  //Randomiza um spawn de gotas abaixo do chuveiro
        Chuveiro[3][random(0, 9)] = '|';  //Randomiza outro spawn de gotas
        for(int i=0; i<13; i++){     //Printa o Chuveiro
            cout << "      "<< Chuveiro[i] << endl;
        }
        printBixin();               //Printa o BixIn
        for(int i=12; i>3; i--){  //Desce as gotas pra linha de baixo
            Chuveiro[i] = Chuveiro[i-1];
        }
        Chuveiro[3]= "                    |";  //Limpa a linha abaixo do chuveiro pra uma vazia
        Sleep(100);  //Espera para dar pra visualizar o frame
        LimparTela();  //Limpa a tela
    }
    banho+=20;

}

void IrLoja(){
    vector<string> loja = sprite("Loja");
    string input;
    for(int i=0; i<16; i++){     //Printa a loja
            cout << "   " << loja[i] << endl;
    }
    cout << endl;
    cout << "     Logista: Oi meu amigo" << endl;
    while(cin >> input){

    }
}

void AttStatus(){  //Atualiza os databases e valores utilizando os valores LOCAIS. Utilizado a cada ação feita.
    comida-= (timer-last_time)/1234;    //Diminui a comida (75%~24hrs)
    if(dormindo == false){      //calcula o Sono e estado atual caso o BixIn estivesse acordado na ultimo att
        sono = (sono+(timer-last_time)/360)%120;
        if(sono>=100){
            dormindo=true;
            sono= 100-(sono-100)*5;
        }
    }
    else{       //Mesmo que o acima p/ o caso do BixIn dormindo
        long int dif_ciclos = ((100-sono)+(timer-last_time)/72)%600;
        sono= 100-dif_ciclos;
        if(sono<0){
            dormindo=false;
            sono = abs(sono/5);
        }
    }
    last_time=timer;
    if(happy>100) happy=100;   //Evita Status de passarem do máximo
    if(comida>100) comida=100; //    ||
    if(agua>100) agua=100;     //    ||
    if(banho>100) banho=100;   //    ||
    outfile.open(DiretCol("Status"));
        outfile << "Nome: " << nome << endl;
        outfile << "Raca: " << raca << endl;
        outfile << "Happy: " << happy << endl;
        outfile << "Comida: " << comida << endl;
        outfile << "Agua: " << agua << endl;
        outfile << "Banho: " << banho << endl;
        outfile << "Sono: " << sono << " " << dormindo << endl;
    outfile.close();
    outfile.open(DiretCol("HiddenS"));
        outfile << "LastTime: " << timer << endl;
        outfile << "zZzZ " << coordenadas["zZzZ"].first << " " << coordenadas["zZzZ"].second << endl;
        outfile << "Olho " << coordenadas["Olho"].first << " " << coordenadas["Olho"].second << endl;
        outfile << "Olho2 " << coordenadas["Olho2"].first << " " << coordenadas["Olho2"].second << endl;
        outfile << "Boca " << coordenadas["Boca"].first << " " << coordenadas["Boca"].second << endl;
        outfile << "Amor " << coordenadas["Amor"].first << " " << coordenadas["Amor"].second << endl;
    outfile.close();
    sum=happy+comida+agua+banho; //Calcula a soma dos Status, usada para fzer as emoções
}

void AttBixIn(){ //Atualiza os membros do BixIn para criar as emoções.
    GetBixInPadrao();  //Seta p/ o status padrão no início do processo, para apagar mudanças do status anterior.
    if(happy<=0 || comida<=0 || agua<=0 || banho<=0){       //MORTO
        TrocarMembro("Olho", 0, 0, 'X');
        TrocarMembro("Olho2", 0, 0, 'X');
        TrocarMembro("Boca", 0, 0, '=');
    }
    else if(dormindo == true){                              //DORMINDO
        TrocarMembro("Olho", 0, 0, 'u');
        TrocarMembro("Olho2", 0, 0, 'u');
        TrocarMembro("Boca", 0, 0, '~');
        TrocarMembro("zZzZ", 0, 0, 'z');
        TrocarMembro("zZzZ", 0, +1, 'Z');
        TrocarMembro("zZzZ", -1, +1, 'z');
        TrocarMembro("zZzZ", -1, +2, 'z');
    }
    else if(sum >= 400){                                    //EXTREMAMENTE FELIZ / AMOR
        TrocarMembro("Olho", 0, 0, '*');
        TrocarMembro("Olho2", 0, 0, '*');
        TrocarMembro("Boca", 0, 0, 'O');
        TrocarMembro("Amor", 0, +1, '/');
        TrocarMembro("Amor", 0, -1, '\\');
        TrocarMembro("Amor", +1, 0, 'V');
        TrocarMembro("Amor", -1, 0, 'V');
        TrocarMembro("Amor", -1, +2, ')');
        TrocarMembro("Amor", -1, -2, '(');
        TrocarMembro("Amor", -2, +1, '_');
        TrocarMembro("Amor", -2, -1, '_');

    }
    else if(sum >350){                                      //MUITO FELIZ
        TrocarMembro("Olho", 0, 0, '*');
        TrocarMembro("Olho2", 0, 0, '*');
        TrocarMembro("Boca", 0, 0, 'o');
    }
    else if(sum >300){                                      //BEM FELIZ
        TrocarMembro("Olho", 0, 0, '^');
        TrocarMembro("Olho2", 0, 0, '^');
        TrocarMembro("Boca", 0, 0, 'U');
    }
    else if(sum >260){                                      //FELIZ
        TrocarMembro("Boca", 0, 0, 'u');
    }
    else if(sum > 200);                                     //PADRÃO
    else if(sum > 150){                                     //TRISTE
        TrocarMembro("Olho", 0, 0, 'o');
        TrocarMembro("Olho2", 0, 0, 'o');
    }
    else if(sum > 100){                                     //BEM TRISTE
        TrocarMembro("Olho", 0, 0, 'O');
        TrocarMembro("Olho2", 0, 0, 'O');
        TrocarMembro("Boca", 0, 0, '_');
    }
    else if(sum > 80){                                      //MUITO TRISTE
        TrocarMembro("Olho", 0, 0, '@');
        TrocarMembro("Olho2", 0, 0, '@');
        TrocarMembro("Olho2", 1, 0, 'i');
        TrocarMembro("Boca", 0, 0, '~');
    }
    else if(sum > 0){                                       //EXTREMAMENTE TRISTE / CHORANDO
        TrocarMembro("Olho", 0, 0, 'T');
        TrocarMembro("Olho2", 0, 0, 'T');
        TrocarMembro("Olho2", 1, 0, '_');
        for(int i=coordenadas["Olho"].first+1; i<Bixin.size(); i++)Bixin[i][coordenadas["Olho"].second]='|'; //Lagrimas
        for(int i=coordenadas["Olho2"].first+1; i<Bixin.size(); i++)Bixin[i][coordenadas["Olho2"].second]='|';//  ||
    }
}

int main(){
    srand(time(NULL)); //Inicia Seed de Random
    string input;
    readBixin();       //Pega dados das Databases
    while(1){          //Loop para gameplay
        if(nome == "???"){ //Criando o BixIn
            happy = 50; comida = 50; agua = 50; banho = 50; sono=50; last_time=timer; dormindo=false;//Seta status iniciais
            LimparTela();
            AttBixIn();
            printf("Pelo visto voce ainda nao tem um BixIn desses\n Vamos criar um juntos.\n");
            printBixin();
            printf("\n\nQue nome deseja dar pra ele?\n");
            while(cin >> nome && (nome=="???" || nome=="000"))cout << "Este nome nao esta disponivel, tente outro." << endl;
                                                                                            //Evita que o nome seja ??? ou 000
            printf("Seu BixIn esta pronto. Use !help se tiver alguma duvida in-game.\n\n\n\nCarregando...");
            Colecao(colecao, "Change");
            Sleep(5000);
            LimparTela();
        }
        if(Forced_State==false) AttStatus();  //Atualiza os status td ação. A não ser que um status tenha sido forçado
        AttBixIn();  //Atualiza Sprite do BixIn pra ter emoções
        cout << "       " << nome << endl;
        printBixin();
        printf("\n\n\n");
        if(happy<=0 || comida<=0 || banho==0 || agua==0){ //BixIn Morto
            cout << "Pelo visto seu BixIn morreu, triste, mas ele sempre viverá em seu coracao." << endl;
            cout << "Quer um !novo ou quer !sair?\n\n!";
            while(cin >> input){
                if(input == "sair") return 0;
                else if(input == "novo"){
                    nome="???";
                    break;
                }
            }
        }
        else{
        cout << "Alegria: " << happy << "/100" << endl;         //printa os status
        cout << "Comida: " << comida << "/100" << endl;         //    ||
        cout << "Agua: " << agua << "/100" << endl;             //    ||
        cout << "Banho: " << banho << "/100" << endl;           //    ||
        cout << "Sono: " << sono << "/100" << endl;             //    ||
        if(dormindo == true){               //Evita de fazer ações caso o BixIn esteja dormindo
            cout << "\n\nSeu BixIn esta dormindo, volte mais tarde\n";
            break;        //Break fodase;
        }
        printf("!"); cin >> input;          //Lê Input, "!" para saber que eh pra inputar
        input = lower(input);               //Tranforma tudo em lowercase pra evitar problemas de letras maiusculas no input
        cout << input << endl;
        if(input == "help"){
            LimparTela();
            printf("       Comandos:\n");
            printf("!Acareciar: Acarecia a cabeça do(a) BiXin, aumenta alegria\n");
            printf("!Banho: Da banho no BixIn, aumenta banho\n");
            printf("!Dormir: Poe o BixIn paara dormir até o Sono chegar a 0, nao podera agir nesse tempo\n");
            printf("                (BixIns dormem automaticamente quando o Sono chega em 100)\n");
        }
        else if(input == "acareciar"){      //Inicia função de Acareciar
            LimparTela();
            Acareciar();
        }
        else if(input == "banho"){          //Inicia função de DarBanho
            LimparTela();
            DarBanho();

        }
        else if(input=="dormir"){           //Muda Estado para Dormindo
            LimparTela();
            dormindo=true;
        }
        else if(input=="loja"){
            LimparTela();
            IrLoja();
        }
        else if(input=="trocar"){
            LimparTela();
            cout << "    Esses sao todos os seus BixIns:\n";
            Colecao(colecao, "Print");
            cout << "\n    Escolha a Raca do BixIn que vai escolher, ou !Sair para cancelar.\n!";
            while(cin >> input && input != "Sair"){
                if(input==raca){
                    LimparTela();
                    cout <<"    Este ja eh seu BixIn atual";
                    Sleep(1000);
                }
                else if(colecao[input]!= "000" && colecao[input]!= ""){
                    outfile.open("Databases/BixInAtual.txt");
                        outfile << input;
                    outfile.close();
                    readBixin();
                    LimparTela();
                    if(colecao[input]!="???"){
                        cout <<"    Agora esta cuidando do seu " << raca << ": " << nome;
                        Sleep(1000);
                    }
                    break;
                }
                LimparTela();
                cout << "    Esses sao todos os seus BixIns:\n";
                Colecao(colecao, "Print");
                cout << "\n    Escolha a Raca do BixIn que vai escolher, ou !Sair para cancelar.\n!";
            }
            LimparTela();
        }
        else if(input=="fs"){               //Forçar Estado
            cin >> input;
            if(input=="Sleep") dormindo=true;
            else if(input=="Dead") happy=0;
            else if(input=="Change_Name") cin >> nome;
            else sum = 40+(stoi(input)*50);
            Forced_State=true;
        }
    }
    }
}
/*

*/
