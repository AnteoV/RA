#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

GLint Ix = 2;
GLuint window;
GLuint width = 300;
GLuint height=300;
int broj_tocaka;
int broj_segmenata;
double cosinus;
string lines[100];
double** tocke_kr;
double s[3] = { 0.0,0.0,1.0 };
double os[3];
double vrhovi[4][3] = { {1.00, 1.00, 1.00},
						  {2.00, 1.00, 1.00},
						  {1.00, 2.00, 1.00},
						  {1.00, 1.00, 2.00} };

double p[4][3] = { {1, 3, 2},
				{1, 4, 3},
				{1, 2, 4},
				{2, 3, 4} };

void draw(); 
void display();
void reshape(int width, int height);

int main(int argc, char** argv)
{
	fstream krivulja_file;
	krivulja_file.open("tocke.txt", ios::in);
	broj_tocaka = 0;
	if (krivulja_file.is_open()) {
		string line;
		while (getline(krivulja_file, line)) {
			lines[broj_tocaka++] = line;
		}
	}
	broj_segmenata = broj_tocaka - 3;

	tocke_kr = new double* [broj_tocaka];
	for (int i = 0; i < broj_tocaka; i++) {
		tocke_kr[i] = new double[3];
	}

	for (int i = 0; i < broj_tocaka; i++) {
		int ind = 0;
		string s_temp = "";
		s_temp += lines[i][0];
		for (int j = 1; j < lines[i].size(); j++) {
			if (lines[i][j] != ' ') {
				s_temp += lines[i][j];
				if ((j + 1) == lines[i].size()) {
					tocke_kr[i][ind] = stoi(s_temp);
				}
			}
			else {
				tocke_kr[i][ind++] = stod(s_temp);
				s_temp = "";
			}
		}
	}

	for (int i = 0; i < broj_tocaka; i++) {
		for (int j = 0; j < 3; j++) {
			cout << tocke_kr[i][j] << " ";
		}
		cout << endl;
	}



	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutInit(&argc, argv);
	window = glutCreateWindow("Glut OpenGL Linija");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void display() {

	glTranslated(100, 10, 0);
	glScaled(20, 20, 0);

	

	for (int i = 0; i < broj_segmenata; i++) {
		for (double t = 0.01; t < 1; t = t + 0.01) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			draw();
			Sleep(10);
			double t_matrica_draw[4];
			for (int j = 3, k = 0; j >= 0; j--, k++) {
				t_matrica_draw[k] = (1.0 / 6.0) * pow(t, j);
			}

			double t_matrica_tangenta_draw[3];
			for (int j = 2, k = 0; j >= 0; j--, k++) {
				t_matrica_tangenta_draw[k] = (1.0 / 2.0) * pow(t, j);
			}

			double koef_matrica_draw[4][4] = { {-1, 3, -3, 1},
											   {3, -6, 3, 0},
											   {-3, 0, 3, 0},
											   {1, 4, 1, 0} };

			double koef_matrica_tangenta_draw[3][4] = { {-1, 3, -3, 1},
													 {2, -4, 2, 0},
													 {-1, 0, 1, 0} };

			double r_matrica_draw[4][3];

			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 3; k++) {
					r_matrica_draw[j][k] = tocke_kr[i + j][k];
				}
			}

			double temp_draw[4] = { 0 };
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					temp_draw[j] += t_matrica_draw[k] * koef_matrica_draw[k][j];
				}
			}

			double temp_tangenta_draw[4] = { 0 };
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 3; k++) {
					temp_tangenta_draw[j] += t_matrica_tangenta_draw[k] * koef_matrica_tangenta_draw[k][j];
				}
			}

			double tangenta[3] = { 0 };
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 4; k++) {
					tangenta[j] += temp_tangenta_draw[k] * r_matrica_draw[k][j];
				}
			}


			double final_draw[3] = { 0 };
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 4; k++) {
					final_draw[j] += temp_draw[k] * r_matrica_draw[k][j];
				}
			}

			double smjer[3] = { final_draw[0], final_draw[1], final_draw[2] };

			os[0] = s[1] * smjer[2] - smjer[1] * s[2];
			os[1] = -(s[0] * smjer[2] - smjer[0] * s[2]);
			os[2] = s[0] * smjer[1] - smjer[0] * s[1];

			double skalar = 0.0;
			double n_s = 0.0;
			double n_smjer = 0.0;
			for (int i = 0; i < 3; i++) {
				skalar += smjer[i] * s[i];
				n_s += pow(s[i], 2);
				n_smjer += pow(smjer[i], 2);
			}

			cosinus = skalar * 1.0 / (sqrt(n_s) * sqrt(n_smjer) * 1.0);
			cosinus = acos(cosinus) * 57.29578;
			cout << cosinus << " ";

			
			glPushMatrix();
			glTranslatef(smjer[0], smjer[1], smjer[2]);
			glRotatef(cosinus, os[0], os[1], os[2]);
			for (int i = 0; i < 4; i++) {
				int vrh_1 = p[i][0] - 1;
				int vrh_2 = p[i][1] - 1;
				int vrh_3 = p[i][2] - 1;
				
				glColor3f(1.0, 0, 0.0);
				glBegin(GL_LINES);
				{
					glVertex3f(vrhovi[vrh_1][0], vrhovi[vrh_1][1], vrhovi[vrh_1][2]);
					glVertex3f(vrhovi[vrh_2][0], vrhovi[vrh_2][1], vrhovi[vrh_2][2]);
					glVertex3f(vrhovi[vrh_1][0], vrhovi[vrh_1][1], vrhovi[vrh_1][2]);
					glVertex3f(vrhovi[vrh_3][0], vrhovi[vrh_3][1], vrhovi[vrh_3][2]);
					glVertex3f(vrhovi[vrh_3][0], vrhovi[vrh_3][1], vrhovi[vrh_3][2]);
					glVertex3f(vrhovi[vrh_2][0], vrhovi[vrh_2][1], vrhovi[vrh_2][2]);
				}
				glEnd();
				glColor3f(0, 1.0, 0.0);
				glBegin(GL_LINES);
				{
					glVertex3f(final_draw[0], final_draw[1], final_draw[2]);
					glVertex3f(final_draw[0] +tangenta[0], final_draw[1] +tangenta[1], final_draw[2] + tangenta[2]);
					
				}
				glEnd();
				
			}
			glPopMatrix();
			
			glutSwapBuffers();
			
			
		}
	}

	cout << "IZASLI";
	//glFlush();
}


