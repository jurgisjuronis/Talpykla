#include <windows.h>
#include <stdio.h>   //del random generacijos
#include <time.h>    // del random generacijos
#include <stdlib.h> 
#include <tgmath.h>

bool running = true;
int plotis = 800;
int aukstis = 600;
int rnd_gen;
int plius_minus;
int sok_tik;
int turis, uzimta;
int lygio_vidurkis;
int siurkst_verte;
double tankis;
double priem;

int P[800];
int M[800][600];

int buffer_size;
void* buffer_memory;
BITMAPINFO buffer_bitmap_info;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;

	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
}
void clear_screen(unsigned int color1, unsigned int color2, unsigned int color3, unsigned int color4, unsigned int color5, unsigned int color6, unsigned int color7, unsigned int color9) {
	
	for (int y = 0; y < aukstis ; y++) {
		unsigned int* pixel = (unsigned int*)buffer_memory + y * plotis;
		for (int x = 0; x < plotis; x++) {
			if (M[x][y] == 1) {
				*pixel = color1;
			} else if (M[x][y] == 2) {
				*pixel = color2;
			} else if (M[x][y] == 3) {
				*pixel = color3;
			} else if (M[x][y] == 4) {
				*pixel = color4;
			} else if (M[x][y] == 5) {
				*pixel = color5;
			} else if (M[x][y] == 6) {
				*pixel = color6;
			} else if (M[x][y] == 7) {
				*pixel = color7;
			} else if (M[x][y] == 9) {
				*pixel = color9;
			}
			*pixel++;
		}
	}
};

