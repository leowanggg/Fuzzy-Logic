#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include "regle.h"
#include "meta_regle.h"
#include "bull.h"
//Change the input bulletin file "bulletin.txt" or "bul.txt" or "bull2.txt"
#define BULLFILE "bulletin.txt" 
using namespace std;
//Function for reading the regles from the file "regles.txt", and save them in the vector.
void InitializeRegles(vector<Regle> &regles){
  string token;
  vector<string> data;
  RegleCondition condition;
  RegleResult result;
  string certitude;
  //Read context from the file "regles.txt"
  ifstream myfile ("regles.txt");
  if (myfile.is_open()){

    while ( getline (myfile,token,' ')){

       if((token != "") && (token != "Si") && (token != "et") && (token != "et\t") && (token != "Certitude")){
          token.erase (remove(token.begin(), token.end(), '\n'), token.end());
          //cout << token << endl;
          data.push_back(token);

       }
    }
    myfile.close();
  }
  else cout << "Unable to open file"; 
//Generate the vector of regles
  vector<string>::iterator it_data;
  for ( it_data = data.begin() ; it_data != data.end() ; it_data++ ){  
   Regle r;
   if(*it_data == "Regle"){
      it_data++;
      r.set_regle_name(*it_data);
      it_data++;

      while(*it_data != "Alors"){

        condition.subject = *it_data;
        it_data++;
        condition.mark = *it_data;
        it_data++;
        r.set_condition(condition);

      }

      it_data++;
      result.result_name = *it_data;
      it_data++;
      result.result_mark = *it_data;
      r.set_result(result);
      it_data++;
      certitude = *it_data;
      r.set_certitude(certitude);

      regles.push_back(r);
    }
    
  }
}
//Function for initializing the meta_regles(generate the vector of meta_regles)
void InitializeMetaRegles(vector<MetaRegle> &meta_regles){
  string token;
  vector<string> data;
  MetaCondition condition;
  string result;
  //Read context from the file "regles.txt"
  ifstream myfile ("meta-r.txt");
  if (myfile.is_open()){

    while ( getline (myfile,token,' ')){

       if((token != "") && (token != "Si") && (token != "ou")){
          token.erase (remove(token.begin(), token.end(), '\n'), token.end());
          //cout << token << endl;
          data.push_back(token);

       }
    }
    myfile.close();
  }
  else cout << "Unable to open file"; 
  //Generate the vector of meta_regles
  vector<string>::iterator it_data;
  for ( it_data = data.begin() ; it_data != data.end() ; it_data++ ){  
   MetaRegle r;
   if(*it_data == "Regle"){
      it_data++;
      r.set_regle_name(*it_data);
      it_data++;

      while(*it_data != "Evite"){

        condition.subject = *it_data;
        it_data++;
        condition.mark = *it_data;
        it_data++;
        r.set_condition(condition);
      }
      it_data++;
      result = *it_data;
      r.set_result(result);
      meta_regles.push_back(r);
    }
    
  }
}
//Function for initializing the bulletin(generate the vector of bulletin)
void InitializeBull(vector<Bull> &bulls){
  string token;
  vector<string> data;
  ifstream myfile (BULLFILE);
  if (myfile.is_open()){

    while ( getline (myfile,token,' ')){

       if((token != "")){
          token.erase (remove(token.begin(), token.end(), '\n'), token.end());
          //cout << token << endl;
          data.push_back(token);

       }
    }
    myfile.close();
  }
  else cout << "Unable to open file"; 
  //Generate the vector of bulletin.
  vector<string>::iterator it_data;
  for ( it_data = data.begin() ; it_data != data.end() ; it_data++){  
      Bull b;
      b.set_subject(*it_data);
      it_data++;
      b.set_mark(*it_data);
      it_data++;
      b.set_certitude(*it_data);
      bulls.push_back(b);
  }
}
//Define the flou.
vector<float> B = {0.001, 0.005, 0.005, 0.01, 0.1, 0.3, 0.4, 0.6, 0.8, 0.9, 1};
vector<float> P = {0, 0, 0.1, 0.4, 0.8, 1, 0.8, 0.4, 0.1, 0, 0};
vector<float> F = {1, 0.99, 0.99, 0.99, 0.9, 0.7, 0.6, 0.4, 0.2, 0.1, 0};
vector<float> TB = {0, 0, 0, 0, 0.01, 0.09, 0.16, 0.36, 0.64, 0.81, 1};
vector<float> AB = {0, 0.07, 0.07, 0.09, 0.31, 0.54, 0.63, 0.77, 0.89, 0.949, 1};
vector<float> TF = {1, 0.98, 0.98, 0.98, 0.81, 0.49, 0.36, 0.16, 0.04, 0.01, 0};
vector<float> AF = {1, 0.99, 0.99, 0.99, 0.949, 0.84, 0.77, 0.63, 0.45, 0.32, 0};
// For obtaining the notion flou
vector<float> GetFlou(const string &f){
  if(f == "B")
    return B;
  else if(f == "P")
    return P;
  else if(f == "F")
    return F;
  else if(f == "TB")
    return TB;
  else if(f == "AB")
    return AB;
  else if(f == "TF")
    return TF;
  else
    return AF;
}
//For obtaining the relation matrix between F1 and F2.
vector<vector<float>> GetMatrix(const string &_f1, const string &_f2){
  vector<vector<float>> f1_f2;
  vector<float> v;
  vector<float> f1 = GetFlou(_f1);
  vector<float> f2 = GetFlou(_f2);
  vector<float>::iterator it_f1;
  vector<float>::iterator it_f2;
  for (it_f1 = f1.begin(); it_f1 != f1.end(); ++it_f1){
    for (it_f2 = f2.begin(); it_f2 != f2.end(); ++it_f2){
      if((*it_f1) <= (*it_f2)){
        v.push_back(1.0);
      }
      else{
        v.push_back(*it_f2);
      }
    }
    f1_f2.push_back(v);
    v.clear();
  }
  return f1_f2;
}
//Calcul the Ecart between F1 and F2.
float CalEcart(const vector<float> &f1, const vector<float> &f2){
  vector<float>::const_iterator it_f1 = f1.begin();
  vector<float>::const_iterator it_f2 = f2.begin();
  float ecart;
  for (int i = 0; i < 11; ++i){
    ecart += ((*it_f1)-(*it_f2))*((*it_f1)-(*it_f2));
    ++it_f1;
    ++it_f2;
  }
  return ecart;
}
//Find the notion flou the most close 
string FindFlou(const vector<float> &f){
  string flou;
  vector<float> ens_ecart;
  vector<float>::iterator it_ens_ecart;
  ens_ecart.push_back(CalEcart(f, B));
  ens_ecart.push_back(CalEcart(f, P));
  ens_ecart.push_back(CalEcart(f, F));
  ens_ecart.push_back(CalEcart(f, TB));
  ens_ecart.push_back(CalEcart(f, AB));
  ens_ecart.push_back(CalEcart(f, TF));
  ens_ecart.push_back(CalEcart(f, AF));
  float min = *ens_ecart.begin();
  int i = 0;
  for (it_ens_ecart = ens_ecart.begin(); it_ens_ecart != ens_ecart.end(); ++it_ens_ecart)
  {
    if(min >= (*it_ens_ecart)){
      min = *it_ens_ecart;
    }
  }
  for (it_ens_ecart = ens_ecart.begin(); it_ens_ecart != ens_ecart.end(); ++it_ens_ecart){
    if(min == (*it_ens_ecart)){
      break;
    }
    ++i;
  }
  switch (i){
    case 0:{
      return "B";
      break;
    }
    case 1:{
      return "P";
      break;
    }
    case 2:{
      return "F";
      break;
    }
    case 3:{
      return "TB";
      break;
    }
    case 4:{
      return "AB";
      break;
    }
    case 5:{
      return "TF";
      break;
    }
    case 6:{
      return "AF";
      break;
    }
    default:
      cout <<"ERROR"<<endl;
  }

}
float Min(float a, float b){
  if(a <= b)
    return a;
  else
    return b;
}
vector<float> MinFlou(const float uf, const vector<float> &ur){
  vector<float> minf;
  vector<float>::const_iterator it_ur;
  for (it_ur = ur.begin(); it_ur != ur.end(); ++it_ur){
    minf.push_back(Min(uf, (*it_ur)));
  }
  return minf;
}
//Calcul the result of single premisse
string GetResult(const string f1, const string f2, const string _f){
  vector<vector<float>> matrix = GetMatrix(f1, f2);
  vector<vector<float>> result_matrix;
  vector<vector<float>>::iterator it_result_matrix;
  float max = 0.0;
  vector<float> max_vector;
  vector<vector<float>>::const_iterator it_matrix = matrix.begin();
  vector<float> f = GetFlou(_f);
  vector<float>::iterator it_f = f.begin();
  vector<float>::iterator it_v;
  for (int i = 0; i < 11; ++i){
    result_matrix.push_back(MinFlou(*it_f, *it_matrix));
    ++it_f;
    ++it_matrix;
  }
  for (int i = 0; i < 11; ++i){
    for (it_result_matrix = result_matrix.begin(); it_result_matrix != result_matrix.end(); ++it_result_matrix){
      it_v = (*it_result_matrix).begin() + i;
      if(max <= (*it_v))
        max = *it_v;
    }
    max_vector.push_back(max);
  }
  string rf = FindFlou(max_vector);
  return rf;

}
//The operation union
string Union(const string _f1, const string _f2){
  vector<float> f1 = GetFlou(_f1);
  vector<float> f2 = GetFlou(_f2);
  vector<float>::iterator it_f1 = f1.begin();
  vector<float>::iterator it_f2 = f2.begin();
  vector<float> f;
  float max;
  for (int i = 0; i < 11; ++i){
    if(*it_f1 <= *it_f2){
      max = *it_f2;
    }
    else{
      max = *it_f1;
    }
    f.push_back(max);
    ++it_f1;
    ++it_f2;
  }
  string ff = FindFlou(f);
  return ff;
}
//For obtaining the result of regle (single premisse or several premisse)
Note GetRegleResult(Regle &r, vector<Bull> &bulls){
  vector<RegleCondition> conditions;
  r.get_condition(conditions);
  vector<RegleCondition>::iterator it_conditions;
  vector<Bull>::iterator it_bulls;
  string subject;
  string mark;
  RegleResult result;
  string condition_result;
  vector<string> condition_results;
  vector<string>::iterator it_condition_results;
  RegleResult regle_result;
  string certitude;
  Note note;
  float note_certitude;
  r.get_certitude(certitude);
  r.get_result(regle_result);
  note_certitude = ::atof(certitude.c_str());
  for (it_conditions = conditions.begin(); it_conditions != conditions.end(); ++it_conditions){
    for (it_bulls = bulls.begin(); it_bulls != bulls.end(); ++it_bulls){
      (*it_bulls).get_subject(subject);
      if(it_conditions -> subject == subject){
        (*it_bulls).get_mark(mark);
        r.get_result(result);
        condition_result = GetResult(it_conditions -> mark, result.result_mark, mark);
        condition_results.push_back(condition_result);
        break;
      }
    }
  }
  regle_result.result_mark = *(condition_results.begin());
  for (it_condition_results = (condition_results.begin()+1); it_condition_results != condition_results.end(); ++it_condition_results){
    regle_result.result_mark = Union(regle_result.result_mark, *it_condition_results);
  }
  note.level_name = regle_result.result_name;
  note.mark = regle_result.result_mark;
  note.certitude = note_certitude;
  return note;


}
// the function pi
float PP(vector<float> f1, const string _f2){
  vector<float> f2 = GetFlou(_f2);
  vector<float>::iterator it_f1 = f1.begin();
  vector<float>::iterator it_f2 = f2.begin();
  float max = 0.0;
  vector<float> min;
  vector<float>::iterator it_min;
  for (int i = 0; i < 11; ++i){
    if(*it_f1 <= *it_f2){
      min.push_back(*it_f1);
    }
    else
      min.push_back(*it_f2);
    ++it_f1;
    ++it_f2;

  }
  for (it_min = min.begin(); it_min != min.end(); ++it_min){
    if(max <= *it_min){
      max = *it_min;
    }
  }
  return max;
}

