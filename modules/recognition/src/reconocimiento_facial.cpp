#include <sstream>
#include </home/morgal/work/opencv/include/opencv2/opencv.hpp>
#include </home/morgal/work/opencv_contrib/modules/face/include/opencv2/face.hpp>

using namespace cv;
using namespace std;

CascadeClassifier faceDetector;
CascadeClassifier lEyeDetector;
CascadeClassifier rEyeDetector;

VideoCapture capture;

float EYE_SX = 0.12f;
float EYE_SY = 0.17f;
float EYE_SW = 0.37f;
float EYE_SH = 0.36f;

double DESIRED_LEFT_EYE_Y = 0.14;
double DESIRED_LEFT_EYE_X = 0.19;  

int FaceWidth = 100;
int FaceHeight = 100;

int REDUCED_SIZE = 480;

//Obtiene las coordenas de los ojos y el rostro, devuelve true si las encuentra
bool ReconoceOjos(Mat& frame, Rect& rostro, Rect& lEye, Rect& rEye)
{
	vector<Rect> faces;
	faceDetector.detectMultiScale(frame, faces, 1.1, 3, CASCADE_FIND_BIGGEST_OBJECT | CASCADE_DO_ROUGH_SEARCH);

	if(faces.size() == 1)
	{
		rostro = faces[0];
		Mat face = frame(rostro);

		int leftX = cvRound(face.cols * EYE_SX);
		int topY = cvRound(face.rows * EYE_SY);
		int widthX = cvRound(face.cols * EYE_SW);
		int heightY = cvRound(face.rows * EYE_SH);
		int rightX = cvRound(face.cols * (1.0-EYE_SX-EYE_SW));

		Mat topLeftOfFace = face(Rect(leftX, topY, widthX,heightY));
		Mat topRightOfFace = face(Rect(rightX, topY, widthX, heightY));

		vector<Rect> lEyeR, rEyeR;

		lEyeDetector.detectMultiScale(topLeftOfFace, lEyeR, 1.1, 3, CASCADE_DO_ROUGH_SEARCH);
		lEyeDetector.detectMultiScale(topRightOfFace, rEyeR, 1.1, 3, CASCADE_DO_ROUGH_SEARCH);

		if(lEyeR.size() == 1 && rEyeR.size() == 1)
		{
			lEye = lEyeR[0];
			rEye = rEyeR[0];

			lEye.x += leftX;
			lEye.y += topY;

			rEye.x += rightX;
			rEye.y += topY;

			return true;
		}
	}

	return false;
}

//Alinea y recorta el rostro
void RecortaCara(const Mat& face, Mat& warped, Rect leftEye, Rect rightEye)
{
	Point left = Point(leftEye.x + leftEye.width/2, leftEye.y + leftEye.height/2);
	Point right = Point(rightEye.x + rightEye.width/2, rightEye.y + rightEye.height/2);
	Point2f eyesCenter = Point2f( (left.x + right.x) * 0.5f, (left.y + right.y) * 0.5f );

	// Obtiene el ángulo entre los dos ojos
	double dy = (right.y - left.y);
	double dx = (right.x - left.x);
	double len = sqrt(dx*dx + dy*dy);
	double angle = atan2(dy, dx) * 180.0 / CV_PI;

	// Le decimos que, en una imagen escalada, la posición ideal para el ojo derecho debe ser (0.19, 0.14) 
	const double DESIRED_RIGHT_EYE_X = (1.0f - DESIRED_LEFT_EYE_X);

	//Obtiene la cantidad de escalado que debemos aplicar a la imagen para que sea del tamaño que deseamos
	double desiredLen = (DESIRED_RIGHT_EYE_X - DESIRED_LEFT_EYE_X) * FaceWidth;
	double scale = desiredLen / len;

	// Obtiene la matriz necesaria para rotar y escalar la cara de la imagen hasta el ángulo y tamaño deseado
	Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, scale);

	// Cambia el centro de los ojos al que nosotros queremos
	rot_mat.at<double>(0, 2) += FaceWidth * 0.5f - eyesCenter.x;
	rot_mat.at<double>(1, 2) += FaceHeight * DESIRED_LEFT_EYE_Y - eyesCenter.y;

	warped = Mat(FaceHeight, FaceWidth, CV_8U, Scalar(128));

	warpAffine(face, warped, rot_mat, warped.size());
}

