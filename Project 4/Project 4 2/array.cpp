//
//  main.cpp
//  Project 4
//
//  Created by Brian Wong on 5/1/15.
//  Copyright (c) 2015 Brian Wong. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <cassert>
using namespace std;

int enumerate(const string a[], int n, string target);
int locate(const string a[], int n, string target);
bool locateSequence(const string a[], int n, string target, int&begin, int&end);
int locationOfMin(const string a[], int n);
int moveToEnd(string a[], int n, int pos);
void showStrings(const string x[], int n);
int moveToBeginning(string a[], int n, int pos);
int locateDifference(const string a1[], int n1, const string a2[], int n2);
int eliminateDups(string a[], int n);
bool subsequence(const string a1[], int n1, const string a2[], int n2);
int makeMerger (const string a1[], int n1, const string a2[], int n2, string result[], int max);
int divide(string a[], int n, string divider);



int main(){

}



int enumerate(const string a[], int n, string target){
    if(n<0){
        return -1;
    }
    int stringCount = 0;
    for (int i=0; i<n; i++){
        if(a[i] == target){
            stringCount++;
        }
    }
    return stringCount;
}

int locate(const string a[], int n, string target){
    for (int i=0; i<n; i++){
        if(a[i] == target){
            return i;
        }
    }
    return -1;
}

bool locateSequence(const string a[], int n, string target, int&begin, int&end){
    if(n<0){
        return false;
    }
    for(int i=0; i < n; i++){
        if(a[i] == target){
            begin = i;
            end = i;
            for(int k=(begin+1); k < n; k++){
                if(a[k] == target){
                    end = k;
                    return true;
                }
            }
        }
    }
    if(begin == end){
        return true;
    }else{
        return false;
    }
}

int locationOfMin(const string a[], int n){
    int smallestPosition = 0;
    string smallest = a[0];
    if(n<=0){
        return -1;
    }
    for (int i=0; i<n; i++){
        if(smallest > a[i]){
            smallest = a[i];
            smallestPosition = i;
            
        }
        
    }
    return smallestPosition;
}

int moveToEnd(string a[], int n, int pos){
    if (n <= 0 || pos < 0 || pos >= n) {
        return -1;
    }
    string endMove = a[pos];
    for(int i=pos; i<n-1; i++) {
        a[i]=a[i+1];
        }
    a[n-1] = endMove;
    return pos;
}


void showStrings(const string s[], int n) {
        cout << "string[" << n << "] = [";
    for (int i = 0; i < n; i++) {
        cout << s[i] << ",";
        }
    cout << "]"<< endl;
}

int moveToBeginning(string a[], int n, int pos){
    if (n <= 0 || pos < 0 || pos >= n) {
        return -1;
    }
    string first = a[pos];
    for (int i=pos; i>0; i--) {
        a[i]=a[i-1];
    }
    a[0] = first;
    return pos;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    int i = 0;
    while (true) {
        if (i == n1) {
            return n1;
        } else if (i == n2) {
            return n2;
        }
        if (a1[i] != a2[i]) {
            return i;
        }
        i++;
    }
}



int eliminateDups(string a[], int n){
    if(n == 0 || n == 1){
        return n;
    }
    for (int i=0; i<n-1; i++){
        if(a[i] == a[i+1]) {
            moveToEnd(a, n, i+1);
            n = n-1;
            i--; //Stays in current position until all dups are gone
        }
    }
    return n;
}

bool subsequence(const string a1[], int n1, const string a2[], int n2){
    if(n2 == 1){
        return true;
    }
    int subInt = 0;
    for(int i=0; i<n1; i++){
        if(a1[i] == a2[subInt]){
            subInt++;
            if(subInt == n2){
                return true;
            }
        }
    }
    return false;
}



int makeMerger (const string a1[], int n1, const string a2[], int n2, string result[], int max){
    int resultsize = n1+n2;
    
    if (max < resultsize) {
        return -1;
    }
    
    for(int i=0; i<n1-1; i++){
        if(a1[i] > a1[i+1]){
            return -1;
        }
    }
    
    for (int k = 0; k<n2-1; k++) {
        if(a2[k] > a2[k+1]){
            return -1;
        }
    }
    
    for (int a=0; a<n1; a++) {
        result[a] = a1[a];
    }
    for (int b=n1, c=0; b<resultsize; b++, c++){
        result[b] = a2[c];
    }
    
    string temp;
    for(int q = 0; q < resultsize; q++){
        for(int p = q+1; p < resultsize; p++){
            if(result[p] < result[q]){
                temp = result[q];
                result[q] = result[p];
                result[p] = temp;
            }
        }
    }
    return n1+n2;
}

int divide(string a[], int n, string divider){
    if (n < 0) {
        return -1;
    }
    
    if (n == 0) {
        return 0;
    }
    //Sorts the array
    string temp;
    int start = 0;
    int end = n - 1;
    while (start < end) {
        if (a[start] < divider) {
            start++;
        }
        if (a[end] > divider) {
            end--;
        }
        if (start < end) {
            temp = a[start];
            a[start] = a[end];
            a[end] = temp;
        }
    }
    
    //Loops after array is sorted to find first element >= divider
    for (int i = 0; i < n; i++) {
        if (a[i] >= divider) {
            return i;
        }
    }
    return n;
}


