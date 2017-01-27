/***Reconocimiento Facial - TUTOR DE PROGRAMACION***/
/***Para mas informacion visita: http://acodigo.blogspot.com/2014/03/reconocimiento-facial.html
****Autor: Carmelo Marin A**/

#include <opencv2\opencv.hpp>

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
bool GetFaceAndEyes(Mat& frame, Rect& rostro, Rect& lEye, Rect& rEye)
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
void CropFace(Mat& face, Mat& warped, Rect leftEye, Rect rightEye)
{
	Point left = Point(leftEye.x + leftEye.width/2, leftEye.y + leftEye.height/2);
	Point right = Point(rightEye.x + rightEye.width/2, rightEye.y + rightEye.height/2);
	Point2f eyesCenter = Point2f( (left.x + right.x) * 0.5f, (left.y + right.y) * 0.5f );

	// Get the angle between the 2 eyes.
	double dy = (right.y - left.y);
	double dx = (right.x - left.x);
	double len = sqrt(dx*dx + dy*dy);
	double angle = atan2(dy, dx) * 180.0 / CV_PI;

	// Hand measurements shown that the left eye center should ideally be at roughly (0.19, 0.14) of a scaled face image.
	const double DESIRED_RIGHT_EYE_X = (1.0f - DESIRED_LEFT_EYE_X);

	// Get the amount we need to scale the image to be the desired fixed size we want.
	double desiredLen = (DESIRED_RIGHT_EYE_X - DESIRED_LEFT_EYE_X) * FaceWidth;
	double scale = desiredLen / len;

	// Get the transformation matrix for rotating and scaling the face to the desired angle & size.
	Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, scale);

	// Shift the center of the eyes to be the desired center between the eyes.
	rot_mat.at<double>(0, 2) += FaceWidth * 0.5f - eyesCenter.x;
	rot_mat.at<double>(1, 2) += FaceHeight * DESIRED_LEFT_EYE_Y - eyesCenter.y;

	warped = Mat(FaceHeight, FaceWidth, CV_8U, Scalar(128));

	warpAffine(face, warped, rot_mat, warped.size());
}

//Dibuja las marcas para resaltar el rostro encontrado
void DrawMarker(Mat& dst, Rect rect, string msg, int LINE_WIDTH)
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

	if(!faceDetector.load("haarcascade_frontalface_alt_tree.xml"))
	{
		cout << "No se encuentra el archivo haarcascade_frontalface_alt_tree.xml" << endl;
		return false;
	}

	if(!lEyeDetector.load("haarcascade_eye_tree_eyeglasses.xml"))
	{
		cout << "No se encuentra el archivo haarcascade_eye_tree_eyeglasses.xml" << endl;
		return false;
	}

	if(!rEyeDetector.load("haarcascade_eye_tree_eyeglasses.xml"))
	{
		cout << "No se encuentra el archivo haarcascade_eye_tree_eyeglasses.xml" << endl;
		return false;
	}

	return true;
}

int main()
{
	Mat frame, copyFrame;
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	vector<Mat> rostros;
	vector<int> ids;
	map<int , string> names;

	bool entrenado = false;
	bool agregarRostro = false;
	bool entrenar = false;
	int identificador = 0, capCount = 0;

	string msg1 = "Reconocimiento Facial \n\n\t[E] Iniciar Entrenamiento \n\t[ESC] Salir\n";
	string msg2 = "Reconocimiento Facial \n\n\t[A] Capturar Rostro \n\t[T] Finalizar Entrenamiento \n\t[ESC] Salir\n";
	cout << msg1;

	bool correct = Init();

	while (correct)
	{
		capture >> frame;

		//Reducir el tamaño de la imagen para mejor rendimiento
		float scale = frame.cols / (float) REDUCED_SIZE;

		if (frame.cols > REDUCED_SIZE) {
			int scaledHeight = cvRound(frame.rows / scale);
			resize(frame, frame, Size(REDUCED_SIZE, scaledHeight));
		}

		cvtColor(frame, copyFrame, CV_BGR2GRAY);

		//Obtener las coordenadas del rostro y los ojos
		Rect face, lEye, rEye;

		if(GetFaceAndEyes(copyFrame, face, lEye, rEye))
		{
			//si el modo entrenamiento esta activo
			if(entrenado)
			{
				Mat nface;
				CropFace(copyFrame(face), nface, lEye, rEye);

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
					cin >> names[identificador];
					system("cls");

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
				CropFace(copyFrame(face), nface, lEye, rEye);

				//calquier confidence mayor que threshold id = -1
				//redicir o aumentar este valor segun nos convenga
				model->set("threshold", 70);
				model->predict(nface, id, confidence);

				if(id >= 0)
				{
					string msg = names[id] + " : " + to_string((int)confidence);

					DrawMarker(frame, face, msg , 20);
				} 
				else DrawMarker(frame, face, "???", 20);
			}
			else DrawMarker(frame, face, "???", 20);
		}

		imshow("Reconocimiento de rostros", frame);

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
			system("cls");
			cout << msg2 << endl;
			break;
		case 27:
			return 0;
		}
	}

	system("pause");

	return 0;
}