//Dibuja las marcas para resaltar el rostro encontrado
void DibujaCuadro(Mat& dst, Rect rect, string msg, int LINE_WIDTH)
{
	Rect r = rect;
	Scalar DETECT_COLOR = CV_RGB(0,255,0);

	line(dst, Point(r.x, r.y), Point(r.x, r.y + LINE_WIDTH), DETECT_COLOR, 3);
	line(dst, Point(r.x, r.y), Point(r.x + LINE_WIDTH, r.y), DETECT_COLOR, 3);

	line(dst, Point(r.x + r.width, r.y), Point(r.x + r.width , r.y + LINE_WIDTH), DETECT_COLOR, 3);
	line(dst, Point(r.x + r.width, r.y), Point(r.x + r.width - LINE_WIDTH, r.y),  DETECT_COLOR, 3);

	line(dst, Point(r.x, r.y + r.height), Point(r.x, r.y + r.height - LINE_WIDTH), DETECT_COLOR, 3);
	line(dst, Point(r.x, r.y + r.height), Point(r.x + LINE_WIDTH, r.y + r.height), DETECT_COLOR, 3);

	line(dst, Point(r.x + r.width, r.y + r.height), Point(r.x + r.width, r.y + r.height - LINE_WIDTH), DETECT_COLOR, 3);
	line(dst, Point(r.x + r.width, r.y + r.height), Point(r.x + r.width - LINE_WIDTH, r.y + r.height), DETECT_COLOR, 3);

	int font = FONT_HERSHEY_DUPLEX;
	Size s = getTextSize(msg, font, 1, 1, 0);

	int x = (dst.cols - s.width) / 2;
	int y = rect.y + rect.height + s.height + 5;

	putText(dst, msg, Point(x, y), font, 1, CV_RGB(255,0,0), 1, CV_AA);
}

//Inicializa los clasificadores en cascada .xml y la webcam
bool Init()
{
	if(!capture.open(0))
	{
		cout << "No se ha podido acceder a la webcam" << endl;
		return false;
	}

	if(!faceDetector.load("/home/tester/opencv/data/haarcascades/haarcascade_frontalface_alt_tree.xml"))
	{
		cout << "No se encuentra el archivo haarcascade_frontalface_alt_tree.xml" << endl;
		return false;
	}

	if(!lEyeDetector.load("/home/tester/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml"))
	{
		cout << "No se encuentra el archivo haarcascade_eye_tree_eyeglasses.xml" << endl;
		return false;
	}

	if(!rEyeDetector.load("/home/tester/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml"))
	{
		cout << "No se encuentra el archivo haarcascade_eye_tree_eyeglasses.xml" << endl;
		return false;
	}

	return true;
}

