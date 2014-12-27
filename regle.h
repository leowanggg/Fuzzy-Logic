#ifndef _REGLE_H_
#define _REGLE_H_
#endif
//condition in the regle
struct RegleCondition{

	std::string subject;
	std::string mark; 
			
};
//the result of each regle
struct RegleResult{

	std::string result_name;
	std::string result_mark;

};
// the class for regles
class Regle{

	private: 
		
		std::string regle_name;
		//the vector which contains conditions of regle
		std::vector<RegleCondition> conditions;
		RegleResult result;
		std::string certitude;
	
	public:
		Regle(){};
	    ~Regle(){};
		void set_regle_name(const std::string _regle_name){regle_name = _regle_name;}
		void set_condition(const RegleCondition condition){conditions.push_back(condition);}
		void set_result(const RegleResult _result){result = _result;}
		void set_certitude(const std::string _certitude){certitude = _certitude;}
		void get_condition(std::vector<RegleCondition> &_conditions){_conditions = conditions;}
		std::string get_regle_name(){return regle_name;}
		void get_result(RegleResult &_result){_result = result;}
		void get_certitude(std::string &_certitude){_certitude = certitude;}
};
		std::ostream &operator<<(std::ostream &os, Regle& regle){
		std::string _regle_name = regle.get_regle_name();
		std::vector<RegleCondition> _conditions;
		RegleResult _result;
		std::string _certitude;
		regle.get_condition(_conditions);
		regle.get_result(_result);
		regle.get_certitude(_certitude);
  		os << "Regle " << _regle_name << std::endl;
  		for (std::vector<RegleCondition>::iterator it_conditions = _conditions.begin(); it_conditions != _conditions.end(); ++it_conditions){
  			if(it_conditions == _conditions.begin())
  				os << "  Si        ";
  			else
  				os << "    et      ";
  			os << (it_conditions -> subject) << "  " << (it_conditions -> mark) << std::endl;
  		}
  		os << "  Alors     " << _result.result_name << "    " << _result.result_mark << std::endl
  		   << "  certitude " << _certitude << std::endl;
  		return os;
  		}