void vert_kris(int Pirm_kd, int Pirm_Son, int Pirm_Son_Max, int Pirm_Dreif, int Pirm_Max, int Pirm_Dr_Son, int pirm_krist, int Pirm_Prad, int pirm_bazinis, int pirm_bazin2, int Antr_kd, int Antr_Son, int Antr_Son_Max, int Antr_Dreif, int Antr_Max, int Antr_Dr_Son, int antr_krist, int Antr_Prad, int antr_bazinis, int antr_bazin2) {

	for (int y = 0; y < aukstis - 10; y++) {
		for (int x = 1; x < plotis - 1; x++) {
			if (M[x][y] == 1) {                    //geltona judri
				plius_minus = rand() % 2 + 1;
				sok_tik = rand() % 10000 + 1;
				if (M[x][y - 1] == 3) {     // pradinis nusodimas
					if (sok_tik < Pirm_Prad) {
						M[x][y] = 4;
					}else {
						M[x][y] = 1;
					}
				}
				else if (M[x][y] == 1 && M[x][y - 1] != 0 && M[x][y - 1] != 4 && M[x - 1][y] == 0 && M[x + 1][y] == 0 && M[x][y + 1] == 0) {
					if (sok_tik <= Pirm_kd) {      //nuseda ne ant kristalizuoto pagrindo ir visur tuscia
						if (plius_minus == 1) {   //apsprendzia ar i kaire ar i dersine soka 
							M[x - 1][y] = 1;
							M[x][y] = 0;
						}
						else if ( plius_minus == 2) {
							M[x + 1][y] = 1;
							M[x][y] = 0;
						}
					}
					else if(M[x][y - 1] == 5) {
						M[x][y] = 4;    // kristalizuojasi
					}
					else {
						M[x][y] = 1;  
					}
				}

				else if (M[x][y] == 1 && M[x][y + 1] == 4 ) {
					if (sok_tik <= pirm_krist) {       //virsus arba apacia kristalizuota
						M[x][y] = 4;
					}
					else {
						M[x][y] = 1;
					}                   
				}
				else if (M[x][y] == 1 && M[x][y - 1] == 4 && M[x - 1][y] == 0 && M[x + 1][y] == 0 && M[x][y + 1] == 0) {
					if(sok_tik >=  pirm_krist) {      //nuseda ant kristalizuoto pagrindo ir visur tuscia
						if (plius_minus == 1) {   //apsprendzia ar i kaire ar i dersine soka 
							M[x - 1][y] = 1;
							M[x][y] = 0;
						}
						else if (plius_minus == 2) {
							M[x + 1][y] = 1;
							M[x][y] = 0;
						}
					}
					else {
						M[x][y] = 4;    // kristalizuojasi
					}
				}
				else if (M[x][y] == 1 && M[x][y - 1] != 0 && M[x][y + 1] == 0 && M[x + 1][y] == 4 && M[x - 1][y] == 0) {
					if (sok_tik >= pirm_krist) {
						M[x - 1][y] = 1;;
						M[x][y] = 0;
					}
					else {
						M[x][y] = 4;
					}//desinej kristalas, jei is kaires tuscia, soka i kaire
				}
				else if (M[x][y] == 1 && M[x][y - 1] != 0 && M[x][y + 1] == 0 && M[x + 1][y] == 0 && M[x - 1][y] == 4) {
					if (sok_tik >= pirm_krist) {
						M[x + 1][y] = 1;
						M[x][y] = 0;
					}
					else {
						M[x][y] = 4;
					}//kairej kristalas, jei is desines tuscia soka
				}

				else if (M[x][y] == 1 && M[x][y - 1] != 0 && M[x][y + 1] == 0 && M[x + 1][y] == 0 && M[x - 1][y] != 0 && M[x - 1][y] != 4) {
					if (sok_tik < Pirm_Son) {  //kaire puse uzimta, soka i desine
						M[x + 1][y] = 1;
						M[x][y] = 0;
					}
					else if (sok_tik >= Pirm_Son && sok_tik < Pirm_Son_Max) {
						M[x][y] = 1;
					}
					else if(M[x][y - 1] == 5 ) {
						M[x][y] = 4;
					} else {
						M[x][y] = 1;
					}
				}
				else if (M[x][y] == 1 && M[x][y - 1] != 0 && M[x][y + 1] == 0 && M[x + 1][y] != 0 && M[x + 1][y] != 4 && M[x - 1][y] == 0) {
					if (sok_tik < Pirm_Son) {  //desine uzimta, soka i kaire
						M[x - 1][y] = 1;
						M[x][y] = 0;
					}
					else if ( sok_tik >= Pirm_Son && sok_tik < Pirm_Son_Max) {
						M[x][y] = 1;
					}
					else if( M[x][y - 1] == 5) {
						M[x][y] = 4;
					} else {
						M[x][y] = 1;
					}
				}
				
				else if (M[x][y] == 1 && M[x][y + 1] == 0 && M[x][y - 1] != 0 && M[x - 1][y] != 0 && M[x + 1][y] != 0 && M[x - 1][y + 1] == 0 && M[x + 1][y + 1] == 0) {
					if (sok_tik < Pirm_Dreif) {      // Dreifo tikimybe
						if (plius_minus == 1) {   //apsprendzia ar i kaire ar i dersine soka 
							M[x - 1][y + 1] = 1;
							M[x][y] = 0;
						}
						else if (plius_minus == 2) {
							M[x + 1][y + 1] = 1;
							M[x][y] = 0;
						}
					}
					else if (sok_tik < Pirm_Max) {
						M[x][y] = 1;
					}
					else if (M[x][y - 1] == 5) {
						M[x][y] = 4;
					} else {
						M[x][y] = 1;
					}
				}
				else if (M[x][y] == 1 && M[x][y + 1] == 0 && M[x][y - 1] != 0 && M[x - 1][y] != 0 && M[x + 1][y] != 0 && M[x - 1][y + 1] == 0 && M[x + 1][y + 1] != 0) {
					if (sok_tik < Pirm_Dr_Son) {      // Dreifo tikimybe
						M[x - 1][y + 1] = 1;
						M[x][y] = 0;
					}
					else if (sok_tik < Pirm_Max) {
						M[x][y] = 1;
					}
					else if (M[x][y - 1] == 5) {
						M[x][y] = 4;
					} else {
						M[x][y] = 1;
					}
				}
				else if (M[x][y] == 1 && M[x][y + 1] == 0 && M[x][y - 1] != 0 && M[x - 1][y] != 0 && M[x + 1][y] != 0 && M[x - 1][y + 1] != 0 && M[x + 1][y + 1] == 0) {
					if (sok_tik < Pirm_Dr_Son) {      // Dreifo tikimybe
						M[x + 1][y + 1] = 1;
						M[x][y] = 0;
					}
					else if (sok_tik < Pirm_Max) {
						M[x][y] = 1;
					}
					else {
						M[x][y] = 4;
					}
				}

				else if (M[x][y] == 1 && M[x][y - 1] == 4) {
				if (sok_tik <= pirm_bazinis) {       //virsus arba apacia kristalizuota
					M[x][y] = 4;
				}
				else {
					M[x][y] = 1;
				}
				}
				else if (M[x][y] == 1 && M[x][y - 1] == 5) {
				if (sok_tik <= pirm_bazin2) {       //virsus arba apacia kristalizuota
					M[x][y] = 4;
				}
				else {
					M[x][y] = 1;
				}
				}
				// 1 tipo daleles kristalizacijos PABAIGA
			} else if (M[x][y] == 2) {                    // Zali
				plius_minus = rand() % 2 + 1;
				sok_tik = rand() % 10000 + 1;
				if ( M[x][y - 1] == 3) {
					if (sok_tik < Pirm_Prad) {
						M[x][y] = 5;
					}
					else {
						M[x][y] = 2;
					}
				}
				else if (M[x][y] == 2 && M[x][y - 1] != 0 && M[x][y - 1] != 5 && M[x - 1][y] == 0 && M[x + 1][y] == 0 && M[x][y + 1] == 0) {
					if (sok_tik <= Antr_kd) {
						if (plius_minus == 2) {   //apsprendzia ar i kaire ar i dersine soka 
							M[x - 1][y] = 2;
							M[x][y] = 0;
						}
						else if (plius_minus == 1) {
							M[x + 1][y] = 2;
							M[x][y] = 0;
						}
					}
					else if( M[x][y - 1] == 4 ) {
						M[x][y] = 5;    // kristalizuojasi
					}
					else {
						M[x][y] = 2;
					}
				}
				
				else if (M[x][y] == 2 && M[x][y + 1] == 5) {
					if (sok_tik <= antr_krist) {       //virsus  kristalizuota
						M[x][y] = 5;
					}
					else {
						M[x][y] = 2;
					}
				}
				else if (M[x][y] == 2 && M[x][y - 1] == 5 && M[x - 1][y] == 0 && M[x + 1][y] == 0 && M[x][y + 1] == 0) {
					if (sok_tik >= antr_krist) {      //nuseda ant kristalizuoto pagrindo ir visur tuscia
						if (plius_minus == 2) {   //apsprendzia ar i kaire ar i dersine soka 
							M[x - 1][y] = 2;
							M[x][y] = 0;
						}
						else if (plius_minus == 1) {
							M[x + 1][y] = 2;
							M[x][y] = 0;
						}
					}
					else {
						M[x][y] = 5;    // kristalizuojasi
					}
				}
				else if (M[x][y] == 2 && M[x][y - 1] != 0 && M[x][y + 1] == 0 && M[x + 1][y] == 5 && M[x - 1][y] == 0) {
					if (sok_tik >= antr_krist) {
						M[x - 1][y] = 2;;
						M[x][y] = 0;
					}
					else {
						M[x][y] = 5;
					}//desinej kristalas, jei is kaires tuscia, soka i kaire
				}
				else if (M[x][y] == 2 && M[x][y - 1] != 0 && M[x][y + 1] == 0 && M[x + 1][y] == 0 && M[x - 1][y] == 5) {
					if (sok_tik >= antr_krist) {
						M[x + 1][y] = 2;
						M[x][y] = 0;
					}
					else {
						M[x][y] = 5;
					}//kairej kristalas, jei is desines tuscia soka
				}

				else if (M[x][y] == 2 && M[x][y - 1] != 0 && M[x][y + 1] == 0 && M[x + 1][y] == 0 && M[x - 1][y] != 0 && M[x - 1][y] != 5) {
					if (sok_tik < Antr_Son) {     // soka i desine nes nes kaire uzimta
						M[x + 1][y] = 2;
						M[x][y] = 0;
					}
					else if (sok_tik > Antr_Son && sok_tik < Antr_Son_Max) {
						M[x][y] = 2;
					}
					else {
						M[x][y] = 5;
					}
				}
				else if (M[x][y] == 2 && M[x][y - 1] != 0 && M[x][y + 1] == 0 && M[x + 1][y] != 0 && M[x + 1][y] != 5 && M[x - 1][y] == 0) {
					if (sok_tik < Antr_Son) {    // soka i kaire
						M[x - 1][y] = 2;
						M[x][y] = 0;
					}
					else if (sok_tik >= Antr_Son && sok_tik < Antr_Son_Max) {
						M[x][y] = 2;
					}
					else {
						M[x][y] = 5;
					}
				}

				else if (M[x][y] == 2 && M[x][y + 1] == 0 && M[x][y - 1] != 0 && M[x - 1][y] != 0 && M[x + 1][y] != 0 && M[x - 1][y + 1] == 0 && M[x + 1][y + 1] == 0) {
					if (sok_tik < Antr_Dreif) {      // Dreifo tikimybe
						if (plius_minus == 2) {   //apsprendzia ar i kaire ar i dersine soka 
							M[x - 1][y + 1] = 2;
							M[x][y] = 0;
						}
						else if (plius_minus == 1) {
							M[x + 1][y + 1] = 2;
							M[x][y] = 0;
						}
					}
					else if (sok_tik < Antr_Max) {
						M[x][y] = 2;
					}
					else {
						M[x][y] = 5;
					}
				}
				else if (M[x][y] == 2 && M[x][y + 1] == 0 && M[x][y - 1] != 0 && M[x - 1][y] != 0 && M[x + 1][y] != 0 && M[x - 1][y + 1] == 0 && M[x + 1][y + 1] != 0) {
					if (sok_tik < Antr_Dr_Son) {      // Dreifo tikimybe
						M[x - 1][y + 1] = 2;
						M[x][y] = 0;
					}
					else if (sok_tik < Antr_Max) {
						M[x][y] = 2;
					}
					else {
						M[x][y] = 5;
					}
				}
				else if (M[x][y] == 2 && M[x][y + 1] == 0 && M[x][y - 1] != 0 && M[x - 1][y] != 0 && M[x + 1][y] != 0 && M[x - 1][y + 1] != 0 && M[x + 1][y + 1] == 0) {
					if (sok_tik < Antr_Dr_Son) {      // Dreifo tikimybe
						M[x + 1][y + 1] = 2;
						M[x][y] = 0;
					}
					else if (sok_tik < Antr_Max) {
						M[x][y] = 2;
					}
					else {
						M[x][y] = 5;
					}
				}

				else if (M[x][y] == 2 && M[x][y - 1] == 5) {
				if (sok_tik <= antr_bazinis) {       //apacia  kristalizuota
					M[x][y] = 5;
				}
				else {
					M[x][y] = 2;
				}
				}
				else if (M[x][y] == 2 && M[x][y - 1] == 4) {
				if (sok_tik <= antr_bazin2) {       //apacia  kristalizuota
					M[x][y] = 5;
				}
				else {
					M[x][y] = 2;
				}
				}
			}
		}
	}
};