vector<float> Inverse(const string _f){
  vector<float> f = GetFlou(_f);
  vector<float>::iterator it_f;
  vector<float> invf;
  for (it_f = f.begin(); it_f != f.end(); ++it_f){
    invf.push_back(1-(*it_f));
  }
  return invf;
}
//The function N
float N(const string f1, const string f2){
  return (1 - PP((Inverse(f1)), f2));
}
//The function S
float S(const string f1, const string f2){
  if(N(f1, f2) < 0.5)
  return ((N(f1, f2) + 0.5) * PP(GetFlou(f1), f2));
  if(N(f1, f2) > 0.5)
  return PP(GetFlou(f1), f2);
}

float CalCertitude(const float fn_regle, const float fn_a, const string f1, const string f2){
  return (fn_a * fn_regle * S(f1, f2));
}
//For obtaining the choice for students from through the regles and bulletin.
void GetChoice(vector<Choice> &choices, vector<Regle> &regles, vector<Note> &notes){
  Choice choice;
  vector<Regle>::iterator it_regles;
  vector<Note>::iterator it_notes;
  RegleResult regle_result;
  vector<RegleCondition> conditions;
  string _regle_certitude;
  float regle_certitude;
  string mark;
  for(it_notes = notes.begin(); it_notes != notes.end(); ++it_notes){
    for (it_regles = regles.begin(); it_regles != regles.end(); ++it_regles){
      (*it_regles).get_result(regle_result);
      mark = regle_result.result_mark;
      if(mark == "*"){
        (*it_regles).get_condition(conditions);
        if((*(conditions.begin())).subject == (*it_notes).level_name){
        (*it_regles).get_certitude(_regle_certitude);
        regle_certitude = ::atof(_regle_certitude.c_str());
        choice.subject_name = regle_result.result_name;
        choice.certitude = CalCertitude(regle_certitude, (*it_notes).certitude, (*(conditions.begin())).mark, (*it_notes).mark);
        choices.push_back(choice);
        }
      }
    }
  }
}