int main()
{
	Mat frame, copyFrame;
	Ptr<face::FaceRecognizer> model = face::createLBPHFaceRecognizer();
	vector<Mat> rostros;
	vector<int> ids;
	map<int , string> nombres;

	Mat lena = imread("lena.png");

	bool entrenado = false;
	bool agregarRostro = false;
	bool entrenar = false;
	bool input_rec = false;
	int identificador = 0, capCount = 0;

	string msg1 = "Reconocimiento Facial \n\n\t[E] Iniciar Entrenamiento \n\t[R] Reconocer imagen input \n\t[ESC] Salir\n";
	string msg2 = "Reconocimiento Facial \n\n\t[A] Capturar Rostro \n\t[T] Finalizar Entrenamiento \n\t[ESC] Salir\n";
	string msg3 = "Reconocimiento Facial \n\n\t[V] Volver \n";
	cout << msg1;

	bool correcto = Init();

	while (correcto)
	{
		capture >> frame;

		if(input_rec)
		{
			//Reducir el tamaño de la imagen para mejor rendimiento
			float scale = lena.cols / (float) REDUCED_SIZE;

			if (lena.cols > REDUCED_SIZE) {
				int scaledHeight = cvRound(lena.rows / scale);
				resize(lena, lena, Size(REDUCED_SIZE, scaledHeight));
			}

			cvtColor(lena, copyFrame, CV_BGR2GRAY);
		}else
		{
			//Reducir el tamaño de la imagen para mejor rendimiento
			float scale = frame.cols / (float) REDUCED_SIZE;

			if (frame.cols > REDUCED_SIZE) {
				int scaledHeight = cvRound(frame.rows / scale);
				resize(frame, frame, Size(REDUCED_SIZE, scaledHeight));
			}

			cvtColor(frame, copyFrame, CV_BGR2GRAY);
		}
		//Obtener las coordenadas del rostro y los ojos
		Rect face, lEye, rEye;

		if(ReconoceOjos(copyFrame, face, lEye, rEye))
		{
			//si el modo entrenamiento esta activo
			if(entrenado)
			{
				Mat nface;
				RecortaCara(copyFrame(face), nface, lEye, rEye);

				//Agregar el rostro y su numero id a las correspondientes listas
				if(agregarRostro)
				{
					Mat fface;

					flip(nface, fface, 1);
					rostros.push_back(fface);
					ids.push_back(identificador);

					rostros.push_back(nface);
					ids.push_back(identificador);
					agregarRostro = false;

					capCount += 1;
					cout << "Se han capturado " << capCount << " Rostros" << endl; 
				}

				//entrenar el modelo con los rostros capturados
				if(entrenar && rostros.size() >= 1)
				{
					model->update(rostros, ids);

					cout << "\nNombre de la persona: ";
					cin >> nombres[identificador];
					system("clear");

					entrenar = agregarRostro = entrenado = false;
					rostros.clear();
					ids.clear();
					identificador += 1;
					capCount = 0;

					cout << msg1;
				}
			}

			if(identificador >= 1)
			{
				int id = -1;
				double confidence = 0.0;

				Mat nface;
				RecortaCara(copyFrame(face), nface, lEye, rEye);

				//cualquier confidence mayor que threshold id = -1
				//reducir o aumentar este valor segun nos convenga
				model->setThreshold(70);
				model->predict(nface, id, confidence);

				if(id >= 0)
				{
					std::stringstream txt;
					txt << confidence;
					string msg = nombres[id] + " : " + txt.str();

					if(input_rec) DibujaCuadro(lena, face, msg , 20);
					else DibujaCuadro(frame, face, msg , 20);
				} 
				else 
				{
					if(input_rec) DibujaCuadro(lena, face, "???", 20);
					else DibujaCuadro(frame, face, "???", 20);
				}
			}
			else 
				{
					if(input_rec) DibujaCuadro(lena, face, "???", 20);
					else DibujaCuadro(frame, face, "???", 20);
				}
		}

		if(input_rec) imshow("input", lena);
		else imshow("Reconocimiento de rostros", frame);
		

		switch (waitKey(30))
		{
		case 'T':
		case 't':
			entrenar = true;
			break;
		case 'A':
		case 'a':
			agregarRostro = entrenado;
			break;
		case 'E':
		case 'e': 
			entrenado = true;
			system("clear");
			cout << msg2 << endl;
			break;
		case 'R':
		case 'r':
			input_rec = true;
			system("clear");
			cout << msg3 << endl;
			break;
		case 'V':
		case 'v':
			input_rec = false;
			cvDestroyWindow("input");
			system("clear");
			cout << msg1 << endl;
			break;
		case 27:
			return 0;
		}
	}

	system("pausa");

	return 0;
}
