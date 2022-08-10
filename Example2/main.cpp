#include <iostream>
#include <python3.8/Python.h>
#include <opencv2/opencv.hpp>
#include "numpy/ndarrayobject.h"
using namespace std;

int main(int argc, char *argv[])
{
    PyObject *py_module, *py_func;
    
    if(argc != 4)//만약에 실행할 파이썬 파일 경로가 없다면, 
    {
        cout<<"Error : 칼라 사진의 경로, 흑백 사진의 경로, 해당 파이썬 파일의 폴더위치를 인자로 넣어주세요."<<endl;
        return 0;
    }
    setenv("PYTHONPATH", argv[3], 1);//파이썬 코드가 어디있는지 지정합니다. 
    Py_Initialize();
    py_module = PyImport_ImportModule("mat_worker");//모듈이름을 얻어옵니다.

    
    if(py_module ==NULL)
    {
        cout<<"해당위치에 sum_worker 모듈이 없는듯합니다."<<endl;
        return 0;
    }
    py_func = PyObject_GetAttrString(py_module,"make_box");//해당파일로부터 sum함수를 얻어옵니다. 
    if(py_module ==NULL)
    {
        cout<<"해당 모듈에 그런 함수가 없는듯합니다."<<endl;
        return 0;
    }
    // !!this macro is defined by NumPy and must be included
    import_array1(-1);
    cv::Mat color_image = cv::imread(argv[1],cv::IMREAD_COLOR);//칼라로 얻어옵니다.
    cv::Mat gray_image = cv::imread(argv[2],cv::IMREAD_GRAYSCALE);//그레이로 얻어옵니다.

    //------------------------Gray case
    int image_width = gray_image.cols;
    int image_height = gray_image.rows; 

    const unsigned int nElem = image_height*image_width;//요소의 개수
    uchar* m = new uchar[nElem];//적절한 형태로 저장할 matrix를 만듭니다.
    std::memcpy(m, gray_image.data, nElem * sizeof(uchar));
    npy_intp mdim[] = { image_height, image_width };//matrix차원
    PyObject* gray_mat = PyArray_SimpleNewFromData(2, mdim, NPY_UINT8, (void*) m);//차원갯수, 각 원소수, 타입(uint8), 넣을 데이터 

    PyObject *pArgs;
    pArgs = PyTuple_New(1);//인자들을 모아서 저장할 변수
    PyTuple_SetItem(pArgs,0,gray_mat);//0번째로 인자숫자 1을 넣어줍니다.
    PyObject* gray_result = PyObject_CallObject(py_func,pArgs);//결과를얻습니다.
    //rgb이미지 변환합니다.
    cv::Mat return_gray(image_height, image_width, CV_8UC1, PyArray_DATA(gray_result));
    cv::imshow("gray result",return_gray);

    //-------------------------Color case
    int image_width_color = color_image.cols;
    int image_height_color = color_image.rows; 

    const unsigned int nElem_color = image_height_color*image_width_color*3;//요소의 개수
    uchar* m_color = new uchar[nElem_color];//적절한 형태로 저장할 matrix를 만듭니다.
    std::memcpy(m_color, color_image.data, nElem_color * sizeof(uchar));
    npy_intp mdim_color[] = { image_height_color, image_width_color,3};//matrix차원
    PyObject* color_mat = PyArray_SimpleNewFromData(3, mdim_color, NPY_UINT8, (void*) m_color);//차원갯수, 각 원소수, 타입(uint8), 넣을 데이터 
    PyObject *pArgs_color;
    pArgs_color = PyTuple_New(1);//인자들을 모아서 저장할 변수
    PyTuple_SetItem(pArgs_color,0,color_mat);//0번째로 인자숫자 1을 넣어줍니다.
    PyObject* color_result = PyObject_CallObject(py_func,pArgs_color);//결과를얻습니다.
    
    //bgr이미지로 변환합니다.
    cv::Mat return_color(image_height_color, image_width_color, CV_8UC3, PyArray_DATA(color_result));
    cv::imshow("color result",return_color);
    cv::waitKey(0);
    return 0;
}