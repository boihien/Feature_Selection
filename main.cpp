#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;
//test files Huang	Boi-Hien	small:40	large:33
//class. features
//CS170_largetestdata__33.txt
//CS170_SMALLtestdata__40.txt
vector<int> forwardSearch(vector<vector<double>>& features, vector<int>& classLabel, vector<double>& accuracyVec);
vector<int> backwardSearch(vector<vector<double>>& features, vector<int>& classLabel, vector<double>& accuracyVec);
void leaveOneOutCross();
void readFile();
double crossValidation(vector<int>& classLabel, vector<vector<double>>& features);
void removeFeatures(vector<int>& temp, vector<vector<double>>& emptyFeatures);

//first colum is class label
//11 columms
//rest is feature
//https://www.cplusplus.com/doc/tutorial/files/
void readFile(string fileName, vector<int>& classLabel, vector<vector<double>>& features){
    ifstream inFile;
    inFile.open(fileName);
    double data;
    int line = 0;
    int count = 2; //first one is feature and already pushed one
    if(fileName == "CS170_SMALLtestdata__40.txt" || fileName == "test1row.txt" || "CS170_small_special_testdata__95.txt"){
        if(!inFile.is_open()){
            cout << "Could not open file" << endl;
            return;
        }
        else{
            inFile >> data;
            classLabel.push_back((int) data);
            features.push_back(vector<double>());
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
  //number_correctly_classified = 0;
  double numberCorrect = 0;
  int nearest = 0;
  int skip = 0; //incorrect neighbor
  double dist = 0.0;
  while(skip < 200){
      nearest = 0;
      double currentMin = numeric_limits<double>::infinity();//positive infinity
      for(int i = 0; i < features.size(); i++){
          dist = 0.0;
          if(i != skip){//skip incorrect neighbor
            for(int k = 0; k < features[0].size(); k++){
                dist += (features[skip][k] - features[i][k]) * (features[skip][k] - features[i][k]);
            }

            dist = sqrt(dist);
            if(dist < currentMin){
                currentMin = dist;
                nearest = i;
            }
          }
      }
      /*if(label_object_to_classify == nearest_neighbor_label){
            number_correctly_classified = number_correctly_clasified + 1;
        }*/
      if(classLabel[skip] == classLabel[nearest]){
          numberCorrect++;
      }
      skip++;
  }
  return numberCorrect/200;
    /*for (int i = 1; i < data.size(); i++){
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
    accuracy = number_correctly_classified / size(data, i);*/
}

vector<int> backwardSearch(vector<vector<double>>& features, vector<int>& classLabel, vector<double>& accuracyVec){
    double currentBest = 0.0;
    double globalBest = 0.0;
    vector<int> currentSetFeatures;//initialize empty set 
    vector<int> globalBestVec;

    for(int i = 0; i < features[0].size(); i++){
        currentSetFeatures.push_back(i);
    }

    for(int i = 0; i < currentSetFeatures.size(); i++){
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int featureToAddLevel;
        double bestSoFar = 0.0;
        double accuracy = 0.0;
        for(int k = 0; k < currentSetFeatures.size(); k++){
            currentSetFeatures.erase(currentSetFeatures.begin() + k);//remove current feature sets starting from beginning
            if(currentSetFeatures.size() >= 1){ //if not empty, consider adding if not empty
                cout << "--Considering adding the " << currentSetFeatures[0] + 1 << " feature" << endl;
                for(int i = 1; i < currentSetFeatures.size(); i++){
                    cout << "--Considering adding the " << currentSetFeatures[i] + 1 << " feature" << endl; //add one since need to index from 1
                }
                vector<vector<double>> empty = features;
                vector<int> temp = currentSetFeatures;
                removeFeatures(temp, empty);//remove features by replacing with 0
                accuracy = crossValidation(classLabel, empty);//use crossvalidation function stub
                
                accuracyVec.push_back(accuracy);//keep track of accuracy
            }
            if(accuracy > bestSoFar){
                bestSoFar = accuracy;
                featureToAddLevel = k;
            }
            currentSetFeatures.insert(currentSetFeatures.begin() + k, k); //add current feature set to vector from beginning to k
        }
        if(currentBest < bestSoFar){//checking for best overall accuracy 
            currentBest = bestSoFar;
            if(globalBest < currentBest){
                globalBest = currentBest;
                globalBestVec = currentSetFeatures;
                globalBestVec.erase(globalBestVec.begin() + featureToAddLevel);//keep track of best overall feature to add at this level
            }
        }
        currentSetFeatures.erase(currentSetFeatures.begin() + featureToAddLevel);
        //currentSetoffeatures(i) = feature to add at this level
        //cout << currentSetFeatures[0] + 1;
        cout << "On level " << i + 1 << " i added feature " << currentSetFeatures.back() << " to current set" << endl;
        cout << "with accuracy " << bestSoFar * 100 << "%" << endl;
            
        
    }
    cout << "Reached here. Best feature subset: ";
    cout << globalBestVec[0] + 1;
    for(int a = 1; a < globalBestVec.size(); a++){
        cout << ", " << globalBestVec[a] + 1; 
    }
    cout << " accuracy: " << globalBest * 100 << "%" << endl;

    return globalBestVec;
}

vector<int> forwardSearch(vector<vector<double>>& features, vector<int>& classLabel, vector<double>& accuracyVec){
    double currentBest = 0.0;
    double globalBest = 0.0;
    vector<int> currentSetFeatures;//initialize empty set 
    vector<int> globalBestVec;
    for(int i = 0; i < features[0].size(); i++){
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int featureToAddLevel;
        double bestSoFar = 0.0;
        double accuracy = 0.0;
        for(int k = 0; k < features[i].size(); k++){
            if(find(currentSetFeatures.begin(), currentSetFeatures.end(), k) == currentSetFeatures.end()){ //if isempty(intersect(current_set_of_features,k)) %only consider adding, if not already added
                vector<vector<double>> emptyFeatures = features;
                vector<int> temp = currentSetFeatures;
                temp.push_back(k);
                cout << "--Considering adding the " << temp[0] + 1 << " feature" << endl;
                for(int i = 1; i < temp.size(); i++){
                    cout << "--Considering adding the " << temp[i] + 1 << " feature" << endl; //add one since need to index from 1
                }
                removeFeatures(temp, emptyFeatures);
                accuracy = crossValidation(classLabel, emptyFeatures);//use crossvalidation function stub
                
                accuracyVec.push_back(accuracy);//keep track of accuracy
            }
            if(accuracy > bestSoFar){
                bestSoFar = accuracy;
                featureToAddLevel = k;
                //cout << accuracy << endl;
                //cout << bestSoFar <<endl;
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
                cout << "On level " << i + 1 << " i added feature " << currentSetFeatures.back() << " to current set" << endl;
                cout << "with accuracy " << bestSoFar * 100 << "%" << endl;
            }
        }
    }
    cout << "Reached Here. Best feature subset: ";
    cout << globalBestVec[0] + 1;
    for(int a = 1; a < globalBestVec.size(); a++){
        cout << ", " << globalBestVec[a] + 1; 
    }
    cout << " accuracy: " << globalBest* 100 << "%" << endl;

    return globalBestVec;
}

void removeFeatures(vector<int>& temp, vector<vector<double>>& emptyFeatures){
    for(int i = 0; i < emptyFeatures.size(); i++){
        for(int j = 0; j < emptyFeatures[0].size(); j++){
            if(find(temp.begin(), temp.end(), j) == temp.end()){//if feature already added
                emptyFeatures[i][j] = 0.0;
            }
        }
    }
}

int main(){
    vector<vector<double>> features;
    vector<int> classLabel;
    vector<double> accuracy;
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
        vector<int>bestFeatures = forwardSearch(features, classLabel, accuracy);
    }
    if(algo == 2){
        vector<int>bestFeatures = backwardSearch(features, classLabel, accuracy);
    }
    return 0;
}