void pakilimas(int pirm_pakil, int antr_pakil) {
	for (int y = 1; y < aukstis - 10; y++) {
		for (int x = 1; x < plotis - 1; x++) {
			if (M[x][y] == 1) {
				sok_tik = rand() % 100 + 1;
				if (M[x][y - 1] != 0 && M[x][y - 1] != 4 && M[x - 1][y] != 4 && M[x + 1][y] != 4 && M[x][y + 1] != 4 && ((M[x - 1][y] != 4 && M[x - 1][y] != 0) || (M[x + 1][y] != 0 && M[x + 1][y] != 4))) {
					if (sok_tik < pirm_pakil) {
						M[x][y] = 6;
					}
				}
			}
			else if (M[x][y] == 2) {
				sok_tik = rand() % 100 + 1;
				if (M[x][y - 1] != 0 && M[x][y - 1] != 5 && M[x - 1][y] != 5 && M[x + 1][y] != 5 && M[x][y + 1] != 5 && ((M[x - 1][y] != 5 && M[x - 1][y] != 0) || (M[x + 1][y] != 0 && M[x + 1][y] != 5))) {
					if (sok_tik < antr_pakil) {
						M[x][y] = 7;
					}
				}
			}
		}
	}
}

void horiz_kris(int pirm, int antr) {
	for (int y = 1; y < aukstis - 10; y++) {
		for (int x = 1; x < plotis - 1; x++) {
			if (M[x][y] == 1) {                       // Geltoni judrus
				sok_tik = rand() % 100 + 1;
				if (M[x][y] == 1 && M[x][y - 1] == 0 && (M[x - 1][y] == 4 || M[x + 1][y] == 4)) {
					if (sok_tik < pirm) {
						M[x][y] = 4;
					}
				} 
			}
			else if (M[x][y] == 2) {
				sok_tik = rand() % 100 + 1;
				if (M[x][y] == 2 && M[x][y - 1] == 0 && ( M[x - 1][y] == 5 || M[x + 1][y] == 5)) {
					if (sok_tik < antr) {
						M[x][y] = 5;
					}
				}
			}
		}
	}
}

