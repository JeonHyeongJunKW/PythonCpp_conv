#include <iostream>
#include <python3.8/Python.h>

using namespace std;

int main(int argc, char *argv[])
{
    PyObject *py_module, *py_func;
    
    if(argc <4)//만약에 실행할 파이썬 파일 경로가 없다면, 
    {
        cout<<"Error : 더할 숫자 두 개와 해당 파이썬 파일의 폴더위치를 넣어주세요."<<endl;
        return 0;
    }
    setenv("PYTHONPATH", argv[3], 1);//파이썬 코드가 어디있는지 지정합니다. 
    Py_Initialize();
    py_module = PyImport_ImportModule("sum_worker");//모듈이름을 얻어옵니다.
    if(py_module ==NULL)
    {
        cout<<"해당위치에 sum_worker 모듈이 없는듯합니다."<<endl;
        return 0;
    }
    py_func = PyObject_GetAttrString(py_module,"sum");//해당파일로부터 sum함수를 얻어옵니다. 
    if(py_module ==NULL)
    {
        cout<<"해당 모듈에 그런 함수가 없는듯합니다."<<endl;
        return 0;
    }
    PyObject *pValue_a, *pValue_b;
    int a = atoi(argv[1]);//원본 인자 숫자 1
    int b = atoi(argv[2]);//원본 인자 숫자 2
    pValue_a = PyLong_FromLong(a);//인자 숫자1을 PyObject로 만들어줍니다.
    pValue_b = PyLong_FromLong(b);//인자 숫자2를 PyObject로 만들어줍니다.

    PyObject *pArgs;
    pArgs = PyTuple_New(2);//인자들을 모아서 저장할 변수

    PyTuple_SetItem(pArgs,0,pValue_a);//0번째로 인자숫자 1을 넣어줍니다.
    PyTuple_SetItem(pArgs,1,pValue_b);//1번째로 인자숫자 2를 넣어줍니다.

    PyObject *pReturn_Value = PyObject_CallObject(py_func,pArgs);//함수호출과 동시에 PyObject형태의 리턴값을 얻어옵니다. 
    int return_value = PyLong_AsLong(pReturn_Value);//반환숫자를 int형으로 바꿉니다.

    cout<<"결과는 "<<return_value<<"입니다."<<endl;//항상 정수로 반환합니다.
    return 0;
}