void draw() {
	for (int i = 0; i < broj_segmenata; i++) {
		for (double t = 0; t < 1; t += 0.01) {
			double t_matrica_draw[4];
			for (int j = 3, k = 0; j >= 0; j--, k++) {
				t_matrica_draw[k] = (1.0 / 6.0) * pow(t, j);
			}

			double koef_matrica_draw[4][4] = { {-1, 3, -3, 1},
											   {3, -6, 3, 0},
											   {-3, 0, 3, 0},
											   {1, 4, 1, 0} };

			double r_matrica_draw[4][3];
			
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 3; k++) {
					r_matrica_draw[j][k] = tocke_kr[i + j][k];
				}
			}

			double temp_draw[4] = { 0 };
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					temp_draw[j] += t_matrica_draw[k] * koef_matrica_draw[k][j];
				}
			}

			double final_draw[3] = { 0 };
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 4; k++) {
					final_draw[j] += temp_draw[k] * r_matrica_draw[k][j];
				}
			}
			
			glPointSize(1.0);
			glColor3b(1.0, 1.0, 0.0);
			glBegin(GL_POINTS);
			{
				glVertex2f(final_draw[0], final_draw[1]);
			}
			glEnd();
		}
	}
}


void reshape(int w, int h)
{
	width = w; height = h;               //promjena sirine i visine prozora
	Ix = 0;								//	indeks tocke 0-prva 1-druga tocka
	glViewport(0, 0, width, height);	//  otvor u prozoru

	glMatrixMode(GL_PROJECTION);		//	matrica projekcije
	glLoadIdentity();					//	jedinicna matrica
	gluOrtho2D(0, width, 0, height); 	//	okomita projekcija
	glMatrixMode(GL_MODELVIEW);			//	matrica pogleda
	glLoadIdentity();					//	jedinicna matrica

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // boja pozadine
	glClear(GL_COLOR_BUFFER_BIT);		//	brisanje pozadine
	glPointSize(1.0);					//	postavi velicinu tocke za liniju
	glColor3f(0.0f, 0.0f, 1.0f);		//	postavi boju linije
}