void kristal_judejimas(int pirm, int antr) {
	for (int y = 1; y < aukstis; y++) {
		for (int x = 1; x < plotis - 1; x++) {
			if (M[x][y] == 4) {
				if (M[x][y - 1] == 0 || M[x - 1][y] == 0 || M[x + 1][y] == 0 || M[x][y + 1] == 0) {
					sok_tik = rand() % 100000 + 1;
					plius_minus = rand() % 3 + 1;
					if (M[x][y - 1] != 0 && M[x - 1][y] == 0 && M[x + 1][y] == 0 && M[x][y + 1] == 0 && sok_tik < pirm) {
						if (plius_minus == 1) {
							M[x - 1][y] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 2) {
							M[x + 1][y] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 3) {
							M[x][y + 1] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] != 0 && M[x - 1][y] != 0 && M[x + 1][y] == 0 && M[x][y + 1] == 0 && sok_tik < pirm) {
						if (plius_minus == 2) {
							M[x + 1][y] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 3) {
							M[x][y + 1] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] != 0 && M[x - 1][y] == 0 && M[x + 1][y] != 0 && M[x][y + 1] == 0 && sok_tik < pirm) {
						if (plius_minus == 2) {
							M[x - 1][y] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 3) {
							M[x][y + 1] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] != 0 && M[x - 1][y] == 0 && M[x + 1][y] == 0 && M[x][y + 1] != 0 && sok_tik < pirm) {
						if (plius_minus == 1) {
							M[x - 1][y] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 2) {
							M[x + 1][y] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] != 0 && M[x - 1][y] != 0 && M[x + 1][y] != 0 && M[x][y + 1] == 0 && sok_tik < pirm) {
						if (plius_minus == 3) {   
							M[x][y + 1] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] != 0 && M[x - 1][y] != 0 && M[x + 1][y] == 0 && M[x][y + 1] != 0 && sok_tik < pirm) {
						if (plius_minus == 2) {     //124N
							M[x + 1][y] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] != 0 && M[x - 1][y] == 0 && M[x + 1][y] != 0 && M[x][y + 1] != 0 && sok_tik < pirm) {
						if (plius_minus == 2) {     //134N
							M[x - 1][y] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] == 0 && M[x - 1][y] != 0 && M[x + 1][y] == 0 && M[x][y + 1] == 0 && sok_tik < pirm) {
						if (plius_minus == 1) {     //2NNN
							M[x][y - 1] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 2) {
							M[x + 1][y] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 3) {
							M[x][y + 1] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] == 0 && M[x - 1][y] != 0 && M[x + 1][y] != 0 && M[x][y + 1] == 0 && sok_tik < pirm) {
						if (plius_minus == 1) {     //23NN
							M[x][y - 1] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 3) {
							M[x][y + 1] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] == 0 && M[x - 1][y] != 0 && M[x + 1][y] == 0 && M[x][y + 1] != 0 && sok_tik < pirm) {
						if (plius_minus == 1) {     //24NN
							M[x][y - 1] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 3) {
							M[x + 1][y] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] == 0 && M[x - 1][y] != 0 && M[x + 1][y] != 0 && M[x][y + 1] != 0 && sok_tik < pirm) {
						if (plius_minus == 1) {     // 234N
							M[x][y - 1] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] == 0 && M[x - 1][y] == 0 && M[x + 1][y] != 0 && M[x][y + 1] != 0 && sok_tik < pirm) {
						if (plius_minus == 1) {     //34NN
							M[x][y - 1] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 2) {
							M[x - 1][y] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] == 0 && M[x - 1][y] == 0 && M[x + 1][y] != 0 && M[x][y + 1] == 0 && sok_tik < pirm) {
						if (plius_minus == 1) {     //3NNN
							M[x][y - 1] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 2) {
							M[x - 1][y] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 3) {
							M[x][y + 1] = 6;
							M[x][y] = 0;
						}
					}
					else if (M[x][y - 1] == 0 && M[x - 1][y] == 0 && M[x + 1][y] == 0 && M[x][y + 1] != 0 && sok_tik < pirm) {
						if (plius_minus == 1) {     //4NNN
							M[x][y - 1] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 2) {
							M[x - 1][y] = 6;
							M[x][y] = 0;
						}
						else if (plius_minus == 3) {
							M[x + 1][y] = 6;
							M[x][y] = 0;
						}
					}
				}
			}
		}
	}
}