//function for initializing the regles(generate the vector of the regles)




//function for match the bulletin with the meta_regles, remove the choices which are not neccessary
void MatchMetaRegles(vector<MetaRegle> &meta_regles, vector<Choice> &choices, vector<Bull> &bulls){
  vector<MetaRegle>::iterator it_meta_regle;
  vector<MetaCondition> conditions;
  vector<MetaCondition>::iterator it_condition;
  vector<Bull>::iterator it_bull;
  vector<Choice>::iterator it_choice;
  string subject;
  string mark;
  string result;
  int matchpoint = 0;
  for (it_meta_regle = meta_regles.begin() ; it_meta_regle != meta_regles.end() ; it_meta_regle++){
    (*it_meta_regle).get_condition(conditions);
    for (it_condition = conditions.begin(); it_condition != conditions.end(); it_condition++){
      for(it_bull = bulls.begin(); it_bull != bulls.end(); it_bull++){
        (*it_bull).get_subject(subject);
        (*it_bull).get_mark(mark);
        if((((*it_condition).subject) == subject)&&(Compare(mark, (*it_condition).mark))){
          matchpoint++;
        }
      }
    }
    if(matchpoint != 0){
      it_meta_regle -> get_result(result);
      for (it_choice = choices.begin() ; it_choice != choices.end() ; it_choice++){
        if(((*it_choice).subject_name) == result)
          choices.erase(it_choice);
      }

    }
    matchpoint = 0;
  }
}
void EreseDups(vector<Note> &notes){
  vector<Note>::iterator it_notes_1;
  vector<Note>::iterator it_notes_2;
    for (it_notes_1 = notes.begin() ; it_notes_1 != notes.end() ; it_notes_1++){
    for (it_notes_2 = (it_notes_1 + 1) ; it_notes_2 != notes.end() ; it_notes_2++){
      if(((*it_notes_1).level_name) == ((*it_notes_2).level_name)){
        if(((*it_notes_1).certitude) >= ((*it_notes_2).certitude)){
          notes.erase(it_notes_2);
          it_notes_2--;
        }
        else{
          notes.erase(it_notes_1);
          it_notes_1--;
        }
      }
    }
  }
}
void EreseMinCertitude(vector<Choice> &choices){
  vector<Choice>::iterator it_choices_1;
  vector<Choice>::iterator it_choices_2;
  for (it_choices_1 = choices.begin() ; it_choices_1 != choices.end() ; ++it_choices_1){
    for (it_choices_2 = (it_choices_1 + 1) ; it_choices_2 != choices.end() ; ++it_choices_2){
      if((*it_choices_1).subject_name == (*it_choices_2).subject_name){
        if((*it_choices_1).certitude >= (*it_choices_2).certitude){
          choices.erase(it_choices_2);
          it_choices_2--;
        }
        else{
          choices.erase(it_choices_1);
          it_choices_1--;
        }
      }
    }
  }
}
int main(int argc, char const *argv[]){
  
  //The regles in the file"regles.txt" are saved in the vector regles
  vector<Regle> regles;
  vector<Regle>::iterator it_regles;
  //The meta-regles in the file"meta-regles.txt" are saved in the vector regles
  vector<MetaRegle> meta_regles;
  //The bulletin in the file "bulletin.txt" are saved in the vector regles
  vector<Bull> bulls;
  vector<Note> notes;
  vector<Choice> choices;
  vector<Choice>::iterator it_choices;
  Note note;
  string mark;
  RegleResult regle_result;
  InitializeRegles(regles);
  InitializeMetaRegles(meta_regles);
  InitializeBull(bulls);
  //For obtaining the advices for the students from their bulletin.
  for (it_regles = regles.begin(); it_regles != regles.end(); ++it_regles){
    (*it_regles).get_result(regle_result);
    mark = regle_result.result_mark;
    if(mark != "*"){
      note = GetRegleResult(*it_regles, bulls);
      notes.push_back(note);
    }
  }
  EreseDups(notes);
  GetChoice(choices, regles, notes);
  EreseMinCertitude(choices);
  MatchMetaRegles(meta_regles, choices, bulls);
  cout << "Choix" << "     " << "Certitude" << endl;
  for (it_choices = choices.begin(); it_choices != choices.end(); ++it_choices){
    cout << *it_choices;
  }
  //Pour prerenter
  //Simple exemple: F1 = TB, F2 = B (regle with one premisse)
  cout << endl;
  cout << endl;
  cout << "presenter les fonctions" << endl
       << "F1 = TB, F2 = B, la matrice est:" << endl;
  vector<vector<float>> matrice = GetMatrix("TB", "B");
  vector<vector<float>>::iterator it_matrice;
  vector<float>::iterator it_ligne;
  for (it_matrice = matrice.begin(); it_matrice != matrice.end(); ++it_matrice){
    for (it_ligne = (*it_matrice).begin(); it_ligne != (*it_matrice).end(); ++it_ligne){
      cout << *it_ligne << "  ";
    }
    cout << endl;
  }
  cout << endl;
  string conclusion = GetResult("TB", "B", "B");
  cout << "la conclusion est:" << endl
      << conclusion << endl;
  cout << endl;
  cout << endl;
  float s = S("B", "AB");
  float FNB = CalCertitude(0.8, 0.9, "B", "AB");
  cout << "FNregle = 0.8, FNA = 0.9, F1 = B, F2 = AB" << endl
        << "S(F1, F2) = " << s << endl << "FNB = FNA * FNregle * S(F1,F2) = " << FNB << endl << endl;
  //regle with several premisses
  int r;
  do{
  cout << "Enter the regle floue number, for example: 9, and enter 0 for esc" << endl;
  cout << "The regle floue in the regles.txt are:" << endl;
  for (it_regles = regles.begin(); it_regles != regles.end(); ++it_regles){
    it_regles -> get_result(regle_result);
    if(regle_result.result_mark != "*")
      cout << (it_regles -> get_regle_name()) << " ";
  }
  cout << endl;
  cin >> r;
  cout << "The number you enter is " << r << "." << endl;
  cout << regles[r-1] << endl;
  note = GetRegleResult(regles[r-1], bulls);
  cout << "The result of Regle" << r <<" is:" << endl 
       << note << endl;
  }while(r != 0);

  return 0;
}
