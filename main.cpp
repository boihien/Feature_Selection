#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
//test files Huang	Boi-Hien	small:40	large:33
//class. features
//CS170_largetestdata__33.txt
//CS170_SMALLtestdata__40.txt
void forwardSearch(vector<int> data);
void backwardSearch(vector<int> data);
void leaveOneOutCross();
void readFile();
double crossValidation(vector<int>& classLabel, vector<vector<double>>& features);

//first colum is class label
//11 columms
//rest is feature
//https://www.cplusplus.com/doc/tutorial/files/
void readFile(string fileName, vector<int>& classLabel, vector<vector<double>>& features){
    ifstream inFile;
    inFile.open(fileName);
    double data;
    int line = 0;
    if(fileName == "CS170_SMALLtestdata__40.txt" || fileName == "test1row.txt"){
        if(!inFile.is_open()){
            cout << "Could not open file" << endl;
            return;
        }
        else{
            inFile >> data;
            classLabel.push_back((int) data);
            features.push_back(vector<double>());
            int count = 2; //first one is feature and already pushed one
            while(inFile >> data){
                if(count <= 11){//first line of numbers
                    features[line].push_back(data);
                    count++;
                }
                else{//next line of numbers
                    count = 2;
                    line++;
                    classLabel.push_back((int)data);
                    features.push_back(vector<double>());
                }
            }
        }
        cout << "Reached Here" << endl;
        inFile.close();
    }
    else if(fileName == "CS170_largetestdata__33.txt"){
        if(!inFile.is_open()){
            cout << "Could not open file" << endl;
            return;
        }
        else{
            inFile >> data;
            classLabel.push_back((int) data);
            features.push_back(vector<double>());
            int count = 2; //first one is feature and already pushed one
            while(inFile >> data){
                if(count <= 101){//first line of numbers
                    features[line].push_back(data);
                    count++;
                }
                else{//next line of numbers
                    count = 2;
                    line++;
                    classLabel.push_back((int)data);
                    features.push_back(vector<double>());
                }
            }
            cout << "Reached Here" << endl;
        }
        inFile.close();
    }
    else{
        cout << "Error: wrong file name" << endl;
    }
}

//take slice of model 
//temp hide first 2 objects
//would first 2 be correctly classified
    //if class is label is true with model it is correct
    //else not
double crossValidation(vector<int>& classLabel, vector<vector<double>>& features){
/*data in
  number_correctly_classified = 0;
    for (int i = 1; i < data.size(); i++){
        object_to_classify = data[i];
        label_object_to_classify = data[i];

        nearest_neighbor_distance = inf;
        nearest_neightbor_location = inf;
        for(int k = 0; k < data.size(); k++){
            cout << "Ask if is nearest with"
            if(k!= i ){
                distance = sqrt()
                if(distance < nearest_neighbor_distance){
                    nearest_neighbor_distance = distance;
                    nearest_neighbor_location = k;
                    nearest_neighbor_label = data(nearest_neighbor);
                }
            }
        }
        if(label_object_to_classify == nearest_neighbor_label){
            number_correctly_classified = number_correctly_clasified + 1;
        }
        cout << "Object is class" << endl;
        cout << "Its nearest neighbor is " << endl;
    }
    accuracy = number_correctly_classified / size(data, i);
*/
}

void backwardSearch(vector<int> data){
    vector<int> currentSetFeatures = {};
    for(int i = 0; i < data.size(); i++){
        cout << "On the " << i << "th level of the search tree" << endl;
        int featureToAddLevel = 0;
        int bestAccuracy = 0;
        for(int k = 0; i < data.size(); k++){
            /*if(find(currentSetFeatures.begin(), currentSetFeatures.end(), k) == currentSetFeature.end()){ //if isempty(intersect(current_set_of_features,k)) %only consider adding, if not already added
                cout << "Considering adding the " << endl;
                int currentAccuracy = leave_one_out

                if(currentAccuracy > bestAccuracy){
                    bestAccuracy = currentAccuracy;
                    featureToAddLevel = k;
                }
              }
            */
        }
        cout << "On level " << "i added feature " << "to current set" << endl;
    }
}

vector<int> forwardSearch(vector<vector<double>>& features, vector<int>& classLabel, vector<double>& accuracyVec){
    double currentBest;
    double globalBest;
    vector<int> currentSetFeatures;//initialize empty set 
    vector<int> globalBestVec;
    for(int i = 0; i < features[0].size(); i++){
        cout << "On the " << i << "th level of the search tree" << endl;
        int featureToAddLevel = 0;
        double bestSoFar = 0;
        double accuracy = 0;
        for(int k = 0; i < features[i].size(); k++){
            if(find(currentSetFeatures.begin(), currentSetFeatures.end(), k) == currentSetFeatures.end()){ //if isempty(intersect(current_set_of_features,k)) %only consider adding, if not already added
                vector<vector<double>> emptyFeatures = features;
                vector<int> temp = currentSetFeatures;
                temp.push_back(k);
                cout << "--Considering adding the " << temp[0] + 1 << " feature" << endl;
                for(int i = 1; i < temp.size(); i++){
                    cout << "--Considering adding the " << temp[i] + 1 << " feature" << endl; //add one since need to index from 1
                }
                accuracy = crossValidation(classLabel, emptyFeatures);//use crossvalidation function stub
                accuracyVec.push_back(accuracy);//keep track of accuracy
            }
            if(accuracy > bestSoFar){
                bestSoFar = accuracy;
                featureToAddLevel = k;
            }
        }
        if(currentBest < bestSoFar){//checking for best overall accuracy 
            currentBest = bestSoFar;
            if(globalBest < currentBest){
                globalBest = currentBest;
                globalBestVec = currentSetFeatures;
                globalBestVec.push_back(featureToAddLevel);//keep track of best overall feature to add at this level
            }
        }
        if(find(currentSetFeatures.begin(), currentSetFeatures.end(), featureToAddLevel) == currentSetFeatures.end()){//checking if feauture to add at this level was already added
            currentSetFeatures.push_back(featureToAddLevel);//add feature at this level to set of features to add
            if(i < features[0].size() - 1){//check if current level is less than features at zero size
                //currentSetoffeatures(i) = feature to add at this level
                cout << "On level " << i << " i added feature " << currentSetFeatures[0] + 1 << "to current set" << endl;
            }
        }
    }
    cout << "Reached End. Best feature subset is [" << endl;
    cout << globalBestVec[0] + 1 << endl;
    for(int j = 1; j < globalBestVec.size(); j++){
        cout << ", " << globalBestVec[j] + 1; 
    }
    cout << "], with an accuracy of " << endl;

    return globalBestVec;
}
int main(){
    vector<vector<double>> features;
    vector<int> classLabel;
    vector<double> temp;
    string fileName;
    int algo;
    cout << "Enter file name: " << endl;
    cin >> fileName;
    cout << "Select Algorithm" << endl;
    cout << "1. Forward" << endl;
    cout << "2. Backward" << endl;
    cin >> algo;
    readFile(fileName, classLabel, features);
    if(algo == 1){
        forwardSearch(features, classLabel, temp);
    }
    return 0;
}