void judejimas(int pirm_virs, int pirm_zemyn, int pirm_son, int antr_virs, int ant_zemyn, int antr_son) {
	for (int y = 1; y < aukstis; y++) {
		for (int x = 1; x < plotis - 1; x++) {
			if (M[x][y] == 6) {
				sok_tik = rand() % 100 + 1;
				if (sok_tik >= 1 && sok_tik <= pirm_virs) {
					if (M[x][y - 1] == 0) {
						M[x][y - 1] = 6;
						M[x][y] = 0;
					}
				}
				else if (sok_tik > pirm_virs && sok_tik <= pirm_virs + pirm_son ) {
					if (M[x - 1][y] == 0) {
						M[x - 1][y] = 6;
						M[x][y] = 0;
					}
				}
				else if (sok_tik > pirm_virs + pirm_son && sok_tik <= pirm_virs + pirm_son + pirm_son) {
					if (M[x + 1][y] == 0) {
						M[x + 1][y] = 6;
						M[x][y] = 0;
					}
				}
				else if (sok_tik > pirm_virs + pirm_son + pirm_son && sok_tik <= 100) {
					if (M[x][y + 1] == 0) {
						M[x][y + 1] = 6;
						M[x][y] = 0;
					}
				}
			}
			else if (M[x][y] == 7) {
				sok_tik = rand() % 100 + 1;
				if (sok_tik >= 1 && sok_tik <= antr_virs) {
					if (M[x][y - 1] == 0) {
						M[x][y - 1] = 7;
						M[x][y] = 0;
					}
				}
				else if (sok_tik > antr_virs && sok_tik <= antr_virs + antr_son) {
					if (M[x + 1][y] == 0) {
						M[x + 1][y] = 7;
						M[x][y] = 0;
					}
				}
				else if (sok_tik > antr_virs + antr_son && sok_tik <= antr_virs + antr_son + antr_son) {
					if (M[x - 1][y] == 0) {
						M[x - 1][y] = 7;
						M[x][y] = 0;
					}
				}
				else if (sok_tik > antr_virs + antr_son + antr_son && sok_tik <= 100) {
					if (M[x][y + 1] == 0) {
						M[x][y + 1] = 7;
						M[x][y] = 0;
					}
				}
			}
		}
	}
}

void nusedimas(int pirm_vert, int pirm_horiz, int antr_vert, int antr_horiz) {
	for (int y = 1; y < aukstis; y++) {
		for (int x = 1; x < plotis - 1; x++) {
			if (M[x][y] == 6) {
				sok_tik = rand() % 100 + 1;
				if ( M[x][y - 1] == 4) {
					if (sok_tik < pirm_vert) {
						M[x][y] = 4;
					}
				}
				if (M[x - 1][y] == 4 || M[x + 1][y] == 4) {
					if (sok_tik < pirm_horiz) {
						M[x][y] = 4;
					}
				}
				if (M[x][y + 1] == 4) {
					if (sok_tik < pirm_horiz) {
						M[x][y] = 4;
					}
				}
			}
			else if (M[x][y] == 7) {
				sok_tik = rand() % 100 + 1;
				if (M[x][y - 1] == 5) {
					if (sok_tik < antr_vert) {
						M[x][y] = 5;
					}
				}
				if (M[x - 1][y] == 5 || M[x + 1][y] == 5) {
					if (sok_tik < antr_horiz) {
						M[x][y] = 5;
					}
				}
				if (M[x][y + 1] == 5) {
					if (sok_tik < antr_horiz) {
						M[x][y] = 5;
					}
				}
			}
		}
	}
}

