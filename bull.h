#ifndef _BULL_H_
#define _BULL_H_
#endif
class Bull{

	private: 
		
		std::string subject;
		std::string mark; 
		std::string certitude;
	
	public:
		Bull(){};
	    ~Bull(){};
		void set_subject(const std::string _subject){subject = _subject;}
		void set_mark(const std::string _mark){mark = _mark;}
		void set_certitude(const std::string _certitude){certitude = _certitude;}
		void get_subject(std::string &_subject){_subject = subject;}
		void get_mark(std::string &_mark){_mark = mark;}

};
//note the result of the first matching
struct Note 
{
	std::string level_name;
	std::string mark;
	float certitude;
};
std::ostream &operator<<(std::ostream &os, const Note &note){
  os << note.level_name << "  " << note.mark << std::endl;
  return os;
}
struct Choice
{
  std::string subject_name;
  float certitude;
};
std::ostream &operator<<(std::ostream &os, const Choice &choice){
  os << choice.subject_name << "  " << choice.certitude << std::endl;
  return os;
}
//function for comparing the mark(AF < F < B < AB < TB)
bool Compare(const std::string &a, const std::string &b){
  bool result;
  if((a == "TF")&&((b == "TF")||(b == "F")||(b == "AF")||(b =="P")||(b == "AB")||(b == "B")||(b == "TB"))){
    result = true;
  }
  else if((a == "F")&&((b == "F")||(b == "AF")||(b =="P")||(b == "AB")||(b == "B")||(b == "TB"))){
    result = true;
  }
  else if((a == "AF")&&((b == "AF")||(b =="P")||(b == "AB")||(b == "B")||(b == "TB"))){
    result = true;
  }
  else if((a == "P")&&((b =="P")||(b == "AB")||(b == "B")||(b == "TB"))){
    result = true;
  }
  else if((a == "AB")&&((b == "AB")||(b == "B")||(b == "TB"))){
    result = true;
  }
  else if((a == "B")&&((b == "B")||(b == "TB"))){
    result = true;
  }
  else if((a == "TB")&&(b == "TB")){
    result = true;
  }
  else{
    result = false;
  } 
  return result;
}