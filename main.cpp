/*
	Autore: Valerio Di Tommaso, Davide Moresco.
	Classe: 3AI.
	Data: 08/02/2023.
	Nome file: giocodelloca.cpp.
*/

#include <iostream>		//input/output
#include <stdlib.h>		//numeri casuali
#include <time.h>		//numeri casuali
#include <unistd.h>		//per sleep()
#include <cstring>		//per salvare in variabili char parole più lunghe
#include <ctime>		//per vedere il giorno e l'ora corrente
#include <iomanip>		//per vedere il giorno e l'ora corrente
#include <fstream> 		//per la gestione file
using namespace std;

int main(){
	int setcas, pselect;
	char sn, snmod, snauto, sname, snsavedata, snreadata, snskip;
	string line;
	srand(time(NULL));

	do{
		int selmod, setzero, setbm, setm, setvb;
		bool monozero=false;
		cout<<"Benvenuti, questo è il gioco dell'oca!\n"<<endl;
		cout<<"Regolamento:\n\t-Scegli la modalità che preferisci.\n\t-Scegli se attivare la modalità automatica.\n\t-Scegli con quanti giocatori vuoi giocare.\n\t-Tira i dadi per vedere di quante caselle devi andare avanti.\n\t-Il programma ti dirà a che casella sei arrivato\n\t-Ci saranno caselle bonus o malus che possono andare da -6 a 6.\n"<<endl;

		do{
			cout<<"Vuoi vedere i dati delle vecchie partite salvate?\n| ";
			cin>>snreadata;
			if(snreadata!='s' and snreadata!='n'){
				cout<<"Devi rispondermi con 's' o 'n'. (Si o No)"<<endl;
			}
		}while(snreadata!='s' and snreadata!='n');
		if(snreadata=='s'){
			ifstream file("datiGiocodelloca.txt");
			if(file.is_open()){
				while(getline(file,line)){
					cout<<line<<endl;
				}
				file.close();
			}
			else{
				cout<<"Impossibile aprire il file di salvataggio, lettura dei dati salvati interrotta."<<endl;
			}
		}
		cout<<endl;

		cout<<"Che modalità vuoi scegliere? Opzioni:"<<endl;
		cout<<"1} FACILE: Ci sono 36 caselle e meno caselle con bonus e malus che valgono di meno"<<endl;
		cout<<"2} NORMALE: Ci sono 63 caselle e un numero bilanciato di caselle con bonus e malus."<<endl;
		cout<<"3} DIFFICLE: Ci sono 100 caselle e un numero incrementato di caselle con bonus e malus."<<endl;
		cout<<"4} CAOS: Ci sono 63 caselle e un numero incrementato di caselle bonus e malus con una probabiltà incrementata di trovare malus."<<endl;
		cout<<"5} INFINITE CAOS: Ci sono 100 caselle e un numero ancora più incrementato di caselle bonus e malus con una probabiltà incrementata di trovare malus."<<endl;
		cout<<"6} PERSONALIZZATA: Scegli quante caselle inserire e quali delle tre opzioni di generazione delle caselle bonus e malus."<<endl;
		do{
			cout<<"| ";
			cin>>selmod;
			if(selmod<1 or selmod>6){
				cout<<"Devi darmi il numero corrispondente alla modalità che vuoi scegliere."<<endl;
			}
		}while(selmod<1 or selmod>6);
		if(selmod==1){
			setcas=36;
			setzero=6;
			setbm=3;
			setm=1;
			setvb=3;
		}
		if(selmod==2){
			setcas=63;
			setzero=5;
			setbm=3;
			setm=1;
			setvb=6;
		}
		if(selmod==3){
			setcas=100;
			setzero=5;
			setbm=4;
			setm=1;
			setvb=6;
		}
		if(selmod==4){
			setcas=63;
			setzero=5;
			setbm=4;
			setm=2;
			setvb=6;
		}
		if(selmod==5){
			setcas=100;
			setzero=4;
			setbm=4;
			setm=2;
			setvb=6;
		}
		if(selmod==6){
			do{
				cout<<"Quante caselle vuoi? [Minimo 36, Massimo 141].\n| ";
				cin>>setcas;
				if(setcas<36 or setcas>141){
					cout<<"Devi darmi un numero di caselle che rientri tra 36 e 141."<<endl;
				}
			}while(setcas<36 or setcas>141);
			do{
				cout<<"Quante caselle vuote di fila vuoi possano esser generate al massimo? [Minimo 1, Massimo "<<setcas<<"].\n| ";	//[La quantità sarà casuale da 1 fino al numero che vuoi impostare e non sarà mai uguale per tutto il tabellone]
				cin>>setzero;
				if(setzero<1 or setzero>setcas){
					cout<<"Devi darmi un numero massimo di caselle vuote consecutive."<<endl;
				}
				if(setzero==setcas){
					monozero=true;
				}
			}while(setzero<1 or setzero>setcas);
			if(monozero==false){
				do{
					cout<<"Quante caselle bonus/malus di fila vuoi possano esser generate al massimo? [Minimo 1, Massimo "<<setcas<<"].\n| ";	//[La quantità sarà casuale da 1 fino al numero che vuoi impostare e non sarà mai uguale per tutto il tabellone]
					cin>>setbm;
					if(setbm<1 or setbm>setcas){
						cout<<"Devi darmi un numero massimo di caselle bonus/malus consecutive."<<endl;
					}
				}while(setbm<1 or setbm>setcas);
				do{
					cout<<"Quanta probabilità su 3 di trovare un malus su una casella bonus/malus: [Minimo 0, Massimo 3].\n| ";
					cin>>setm;
					if(setm<0 or setm>3){
						cout<<"Devi darmi la probabilità su 3 di trovare un malus da 0 a 3."<<endl;
					}
				}while(setm<0 or setm>3);
				do{
					cout<<"Di quanto vuoi sia il massimo bonus o malus di caselle ottenibile nelle caselle bonus/malus? [Minimo 0, Massimo "<<setcas<<"].\n| ";
					cin>>setvb;
					if(setvb<0 or setvb>setcas){
						cout<<"Devi darmi la massima quantità di bonus o malus ottenibili da 0 a 99."<<endl;
					}
				}while(setvb<0 or setvb>setcas);
			}
		}

		setcas++;
		int cas[setcas], zero, cz=0, eff, cef=0, bm, i=0;
		for(i=1;i<setcas;i++){		//Codice generazione caselle: Sceglie quante caselle devono essere vuote di fila in modo alternato con la quantità di caselle bonus/malus e la loro generazione.
			zero=rand()%setzero+1;	//Assegna casualmente alla variabile "zero" il numero di zeri da inserire consecutivamente.
			while(cz<zero and i<setcas){
				cas[i]=0;
				cz++;
				i++;
			}
			eff=rand()%setbm+1;		//Assegna casualmente alla variabile "eff" il numero di bonus/mulus da inserire consecutivamente.
			while(cef<eff and i<setcas){
				bm=rand()%3;	// 33% circa di probabilità che nelle prossime stringhe cas[i] diventi negativo.
				if(setvb>0){
					cas[i]=rand()%setvb+1;
				}
				else{
					cas[i]=0;
				}
				if(bm<setm){
					cas[i]=0-cas[i];
				}
				cef++;
				i++;
			}
			i--;
			cz=0;
			cef=0;
		}
		cas[setcas-1]=0;
		cout<<endl;
		for(i=1;i<setcas;i++){
			cout<<"| "<<cas[i]<<" ";
		}
		cout<<"|"<<endl;
		setcas--;

		do{
			if(snskip!='s'){
				sleep(1);
			}
			if(sn=='s'){
				cout<<"Benvenuti, questo è il gioco dell'oca!\n"<<endl;
				cout<<"Regolamento:\n\t-Scegli con quanti giocatori vuoi giocare.\n\t-Tira i dadi per vedere di quante caselle devi andare avanti.\n\t-Il programma ti dirà a che casella sei arrivato\n\t-Ci saranno caselle bonus o malus che possono andare da -6 a 6."<<endl;
			}
			int i=1, turns=0, dado, dado2, dadot, g1=1, g2=1, g3=1, g4=1, bm, mirror, g=1, totmir=0, cmir1=0, cmir2=0, cmir3=0, cmir4=0, totzeromir=0, czeromir1=0, czeromir2=0, czeromir3=0, czeromir4=0, cbonus1=0, cbonus2=0, cbonus3=0, cbonus4=0, cmalus1=0, cmalus2=0, cmalus3=0, cmalus4=0;
			char name1[20], name2[20], name3[20], name4[20], y[20];
			bool fix=false;

			do{
				cout<<"\nQuanti giocatori siete? [Minimo 2, Massimo 4]:\n| ";
				cin>>pselect;
				if(pselect<=1 or pselect>4){
					cout<<"Devi darmi un numero di giocatori compresi tra 2 e 4.";
				}
			}while(pselect<=1 or pselect>4);

			do{
				cout<<"\nVolete impostare un vostro nome? [s/n]\n| ";
				cin>>sname;
				if(sname!='s' and sname!='n'){
					cout<<"Devi rispondermi con 's' o 'n'. (Si o No)";
				}
			}while(sname!='s' and sname!='n');
			if(sname=='s'){
				if(fix==true){
					cin.getline(y,20);
				}
				if(pselect>=2){
					cout<<"Dammi il nome del primo giocatore: ";
					cin.getline(y,20);
					cin.getline(name1,20);
					cout<<"Dammi il nome del secondo giocatore: ";
					cin.getline(name2,20);
				}
				if(pselect>=3){
					cout<<"Dammi il nome del terzo giocatore: ";
					cin.getline(name3,20);
				}
				if(pselect==4){
					cout<<"Dammi il nome del quarto giocatore: ";
					cin.getline(name4,20);
				}
				if(fix==false){
					fix=true;
				}
			}

			do{
				cout<<"\nVuoi giocare in modalità auto? [s/n]\n| ";
				cin>>snauto;
				if(snauto!='s' and snauto!='n'){
					cout<<"Devi rispondermi con 's' o 'n'. (Si o No)";
				}
			}while(snauto!='s' and snauto!='n');
			snskip='n';
			if(snauto=='s'){
				do{
					cout<<"Vuoi skippare automaticamente tutto e arrivare alla conclusione della partita? [s/n]\n| ";
					cin>>snskip;
					if(snskip!='s' and snskip!='n'){
						cout<<"Devi rispondermi con 's' o 'n'. (Si o No)"<<endl;
					}
				}while(snskip!='s' and snskip!='n');
			}

			std::time_t t=std::time(nullptr);
			std::tm tm=*std::localtime(&t);

			while(g!=setcas){		//Il ciclo si ripete finché un giocatore non è arrivato alla casella setcas.
				turns++;
				cout<<"\n<<<<TURNO "<<turns<<">>>>\n"<<endl;
				for(i=1;i<pselect+1 and g!=setcas;i++){
					if(pselect==3){
						if(i==1){
							g3=g;
							g=g1;
						}
						if(i==2){
							g1=g;
							g=g2;
						}
						if(i==3){
							g2=g;
							g=g3;
						}
					}
					if(pselect==4){
						if(i==1){
							g4=g;
							g=g1;
						}
						if(i==2){
							g1=g;
							g=g2;
						}
						if(i==3){
							g2=g;
							g=g3;
						}
						if(i==4){
							g3=g;
							g=g4;
						}
					}
					if(pselect==2){
						if(i==1){
							g2=g;
							g=g1;
						}
						if(i==2){
							g1=g;
							g=g2;
						}
					}

					do{
						if(sname=='n'){
							cout<<"GIOCATORE "<<i<<":"<<endl;
						}
						if(sname=='s'){
							if(i==1){
								cout<<name1<<":"<<endl;
							}
							if(i==2){
								cout<<name2<<":"<<endl;
							}
							if(i==3){
								cout<<name3<<":"<<endl;
							}
							if(i==4){
								cout<<name4<<":"<<endl;
							}
						}
						cout<<"Casella corrente: ";
						if(i==1){
							cout<<g1<<endl;
						}
						if(i==2){
							cout<<g2<<endl;
						}
						if(i==3){
							cout<<g3<<endl;
						}
						if(i==4){
							cout<<g4<<endl;
						}
						cout<<"Vuoi lanciare i dadi? [s/n]\n| ";
						if(snauto=='n'){
							cin>>sn;
						}
						else{
							cout<<"s"<<endl;
							sn='s';
						}
						if(sn=='n'){
							do{
								cout<<"Vuoi giocare in modalità auto? [s/n].\n| ";
								cin>>snauto;
								if(snauto!='s' and snauto!='n'){
									cout<<"Devi rispondermi con 's' o 'n'. (Si o No)."<<endl;
								}
							}while(snauto!='s' and snauto!='n');
							snskip='n';
							if(snauto=='s'){
								do{
									cout<<"Vuoi skippare automaticamente tutto e arrivare alla conclusione della partita? [s/n]\n| ";
									cin>>snskip;
									if(snskip!='s' and snskip!='n'){
										cout<<"Devi rispondermi con 's' o 'n'. (Si o No)"<<endl;
									}
								}while(snskip!='s' and snskip!='n');
							}

						}
					}while(sn!='s');
					dado=rand()%6+1;
					dado2=rand()%6+1;
					cout<<"Primo dado: ";
					if(snskip!='s'){
						sleep(1);
					}
					cout<<dado<<"."<<endl;
					cout<<"+ Secondo dado: ";
					if(snskip!='s'){
						sleep(1);
					}
					cout<<dado2<<"."<<endl;
					dadot=dado+dado2;
					if(snskip!='s'){
						sleep(1);
					}
					cout<<"= ";
					if(snskip!='s'){
						sleep(1);
					}
					cout<<"+"<<dadot<<endl;
					if(snskip!='s'){
						sleep(1);
					}
					cout<<"Casella "<<g<<" + "<<dadot<<" = ";
					if(snskip!='s'){
						sleep(1);
					}
					g=g+dadot;
					cout<<"Casella "<<g<<"."<<endl;
					if(snskip!='s'){
						sleep(1);
					}
					if(g>1 and g<setcas and g!=setcas and cas[g]==0){
						cout<<"La casella "<<g<<" è vuota, quindi finisci il turno.\n"<<endl;
					}
					if(g>1 and g<setcas and g!=setcas and cas[g]>0){
						cout<<"La casella "<<g<<" ha un Bonus di "<<cas[g]<<" caselle, dunque vai avanti fino alla casella ";
						if(i==1){
							cbonus1++;
						}
						if(i==2){
							cbonus2++;
						}
						if(i==3){
							cbonus3++;
						}
						if(i==4){
							cbonus4++;
						}
					}
					if(g>1 and g<setcas and g!=setcas and cas[g]<0){
						cout<<"La casella "<<g<<" ha un Malus di "<<cas[g]<<" caselle, dunque vai indietro fino alla casella ";
						if(i==1){
							cmalus1++;
						}
						if(i==2){
							cmalus2++;
						}
						if(i==3){
							cmalus3++;
						}
						if(i==4){
							cmalus4++;
						}
					}
					if(g>1 and g<setcas and g!=setcas and cas[g]>0 or cas[g]<0 and g>1 and g<setcas and g!=setcas){
						g=g+cas[g];
						cout<<g<<endl;
					}
					if(snskip!='s'){
						sleep(1);
					}

					while(g<1 or g>setcas){
						if(g<1){
							cout<<"Sei andato dietro la casella 1, dunque il numero di caselle che hai superato dietro l'uno verranno specchiate in avanti a partire dall'1.\n"<<endl;
							g=g*-1;
							totzeromir++;
							if(i==1){
								czeromir1++;
							}
							if(i==2){
								czeromir2++;
							}
							if(i==3){
								czeromir3++;
							}
							if(i==4){
								czeromir4++;
							}
						}
						if(g>setcas){
							cout<<"Oh, hai superato la casella "<<setcas<<", dunque tornerai indietro a partire dalla casella "<<setcas<<" per il numero di caselle che hai superato dopo la suddetta.\n"<<endl;
							mirror=g-setcas;
							g=setcas-mirror;
							totmir++;
							if(i==1){
								cmir1++;
							}
							if(i==2){
								cmir2++;
							}
							if(i==3){
								cmir3++;
							}
							if(i==4){
								cmir4++;
							}
						}
						if(snskip!='s'){
							sleep(1);
						}
					}
				}
				i--;
			}
			if(sname=='n'){
				cout<<"\n\nCongratulazioni Giocatore "<<i<<", HAI VINTO!\n"<<endl;
			}
			if(sname=='s'){
				if(i==1){
					cout<<"\n\nCongratulazioni "<<name1<<", HAI VINTO!\n"<<endl;
				}
				if(i==2){
					cout<<"\n\nCongratulazioni "<<name2<<", HAI VINTO!\n"<<endl;
				}
				if(i==3){
					cout<<"\n\nCongratulazioni "<<name3<<", HAI VINTO!\n"<<endl;
				}
				if(i==4){
					cout<<"\n\nCongratulazioni "<<name4<<", HAI VINTO!\n"<<endl;
				}
			}
			cout<<"STATISTICHE PARTITA:\n-Giocatori: "<<pselect<<".\n-Modalità Auto: ";
			if(snauto=='s'){
				cout<<"Attivata.";
			}
			else{
				cout<<"Disattivata.";
			}
			cout<<"\n-Modalità: ";
			if(selmod==1){
				cout<<"Facile.";
			}
			if(selmod==2){
				cout<<"Normale.";
			}
			if(selmod==3){
				cout<<"Difficile.";
			}
			if(selmod==4){
				cout<<"Caos.";
			}
			if(selmod==5){
				cout<<"Infinite Caos.";
			}
			if(selmod==6){
				cout<<"Personalizzata.";
			}
			cout<<"\n-Turni: "<<turns<<".\n-Volte che sono state superate la casella "<<setcas<<": "<<totmir<<".\n-Volte che si ha indietreggiato la casella 0: "<<totzeromir<<".\n"<<endl;
			if(sname=='n'){
				if(pselect>=2){
					cout<<"STATISTICHE GIOCATORE 1:\n-Volte che sei andato su una casella Bonus: "<<cbonus1<<".\n-Volte che sei andato su una casella Malus: "<<cmalus1<<".\n-Volte che hai superato la casella "<<setcas<<": "<<cmir1<<".\n-Volte che si ha indietreggiato la casella 1: "<<czeromir1<<endl;
					cout<<"\nSTATISTICHE GIOCATORE 2:\n-Volte che sei andato su una casella Bonus: "<<cbonus2<<".\n-Volte che sei andato su una casella Malus: "<<cmalus2<<":\n-Volte che hai superato la casella "<<setcas<<": "<<cmir2<<".\n-Volte che si ha indietreggiato la casella 1: "<<czeromir2<<endl;
				}
				if(pselect>=3){
					cout<<"\nSTATISTICHE GIOCATORE 3:\n-Volte che sei andato su una casella Bonus: "<<cbonus3<<".\n-Volte che sei andato su una casella Malus: "<<cmalus3<<":\n-Volte che hai superato la casella "<<setcas<<": "<<cmir3<<".\n-Volte che si ha indietreggiato la casella 1: "<<czeromir3<<endl;
				}
				if(pselect==4){
					cout<<"\nSTATISTICHE GIOCATORE 4:\n-Volte che sei andato su una casella Bonus: "<<cbonus4<<".\n-Volte che sei andato su una casella Malus: "<<cmalus4<<":\n-Volte che hai superato la casella "<<setcas<<": "<<cmir4<<".\n-Volte che si ha indietreggiato la casella 1: "<<czeromir4<<endl;
				}
			}
			if(sname=='s'){
				if(pselect>=2){
					cout<<"STATISTICHE "<<name1<<":\n-Volte che sei andato su una casella Bonus: "<<cbonus1<<".\n-Volte che sei andato su una casella Malus: "<<cmalus1<<".\n-Volte che hai superato la casella "<<setcas<<": "<<cmir1<<".\n-Volte che si ha indietreggiato la casella 1: "<<czeromir1<<endl;
					cout<<"\nSTATISTICHE "<<name2<<":\n-Volte che sei andato su una casella Bonus: "<<cbonus2<<".\n-Volte che sei andato su una casella Malus: "<<cmalus2<<":\n-Volte che hai superato la casella "<<setcas<<": "<<cmir2<<".\n-Volte che si ha indietreggiato la casella 1: "<<czeromir2<<endl;
				}
				if(pselect>=3){
					cout<<"\nSTATISTICHE "<<name3<<":\n-Volte che sei andato su una casella Bonus: "<<cbonus3<<".\n-Volte che sei andato su una casella Malus: "<<cmalus3<<":\n-Volte che hai superato la casella "<<setcas<<": "<<cmir3<<".\n-Volte che si ha indietreggiato la casella 1: "<<czeromir3<<endl;
				}
				if(pselect==4){
					cout<<"\nSTATISTICHE "<<name4<<":\n-Volte che sei andato su una casella Bonus: "<<cbonus4<<".\n-Volte che sei andato su una casella Malus: "<<cmalus4<<":\n-Volte che hai superato la casella "<<setcas<<": "<<cmir4<<".\n-Volte che si ha indietreggiato la casella 1: "<<czeromir4<<endl;
				}
			}

			do{
				cout<<"Vuoi salvare le statistiche di questa partita? [s/n]\n| ";
				cin>>snsavedata;
				if(snsavedata!='s' and snsavedata!='n'){
					cout<<"Devi rispondermi con 's' o 'n'. (Si o No)"<<endl;
				}
			}while(snsavedata!='s' and snsavedata!='n');
			if(snsavedata=='s'){
				std::ofstream file("datiGiocodelloca.txt", std::ios::app);
				if(file.is_open()){
					file<<std::put_time(&tm,"PARTITA[%d-%m-%Y | %H:%M:%S]{")<<"\n\n\tSTATISTICHE GENERALI:\n\t-Giocatori: "<<pselect<<".\n\t-Modalità Auto: ";
					if(snauto=='s'){
						file<<"Attivata.";
					}
					else{
						file<<"Disattivata.";
					}
					file<<"\n\t-Modalità: ";
					if(selmod==1){
						file<<"Facile.";
					}
					if(selmod==2){
						file<<"Normale.";
					}
					if(selmod==3){
						file<<"Difficile.";
					}
					if(selmod==4){
						file<<"Caos.";
					}
					if(selmod==5){
						file<<"Infinite Caos.";
					}
					if(selmod==6){
						file<<"Personalizzata.";
					}
					if(sname=='n'){
						file<<"\n\t-Vincitore: Giocatore "<<i<<"\n\t-Turni: "<<turns<<".\n\t-Volte che sono state superate la casella "<<setcas<<": "<<totmir<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<totzeromir<<".\n"<<endl;
					}
					if(sname=='s'){
						if(i==1){
							file<<"\n\t-Vincitore: "<<name1<<"\n\t-Turni: "<<turns<<".\n\t-Volte che sono state superate la casella "<<setcas<<": "<<totmir<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<totzeromir<<".\n"<<endl;
						}
						if(i==2){
							file<<"\n\t-Vincitore: "<<name2<<"\n\t-Turni: "<<turns<<".\n\t-Volte che sono state superate la casella "<<setcas<<": "<<totmir<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<totzeromir<<".\n"<<endl;
						}
						if(i==3){
							file<<"\n\t-Vincitore: "<<name3<<"\n\t-Turni: "<<turns<<".\n\t-Volte che sono state superate la casella "<<setcas<<": "<<totmir<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<totzeromir<<".\n"<<endl;
						}
						if(i==4){
							file<<"\n\t-Vincitore: "<<name4<<"\n\t-Turni: "<<turns<<".\n\t-Volte che sono state superate la casella "<<setcas<<": "<<totmir<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<totzeromir<<".\n"<<endl;
						}
					}
					if(sname=='n'){
						if(pselect>=2){
							file<<"\tSTATISTICHE GIOCATORE 1:\n\t-Volte che sei andato su una casella Bonus: "<<cbonus1<<".\n\t-Volte che sei andato su una casella Malus: "<<cmalus1<<".\n\t-Volte che hai superato la casella "<<setcas<<": "<<cmir1<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<czeromir1<<endl;
							file<<"\n\tSTATISTICHE GIOCATORE 2:\n\t-Volte che sei andato su una casella Bonus: "<<cbonus2<<".\n\t-Volte che sei andato su una casella Malus: "<<cmalus2<<":\n\t-Volte che hai superato la casella "<<setcas<<": "<<cmir2<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<czeromir2<<endl;
						}
						if(pselect>=3){
							file<<"\n\tSTATISTICHE GIOCATORE 3:\n\t-Volte che sei andato su una casella Bonus: "<<cbonus3<<".\n\t-Volte che sei andato su una casella Malus: "<<cmalus3<<":\n\t-Volte che hai superato la casella "<<setcas<<": "<<cmir3<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<czeromir3<<endl;
						}
						if(pselect==4){
							file<<"\n\tSTATISTICHE GIOCATORE 4:\n\t-Volte che sei andato su una casella Bonus: "<<cbonus4<<".\n\t-Volte che sei andato su una casella Malus: "<<cmalus4<<":\n\t-Volte che hai superato la casella "<<setcas<<": "<<cmir4<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<czeromir4<<endl;
						}
					}
					if(sname=='s'){
						if(pselect>=2){
							file<<"\tSTATISTICHE "<<name1<<":\n\t-Volte che sei andato su una casella Bonus: "<<cbonus1<<".\n\t-Volte che sei andato su una casella Malus: "<<cmalus1<<".\n\t-Volte che hai superato la casella "<<setcas<<": "<<cmir1<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<czeromir1<<endl;
							file<<"\n\tSTATISTICHE "<<name2<<":\n\t-Volte che sei andato su una casella Bonus: "<<cbonus2<<".\n\t-Volte che sei andato su una casella Malus: "<<cmalus2<<":\n\t-Volte che hai superato la casella "<<setcas<<": "<<cmir2<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<czeromir2<<endl;
						}
						if(pselect>=3){
							file<<"\n\tSTATISTICHE "<<name3<<":\n\t-Volte che sei andato su una casella Bonus: "<<cbonus3<<".\n\t-Volte che sei andato su una casella Malus: "<<cmalus3<<":\n\t-Volte che hai superato la casella "<<setcas<<": "<<cmir3<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<czeromir3<<endl;
						}
						if(pselect==4){
							file<<"\n\tSTATISTICHE "<<name4<<":\n\t-Volte che sei andato su una casella Bonus: "<<cbonus4<<".\n\t-Volte che sei andato su una casella Malus: "<<cmalus4<<":\n\t-Volte che hai superato la casella "<<setcas<<": "<<cmir4<<".\n\t-Volte che si ha indietreggiato la casella 1: "<<czeromir4<<endl;
						}
					}
					file<<"}"<<endl;
				}
				else{
					cout<<"Impossibile aprire il file di salvataggio, salvataggio dei dati interrotto."<<endl;
				}
			}

			do{
				cout<<"\nVuoi vedere i dati delle vecchie partite salvate?\n| ";
				cin>>snreadata;
				if(snreadata!='s' and snreadata!='n'){
					cout<<"Devi rispondermi con 's' o 'n'. (Si o No)"<<endl;
				}
			}while(snreadata!='s' and snreadata!='n');
			if(snreadata=='s'){
				ifstream file("datiGiocodelloca.txt");
				if(file.is_open()){
					while(getline(file,line)){
						cout<<"\n"<<line<<endl;
					}
					file.close();
				}
				else{
					cout<<"Impossibile aprire il file di salvataggio, lettura dei dati salvati interrotta."<<endl;
				}
			}

			do{
				cout<<"Volete giocare ancora? [s/n]\n| ";
				cin>>sn;
				if(sn!='s' and sn!='n'){
					cout<<"Devi rispondermi con 's' o 'n'. (Si o No)"<<endl;
				}
			}while(sn!='s' and sn!='n');
			if(sn=='s'){
				do{
					cout<<"Volete cambiare modalità? [s/n]\n| ";
					cin>>snmod;
					if(snmod!='s' and snmod!='n'){
						cout<<"Devi rispondermi con 's' o 'n'. (Si o No)"<<endl;
					}
				}while(snmod!='s' and snmod!='n');
			}
		}while(sn=='s' and snmod=='n');
	}while(snmod=='s');
}