void kritimas() {
	//generuoja atsitiktinej x koordinateje                         
	rnd_gen = rand() % 800;
	M[rnd_gen][599] = rand() % 2 + 1;
	for (int y = 1; y < aukstis; y++) {
		for (int x = 0; x < plotis; x++) {
			if ((M[x][y] == 1 || M[x][y] == 2 ) && M[x][y - 1] == 0 ) {
				M[x][y - 1] = M[x][y];
				M[x][y] = 0;
			}
		}
	}
}

void apkarpymas(int pabeg) {
	for (int x = 0; x < plotis; x++) {
		if (M[x][0] != 3) {
			M[x][0] = 0;
		}
	}
	for (int y = 20; y < aukstis; y++){
		sok_tik = rand() % 10000 + 1;
		if (sok_tik < pabeg) {
			M[0][y] = 0;
			M[plotis - 1][y] = 0;
		}
	}
}

void krist_krit() {
	for (int y = 1; y < aukstis; y++) {
		for (int x = 1; x < plotis; x++) {
			if (M[x][y] == 4 && M[x][y - 1] == 0 && ( M[x][y + 1] == 0 || M[x][y + 1] == 1 || M[x][y + 1] == 2) && ( M[x - 1][y] != 4 && M[x + 1][y] != 4 )) {
				M[x][y - 1] = M[x][y];
				M[x][y] = 0;
			}
			else if (M[x][y] == 5 && M[x][y - 1] == 0 && (M[x][y + 1] == 0 || M[x][y + 1] == 1 || M[x][y + 1] == 2) && ( M[x - 1][y] != 5 && M[x + 1][y] != 5)) {
				M[x][y - 1] = M[x][y];
				M[x][y] = 0;
			}
		}
	}
}

void staciakampis(int x_centr, int x_dydis, int y_centr, int y_dydis, unsigned int color) {
	for (int y = y_centr - (y_dydis / 2); y < y_centr + (y_dydis / 2); y++) {
		unsigned int* pixel = (unsigned int*)buffer_memory + (x_centr - (x_dydis / 2)) + y * plotis;
		for (int x = x_centr - (x_dydis / 2); x < x_centr + (x_dydis / 2); x++) {
			*pixel = color;
			*pixel++;
		}
	}
}

void skaiciai(int skaicius, int x, int y, int dydis, unsigned int color) {

	bool piesia = false;
	while (skaicius || !piesia) {
		piesia = true;
		int digit = skaicius % 10;
		skaicius = skaicius / 10;
		switch (digit) {
		case 0: {
			staciakampis(x - dydis, dydis, y, dydis * 5, color);
			staciakampis(x + dydis, dydis, y, dydis * 5, color);
			staciakampis(x, dydis * 1.5, y + 2 * dydis, dydis, color);
			staciakampis(x, dydis * 1.5, y - 2 * dydis, dydis, color);
			x -= dydis * 4;
		} break;
		case 1: {
			staciakampis(x, dydis, y, dydis * 5, color);
			x -= dydis * 4;
		} break;
		case 2: {
			staciakampis(x, dydis * 3, y, dydis, color);
			staciakampis(x, dydis * 3, y - dydis * 2, dydis, color);
			staciakampis(x, dydis * 3, y + dydis * 2, dydis, color);
			staciakampis(x - dydis, dydis, y - dydis, dydis * 1.5, color);
			staciakampis(x + dydis, dydis, y + dydis, dydis * 1.5, color);
			x -= dydis * 4;
		} break;
		case 3: {
			staciakampis(x, dydis * 3, y, dydis, color);
			staciakampis(x, dydis * 3, y - dydis * 2, dydis, color);
			staciakampis(x, dydis * 3, y + dydis * 2, dydis, color);
			staciakampis(x + dydis, dydis, y - dydis, dydis * 1.5, color);
			staciakampis(x + dydis, dydis, y + dydis, dydis * 1.5, color);
			x -= dydis * 4;
		} break;
		case 4: {
			staciakampis(x + dydis, dydis, y, dydis * 5, color);
			staciakampis(x, dydis * 3, y, dydis, color);
			staciakampis(x - dydis, dydis, y + dydis, dydis * 3, color);
			x -= dydis * 4;
		} break;
		case 5: {
			staciakampis(x, dydis * 3, y, dydis, color);
			staciakampis(x, dydis * 3, y - dydis * 2, dydis, color);
			staciakampis(x, dydis * 3, y + dydis * 2, dydis, color);
			staciakampis(x + dydis, dydis, y - dydis, dydis * 1.5, color);
			staciakampis(x - dydis, dydis, y + dydis, dydis * 1.5, color);
			x -= dydis * 4;
		} break;
		case 6: {
			staciakampis(x - dydis, dydis, y, dydis * 5, color);
			staciakampis(x + dydis / 2, dydis * 2, y + dydis * 2, dydis, color);
			staciakampis(x + dydis / 2, dydis * 2, y - dydis * 2, dydis, color);
			staciakampis(x + dydis / 2, dydis * 2, y, dydis, color);
			staciakampis(x + dydis, dydis, y - dydis, dydis * 1.5, color);
			x -= dydis * 4;
		} break;
		case 7: {
			staciakampis(x + dydis, dydis, y, dydis * 5, color);
			staciakampis(x - dydis / 2, dydis * 2, y + dydis * 2, dydis, color);
			x -= dydis * 4;
		} break;
		case 8: {
			staciakampis(x - dydis, dydis, y, dydis * 5, color);
			staciakampis(x + dydis, dydis, y, dydis * 5, color);
			staciakampis(x, dydis * 1.5, y, dydis, color);
			staciakampis(x, dydis * 1.5, y - dydis * 2, dydis, color);
			staciakampis(x, dydis * 1.5, y + dydis * 2, dydis, color);
			x -= dydis * 4;
		} break;
		case 9: {
			staciakampis(x + dydis, dydis, y, dydis * 5, color);
			staciakampis(x - dydis / 2, dydis * 2, y + dydis * 2, dydis, color);
			staciakampis(x - dydis / 2, dydis * 2, y - dydis * 2, dydis, color);
			staciakampis(x - dydis / 2, dydis * 2, y, dydis, color);
			staciakampis(x - dydis, dydis, y + dydis, dydis * 1.5, color);
			x -= dydis * 4;
		} break;
		}
	}
}

