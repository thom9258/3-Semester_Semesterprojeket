//#include <iostream>
//#include <string>
//#include <vector>
//#include "analyse_vector.h"
//using namespace std;
//
//vector <int> getVectorFlags(vector<int> v1);
//
//int convertBinaryToDecimal(vector <int> v1);
//
//
//
//
//vector <int> getVectorFlags(vector<int> v2) {
//	vector <int> FlagVector;
//	for (int i = 4; i < 8; i++) {
//		FlagVector.push_back(v2.at(i));
//
//	}
//	return FlagVector;
//};
//
//
//vector <int> getVectorData(vector<int> v1) {
//	vector <int> DataVector;
//	int n = convertBinaryToDecimal(analyse_vector::getVectorLength(v1));
//
//	for (int i = 8; i < n + 8; i++) {
//		DataVector.push_back(v1.at(i));
//
//	}
//	return DataVector;
//};
//
//
//int convertBinaryToDecimal(vector <int> v1)
//{
//	int n = v1.at(0) * 1 + v1.at(1) * 2 + v1.at(2) * 4 + v1.at(3) * 8;
//
//
//	return n;
//}
//vector <int> getVectorCRC(vector<int> v1) {
//	vector <int> CRCVector;
//	int n = convertBinaryToDecimal(analyse_vector::getVectorLength(v1));
//
//	for (int i = v1.size() - 8; i < v1.size(); i++) {
//		CRCVector.push_back(v1.at(i));
//
//	}
//	return CRCVector;
//};
//
//
//
//int main()
//{
//
//	vector<int> v1{ 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 };
//
//	cout << "Length: ";
//	cout << analyse_vector::getVectorLength(v1).at(0);
//	cout << analyse_vector::getVectorLength(v1).at(1);
//	cout << analyse_vector::getVectorLength(v1).at(2);
//	cout << analyse_vector::getVectorLength(v1).at(3);
//	cout << endl << "Flags: ";
//	cout << getVectorFlags(v1).at(0);
//	cout << getVectorFlags(v1).at(1);
//	cout << getVectorFlags(v1).at(2);
//	cout << getVectorFlags(v1).at(3);
//	cout << endl << "decimal number of the 4 first numbers: ";
//	cout << convertBinaryToDecimal(analyse_vector::getVectorLength(v1)) << endl;
//	cout << "Data: ";
//	cout << getVectorData(v1).at(2) << endl;
//	cout << getVectorCRC(v1).at(6);
//	cout << endl;
//	system("pause");
//	return 0;
//}