const char* raides[][7] = {
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 0000",
	"0   00",
	"0",
	"0  000",
	"0    0",
	"0    0",
	" 00000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	"0000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",
	"0  00",

	" 00",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	" 00",
	" 000",
	"0",
	"00 ",
	"  00",
	"   0",
	"000 ",

	"   0",
	"  0",
	"  0",
	" 0",
	" 0",
	"0",
	"0",

	" ",
	" 00",
	" 00",
	"  ",
	" ",
	" 00",
	" 00", 

	" 00  0",
	" 00 0",
	"    0",
	"   0",
	"  0",
	"  0 00",
	" 0  00",
};

void tekstas(const char *tekstas, int x, int y, int dydis, unsigned int color) {
	int pradinis_y = y;

	while(*tekstas){
		const char** a_raide = raides[*tekstas - 'A'];
		if (a_raide == raides[12] || a_raide == raides[13] || a_raide == raides[16] || a_raide == raides[21] || a_raide == raides[22] || a_raide == raides[23] || a_raide == raides[24]) {
			int pradinis_x = x;
			for (int i = 0; i < 7; i++) {
				const char* eile = a_raide[i];
				while (*eile) {
					if (*eile == '0') {
						staciakampis(x, dydis, y, dydis, color);
					}
					x += dydis;
					eile++;
				}
				y -= dydis;
				x = pradinis_x;
			}
			tekstas++;
			x += dydis * 6.5;
			y = pradinis_y;
		}
		else if (a_raide == raides[8] || a_raide == raides[19] || a_raide == raides[28]) {
			int pradinis_x = x;
			for (int i = 0; i < 7; i++) {
				const char* eile = a_raide[i];
				while (*eile) {
					if (*eile == '0') {
						staciakampis(x, dydis, y, dydis, color);
					}
					x += dydis;
					eile++;
				}
				y -= dydis;
				x = pradinis_x;
			}
			tekstas++;
			x += dydis * 4.5;
			y = pradinis_y;
		}
		else if (a_raide == raides[6] || a_raide == raides[29]) {
			int pradinis_x = x;
			for (int i = 0; i < 7; i++) {
				const char* eile = a_raide[i];
				while (*eile) {
					if (*eile == '0') {
						staciakampis(x, dydis, y, dydis, color);
					}
					x += dydis;
					eile++;
				}
				y -= dydis;
				x = pradinis_x;
			}
			tekstas++;
			x += dydis * 8;
			y = pradinis_y;
		}
		else {
			int pradinis_x = x;
			for (int i = 0; i < 7; i++) {
				const char* eile = a_raide[i];
				while (*eile) {
					if (*eile == '0') {
						staciakampis(x, dydis, y, dydis, color);
					}
					x += dydis;
					eile++;
				}
				y -= dydis;
				x = pradinis_x;
			}
			tekstas++;
			x += dydis * 5.5;
			y = pradinis_y;
		}
	}
}

void pavirsiaus_lygis(int apribojimas, int imtis, int salyga) {

	for (int x = apribojimas; x < plotis - apribojimas; x++) {
		for (int y = 20; y < aukstis; y++) {
			int skaitliukas = 0;
			if (M[x][y] == 4 || M[x][y] == 5) {
				for (int i = 1; i <= imtis; i++) {
					if (M[x][y - i] == 4 || M[x][y - i] == 5) {
						skaitliukas++;
					}
				}
				if (skaitliukas >= salyga) {
					P[x] = y;
				}
			}
		}
	}
};

void tankumas(int apribojimas) {
	for (int x = apribojimas; x < plotis - apribojimas; x++) {
		for (int y = 20; y < P[x]; y++) {
			turis++;
			if (M[x][y] != 0) {
				uzimta++;
			}
		}
	}
	tankis = uzimta * 100 / turis;
	uzimta = 0;
	turis = 0;
};

void siurkstumas(int apribojimas) {
	int suma = 0;
	int tarpinis = 0;
	for (int x = apribojimas; x < plotis - apribojimas; x++) {
		suma += P[x];
	}
	lygio_vidurkis = suma / ((plotis - apribojimas) - apribojimas);
	suma = 0;
	for (int x = apribojimas; x < plotis - apribojimas; x++) {
		tarpinis += (P[x] - lygio_vidurkis) * (P[x] - lygio_vidurkis);
	}
	siurkst_verte = sqrt(tarpinis / ((plotis - apribojimas) - apribojimas));
}

void priemaisos(int apribojimas) {
	for (int x = apribojimas; x < plotis - apribojimas; x++) {
		for (int y = 20; y < P[x]; y++) {
			turis++;
			if (M[x][y] != 4 && M[x][y] != 5 && M[x][y] != 0) {
				uzimta++;
			}
		}
	}
	priem = uzimta * 100 / turis;
	turis = 0;
	uzimta = 0;
};

void mastelis() {
	staciakampis(6, 10, 70, 2, RGB(50, 50, 50));
	staciakampis(6, 10, 120, 2, RGB(50, 50, 50));
	staciakampis(6, 10, 170, 2, RGB(50, 50, 50));
	staciakampis(6, 10, 220, 2, RGB(50, 50, 50));
	staciakampis(6, 10, 270, 2, RGB(50, 50, 50));
	staciakampis(6, 10, 320, 2, RGB(50, 50, 50));
	staciakampis(6, 10, 370, 2, RGB(50, 50, 50));
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Create Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = window_callback;

	// Register Class
	RegisterClass(&window_class);

	// Create Window
	HWND window = CreateWindow(window_class.lpszClassName, L"Simuliacija", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	// Atminties sukurimas
	buffer_size = aukstis * plotis * sizeof(unsigned int);

	if (buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);
	buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
	buffer_bitmap_info.bmiHeader.biWidth = plotis;
	buffer_bitmap_info.bmiHeader.biHeight = aukstis;
	buffer_bitmap_info.bmiHeader.biPlanes = 1;
	buffer_bitmap_info.bmiHeader.biBitCount = 32;
	buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 795; x++) {
			if (x % 10 > 8) {
				M[x][y] = 3;
			}
		}
	};


	while (running) {
		// Input
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		// Simulate   // Fonas
		unsigned int* pixel = (unsigned int*)buffer_memory;
		for (int x = 0; x < plotis; x++) {
			for (int y = 0; y < aukstis; y++) {
				*pixel++ = RGB(253, 255, 255);
			}
		}

		//staciakampis(600, 200, 400, 100, RGB(150, 50, 50));

		krist_krit();
		kritimas();
		  // 1 dal - Geltona, //2-dal - Zalia
		  // 1)i sonus laisva, kitaip savaime kristal ant kitos rusies <., 2)i 1 sona kitaip nepakis, 3) < krist proc iki savaiminio krist 4) dreif proc,
		  //  5) < max savaime krist proc, 6) dreif i 1 son, 7777) krist tikimybe 8) Prilip prie pagrindo 9) bazinis prilipimas prie to pacio, 10) bazinis prie kito
		vert_kris(99900, 9801, 99900, 9801, 99900, 9800, 9502, 5, 0, 0, 9991, 9800, 9991, 9800, 9991, 9801, 9502, 49, 0, 0);
		horiz_kris(60, 60);
		kristal_judejimas(2,2);
		pakilimas(50, 50);
		judejimas(25, 25, 25, 25, 25, 25);
		nusedimas(95, 60, 95, 60);

		for (int x = 0; x < plotis; x++) {
			P[x] = 21;
		};
		pavirsiaus_lygis(1, 3, 2);
		siurkstumas(1);
		tankumas(1);
		priemaisos(1);

		skaiciai(tankis, 747, 334, 3, RGB(70, 70, 70));
		skaiciai(siurkst_verte, 747, 314, 3, RGB(70, 70, 70));
		skaiciai(priem, 747, 294, 3, RGB(70, 70, 70));

		staciakampis(400, 782, lygio_vidurkis, 2, RGB(50, 50, 150));
		staciakampis(400, 782, lygio_vidurkis - siurkst_verte, 2, RGB(150, 50, 50));
		staciakampis(400, 782, lygio_vidurkis + siurkst_verte, 2, RGB(150, 50, 50));

		// Š-[ , : - ]    ;
		tekstas("TANKIS]", 655, 340, 2, RGB(100, 100, 100));
		tekstas("[IURK[TUMAS]", 600, 320, 2, RGB(100, 100, 100));
		tekstas("PRIEMAI[OS]", 611, 300, 2, RGB(100, 100, 100));

		tekstas("^", 755, 340, 2, RGB(100, 100, 100));
		tekstas("^", 755, 300, 2, RGB(100, 100, 100));

		mastelis();
		apkarpymas(0);
		clear_screen(RGB(200, 215, 255), RGB(200, 200, 100), RGB(100, 100, 100), RGB(0, 255, 255), RGB(10, 120, 50), RGB(0, 255, 255), RGB(10, 120, 50), RGB(0, 0, 0));


		// Render
		StretchDIBits(hdc, 0, 0, plotis, aukstis, 0, 0, plotis, aukstis, buffer_memory, &buffer_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}

}
